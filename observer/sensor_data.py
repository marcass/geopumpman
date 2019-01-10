# Starts API for listening to incoming data (port 5004) and writes to influx volume via inflxdb container

# Sensor data Writes ###################################################################
from influxdb import InfluxDBClient
from datetime import timedelta
import datetime
import time
import re
import json

measurement = []

db_name = 'sensors'
# setup db
client = InfluxDBClient(host='localhost', port=8087)
# setup db if it ins't already:
def setup_db():
    print ('checking for db')
    flag = False
    dbs = client.get_list_database()
    print (dbs)
    for i in client.get_list_database():
        if db_name in i['name']:
            flag = True
        else:
            print ('doing nothing')
    if not flag:
        print ('making db')
        client.create_database(db_name)

# setup db and use currnet db
setup_db()
client.switch_database(db_name)
# client.drop_database(db_name)

# setup reteniton plicy list must match index of durations
retention_policies = ['24_hours', '7_days','2_months', '1_year', 'forever']
# setup retention policy detail
durations = {'24_hours': {'dur':'1d', 'default':True},
             '7_days': {'dur':'7d', 'default':False},
             '2_months': {'dur':'4w', 'default':False},
             '1_year': {'dur':'52w','default':False},
             'forever': {'dur':'INF','default':False}}
# orgainse graphing periods
periods = {'hours': ['24_hours'], 'days': ['7_days', '2_months'], 'months': ['1_year'], 'years': ['forever']}
def setup_RP(vtype, meas):
    global retention_policies
    global measurement
    RP_list = []
    # try:
    RP = client.get_list_retention_policies(db_name)
    for i in RP:
        # produce list of existing retention policies
        RP_list.append(i['name'])
    # print RP_list
    # except:
    #     print 'No retention polices here'
    for i in retention_policies:
        if i in RP_list:
            print ('RP already here')
        else:
            print ('making rp for '+i)
            client.create_retention_policy(i, durations[i]['dur'], 1, database='sensors', default=durations[i]['default'])
    # https://influxdb-python.readthedocs.io/en/latest/api-documentation.html
    # https://docs.influxdata.com/influxdb/v1.6/guides/downsampling_and_retention/
    try:
        client.query('CREATE CONTINUOUS QUERY \"%s\" ON %s BEGIN SELECT mean(%s) AS \"%s\" INTO "7_days".\"%s\" FROM "24_hours".\"%s\" GROUP BY time(2m), * END' %(vtype+'_cq_7_days', db_name,  vtype, vtype, meas, meas))
        client.query('CREATE CONTINUOUS QUERY \"%s\" ON %s BEGIN SELECT mean(%s) AS \"%s\" INTO "2_months".\"%s\" FROM "24_hours".\"%s\" GROUP BY time(5m), * END' %(vtype+'_cq_2_months', db_name,  vtype, vtype, meas, meas))
        client.query('CREATE CONTINUOUS QUERY \"%s\" ON %s BEGIN SELECT mean(%s) AS \"%s\" INTO "1_year".\"%s\" FROM "24_hours".\"%s\" GROUP BY time(10m), * END' %(vtype+'_cq_1_year', db_name,  vtype, vtype, meas, meas))
        client.query('CREATE CONTINUOUS QUERY \"%s\" ON %s BEGIN SELECT mean(%s) AS \"%s\" INTO "forever".\"%s\" FROM "24_hours".\"%s\" GROUP BY time(20m), * END' %(vtype+'_cq_forever', db_name,  vtype, vtype, meas, meas))
        print ('making cqs for '+vtype)
    except:
        # already exist
        print ("Failed to create CQs, as they already exist")

# sanitise strings to reduce sql-injection issues
def clean(data):
    if isinstance(data, str) or isinstance(data, unicode):
        return re.sub('[^A-Za-z0-9\-_]+', '', data)
    if isinstance(data, dict):
        data = json.dumps(data)
        data = re.sub('[^A-Za-z0-9\-_{}:\',+\."\[\]]+', '', data)
        return json.loads(data)

def clean_debug(data):
    print ('data in = '+str(data))
    print 'type of data is '+str(type(data))
    if isinstance(data, str) or isinstance(data, unicode):
        print ('dirty string = '+data)
        data = re.sub('[^A-Za-z0-9\-_]+', '', data)
        print ('cleaned string = '+data)
        return re.sub('[^A-Za-z0-9\-_]+', '', data)
    if isinstance(data, dict):
        print ('dirty dict = '+str(data))
        data = json.dumps(data)
        print ('dirty dict as a string = '+data)
        data = re.sub('[^A-Za-z0-9\-_{}:\',+\."\[\]]+', '', data)
        print ('cleaned dict string = '+data)
        return json.loads(data)



def write_data(data):
    data = clean(data)
    # incoming format should be:
    # data = {'measurement': 'tablename', 'tags':{'type':'meastype', 'sensorID':'sensor name', 'site': 'thissite'}, 'value':value}
    # print data
    # ensure RP's and CQ's in place for new sites
    if 'measurement' in data:
        measurement = data['measurement']
    else:
        measurement = 'things'
    if 'tags' in data:
        in_type = data['tags']['type']
    if 'type' in data:
        in_type = data['type']
    if in_type not in get_data_types(measurement):
        try:
            setup_RP(in_type, measurement)
        except:
            print ('RP in place for '+data['type']+' '+measurement)
    val = data['value']
    # influx is dropping values if the arrive as truncated floates (eg 16.00 is sent as an int of 16 by arduinoJSON
    # and influx drops point as it won't stuff an int into a float column)
    if (in_type == 'temp') or (in_type == 'humidity'):
        val = float(data['value'])
        if val < -100.0:
            return {'Status': 'Error', 'Message': 'Value of '+str(val)+' out of range'}
    # tank data
    if 'measurement' in data:
        json_data = [
            {
                'measurement': data['measurement'],
                'tags': data['tags'],
                'fields': {
                    in_type: val
                },
                'time': datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%fZ")
                }
            ]
    try:
        client.write_points(json_data)
        return {'Status': 'success', 'Message': 'successfully wrote data points'}
    except:
        return {'Status': 'failed', 'Message': 'exception'}

def get_data_types(meas=0):
    # returnrs a list [light, etc]
    if meas == 0:
        results = client.query('SHOW FIELD KEYS ON "sensors"')
    else:
        meas = clean(meas)
        results = client.query('SHOW FIELD KEYS ON "sensors" FROM \"%s\"' %(meas))
    types = results.get_points()
    types_list = []
    for i in types:
        if i not in types_list:
            types_list.append(i['fieldKey'])
    return types_list

# Api for managing requests #####################################################

from flask import Flask, jsonify, request
from flask_cors import CORS, cross_origin
import json
from init import app, jwt

# Sensor data routes
@app.route("/data", methods=['POST',])
def update_data():
    '''
    Writes data to influx from remote sensors
    '''
    content = request.get_json(silent=False)
    # print content
    return jsonify(write_data(content)), 200

app = Flask(__name__)
CORS(app)

if __name__ == "__main__":
    app.run()

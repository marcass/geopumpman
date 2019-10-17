import serial
import csv
from datetime import datetime

def readlineCR(port):
    global boiler_data
    rv = ""
    while True:
        ch = port.read()
        # print(ch)
#        rv += ch
#       for python3 need to cast to str
        # rv += str(ch, 'UTF-8')
        try:
            s = ch.decode("UTF-8")
            rv += s
            # print(rv)
        except:
            pass
        if ch==b'\r':# or ch=='':
            print(rv)
            if 'DATA' in rv:
                received = rv[6:]
                print(received)
                data = received.split('/')
                exchanger = data[0]
                position = data[1]
                top = data[2]
                bottom = data[3]
                f_name = str(exchanger) + '_' + position + '.csv'
                # current date and time
                now = datetime.now()
                timestamp = datetime.timestamp(now)
                print(data)
                print(exchanger)
                print(position)
                print(top)
                print(bottom)
                print(f_name)
                # print ('exhanger = '+exchanger+'; temps are: '+str(top)+' '+str(bottom)+'; timestamp = '+timestamp)
                # https://docs.python.org/3/library/csv.html
                with open(f_name, 'w+', newline='') as csvfile:
                    fieldnames = ['timestamp', 'top_temp', 'bottom_temp']
                    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
                    writer.writeheader()
                    writer.writerow({'timestamp': timestamp, 'top_temp': top, 'bottom_temp': bottom})
            return rv

port = serial.Serial("/dev/ttyUSB0", baudrate=9600, timeout=3.0)
#port = serial.Serial("/dev/ttyUSB0", baudrate=9600, timeout=3.0)

if __name__ == "__main__":
    while True:
        #for debugging enable printing of serial port data
        rcv = readlineCR(port)
        #print rcv

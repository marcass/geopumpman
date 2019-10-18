import csv
# import matplotlib

file = "2_end.csv"

with open('2_end.csv', newline='') as csvfile:
    data = csv.reader(csvfile, delimiter=' ', quotechar='|')
    # res = {"date":[], "time":[], "top_temp":[], "bottom_temp":[]}
    # for row in data:
    #     if 'timestamp' in row:
    #         print('Skipping header')
    #     else:
    #         res["date"].append(row[0])
    #         res["time"].append(row[2])
    #         res["top_temp"].append(row[3])
    #         res["bottom_temp"].append(row[4])
    # print(', '.join(row))
    # print(res)
    print(data[0])

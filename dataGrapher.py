import json
from datetime import datetime
import matplotlib
import matplotlib.pyplot as plt
import numpy as np    
import matplotlib.lines as mlines
from os import listdir
import time
from os.path import isfile, join
import CMethods
print("Starting!")
mypath = "./tickerData/BTC-LTC"
myoutputpath = "./CMData/BTC-LTC"
onlyfiles = [f for f in sorted(listdir(mypath)) if isfile(join(mypath, f))]
counter = 0
for i in onlyfiles:
    CMethods.findAddressChanges((mypath + "/" + i).encode(), (myoutputpath + "/" + i).encode())
    print("Compiling data: " + str((counter / len(onlyfiles)) * 100))
    counter += 1

counter = 0
#Plotting the candles
candles = {}

with open("./BTC-XMRcandles.json") as json_file:
    candles = json.load(json_file)
    json_file.close()

def splitXandY(points, xLabel, yLabel):
    xArray = []
    yArray = []
    for i in points:
        xArray.append(i[xLabel])
        yArray.append(i[yLabel])
    return {'x':xArray, 'y': yArray}

#for i in coordinateData:

for i in candles["result"]:
    unixtime = time.mktime(time.strptime(i['T'], '%Y-%m-%dT%H:%M:%S'))
    #unixtime = datetime.strptime(i['T'], '%Y-%m-%dT%H:%M:%S')
    #unixtime = int(unixtime.strftime("%s")) / 800000
    #unixtime = datetime.strptime(i['T'], '%Y-%m-%dT%H:%M:%S')
    
    i['TM'] = float(unixtime)
    i['C'] = float(i['C'])
    print("Plotting candles: " + str((counter / len(candles["result"])) * 100))
    counter += 1

coordinateData = splitXandY(candles['result'], 'TM', 'C')
plt.plot(coordinateData['x'], coordinateData['y'])

counter = 0
outfiles = [f for f in sorted(listdir(myoutputpath)) if isfile(join(myoutputpath, f))]
for i in outfiles:
    if(counter % 1000 == 0):
        print(myoutputpath + "/" + i)
        json_file = None
        with open(myoutputpath + "/" + i) as json_file:
            print(json_file)
            data2 = json.load(json_file)
            print(float(data2['book']['timestamp']))
            for b in data2['book']['data']['SELL']:
                
                plt.scatter(float(data2['book']['timestamp']), b["P"], c="red")
            for b in data2['book']['data']['BUY']:
               
                plt.scatter(float(data2['book']['timestamp']), b["P"], c="green")
            json_file.close()
    
    #print("Plotting points: " + str((counter / len(outfiles)) * 100))
    counter += 1
            

plt.xlabel('Date')
plt.ylabel('Price')
plt.show()
"""for i in onlyfiles:
    counter2 += 1
    with open(mypath + "/" + i) as json_file:
        bookData = json.load(json_file)['book']
        fillData = bookData['f']
        sellNode = {"timestamp":bookData['timestamp'], "data":[]}
        buyNode = {"timestamp":bookData['timestamp'], "data":[]}
        counter = 0
        for i in fillData:
            if(i['OT'] == "SELL"):
                sellNode['data'].append(i)
            else:
                buyNode['data'].append(i)
            
        sellData.append(sellNode)
        buyData.append(buyNode)
        json_file.close()
    if(counter2 > 30):
        break
 
for i in sellData:
    for b in i['data']:
        plt.scatter(float(i['timestamp']), b['P'], c="red")

for i in buyData:
    for b in i['data']:
        plt.scatter(float(i['timestamp']), b['P'], c="green")

plt.legend(loc=4)
plt.xlabel('Date')
plt.ylabel('Price')
plt.show()"""

"""{
                "I": 45906771,
                "T": 1574694575150,
                "Q": 0.98945188,
                "P": 0.00715221,
                "t": 0.0070767676306548,
                "F": "FILL",
                "OT": "BUY",
                "U": "b144b6d1-b6b9-4a4f-8b24-b4b3d9f024ce"
            }"""
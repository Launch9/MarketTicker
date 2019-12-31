import json
from datetime import datetime
import matplotlib
import matplotlib.pyplot as plt
import numpy as np    
import matplotlib.lines as mlines
from os import listdir
import os
import time
from os.path import isfile, join
import CMethods
import shutil
print("Starting!")
algoNumber = 1
everySo = 1
INPUT_PATH = "./data/USDT-BAT"
SUMMARIES_PATH = "./data/summaries/"
OUTPUT_PATH = "./CMData/USDT-BAT"
CANDLE_PATH = "./candles/USDT-BTC-c.json"
fig, (ax1) = plt.subplots(1)
fig.suptitle('Bottom: Volume - Top: Candles')

onlyfiles = [f for f in sorted(listdir(INPUT_PATH)) if isfile(join(INPUT_PATH, f))]
summaryfiles = [f for f in sorted(listdir(SUMMARIES_PATH)) if isfile(join(SUMMARIES_PATH, f))]
counter = 0

#Cleaning files
"""if(os.path.exists(OUTPUT_PATH)):
    shutil.rmtree(OUTPUT_PATH)
os.mkdir(OUTPUT_PATH)
for i in summaryfiles:
    if(counter % everySo == 0):
        CMethods.findAddressChanges((INPUT_PATH + "/" + onlyfiles[counter]).encode(), (OUTPUT_PATH + "/" + onlyfiles[counter]).encode(), CANDLE_PATH.encode(), (SUMMARIES_PATH + i).encode(), algoNumber)
    print("Compiling data: " + str((counter / len(summaryfiles)) * 100))
    counter += 1"""

counter = 0
#Plotting the candles
candles = {}

with open(CANDLE_PATH) as json_file:
    candles = json.load(json_file)
    json_file.close()

def splitXandY(points, xLabel, yLabel):
    xArray = []
    yArray = []
    for i in points:
        xArray.append(i[xLabel])
        yArray.append(i[yLabel])
    return {'x':xArray, 'y': yArray}

def splitXandY2(points, xLabel, yLabel):
    xArray = []
    yArray = []
    for i in points:
        xArray.append(i[xLabel])
        yArray.append((i[yLabel]) + 8000)
    return {'x':xArray, 'y': yArray}

def dateToUnix(date):
    year = 0
    month = 0
    day = 0
    hour = 0
    minute = 0
    second = 0
    temp = ""
    ticker = 0
    for i in date:
        if(i == '-' or i == 'T' or i == ":"):
            if(ticker == 0):
                year = int(temp)
            if(ticker == 1):
                month = int(temp)
            if(ticker == 2):
                day = int(temp)
            if(ticker == 3):
                hour = int(temp)
            if(ticker == 4):
                minute = int(temp)
            if(ticker == 5):
                second = int(temp)
            temp = ""
            ticker += 1
            continue
        temp = temp + i
    return (datetime(year,month,day,hour,minute,second) - datetime(1970, 1, 1)).total_seconds()

for i in candles["result"]:
    unixtime = dateToUnix(i["T"])#time.mktime(time.strptime(i['T'], '%Y-%m-%dT%H:%M:%S'))
    
    i['TM'] = float(unixtime)
    #i['TM'] = i['T']
    i['C'] = float(i['C'])
    print("Plotting candles: " + str((counter / len(candles["result"])) * 100))
    counter += 1

coordinateData = splitXandY(candles['result'], 'TM', 'C')
volumeData = splitXandY2(candles['result'], 'TM', 'V')
#baseVolumeData = splitXandY(candles['result'], 'TM', 'H')
ax1.plot(coordinateData['x'], coordinateData['y'])
ax1.plot(volumeData['x'], volumeData['y'])


counter = 0
outfiles = [f for f in sorted(listdir(OUTPUT_PATH)) if isfile(join(OUTPUT_PATH, f))]


    
def convertRGBtoHex(r,g,b):
    if(r > 255):
        r = 255
    elif(r < 0):
        r = 0
    if(g > 255):
        g = 255
    elif(g < 0):
        g = 0
    if(b > 255):
        b = 255
    elif(b < 0):
        b = 0
    return '#%02x%02x%02x' % (r,g,b)

SCX = []
SCY = []
SCC = []
"""for i in outfiles:
    
    
    json_file = None
    with open(OUTPUT_PATH + "/" + i) as json_file:
        data2 = json.load(json_file)
        SCX += data2["book"]["data"]["x"]
        SCY += data2["book"]["data"]["y"]
        SCC += data2["book"]["data"]["c"]
        if(algoNumber == 0):
            algo0(data2["book"]["data"])
        elif(algoNumber == 1):
            algo1(data2)
        elif(algoNumber == 2):
            algo2(data2)
        json_file.close()
    print("Plotting dots: " + str((counter / len(outfiles)) * 100))
    counter += 1
            
ax1.scatter(SCX, SCY, c=SCC)"""

plt.xlabel('Date')
plt.ylabel('Price')
plt.show()
#https://bittrex.com/Api/v2.0/pub/market/GetTicks?marketName=BTC-XMR&tickInterval=onemin&_=1499127220008
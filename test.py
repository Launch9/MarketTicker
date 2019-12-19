import time
from datetime import datetime
t = "2019-12-18T06:01:00"
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
unixtime = time.mktime(time.strptime(t, '%Y-%m-%dT%H:%M:%S'))

dt = datetime(2019, 12, 18, 6, 1, 0)
timestamp = (dt - datetime(1970, 1, 1)).total_seconds()
print(timestamp)

print(unixtime)
print(dateToUnix(t))

from __future__ import print_function
from time import sleep
from bittrex_websocket import OrderBook
from datetime import datetime, timedelta
import time
import json
import os
import requests

def startNode(tickerz):
    class MySocket(OrderBook):
        def on_ping(self, msg):
            print("Pinged!")
            
            
    # Create the socket instance
    ws = MySocket()
    # Enable logging
    ws.enable_log()
    # Define tickers
    tickers = tickerz
    # Subscribe to order book updates
    latest_ping = datetime.now()
    totalTime = 60 #In seconds
    sleepTime = totalTime / len(tickers)
    print("Sleep time is: " + str(sleepTime))
    latest_ping = datetime.now()
    ws.query_exchange_state(tickers)
    while(True):
        """for i in tickers:
            book = ws.get_order_book(i)
            if(book != None):
                high = 0
                low = 99999999999999999
                maxBase = 3
                Qhigh = 0
                Qlow = 0
                for i in book["f"]:
                    if(i["P"] < low and i["OT"] == "SELL"):
                        if(i["P"] * i["Q"] <= maxBase):
                            low = i["P"]
                            Qlow = i["Q"]
                for i in book["f"]:
                    if(i["P"] > high and i["OT"] == "BUY"):
                        if(i["P"] * i["Q"] <= maxBase):
                            high = i["P"]
                            Qhigh = i["Q"]
                if(Qhigh != 0):
                    QpercentIncrease = (Qlow - Qhigh) / abs(Qhigh) * 100
                    if(QpercentIncrease > 0):
                        print("Percent increase for " + book["M"] + ": " + str((high - low) / abs(low) * 100) + "%" + " Qhigh: " + str(Qhigh) + " - " + str(high) + " Qlow: " + str(Qlow) + " - " + str(low) + " Qpercent: " + str(QpercentIncrease) + "%")
                        with open("./miscData/" + str(book["M"]) + ".json", 'w') as json_file:
                            json.dump(book, json_file)
                            json_file.close()"""
        for i in tickers:
            book = ws.get_order_book(i)
            if(book != None):
                high = 0
                low = 99999999999999999
                
                for i in book["S"]:
                    if(i["R"] < low):
                        #if(i["R"] * i["Q"] <= maxBase):
                        low = i["R"]
                        
                for i in book["Z"]:
                    if(i["R"] > high):
                        #if(i["R"] * i["Q"] <= maxBase):
                        high = i["R"]
                        
               
                print("Percent increase for " + book["M"] + ": " + str(((low - high) / abs(high)) * 100) + "%" + " high - " + str(high) + " low - " + str(low))
                with open("./miscData/" + str(book["M"]) + ".json", 'w') as json_file:
                    json.dump(book, json_file)
                    json_file.close()
        sleep(15)
    
            


def get_markets():

    # api-endpoint
    url = "https://bittrex.com/api/v2.0/pub/markets/GetMarketSummaries"
    #"https://api.bittrex.com/api/v1.1/public/getmarketsummaries"
    #url = "https://api.bittrex.com/v3/markets/" + trade_string + "/candles?candleInterval=" + interval
    headers = {
        'Accepts': 'application/json',
    }
    # sending get request and saving the response as response object
    r = requests.get(url=url, headers=headers, verify=True)
    if (r.ok == False):
        return False
    else:
        return r.json()

def main():
    newMarketData = []
    # api-endpoint
    marketData = get_markets()['result']
    for i in marketData:
        M = i["Summary"]["MarketName"]
        if(M[0] == 'E' and M[1] == 'T' and M[2] == 'H'):
            newMarketData.append(M)
    startNode(newMarketData)


if __name__ == "__main__":
    main()
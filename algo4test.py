#!/usr/bin/python
# /examples/order_book.py

# Sample script showing how order book syncing works.

from __future__ import print_function
from time import sleep
from bittrex_websocket import OrderBook
import threading
import json
import GF
import requests
def get_market_summaries():
    # api-endpoint
    url = "https://api.bittrex.com/api/v1.1/public/getmarketsummaries"

    headers = {
        'Accepts': 'application/json',
    }
    # sending get request and saving the response as response object
    r = requests.get(url=url, headers=headers, verify=True)

    if (r.ok == False):
        return False
    else:
        return r.json()['result']

def getOrderData(data):
    if(data != None):
        buySize = len(data['Z'])
        sellSize = len(data['S'])
        buyVolume = 0
        sellVolume = 0
        for i in data['Z']:
            buyVolume += i['R']
        for i in data['S']:
            sellVolume += i['R']
        return {"data":{"size": {"buy": buySize, "sell": sellSize}, "volume":{"buy":buyVolume, "sell":sellVolume}}}
    else:
        return None

def startNode(tickers):
    class MySocket(OrderBook):
        def on_ping(self, msg):
            
            #print('Received order book update for {}'.format(msg))
            #print(msg)
            b = 1

    # Create the socket instance
    ws = MySocket()
    # Enable logging
    ws.enable_log()
    # Subscribe to order book updates
    ws.subscribe_to_orderbook(tickers)
    counter = 0
    #while(counter < 150):
    #sleep(10)
    for i in tickers:
        while(counter < 6):
            book = ws.get_order_book(i)
            #print(i)
            if(book != None):
                #print(getOrderData(book))
                """with open("./orderBooks/" + i + ".json", 'w') as json_file:
                    #json.dump({"book": book, "data": getOrderData(book)}, json_file)
                    json.dump({"book":book}, json_file)
                    json_file.close()"""
                with open("./orderData/" + book['ticker'] + ":" + str(book['timestamp']) + ".json", 'w') as json_file:
                    #json.dump({"book": book, "data": getOrderData(book)}, json_file)
                    json.dump({"book":book}, json_file)
                    json_file.close()
                sleep(30)
            else:
                print("ERROR: -> NULL:  " + i)
                sleep(2)
                counter += 1
        counter = 0
        #counter++
    #else:
        #pass
    

def main():
    marketStrings = []
    marketData = ['BTC-LTC']#get_market_summaries()
    for i in marketData:
        marketStrings.append(i)
    startNode(marketStrings)
    
if __name__ == "__main__":
    main()
#include <../iostream>
#include <../string>
#include <../unistd.h>
#include <../stdio.h>
#include <../experimental/filesystem>
#include <../json/json.h>
#include <../fstream>
#include <../iostream>
#include <../json/writer.h>
#include "GF.cpp"

void test(std::string something){
    std::cout << something << std::endl;
}
/**
 * ALGORITHM 0
 * FILL ORDERS, ALPHA
 */
Json::Value algo0(Json::Value book, Json::Value candles, Json::Value summaries){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    sortAndSeperateFill(book, "Q", sortedSellList, sortedBuyList);
    double sellMin;
    double sellMax;
    double sellRange;
    double buyMin;
    double buyMax;
    double buyRange;
        
    if(sortedSellList.size() > 0){
        sellMax = sortedSellList[0]["Q"].asDouble();
        sellMin = sortedSellList[sortedSellList.size() - 1]["Q"].asDouble();
        sellRange = sellMax - sellMin;
        for(unsigned int i = 0; i < sortedSellList.size(); i++){
            double Q = sortedSellList[i]["Q"].asDouble();
            sortedSellList[i]["color"] = RGBToHexadecimal(255,0,0,255);//255 * (Q/sellRange));
        }
        
    }
    if(sortedBuyList.size() > 0){
        buyMax = sortedBuyList[0]["Q"].asDouble();
        buyMin = sortedBuyList[sortedBuyList.size() - 1]["Q"].asDouble();
        buyRange = buyMax - buyMin;
        for(unsigned int i = 0; i < sortedBuyList.size(); i++){
            double Q = sortedBuyList[i]["Q"].asDouble();
            sortedBuyList[i]["color"] = RGBToHexadecimal(0,255,0,255);// * (Q/buyRange));
        }
        
    }
    
    return toJson(book, sortedSellList, sortedBuyList, "P", "color");
}

/**
 * ALGORITHM 1
 * INSTANT ORDERS, ALPHA BASED ON Q, SORTED BY Q AND FILTERED BY R
 */
Json::Value algo1(Json::Value book, Json::Value candles, Json::Value summaries){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    sortAndSeperateInstant(book, "Q", sortedSellList, sortedBuyList);
    double min = 0;
    double max = 0;
    findMinMax(candles["result"], min, max);
    for(unsigned int i = 0 ; i < sortedSellList.size(); i++){
        if(sortedSellList[i]["R"].asDouble() > max || sortedSellList[i]["R"].asDouble() < min){
            sortedSellList.erase(sortedSellList.begin() + i);
            i--;
        }
    }
    for(unsigned int i = 0 ; i < sortedBuyList.size(); i++){
        if(sortedBuyList[i]["R"].asDouble() > max || sortedBuyList[i]["R"].asDouble() < min){
            sortedBuyList.erase(sortedBuyList.begin() + i);
            i--;
        }
    }
    double sellMin;
    double sellMax;
    double sellRange;
    double buyMin;
    double buyMax;
    double buyRange;
    if(sortedSellList.size() > 0){
        sellMax = sortedSellList[0]["Q"].asDouble();
        sellMin = sortedSellList[sortedSellList.size() - 1]["Q"].asDouble();
        sellRange = sellMax - sellMin;
        for(unsigned int i = 0; i < sortedSellList.size(); i++){
            double Q = sortedSellList[i]["Q"].asDouble();
            sortedSellList[i]["color"] = RGBToHexadecimal(255,0,0,255*(Q/sellRange));
        }
    }
    if(sortedBuyList.size() > 0){
        buyMax = sortedBuyList[0]["Q"].asDouble();
        buyMin = sortedBuyList[sortedBuyList.size() - 1]["Q"].asDouble();
        buyRange = buyMax - buyMin;
        for(unsigned int i = 0; i < sortedBuyList.size(); i++){
            double Q = sortedBuyList[i]["Q"].asDouble();
            sortedBuyList[i]["color"] = RGBToHexadecimal(0,255,0,255*(Q/buyRange));
        }
    }
    return toJson(book, sortedSellList, sortedBuyList, "R", "color");;
}

/**
 * ALGORITHM 2
 * FILL ORDERS, AVERAGED
 */
Json::Value algo2(Json::Value book, Json::Value candles, Json::Value summaries){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    std::vector<Json::Value> newSList;
    std::vector<Json::Value> newBList;
    sortAndSeperateFill(book, "Q", sortedSellList, sortedBuyList);
    double sellMin;
    double sellMax;
    double sellRange;
    double buyMin;
    double buyMax;
    double buyRange;
    if(sortedSellList.size() > 0){
        sellMax = sortedSellList[0]["Q"].asDouble();
        sellMin = sortedSellList[sortedSellList.size() - 1]["Q"].asDouble();
        sellRange = sellMax - sellMin;
        for(unsigned int i = 0; i < sortedSellList.size(); i++){
            double Q = sortedSellList[i]["Q"].asDouble();
            sortedSellList[i]["color"] = RGBToHexadecimal(255,0,0,255 * (Q/sellRange));
        }
        
        double count = 0;
        for(unsigned int i = 0; i < sortedSellList.size(); i++){
            count += sortedSellList[i]["P"].asDouble();
        }
       
        Json::Value jv;
        jv["P"] = count / sortedSellList.size();
        jv["color"] = RGBToHexadecimal(255,0,0,255);
        newSList.push_back(jv);
        
    }
    if(sortedBuyList.size() > 0){
        buyMax = sortedBuyList[0]["Q"].asDouble();
        buyMin = sortedBuyList[sortedBuyList.size() - 1]["Q"].asDouble();
        buyRange = buyMax - buyMin;
        for(unsigned int i = 0; i < sortedBuyList.size(); i++){
            double Q = sortedBuyList[i]["Q"].asDouble();
            sortedBuyList[i]["color"] = RGBToHexadecimal(0,255,0,255 * (Q/buyRange));
        }
        
        double count = 0;
        for(unsigned int i = 0; i < sortedBuyList.size(); i++){
            count += sortedBuyList[i]["P"].asDouble();
        }
        
        Json::Value jv;
        jv["P"] = count / sortedBuyList.size();
        jv["color"] = RGBToHexadecimal(0,255,0,255);
        newBList.push_back(jv);
        
    }
    
    return toJson(book, newSList, newBList, "P", "color");
}

/**
 * ALGORITHM 3
 * FILL ORDERS, MIN MAX, SELL/BUY REVERSED
 */

Json::Value algo3(Json::Value book, Json::Value candles, Json::Value summaries){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    std::vector<Json::Value> newSList;
    std::vector<Json::Value> newBList;
    sortAndSeperateFill(book, "P", sortedSellList, sortedBuyList);
    if(sortedSellList.size() > 0 && sortedBuyList.size() > 0){
        
        Json::Value jv;
        jv["P"] = sortedSellList[sortedSellList.size() - 1]["P"];
        jv["color"] = RGBToHexadecimal(255,0,0,255);
        newSList.push_back(jv);
        Json::Value jv2;
        jv2["P"] = sortedBuyList[0]["P"];
        jv2["color"] = RGBToHexadecimal(0,255,0,255);
        newBList.push_back(jv2);
    }
    return toJson(book, newSList, newBList, "P", "color");
}

/**
 * ALGORITHM 4
 * TOP FILL ORDERS
 */

Json::Value algo4(Json::Value book, Json::Value candles, Json::Value summaries){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    std::vector<Json::Value> newSList;
    std::vector<Json::Value> newBList;
    sortAndSeperateFill(book, "Q", sortedSellList, sortedBuyList);
    if(sortedSellList.size() >= 3){
        int sslsize = sortedSellList.size();
        sortedSellList[sslsize - 3]["color"] = "#FF0000";
        sortedSellList[sslsize - 2]["color"] = "#FF0000";
        sortedSellList[sslsize - 1]["color"] = "#FF0000";
        newSList = std::vector<Json::Value>{sortedSellList[sslsize - 3], sortedSellList[sslsize - 2], sortedSellList[sslsize - 1]};
        
    }
    if(sortedBuyList.size() >= 3){
        
        int sslsize = sortedBuyList.size();
        sortedBuyList[sslsize - 3]["color"] = "#00FF00";
        sortedBuyList[sslsize - 2]["color"] = "#00FF00";
        sortedBuyList[sslsize - 1]["color"] = "#00FF00";
        newBList = std::vector<Json::Value>{sortedBuyList[sslsize - 3], sortedBuyList[sslsize - 2], sortedBuyList[sslsize - 1]};
        
    }
    return toJson(book, newSList, newBList, "P", "color");
}

/**
 * ALGORITHM 5
 * SUMMARIES HIGH LOW
 */

Json::Value algo5(Json::Value book, Json::Value candles, Json::Value summaries){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    std::vector<Json::Value> newSList;
    std::vector<Json::Value> newBList;
    Json::Value top;
    Json::Value xArr(Json::arrayValue);
    Json::Value yArr(Json::arrayValue);
    Json::Value cArr(Json::arrayValue);
    std::string trade = book["ticker"].asString();
    Json::Value summary;
    
    for(int i = 0 ; i < summaries["result"].size(); i++){
        
        if(summaries["result"][i]["Summary"]["MarketName"].asString() == trade){
            std::cout << "Found " + trade << std::endl;
            summary = summaries["result"][i]["Summary"];
            break;
        }
    }
    xArr.append(summaries["timestamp"]);
    yArr.append(summary["Last"].asDouble());
    int buyOrders = summary["OpenBuyOrders"].asInt();
    int sellOrders = summary["OpenSellOrders"].asInt();
    std::cout << buyOrders << std::endl;
    std::cout << sellOrders << std::endl;
    double percentIncrease = buyOrders - sellOrders; //sellOrders - buyOrders / abs(buyOrders);
    std::cout << percentIncrease << std::endl;
    cArr.append(RGBToHexadecimal((255 / 2) + (percentIncrease * 10),0,0,255));
    /*if(summary["OpenBuyOrders"].asInt() > summary["OpenSellOrders"].asInt()){
        cArr.append("#00FF00");
    }
    else if(summary["OpenBuyOrders"].asInt() < summary["OpenSellOrders"].asInt()){
        cArr.append("#FF0000");
    }
    else{
        cArr.append("#0000FF");
    }*/
    
    top["book"]["timestamp"] = summaries["timestamp"];
    top["book"]["data"]["x"] = xArr;
    top["book"]["data"]["y"] = yArr;
    top["book"]["data"]["c"] = cArr;
    
    return top;
}


/**
 * ALGORITHM 6
 * SUMMARIES HIGH LOW
 */

Json::Value algo6(Json::Value book, Json::Value candles, Json::Value summaries){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    std::vector<Json::Value> newSList;
    std::vector<Json::Value> newBList;
    Json::Value top;
    Json::Value xArr(Json::arrayValue);
    Json::Value yArr(Json::arrayValue);
    Json::Value cArr(Json::arrayValue);
    sortAndSeperateFill(book, "Q", sortedSellList, sortedBuyList);
    double sellVolume = 0;
    double buyVolume = 0;
    for(int i = 0 ; i < sortedSellList.size() ; i++){
        sellVolume += sortedSellList[i]["Q"].asDouble();
    }
    for(int i = 0; i < sortedBuyList.size(); i++){
        buyVolume += sortedBuyList[i]["Q"].asDouble();
    }
    xArr.append(book["timestamp"]);
    yArr.append(book["S"][0]["R"]);
    if(sellVolume > buyVolume){
        cArr.append(RGBToHexadecimal(255,0,0,255));
    }
    else if(sellVolume < buyVolume){
        cArr.append(RGBToHexadecimal(0,255,0,255));
    }
    else{
        cArr.append(RGBToHexadecimal(0,0,255,255));
    }
    top["book"]["timestamp"] = book["timestamp"];
    top["book"]["data"]["x"] = xArr;
    top["book"]["data"]["y"] = yArr;
    top["book"]["data"]["c"] = cArr;
    return top;
}
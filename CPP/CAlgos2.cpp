#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <experimental/filesystem>
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <json/writer.h>
#include "GF.cpp"

void test(std::string something){
    std::cout << something << std::endl;
}
/**
 * ALGORITHM 0
 * FILL ORDERS, NO ALPHA
 */
Json::Value algo0(Json::Value book, Json::Value candles){
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
    /*for(unsigned int i = sortedSellList.size() - 1; i > sortedSellList.size() - 3; i--){
        newSList.push_back(sortedSellList[i]);
    }
    for(unsigned int i = sortedBuyList.size() - 1; i > sortedBuyList.size() - 3; i--){
        newBList.push_back(sortedBuyList[i]);
    }*/
    
    
    return toJson(book, newSList, newBList, "P", "color");
}

/**
 * ALGORITHM 1
 * INSTANT ORDERS, NO ALPHA
 */
Json::Value algo1(Json::Value book, Json::Value candles){
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
 * INSTANT ORDERS, ALPHA DEPENDING ON HOW MUCH
 */
Json::Value algo2(Json::Value book, Json::Value candles){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    sortAndSeperateInstant(book, "Q", sortedSellList, sortedBuyList);
    return toJson(book, sortedSellList, sortedBuyList, "S", "S");
}

/**
 * ALGORITHM 3
 * FILL ORDERS, ALPHA DEPENDS ON HOW MUCH
 */

Json::Value algo3(Json::Value book, Json::Value candles){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    sortAndSeperateFill(book, "Q", sortedSellList, sortedBuyList);
    return toJson(book, sortedSellList, sortedBuyList, "S", "s");
}
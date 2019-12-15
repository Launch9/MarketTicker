#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <experimental/filesystem>
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <json/writer.h>
//g++ -c -fPIC CAlgos.cpp -Wextra -Wall -o ./builds/CAlgos.o -ljsoncpp
//g++ -shared -Wl,-soname,./builds/libCAlgos.so -o ./builds/libCAlgos.so ./builds/CAlgos.o -ljsoncpp

void bar(char* string){
    printf("%s", string);
}

Json::Value algo0(Json::Value book, Json::Value candles){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    for(int i = 0; i < book["f"].size(); i++){
        if(book["f"][i]["OT"] == "SELL"){
            if(sortedSellList.size() == 0){
                sortedSellList.push_back(book["f"][i]);
            }
            else{
                for(int b = 0; b < sortedSellList.size(); b++){
                    if(book["f"][i]["Q"] > sortedSellList[b]["Q"]){
                        sortedSellList.insert(sortedSellList.begin() + b, book["f"][i]);
                        break;
                    }
                }
            }
        }
        else{
            if(sortedBuyList.size() == 0){
                sortedBuyList.push_back(book["f"][i]);
            }
            else{
                for(int b = 0; b < sortedBuyList.size(); b++){
                    if(book["f"][i]["Q"] > sortedBuyList[b]["Q"]){
                        sortedBuyList.insert(sortedBuyList.begin() + b, book["f"][i]);
                        break;
                    }
                }
            }
        }
    }
    Json::Value top;
    Json::Value vec(Json::arrayValue);
    Json::Value buyVec(Json::arrayValue);
    for(int i = 0; i < sortedSellList.size(); i++){
        vec.append(sortedSellList[i]);
    }
    for(int i = 0; i < sortedBuyList.size(); i++){
        buyVec.append(sortedBuyList[i]);
    }
    top["book"]["timestamp"] = book["timestamp"];//std::stof(numberString);
    top["book"]["data"]["SELL"] = vec;
    top["book"]["data"]["BUY"] = buyVec;
    return top;
}

Json::Value algo1(Json::Value book, Json::Value candles){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    //Checking for max and min values of candles
    double min = 999999999;
    double max = 0;
    for(int i = 0; i < candles["result"].size(); i++){
       
        Json::Value currentCandle = candles["result"][i];
        if(currentCandle["C"] > max){
            
            max = currentCandle["C"].asDouble();
            
        }
        if(currentCandle["C"] < min){
            
            min = currentCandle["C"].asDouble();
            
        }
    }
    
    for(int i = 0; i < book["S"].size(); i++){
        if(sortedSellList.size() == 0){
            sortedSellList.push_back(book["S"][i]);
        }
        else{
            for(int b = 0; b < sortedSellList.size(); b++){
                if(book["S"][i]["Q"] > sortedSellList[b]["Q"]){
                    
                    if(book["S"][i]["R"] < max && book["S"][i]["R"] > min){
                        sortedSellList.insert(sortedSellList.begin() + b, book["S"][i]);
                        break;
                    }
                }
            }
        }
    }
    for(int i = 0; i < book["Z"].size(); i++){
        if(sortedBuyList.size() == 0){
            sortedBuyList.push_back(book["Z"][i]);
        }
        else{
            for(int b = 0; b < sortedBuyList.size(); b++){
                if(book["Z"][i]["Q"] > sortedBuyList[b]["Q"]){
                    if(book["Z"][i]["R"] < max && book["Z"][i]["R"] > min){
                        sortedBuyList.insert(sortedBuyList.begin() + b, book["Z"][i]);
                        break;
                    }
                }
            }
        }
    }
    Json::Value top;
    Json::Value vec(Json::arrayValue);
    Json::Value buyVec(Json::arrayValue);
    for(int i = 0; i < sortedSellList.size(); i++){
        vec.append(sortedSellList[i]);
    }
    for(int i = 0; i < sortedBuyList.size(); i++){
        buyVec.append(sortedBuyList[i]);
    }
    top["book"]["timestamp"] = book["timestamp"];//std::stof(numberString);
    top["book"]["data"]["SELL"] = vec;
    top["book"]["data"]["BUY"] = buyVec;
    return top;
}

Json::Value algo2(Json::Value book, Json::Value candles){
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    for(int i = 0; i < book["S"].size(); i++){
        if(sortedSellList.size() == 0){
            sortedSellList.push_back(book["S"][i]);
        }
        else{
            for(int b = 0; b < sortedSellList.size(); b++){
                if(book["S"][i]["Q"] > sortedSellList[b]["Q"]){
                    if(book["S"][i]["R"] < 1){
                        sortedSellList.insert(sortedSellList.begin() + b, book["S"][i]);
                        break;
                    }
                }
            }
        }
    }
    for(int i = 0; i < book["Z"].size(); i++){
        if(sortedBuyList.size() == 0){
            sortedBuyList.push_back(book["Z"][i]);
        }
        else{
            for(int b = 0; b < sortedBuyList.size(); b++){
                if(book["Z"][i]["Q"] > sortedBuyList[b]["Q"]){
                    if(book["S"][i]["R"] < 1){
                        sortedBuyList.insert(sortedBuyList.begin() + b, book["Z"][i]);
                        break;
                    }
                }
            }
        }
    }
    Json::Value top;
    Json::Value vec(Json::arrayValue);
    Json::Value buyVec(Json::arrayValue);
    for(int i = 0; i < sortedSellList.size(); i++){
        vec.append(sortedSellList[i]);
    }
    for(int i = 0; i < sortedBuyList.size(); i++){
        buyVec.append(sortedBuyList[i]);
    }
    top["book"]["timestamp"] = book["timestamp"];//std::stof(numberString);
    top["book"]["data"]["SELL"] = vec;
    top["book"]["data"]["BUY"] = buyVec;
    return top;
}

void _findAddressChanges(char* filenameInput, char* filenameOutput, char* candleFilePath, int algoType){
    
    Json::Value root;
    Json::Value book;
    
    std::ifstream ifs;
    ifs.open(filenameInput);
    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    std::string errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << "Throwing Error!" << std::endl;
        std::cout << errs << std::endl;
        return;
    }
    ifs.close();
    ifs.open(candleFilePath);
    Json::Value candles;
    Json::CharReaderBuilder builder2;
    builder["collectComments"] = true;
    std::string errs2;
    if (!parseFromStream(builder2, ifs, &candles, &errs2)) {
        std::cout << "Throwing Error!" << std::endl;
        std::cout << errs2 << std::endl;
        return;
    }
    book = root["book"];
    Json::Value top;
    
    switch(algoType) {
        case 0:
            top = algo0(book, candles);
            break;
        case 1:
            top = algo1(book, candles);
            break;
        case 2:
            top = algo2(book, candles);
            break;
    }
    //Writing results to file
    Json::StreamWriterBuilder builder3;
    builder["commentStyle"] = "None";
    builder["indentation"] = "   ";
    std::unique_ptr<Json::StreamWriter> writer(builder3.newStreamWriter());
    std::ofstream outputFileStream(filenameOutput);
    writer -> write(top, &outputFileStream);
    return;
}

extern "C" {
    void Foo_bar(char* aString){
        bar(aString);
    }
    void findAddressChanges(char* filenameInput, char* filenameOutput, char* candleFilePath, int algoType){
        _findAddressChanges(filenameInput, filenameOutput, candleFilePath, algoType);
    }
}


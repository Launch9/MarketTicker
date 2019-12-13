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

void _findAddressChanges(char* filenameInput, char* filenameOutput){
    
    
    Json::Value root;
    Json::Value book;
    std::vector<Json::Value> sortedSellList;
    std::vector<Json::Value> sortedBuyList;
    std::ifstream ifs;
    ifs.open(filenameInput);
    
    
    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    std::string errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << "Throwing ERror!" << std::endl;
        std::cout << errs << std::endl;
        return;
    }
    book = root["book"];
    
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
    std::string timestampString = std::string(filenameOutput);
    std::string numberString = std::string("");
    bool isPastColon = false;
    bool isPastFirstDot = false;
    //Finding timestamp
    /*for(int i = 0; i < timestampString.length(); i++){
        if(timestampString[i] == ':'){
            isPastColon = true;
            continue;
        }
        else if(isPastColon){
            if(timestampString[i] == '.'){
                if(isPastFirstDot){
                    break;
                }
                else{
                    isPastFirstDot = true;
                }
            }
            numberString = numberString + timestampString[i];
        }

    }*/
    top["book"]["timestamp"] = book["timestamp"];//std::stof(numberString);
    //std::cout << numberString << std::endl;
    top["book"]["data"]["SELL"] = vec;
    top["book"]["data"]["BUY"] = buyVec;
    //Writing results to file
    Json::StreamWriterBuilder builder2;
    builder["commentStyle"] = "None";
    builder["indentation"] = "   ";

    std::unique_ptr<Json::StreamWriter> writer(builder2.newStreamWriter());
    std::ofstream outputFileStream(filenameOutput);
    writer -> write(top, &outputFileStream);
    /*std::cout << "Finished sorting!" << std::endl;
    for(int i = 0; i < sortedSellList.size(); i++){
        std::cout << sortedSellList[i] << std::endl;
    }*/
    
    

    return;
    /*std::string mypath = "./tickerData/BTC-XMR";
    for (const auto & entry : std::experimental::filesystem::directory_iterator(filenameInput)){
        std::string file = entry.path();
        std::vector<
        counter2 = 0
        for i in onlyfiles:
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
        plt.show()
    }*/
}

extern "C" {
    void Foo_bar(char* aString){
        bar(aString);
    }
    void findAddressChanges(char* filenameInput, char* filenameOutput){
        _findAddressChanges(filenameInput, filenameOutput);
    }
}


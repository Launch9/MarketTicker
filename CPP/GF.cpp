#include <../iostream>
#include <../string>
#include <../unistd.h>
#include <../stdio.h>
#include <../experimental/filesystem>
#include <../json/json.h>
#include <../fstream>
#include <../iostream>
#include <../json/writer.h>
#include <../ctime>
#include <../cstring>
void sortAndSeperateFill(Json::Value book, std::string sortBy, std::vector<Json::Value> &sortedSellList, std::vector<Json::Value> &sortedBuyList){
    for(unsigned int i = 0; i < book["f"].size(); i++){
        if(book["f"][i]["OT"] == "SELL"){
            if(sortedSellList.size() == 0){
                sortedSellList.push_back(book["f"][i]);
            }
            else{
                for(unsigned int b = 0; b < sortedSellList.size(); b++){
                    if(book["f"][i][sortBy] > sortedSellList[b][sortBy]){
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
                for(unsigned int b = 0; b < sortedBuyList.size(); b++){
                    if(book["f"][i][sortBy] > sortedBuyList[b][sortBy]){
                        sortedBuyList.insert(sortedBuyList.begin() + b, book["f"][i]);
                        break;
                    }
                }
            }
        }
    }
}

void sortAndSeperateInstant(Json::Value book, std::string sortBy, std::vector<Json::Value> &sortedSellList, std::vector<Json::Value> &sortedBuyList){
    for(unsigned int i = 0; i < book["S"].size(); i++){
        if(sortedSellList.size() == 0){
            sortedSellList.push_back(book["S"][i]);
        }
        else{
            for(unsigned int b = 0; b < sortedSellList.size(); b++){
                if(book["S"][i][sortBy] > sortedSellList[b][sortBy]){
                    sortedSellList.insert(sortedSellList.begin() + b, book["S"][i]);
                    break;
                }
            }
        }
    }
    for(unsigned int i = 0; i < book["Z"].size(); i++){
        if(sortedBuyList.size() == 0){
            sortedBuyList.push_back(book["Z"][i]);
        }
        else{
            for(unsigned int b = 0; b < sortedBuyList.size(); b++){
                if(book["Z"][i][sortBy] > sortedBuyList[b][sortBy]){
                    sortedBuyList.insert(sortedBuyList.begin() + b, book["Z"][i]);
                    break;
                }
            }
        }
    }
}

time_t convertTimeToEpoch(const char* theTime, const char* format = "%Y-%m-%d %H:%M:%S")
{
    std::tm tmTime;
    memset(&tmTime, 0, sizeof(tmTime));
    strptime(theTime, format, &tmTime);
    return mktime(&tmTime);
}

std::string DecimalToHexadecimal(int dec) {
	if (dec < 1) return "00";
	int hex = dec;
	std::string hexStr = "";
	while (dec > 0)
	{
		hex = dec % 16;
		if (hex < 10)
			hexStr = hexStr.insert(0, std::string(1, (hex + 48)));
		else
			hexStr = hexStr.insert(0, std::string(1, (hex + 55)));
		dec /= 16;
	}
    if(hexStr.size() == 1){
        hexStr.append("0");
    }
    if(hexStr.size() != 2){
        hexStr = "00";
    }
	return hexStr;
}

std::string RGBToHexadecimal(int red, int green, int blue, int alpha) {
	std::string rs = DecimalToHexadecimal(red);
	std::string gs = DecimalToHexadecimal(green);
	std::string bs = DecimalToHexadecimal(blue);
    if(alpha > 255){
        alpha = 255;
    }
    else if(alpha < 0){
        alpha = 0;
    }
    if(red > 255){
        red = 255;
    }
    else if(red < 0){
        red = 0;
    }
    if(blue > 255){
        blue = 255;
    }
    else if(blue < 0){
        blue = 0;
    }
    if(green > 255){
        green = 255;
    }
    else if(green < 0){
        green = 0;
    }
    std::string as = DecimalToHexadecimal(alpha);
	return '#' + rs + gs + bs + as;
}

Json::Value toJson(Json::Value book, std::vector<Json::Value> sellList, std::vector<Json::Value> buyList, std::string y, std::string c){
    Json::Value top;
    Json::Value xArr(Json::arrayValue);
    Json::Value yArr(Json::arrayValue);
    Json::Value cArr(Json::arrayValue);
    
    for(unsigned int i = 0; i < sellList.size(); i++){
        xArr.append(book["timestamp"]);
        yArr.append(sellList[i][y]);
        cArr.append(sellList[i][c]);
    }
    for(unsigned int i = 0; i < buyList.size(); i++){
        xArr.append(book["timestamp"]);
        yArr.append(buyList[i][y]);
        cArr.append(buyList[i][c]);
    }
    
    top["book"]["timestamp"] = book["timestamp"];
    top["book"]["data"]["x"] = xArr;
    top["book"]["data"]["y"] = yArr;
    top["book"]["data"]["c"] = cArr;
    return top;
}

void findMinMax(Json::Value candles, double &min, double &max){
    //Checking for max and min values of candles
    min = 999999999;
    max = 0;
    for(unsigned int i = 0; i < candles.size(); i++){
        Json::Value currentCandle = candles[i];
        if(currentCandle["C"] > max){
            max = currentCandle["C"].asDouble();
        }
        if(currentCandle["C"] < min){
            min = currentCandle["C"].asDouble();
        }
    }

}
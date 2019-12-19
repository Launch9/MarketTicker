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
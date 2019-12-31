#include <../iostream>
#include <../string>
#include <../unistd.h>
#include <../stdio.h>
#include <../experimental/filesystem>
#include <../json/json.h>
#include <../fstream>
#include <../json/writer.h>
#include "CAlgos2.cpp"
//g++ -c -fPIC CAlgos.cpp -Wextra -Wall -o ./builds/CAlgos.o -ljsoncpp
//g++ -shared -Wl,-soname,./builds/libCAlgos.so -o ./builds/libCAlgos.so ./builds/CAlgos.o -ljsoncpp

void bar(char* string){
    printf("%s", string);
}

void _findAddressChanges(char* filenameInput, char* filenameOutput, char* candleFilePath, char* summariesInput, int algoType){
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
    builder2["collectComments"] = true;
    std::string errs2;
    if (!parseFromStream(builder2, ifs, &candles, &errs2)) {
        std::cout << "Throwing Error!" << std::endl;
        std::cout << errs2 << std::endl;
        return;
    }
    ifs.close();
    
    ifs.open(summariesInput);
    Json::Value summaries;
    Json::CharReaderBuilder builder3;
    builder3["collectComments"] = true;
    std::string errs3;
    if (!parseFromStream(builder3, ifs, &summaries, &errs3)) {
        std::cout << "Throwing Error!" << std::endl;
        std::cout << errs3 << std::endl;
        return;
    }
    
    book = root["book"];
    Json::Value top;
    switch(algoType) {
        case 0:
            top = algo0(book, candles, summaries);
            break;
        case 1:
            top = algo1(book, candles, summaries);
            break;
        case 2:
            top = algo2(book, candles, summaries);
            break;
        case 3:
            top = algo3(book, candles, summaries);
            break;
        case 4:
            top = algo4(book, candles, summaries);
            break;
        case 5:
            top = algo5(book, candles, summaries);
            break;
        case 6:
            top = algo6(book, candles, summaries);
            break;
    }
    //Writing results to file
    Json::StreamWriterBuilder builder4;
    builder["commentStyle"] = "None";
    builder["indentation"] = "   ";
    std::unique_ptr<Json::StreamWriter> writer(builder4.newStreamWriter());
    std::ofstream outputFileStream(filenameOutput);
    writer -> write(top, &outputFileStream);
    return;
}

extern "C" {
    void Foo_bar(char* aString){
        bar(aString);
    }
    void findAddressChanges(char* filenameInput, char* filenameOutput, char* candleFilePath, char* summariesInput, int algoType){
        _findAddressChanges(filenameInput, filenameOutput, candleFilePath, summariesInput, algoType);
    }
}


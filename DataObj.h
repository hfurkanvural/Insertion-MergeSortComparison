#ifndef DataObj_h
#define DataObj_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

class DataObj
{
public:
    string timestamp;
    string instrument_token;
    double last_price;
    string otherinfo;
    
    void getvalts(string x){timestamp=x;}
    void getvalit(string x){instrument_token=x;}
    void getvallp(string x){double fx = stod(x); last_price = fx;}
    void getvaloi(string x){otherinfo=x;}
    DataObj operator=( DataObj&) ;
    DataObj(){}
    
};


#endif
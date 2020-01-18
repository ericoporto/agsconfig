//
// Created by erico on 18/01/2020.
//

#ifndef AGSCONFIG_UTIL_STR_H
#define AGSCONFIG_UTIL_STR_H

#include <string>
using namespace std;

string BoolToStr(bool b){
    return b ? "1" : "0";
}

string IntToStr(int i){
    return to_string(i);
}

string FloatToStr(float f){
    return to_string(f);
}

bool StrToBool(const string& b_str){
    return b_str != "0";
}

int StrToInt(const string& i_str){
    return stoi(i_str);
}

float StrToFloat(const string& f_str){
    return stof(f_str);
}

#endif //AGSCONFIG_UTIL_STR_H

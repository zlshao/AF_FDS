#ifndef MYREDIS_H
#define MYREDIS_H

#include "hiredis.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

template<class T>
T str2num(const std::string& str)
{
    std::stringstream ss;
    T num;
    ss << str;
    ss >> num;
    return num;
}

//字符串转数值
//demo: double num=-23.1; string str = num2str(num);
//建议指定T的类型，str = num2str<int>(num);
template<class T>
std::string num2str(const T& num)
{
    std::stringstream ss;
    ss << num;
    std::string str;
    ss >> str;
    return str;
}


class myredis
{
    public:
        myredis(const char * ip,int port);
        ~myredis();
        void insert(string key,vector<string> values);
        vector<string> get(string key);
        void scan(string pattern);

    private:
        redisContext *pContext;

};

#endif
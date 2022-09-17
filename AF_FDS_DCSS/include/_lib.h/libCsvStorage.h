/**
MIT License

Copyright (c) 2021 caymanhu(caymanhu@qq.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef LIB_CSV_STORAGE_H
#define LIB_CSV_STORAGE_H

#include "IEVStorage.h"
#include "libBaseSE.h"

class CCsvStorageCreator
{
public:
    static IEigenvectorStorage* createCsvStorage();
};

class CCsvStorage: public IEigenvectorStorage
{
public:    
    CCsvStorage();
    ~CCsvStorage();
public:    
    void initialPara(std::string strPara, int iPara, std::string resrPara);
    void insertEV(std::string strKey, std::string strValue);
private:
    static const int iLevelCount = pso_SelfDefine; 
private:
    std::string strPcapFN;
    std::string arrFileName[iLevelCount];   //stat filename
private:
    void saveTitle(std::string strKey, std::string strValue);
    void saveValue(std::string strKey, std::string strValue);
    int getNextBit(uint32_t value, int beginPos);
};

#endif

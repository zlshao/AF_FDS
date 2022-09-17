/**
MIT License

Copyright (c) 2021 刘嵩涛(220215545@seu.edu.cn) caymanhu(caymanhu@qq.com)

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

/**
 * @file IEVStorage.h (https://www.seu.edu.cn/)
 * @author 刘嵩涛(220215545@seu.edu.cn), caymanhu(caymanhu@qq.com)
 * @brief Feature vector storage for multi-counter sketch, 用于多计数器sketch产生的特征向量储存
 * @version 0.1
 * @date 2021-11-07
 */

#ifndef EIGENVECTOR_STORAGE_H
#define EIGENVECTOR_STORAGE_H

#include <cstdlib>
#include <cstring>
#include <string>

class IEigenvectorStorage
{
public:
    virtual ~IEigenvectorStorage(){}
public:
    virtual void initialPara(std::string strPara, int iPara, std::string resrPara) = 0;
    virtual void insertEV(std::string strKey, std::string strValue) = 0;
};

#endif

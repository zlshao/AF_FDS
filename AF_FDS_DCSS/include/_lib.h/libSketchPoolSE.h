/**
MIT License

Copyright (c) 2021 hwu(hwu@seu.edu.cn), caymanhu(caymanhu@qq.com)

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
 * @file libPcapSE.h (https://www.seu.edu.cn/) 
 * @author hwu(hwu@seu.edu.cn), caymanhu(caymanhu@qq.com)
 * @brief sketch pool
 * @version 0.1
 * @date 2021-09-03
 */

#ifndef LIB_SKETCH_POOL_SE_H
#define LIB_SKETCH_POOL_SE_H

#include <vector>
#include <stdint.h>
#include "IEVStorage.h"
#include "libBaseSE.h"
#include "libPacketSE.h"

class ISketchPool
{
public:
    virtual ~ISketchPool(){}
public:
    /**
     * @brief  增加多计数器sketch
     * 
     * @param skType 种类
     * @param bit hash bit位
     * @param pck_thre 统计阈值
     * @param skFeature 特征
     * @param lpVctTCPRange TCP range可选
     * @param lpVctUDPRange UDP range可选
     * @return true 
     * @return false 
     */
    virtual bool addSketch(packet_statistics_object_type skType, int bit, int pck_thre,
                           uint64_t skFeature, std::vector<int>* lpVctTCPRange, std::vector<int>* lpVctUDPRange) = 0;
    virtual void setStorage(IEigenvectorStorage* lpStor) = 0;
public:
    virtual bool procPacket(CPacket* lppck) = 0;
};

class CSketchPoolCreator
{
public:
    static ISketchPool* create_sketch_pool(int ratio);
};

#endif
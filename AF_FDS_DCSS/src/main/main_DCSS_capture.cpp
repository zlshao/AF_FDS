/**
MIT License

Copyright (c) 2022 hwu(hwu@seu.edu.cn), zlshao(zlshao@seu.edu.cn), chentz(chentz@seu.edu.cn)

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

#include <stdio.h>
#include <pcap.h>
#include <iostream>
#include "_lib.h/libPacketSE.h"
#include "PckCap/CPckCap.h"
#include "_lib.h/libSketchPoolSE.h"
#include "_lib.h/libCsvStorage.h"
#include "_lib.h/libconfig.h++"
#include "other/bit_conversion.h"
#include <sys/time.h>
//#include "_lib.h/libRedisStorage.h"

using namespace std;
using namespace libconfig;

timeval timde;

bool add_SDS_SK(Config* lpCfg, ISketchPool* lpSKP)
{
    bool bout = false;
    if(lpCfg && lpSKP)
    {
        int type, bit, thre;
        //type
        lpCfg->lookupValue("DCSS_key_type", type);
        cout << "DCSS sketch hash key type:" << type << endl;
        //bit
        lpCfg->lookupValue("DCSS_sketch_hash_bit", bit);
        cout << "DCSS sketch length:2^" << bit << endl;
        //threshold
        lpCfg->lookupValue("DCSS_sketch_threshold", thre);
        cout << "sketch statistics threshold:" << thre << endl;
        //features
        string strFea = lpCfg->lookup("DCSS_sketch_feature");
        cout << "sketch features:" << strFea << endl;
        uint64_t ufea = convStringValue(strFea);
        //range
        uint32_t uflag = 12;
        vector<int> vctTCP, vctUDP;
        if(ufea & uflag) 
        {
            //have range flag
            vctTCP.clear();
            vctUDP.clear();

            int cntRange;
            lpCfg->lookupValue("DCSS_sketch_range_count", cntRange);
            cout << "DCSS sketch range count:" << cntRange << endl;
            for(int j=1; j<=cntRange; j++)
            {
                int value;
                if(lpCfg->lookupValue("DCSS_sketch_range_TCP_" + to_string(j), value))
                {
                    vctTCP.push_back(value);
                    cout << "DCSS sketch TCP payload range threshold " + to_string(j) << ":" << value << endl;
                }
                if(lpCfg->lookupValue("DCSS_sketch_range_UDP_" + to_string(j), value))
                {
                    vctUDP.push_back(value);
                    cout << "DCSS sketch UDP payload range threshold " + to_string(j) << ":" << value << endl;
                }
            }
        }
        if(lpSKP->addSketch((packet_statistics_object_type)type, bit, thre, ufea, &vctTCP, &vctUDP))
            bout = true;
        else
            cout << "DCSS sketch setting error!" << endl;
    }
    return true;
}

int main(int argc, char *argv[])
{

    char buf[UINT8_MAX] = "data.cfg";

    if(argc==2)
        strcpy(buf, argv[1]);

    std::cerr << "capture begin" << std::endl;        

    Config cfg;
    try
    {
        cfg.readFile(buf);
    }
    catch(...)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE); 
    }    

    try
    {
        //dev
        string dev = cfg.lookup("DCSS_dev");    
        cout << "Capture dev name:" << dev << endl;
        //file
        string file = cfg.lookup("DCSS_out_pcap_file");    
        cout << "Capture output file name:" << file << endl;

        int dumptype;
        cfg.lookupValue("DCSS_dump_type", dumptype);
        cout << "dump type(0--not capture, 1--capture sample, 2--capture all):" << dumptype << endl;

        //ratio
        int rationo, ratio;
        cfg.lookupValue("DCSS_ratio", rationo);
        cout << "Sample ratio No.:" << rationo << endl;
        ratio = calSampleRate(rationo);
        cout << "Sample ratio:1/" << ratio << endl;

        uint32_t cntPck;
        cfg.lookupValue("DCSS_max_packet", cntPck);
        cout << "Maximum packet capture:" << cntPck << endl;
        int tmCap;
        cfg.lookupValue("DCSS_capture_time", tmCap);
        cout << "Maximum packet capture time:" << tmCap << endl;

        if(dev.length()>0)
        {
            IEigenvectorStorage* lpStorage = CCsvStorageCreator::createCsvStorage();
            lpStorage->initialPara(file, 0, "");
            ISketchPool* lpSKPool = CSketchPoolCreator::create_sketch_pool(ratio);
            //Eigenvectors are stored in a CSV file
            lpSKPool->setStorage(lpStorage);
            //Eigenvectors are stored in Redis
            //IEigenvectorStorage* lpStorage3 = CRedisStorageCreator::createRedisStorage();
            //lpSKPool->setStorage(lpStorage3);

            if(add_SDS_SK(&cfg, lpSKPool))
            {

                CPckCap* lpPC = new CPckCap(dev, file);
                lpPC->setPcapType(dumptype);
                lpPC->setSketchPool(lpSKPool);

                lpPC->starCapture(cntPck, tmCap, ratio);
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return(EXIT_FAILURE);
    }
    std::cerr << "capture end" << std::endl;        

    return 0;    
}

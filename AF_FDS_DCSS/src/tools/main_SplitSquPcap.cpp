/**
 * Copyright (C) 2021
 * hwu(hwu@seu.edu.cn), ???
 * 按时间范围或编号范围切分“依序编号pcap文件”
 **/

#include <iostream>
#include <cstring>
#include "_lib.h/libconfig.h++"
#include "_lib.h/libPcapSE.h"

using namespace std;
using namespace libconfig;

void cutSquPcapFile(string name, int cutType, int iBegin, int iEnd, int payload)
{
    char buffer[256];
    CPacket *lppck;
    size_t icnt = 0;

    if(iEnd>=0 && iEnd<iBegin)
    {
        std::cerr << "error 1" << std::endl;        
        return;
    }

    CSquReader *reader = create_squ_pcap_reader(name.c_str());
    reader->checkSquPcap();
    reader->setMsg(true);
    sprintf(buffer, "%s.squ_cut_type%d_%d-%d.pcap", name.c_str(), cutType, iBegin, iEnd);
    CWriter *pw;
    if(payload==0)
        pw = create_pcap_writer(buffer, 0);
    else
        pw = create_pcap_writer(buffer, 1);
    pw->openWriter();

    bool bWR = false;
    bool bret = reader->openPcap();
    if(bret)
        bret = reader->findSquPcap(iBegin);
    if(bret)
    {
        int iret = 0;
        while(iret>=0)
        {
            iret = reader->readPacket();
            if(iret>=0)
            {
                lppck = reader->getPacket();
                if(lppck->getPckNum()%1000000==0)
                {
                    cout << "cnt :" << lppck->getPckNum() << ", time:" << lppck->getPckOffTime() << endl;
                    
                }

                if(!bWR)  
                {
                    if(cutType==1)  //pck num
                    {
                        if(lppck->getPckNum() >= iBegin)
                            bWR = true;
                    }
                    else
                    {
                        if(lppck->getPckOffTime() >= iBegin)
                            bWR = true;
                    }
                }
                
                if(bWR)
                {
                    if(iEnd > 0)
                    {
                        if(cutType==1)  //pck num 
                        {
                            if(lppck->getPckNum() >= iEnd)
                                bWR = false;
                        }
                        else
                        {
                            if(lppck->getPckOffTime() >= iEnd)
                                bWR = false;
                        }
                    }
                    if(!bWR)
                        break;
                }

                if(bWR && lppck)
                {
                    pw->addPacket(lppck);
                    icnt++;
                }
            }
        }
    }
    std::cout << "cnt file:" << buffer << ", pck count:" << icnt << std::endl;

    delete reader;
    pw->closeWriter();
    delete pw;
}

int main(int argc, char *argv[])
{
    char buf[UINT8_MAX] = "data.cfg";

    if(argc==2)
        strcpy(buf, argv[1]);

    std::cerr << "begin..." << std::endl;        

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
        string name = cfg.lookup("SSPF_first_pcap");    
        cout << "first pcap file name:" << name << endl;

        int cutType;
        cfg.lookupValue("SSPF_type", cutType);
        cout << "split type(type 0--time, 1--Pck. No.): " << cutType << endl;

        int iBegin, iEnd;
        cfg.lookupValue("SSPF_begin", iBegin);
        cfg.lookupValue("SSPF_end", iEnd);
        cout << "split begin:" << iBegin << ", end:" << iEnd << endl;

        int payload;
        cfg.lookupValue("SSPF_payload", payload);

        cutSquPcapFile(name, cutType, iBegin, iEnd, payload);
//        getSquPcap(name.c_str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return(EXIT_FAILURE);
    }

    return 0;
}

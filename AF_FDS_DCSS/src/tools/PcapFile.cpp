#include <iostream>
#include "tools/PcapFile.h"

using namespace std;

PcapFile::PcapFile(string fname)
{
    filename = fname;

    bFin = false;
    reader = NULL;
}

PcapFile::~PcapFile()
{
    delReader();
}

bool PcapFile::getPcapInfo()
{
    bool bout = true;
    CPacket *lppck;

    cout << filename << endl;

    CReader *pr = create_pcap_reader(filename.c_str());
    iPckCount = 0;
    dbDuring = 0;

    bool bret = pr->openPcap();
    if(bret){
        int iret = 0;
        while(iret>=0){
            iret = pr->readPacket();
            if(iret>=0)
            {
                if(iPckCount==0)
                    dbBeginTM = pr->getBaseTM();
                lppck = pr->getPacket();
                dbDuring = lppck->getPckOffTime();
                iPckCount ++;
                if(iPckCount%1000000 == 0)
                    cout << "-";
            }
        }
    }
    else
        bout  = false;

    cout << endl;
    cout << "    during:" << dbDuring << ", Pck count:" << iPckCount << endl;
    delete pr;

    return bout;
}

void PcapFile::delReader()
{
    if(reader)
    {
        delete reader;
        reader = NULL;
    }
    bFin = true;
}


bool PcapFile::firstPacket()
{
    bool bout  = false;
    CPacket* lppck;

    delReader();

    bFin = false;

    reader = create_pcap_reader(filename.c_str());
    bool bret = reader->openPcap();
    if(bret)
    {
        int iret = reader->readPacket();
        if(iret>=0 && lppck)
        {
            lppck = reader->getPacket();
            if(lppck)
            {
                double tm = lppck->getPckOffTime();
                lppck->setPckGMTTime(dbBeginTM + tm);
                bout = true;
            }
            else
                delReader();
        }
        else
            delReader();
    }
    else
        delReader();
    
    return bout;
}

bool PcapFile::nextPacket()
{
    bool bout = false;
    CPacket* lppck;

    if(reader)
    {
        int iret = reader->readPacket();
        if(iret>=0)
        {
            lppck = reader->getPacket();
            if(lppck)
            {
                double tm = lppck->getPckOffTime();
                lppck->setPckGMTTime(dbBeginTM + tm);
                bout = true;
            }
            else
                delReader();
        }
        else   
            delReader();
    }
    return bout;
}

CPacket* PcapFile::getCurPck()
{
    CPacket* lppck = NULL;

    if(reader)
    {
        lppck = reader->getPacket();
    }   

    return lppck; 
}
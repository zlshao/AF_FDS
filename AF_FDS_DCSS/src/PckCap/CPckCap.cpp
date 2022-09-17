#include "PckCap/CPckCap.h"
#include <iostream>

using namespace std;

CPckCap::CPckCap(string dev, string file)
{
    strDev = dev;
    strFile = file;

    lppck = create_packet();
    CPckCap::pPC = this;
}

CPckCap::~CPckCap()
{
    delete lppck;
}

void CPckCap::setPcapType(int type)
{
    typeCap = type;
}

int CPckCap::starCapture(int64_t maxPck, uint32_t maxTime, int sample)
{
    int iout = -1;
    smpCap = sample;
    tmMax = maxTime;
    curPck = 0;

    char errbuf[PCAP_ERRBUF_SIZE];    /* Error string */    
    handleDev = pcap_open_live(strDev.c_str(), UINT16_MAX, 1, 1000, errbuf);
    if (handleDev == NULL) 
        cout << "Couldn't open device " << strDev << ": " << errbuf << endl;
    else
    {
        out_pcap = NULL;
        if(typeCap != 0)
        {
            out_pcap  = pcap_dump_open(handleDev, strFile.c_str());
            if(!out_pcap)
                cout << "Couldn't create pcap file " << strFile << endl;
        }
        pcap_loop(handleDev, maxPck, processPck, (u_char *)out_pcap);
        /* And close the session */
        pcap_close(handleDev);            

        if(out_pcap)
        {
            /*flush buff*/
            pcap_dump_flush(out_pcap);
        
            pcap_dump_close(out_pcap);
        }
        iout = 0;
    }
    return iout;
}

void CPckCap::processPck(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
    if(pPC)
        pPC->procPck(arg, pkthdr, packet);
}

void CPckCap::procPck(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
    if(curPck==0)
    {
        calBeginTime(pkthdr);
    }
    curPck ++;
    //show step
    if(curPck%65536==0)
        cout << curPck << endl;

    bool bSample = false;
    if(smpCap==1 || curPck%smpCap==0)
        bSample = true;

    if(bSample)
    {
        if(!sketchPck(pkthdr, packet))
            pcap_breakloop(handleDev);
    }
    if((typeCap==1 && bSample) || typeCap==2)
        pcap_dump(arg, pkthdr, packet);
}


bool CPckCap::sketchPck(const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
    bool bout = true;
    if(pkthdr->ts.tv_sec > tmEnd)
    {
        bout = false;
        cout << "during time:" << pkthdr->ts.tv_sec - tmBegin << endl;
    }
    if(lpSKPool && bout)
    {
        lppck->set_pcap_pkthdr(&(pkthdr->ts), pkthdr->caplen, pkthdr->len);
        int ret = lppck->getPckDetailFromBuffer(packet, pkthdr->caplen, 1);
        if(ret==6 || ret==17)
        {
            lpSKPool->procPacket(lppck);
        }
    }
    return bout;
}

void CPckCap::calBeginTime(const struct pcap_pkthdr *pkthdr)
{
    double time = pkthdr->ts.tv_usec;
    time /= 1000000;
    time += pkthdr->ts.tv_sec;
    tmBegin = pkthdr->ts.tv_sec;
    tmEnd = tmBegin + tmMax;
    if(lppck)
        lppck->setBeginTime(time);
}

CPckCap* CPckCap::pPC = NULL;


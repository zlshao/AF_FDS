#ifndef USE_LIBPCAP_H
#define USE_LIBPCAP_H

#include <cstdlib>
#include <pcap.h>
#include <stdint.h>
#include <string>
#include "_lib.h/libPacketSE.h"
#include "_lib.h/libSketchPoolSE.h"

//void processPck(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet);  

class CPckCap
{
public:
    CPckCap(std::string dev, std::string file);
    ~CPckCap();
public:
    void setPcapType(int type);  //0 -- not capture, 1 -- sample packet, 2 -- all packet
public:
    int starCapture(int64_t maxPck, uint32_t maxTime, int sample);
public:     //callback
    static void processPck(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet);
public:
    void procPck(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet);

    bool sketchPck(const struct pcap_pkthdr *pkthdr, const u_char *packet);
    void calBeginTime(const struct pcap_pkthdr *pkthdr);

    void setSketchPool(ISketchPool* lpSketch) {lpSKPool = lpSketch;}
private:
    CPacket* lppck;
    pcap_t* handleDev;     
    pcap_dumper_t* out_pcap; 
private:
    static CPckCap* pPC;
    ISketchPool* lpSKPool;
private:
    std::string strDev;
    std::string strFile;
    uint32_t tmBegin;
    uint32_t tmEnd;
    uint32_t tmMax;
private:
    int64_t curPck;
    int smpCap;
    int typeCap;
};

#endif

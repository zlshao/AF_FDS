#ifndef PCAP_FILE_H
#define PCAP_FILE_H

#include "_lib.h/libPcapSE.h"

class PcapFile
{
private:
    std::string filename;
    double dbDuring;
    size_t iPckCount;
    double dbBeginTM;
public:
    double getDuring(){return dbDuring;}    
    size_t getPckCnt(){return iPckCount;}
    void setBeginTM(double tm){dbBeginTM = tm;}
    double getBeginTM(){return dbBeginTM;}
    std::string getFilename(){return filename;}
public:
    bool getPcapInfo();    
private:
    bool bFin;
    CReader* reader;
private:
    void delReader();
public:
    bool getFin(){return bFin;}

    bool firstPacket();
    bool nextPacket();
    CPacket* getCurPck();
public:
    PcapFile(std::string fname);
    ~PcapFile();
};

#endif
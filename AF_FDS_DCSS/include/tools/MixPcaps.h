#ifndef MIX_PCAPS_H
#define MIX_PCAPS_H

#include <list>
#include "_lib.h/libPcapSE.h"
#include "_lib.h/libHashSE.h"
#include "PcapFile.h"

class MixPcaps
{
private:
    std::string fMainFile;
    std::string fAddPath;

    std::list<PcapFile*> lstPcap;
    PcapFile* lpMain;
    int fFix;
    int fPayload;
private:
    void checkPath();
    bool checkPcapName(const char* fn);
    bool checkFile(std::string pathfile);

    void calBaseTime(int rand);
    void initPcapList();
    void makeMixPcap(int rand);
    PcapFile* getEarliestPck();

    double getRand();
public:
    bool checkPcaps();
    void mixingData(int rseed);
public:
    MixPcaps(std::string pcapF, std::string addP, int fix, int pl);
    ~MixPcaps();
};

#endif
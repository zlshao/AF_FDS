#include <iostream>
#include <bits/stdc++.h>
#include "tools/MixPcaps.h"
#include "winlin/winlinux.h"
/*
#ifdef _WIN32
    #include <io.h>
#elif __linux__
    #include <sys/types.h>
    #include <dirent.h>
#endif
*/
using namespace std;

const double MIN_DURING = 0.001;
const int MIN_PACKET = 10;
const double MIN_BEGINTM = 0.02;

MixPcaps::MixPcaps(string pcapF, string addP, int fix, int pl)
{
    fMainFile = pcapF;
    fAddPath = addP;
    fFix = fix;
    fPayload = pl;

    lpMain = NULL;
}

MixPcaps::~MixPcaps()
{

}

bool MixPcaps::checkPcaps()
{
    bool bout = false;

    cout << "check pcap files" << endl;
    //check main file
    lpMain = new PcapFile(fMainFile);
    if(lpMain->getPcapInfo() && 
       lpMain->getDuring() > MIN_DURING && 
       lpMain->getPckCnt() > MIN_PACKET)
    {
        bout = true;
        lstPcap.push_back(lpMain);
        //check path
        checkPath();
    }
    else
    {
        delete lpMain;
        lpMain = NULL;
    }

    return bout;
}

void MixPcaps::checkPath()
{
    if(fAddPath.length()>0)
    {
        vector<string> vctFN;
        if(iterPathPcaps(fAddPath, &vctFN))
        {
            for(vector<string>::iterator iter=vctFN.begin(); iter!=vctFN.end(); ++iter)
            {
                string strFN = *iter;
                if(strFN.length()>0)
                    checkFile(strFN);
            }
        }
    }
}

bool MixPcaps::checkFile(string pathfile)
{
    bool bout = false;

    PcapFile* lpPF = new PcapFile(pathfile);
    if(lpPF->getPcapInfo() && 
        lpPF->getDuring() > MIN_DURING && 
        lpPF->getPckCnt() > MIN_PACKET)
    {
        lstPcap.push_back(lpPF);
        bout = true;
    }
    else
        delete lpPF;

    return bout;
}

/*
bool MixPcaps::checkFile(char* pathfile, char* fname)
{
    bool bout = false;
    if(checkPcapName(fn))
    {
        string strFN = fAddPath + fn;
        PcapFile* lpPF = new PcapFile(strFN);
        if(lpPF->getPcapInfo() && 
            lpPF->getDuring() > MIN_DURING && 
            lpPF->getPckCnt() > MIN_PACKET)
        {
            lstPcap.push_back(lpPF);
            bout = true;
        }
        else
            delete lpPF;
    }

    return bout;
}
*/

bool MixPcaps::checkPcapName(const char* filename)
{
    bool bout = false;

    string fnn = filename;
    if(fnn.size()>5)
    {
        string sub = fnn.substr(fnn.size()-5,5);
        transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
        if(sub==".pcap")
            bout = true;
    }
    if(!bout && fnn.size()>7)
    {
        string sub = fnn.substr(fnn.size()-7,7);
        transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
        if(sub==".pcapng")
            bout = true;
    }

    return bout;
}


void MixPcaps::mixingData(int rseed)
{
    time_t timeB, timeE;

    timeB = time(NULL);

    //calculate base time
    calBaseTime(rseed);
    //initial
    initPcapList();
    //make new pcap
    makeMixPcap(rseed);

    timeE = time(NULL);
}

double MixPcaps::getRand()
{
    double dbout = rand()%10000;
    dbout = dbout/10000;
    return dbout;
}

void MixPcaps::calBaseTime(int rand)
{
    double tmDuring, tmBase;
    PcapFile* lpPF;

    //srand(rand);
    if(lpMain)
    {
        tmDuring = lpMain->getDuring();
        tmBase = lpMain->getBeginTM();

        list<PcapFile*>::iterator iter=lstPcap.begin();
        iter++;
        for(; iter != lstPcap.end(); ++iter )
        {
            lpPF = *iter;
            if(lpPF)
            {
                if(fFix < 0)
                {
                    double tmd = lpPF->getDuring();
                    double tmNew;
                    if(tmd < tmDuring)
                    {
                        tmNew = tmBase + (tmDuring - tmd) * getRand();
                        lpPF->setBeginTM(tmNew);
                    }
                    else
                    {
                        tmNew = tmBase + tmDuring * MIN_BEGINTM * getRand();
                        lpPF->setBeginTM(tmNew);
                    }
                }
                else
                {
                    double tm = 0.02*getRand();
                    lpPF->setBeginTM(tmBase+fFix+tm);
                }
                cout << lpPF->getFilename() << ", starting time:" << lpPF->getBeginTM()-tmBase << endl;
            }
        }
    }
}

void MixPcaps::initPcapList()
{
    PcapFile* lpPF;

    for(list<PcapFile*>::iterator iter=lstPcap.begin(); iter!=lstPcap.end(); ++iter)
    {
        lpPF = *iter;
        if(lpPF)
        {
            lpPF->firstPacket();
        }
    }

}

void MixPcaps::makeMixPcap(int rand)
{
    char buffer[UINT8_MAX];
    PcapFile* lpPF;

    //new writer
    sprintf(buffer, "%s.Mixed_rseed-%d.pcap", fMainFile.c_str(), rand);
    cout << buffer << endl;

    size_t icount = 0;
    CWriter *pw;
    if(fPayload==1)
        pw = create_pcap_writer(buffer, 1);
    else
        pw = create_pcap_writer(buffer, 0);
    pw->openWriter();

    //find earliest pck
    lpPF = getEarliestPck();
    while(lpPF)
    {
        CPacket* lppck = lpPF->getCurPck();
        if(lppck)
        {
            pw->addPacket(lppck);
            icount ++;
            if(icount%1000000==0)
                cout << "+";
        }
        lpPF->nextPacket();
        lpPF = getEarliestPck();
    }

    //close 
    pw->closeWriter();
    delete pw;       

    cout << endl;
    cout << "packet count:" << icount << endl;
}

PcapFile* MixPcaps::getEarliestPck()
{
    CPacket* lpCur = NULL;
    PcapFile *lpPF, *lpPFOut = NULL;
    double maxtime = 1e60;

    if(lstPcap.empty())
        return lpPFOut;
    for(list<PcapFile*>::iterator iter=lstPcap.begin(); iter!=lstPcap.end(); ++iter)
    {
        lpPF = *iter;
        if(lpPF && !lpPF->getFin())
        {
            lpCur = lpPF->getCurPck();
            if(lpCur->getPckGMTTime() < maxtime)
            {
                maxtime = lpCur->getPckGMTTime();
                lpPFOut = lpPF;
            }
        }   
    } 
    return lpPFOut;
}

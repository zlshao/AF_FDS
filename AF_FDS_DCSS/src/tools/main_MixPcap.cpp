/**
 * Copyright (C) 2021
 * hwu(hwu@seu.edu.cn), ???
 * pcap数据混合，主数据文件和路径下所有文件混合。
 **/

#include <iostream>
#include <cstring>
#include "_lib.h/libconfig.h++"
#include "tools/MixPcaps.h"

using namespace std;
using namespace libconfig;


void mixPcap(string pcapF, string addP, int seed, int fix, int pl)
{
    srand(seed);
    MixPcaps* mp = new MixPcaps(pcapF, addP, fix, pl);
    //check main pcap, add files
    if(mp->checkPcaps())
    {
        mp->mixingData(seed);
    }
    else
        std::cerr << "data.cfg config error!" << std::endl;        
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
        string mpmName = cfg.lookup("MP_main_file");    
        cout << "Mix pcap, main file name: " << mpmName << endl;

        string addPath = cfg.lookup("MP_mixed_files_path");
        cout << "Mix pcap, mixed files path: " << addPath << endl;

        int iRandomSeed = 22;
        cfg.lookupValue("MP_random_seed", iRandomSeed);
        cout << "Mix pcap, random seed: " << iRandomSeed << endl;

        int ipl = 0;
        cfg.lookupValue("MP_payload", ipl);

        int iFix = 0;
        cfg.lookupValue("MP_start_time", iFix);

        mixPcap(mpmName, addPath, iRandomSeed, iFix, ipl);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return(EXIT_FAILURE);
    }

    return 0;
}

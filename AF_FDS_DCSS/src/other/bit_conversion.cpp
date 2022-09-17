#include "other/bit_conversion.h"

int calSampleRate(int num)
{
    int iout;

    switch (num)
    {
    case 0:
        iout = 1;
        break;
    case 1:
        iout = 8;
        break;
    case 2:
        iout = 16;
        break;
    case 3:
        iout = 32;
        break;
    case 4:
        iout = 64;
        break;
    case 5:
        iout = 128;
        break;
    case 6:
        iout = 256;
        break;
    case 7:
        iout = 512;
        break;
    case 8:
        iout = 1024;
        break;
    case 9:
        iout = 2048;
        break;
    case 10:
        iout = 4096;
        break;
    case 11:
        iout = 8192;
        break;
    case 12:
        iout = 16384;
        break;
    case 13:
        iout = 32768;
        break;
    case 14:
        iout = 65536;
        break;
    default:
        iout = 256;
        break;
    }
    return iout;
}

uint32_t getStringValue(std::string str)
{
    uint32_t ulout = 0;
    std::string::size_type found;

    found = str.find("a");
    if (found!=std::string::npos)
        ulout |= 1;
    found = str.find("b");
    if (found!=std::string::npos)
        ulout |= (1 << 1);
    found = str.find("c");
    if (found!=std::string::npos)
        ulout |= (1 << 2);
    found = str.find("d");
    if (found!=std::string::npos)
        ulout |= (1 << 3);
    found = str.find("e");
    if (found!=std::string::npos)
        ulout |= (1 << 4);
    found = str.find("f");
    if (found!=std::string::npos)
        ulout |= (1 << 5);
    found = str.find("g");
    if (found!=std::string::npos)
        ulout |= (1 << 6);
    found = str.find("h");
    if (found!=std::string::npos)
        ulout |= (1 << 7);
    found = str.find("i");
    if (found!=std::string::npos)
        ulout |= (1 << 8);
    found = str.find("j");
    if (found!=std::string::npos)
        ulout |= (1 << 9);
    found = str.find("k");
    if (found!=std::string::npos)
        ulout |= (1 << 10);
    found = str.find("l");
    if (found!=std::string::npos)
        ulout |= (1 << 11);
    found = str.find("m");
    if (found!=std::string::npos)
        ulout |= (1 << 12);
    found = str.find("n");
    if (found!=std::string::npos)
        ulout |= (1 << 13);
    found = str.find("o");
    if (found!=std::string::npos)
        ulout |= (1 << 14);
    found = str.find("p");
    if (found!=std::string::npos)
        ulout |= (1 << 15);
    found = str.find("q");
    if (found!=std::string::npos)
        ulout |= (1 << 16);
    found = str.find("r");
    if (found!=std::string::npos)
        ulout |= (1 << 17);
    found = str.find("s");
    if (found!=std::string::npos)
        ulout |= (1 << 18);
    found = str.find("t");
    if (found!=std::string::npos)
        ulout |= (1 << 19);
    found = str.find("u");
    if (found!=std::string::npos)
        ulout |= (1 << 20);
    found = str.find("v");
    if (found!=std::string::npos)
        ulout |= (1 << 21);
    found = str.find("0");
    if (found!=std::string::npos)
        ulout |= (1 << 22);
    found = str.find("1");
    if (found!=std::string::npos)
        ulout |= (1 << 23);
    found = str.find("2");
    if (found!=std::string::npos)
        ulout |= (1 << 24);
    found = str.find("3");
    if (found!=std::string::npos)
        ulout |= (1 << 25);
    found = str.find("4");
    if (found!=std::string::npos)
        ulout |= (1 << 26);
    found = str.find("5");
    if (found!=std::string::npos)
        ulout |= (1 << 27);
    found = str.find("6");
    if (found!=std::string::npos)
        ulout |= (1 << 28);
    found = str.find("7");
    if (found!=std::string::npos)
        ulout |= (1 << 29);
    found = str.find("8");
    if (found!=std::string::npos)
        ulout |= (1 << 30);
    found = str.find("9");
    if (found!=std::string::npos)
        ulout |= (1 << 31);

    return ulout;
}

uint64_t convStringValue(std::string str)
{
    uint64_t ulout = 0;
    std::string::size_type found;

    found = str.find("a");
    if (found!=std::string::npos)
        ulout |= (uint64_t)1;
    found = str.find("b");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 1);
    found = str.find("c");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 2);
    found = str.find("d");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 3);
    found = str.find("e");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 4);
    found = str.find("f");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 5);
    found = str.find("g");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 6);
    found = str.find("h");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 7);
    found = str.find("i");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 8);
    found = str.find("j");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 9);
    found = str.find("k");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 10);
    found = str.find("l");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 11);
    found = str.find("m");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 12);
    found = str.find("n");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 13);
    found = str.find("o");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 14);
    found = str.find("p");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 15);
    found = str.find("q");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 16);
    found = str.find("r");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 17);
    found = str.find("s");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 18);
    found = str.find("t");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 19);
    found = str.find("u");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 20);
    found = str.find("v");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 21);
    found = str.find("w");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 22);
    found = str.find("x");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 23);
    found = str.find("y");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 24);
    found = str.find("z");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 25);

    found = str.find("A");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 26);
    found = str.find("B");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 27);
    found = str.find("C");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 28);
    found = str.find("D");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 29);
    found = str.find("E");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 30);
    found = str.find("F");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 31);
    found = str.find("G");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 32);
    found = str.find("H");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 33);
    found = str.find("I");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 34);
    found = str.find("J");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 35);
    found = str.find("K");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 36);
    found = str.find("L");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 37);
    found = str.find("M");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 38);
    found = str.find("N");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 39);
    found = str.find("O");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 40);
    found = str.find("P");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 41);
    found = str.find("Q");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 42);
    found = str.find("R");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 43);
    found = str.find("S");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 44);
    found = str.find("T");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 45);
    found = str.find("U");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 46);
    found = str.find("V");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 47);
    found = str.find("W");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 48);
    found = str.find("X");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 49);
    found = str.find("Y");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 50);
    found = str.find("Z");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 51);

    found = str.find("0");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 52);
    found = str.find("1");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 53);
    found = str.find("2");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 54);
    found = str.find("3");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 55);
    found = str.find("4");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 56);
    found = str.find("5");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 57);
    found = str.find("6");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 58);
    found = str.find("7");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 59);
    found = str.find("8");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 60);
    found = str.find("9");
    if (found!=std::string::npos)
        ulout |= ((uint64_t)1 << 61);

    return ulout;
}
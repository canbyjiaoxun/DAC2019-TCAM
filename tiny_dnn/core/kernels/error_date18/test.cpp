// file floattobinary.cc
#include <inttypes.h> // for uint32_t
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define BIT_CHUNK 20
#define NUM_FREQ 40 // number of frequent patterns saved in BF
#define ERROR_RATE_FC 1000
#define ERROR_RATE_CONV1 1000

using namespace std;

void floatToBinary(float f, string& str)
{
    union { float f; uint32_t i; } u;
    u.f = f;
    str.clear();

    for (int i = 0; i < 32; i++)
    {
        if (u.i % 2)  str.push_back('1');
        else str.push_back('0');
        u.i >>= 1;
    }

    // Reverse the string since now it's backwards
    string temp(str.rbegin(), str.rend());
    str = temp;
    std::cout << str; 
}

int main()
{
   string s; 
   floatToBinary(0.45, &s); 
}




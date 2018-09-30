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

int error_cnt_fc(0);
int error_cnt_conv1(0);
string fname("./freqPatterns.txt");
struct prof_data_struct{
	string op1;
	string op2;
}

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
}

vector patternsToVector(string fname)
{
	fstream f;
	f.open(fname, fstream::in);
	vector<string> freq_patterns;
	freq_patterns.reserve(NUM_FREQ);
	string a, b, c;
	
	while (f >> a >> b >> c)
	{
		string astr, bstr, s_vec;
		floatToBinary(atof(a), &astr);
		floatToBinary(atof(b), &bstr);
		strcat(astr,bstr);
		strcpy (s_vec,astr.substr(0,BIT_CHUNK));
		strcat (s_vec,bstr.substr(0,BIT_CHUNK));
		freq_patterns.push_back(s_vec);
	}
	
	return freq_patterns;
    
}

vector outputsToVector(string fname)
{
	fstream f;
	f.open(fname, fstream::in);
	vector<string> freq_outputs;
	freq_outputs.reserve(NUM_FREQ);
	
	string a, b, c;
	while (f >> a >> b >> c)
	{
		freq_outputs.push_back(c);
	}
	
	return freq_outputs;
    
}



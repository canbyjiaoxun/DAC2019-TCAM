#include <assert.h>
#include <random>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count_adder = 0;
int max_count_adder = 100000;
std::poisson_distribution<> pd_adder((int)(1.0/ADDER_ERROR_RATE*32));
std::random_device rd_adder;
std::mt19937 gen_adder(rd_adder());

std::random_device rd;
std::mt19937 gen(rd());


template<size_t size> 
typename std::bitset<size> random_bitset_flip1() {
	 typename std::bitset<size> bits;
   for ( int n = 0; n < size; n++ ) { 
         bits[n] = 0;
   }
	 srand(time(NULL));
	 bits[rand()%size] = 1; 
   return bits;
}       


inline float genErrorFloat(double errorRate, float orig) {
        union Flip
        {
                float input;
                long output;
        } data, ret;
        data.input = orig;
    
        //auto mask = random_bitset<sizeof(float)>(errorRate);
	      auto mask = random_bitset_flip1<sizeof(int32_t)>();
        std::bitset<sizeof(float)> bits(data.output);
        ret.output = ( bits ^ mask ).to_ullong();
        return ret.input;
}

int main(){
        orig = 1.0; 
        union Flip
        {
                float input;
                long output;
        } data, ret;
        data.input = orig;
        auto mask = random_bitset_flip1<sizeof(float)>(); 
        printf();
        //std::bitset<sizeof(float)> bits(data.output);

  
}

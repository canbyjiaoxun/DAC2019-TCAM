#include <assert.h>
#include <random>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define ADDER_ERROR_RATE 0.00001
//#define MULTI_ERROR_RATE 0.00001
#ifndef BIT_ERROR
#define BIT_ERROR
namespace tiny_dnn {
namespace kernels {
int count_adder = 0;
int max_count_adder = 100000;
std::poisson_distribution<> pd_adder((int)(1.0/ADDER_ERROR_RATE));
std::random_device rd_adder;
std::mt19937 gen_adder(rd_adder());

std::random_device rd;
std::mt19937 gen(rd());

template<size_t size> 
typename std::bitset<size> random_bitset( double p = 0.5) {
	std::bernoulli_distribution d(p);
	typename std::bitset<size> bits;
        for ( int n = 0; n < size; n++ ) { 
                bits[n] = d(gen);
        } 
        return bits;
}       

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

inline double genErrorDouble(double errorRate, double orig) {
        union Flip
        {
                double input;
                long long output;
        } data, ret;
        data.input = orig;
    
        auto mask = random_bitset<sizeof(double)>(errorRate);
        std::bitset<sizeof(double)> bits(data.output);
        ret.output = ( bits ^ mask ).to_ullong();
        return ret.input;
}

inline int32_t genError32(int32_t orig) {
	union Flip
	{
		int32_t input;
		int output;	
	} data, ret;
	data.input = orig;
	
	//auto mask = random_bitset<sizeof(int32_t)>(errorRate);
	auto mask = random_bitset_flip1<sizeof(int32_t)>();
	std::bitset<sizeof(int32_t)> bits(data.output);
	ret.output = ( bits ^ mask).to_ulong();
	return ret.input;
} 

inline int32_t flip_int(int32_t orig, int bit_pos) {
        int32_t flip_orig; 
        flip_orig = orig ^ (1 << bit_pos);
        //printf("orig %d, bit_pos %d, flip_orig %d\n", orig, bit_pos, flip_orig);
        return flip_orig; 
}


inline float genErrorFloat(double errorRate, float orig) {
        union Flip
        {
                float input;
                long output;
        } data, ret;
        data.input = orig;
    
        auto mask = random_bitset<sizeof(float)>(errorRate);
        std::bitset<sizeof(float)> bits(data.output);
        ret.output = ( bits ^ mask ).to_ullong();
        return ret.input;
}


/*
inline float bitflip(float orig, int bit_pos) {
        

}
*/

int count_multi = 0;
int max_count_multi = 100000;
std::poisson_distribution<> pd_multi((int)(1.0/MULTI_ERROR_RATE));
std::random_device rd_multi;
std::mt19937 gen_multi(rd_multi());

/*
inline double FlipAdder(double operand) {
	if ( count_adder > max_count_adder ) {
		count_adder = 0;
		max_count_adder = pd_adder(gen_adder);
		double error = genErrorDouble(ADDER_ERROR_RATE, operand);
		return error;		
	} else {
		count_adder++;
		return operand;
	}
}
*/

inline float flip_float(float orig, int bit_pos) { 
        typedef union mytypes_t {
                float input;
		            unsigned int output;
        }f2int; 
        f2int f2int_x; 
        f2int_x.input = orig;
        f2int_x.output = f2int_x.output ^ (1 << (bit_pos));
        //printf("orig: %f, bit_pos: %d, new: %f\n", orig, bit_pos, f2int_x.input);
        return f2int_x.input; 
}

inline float FlipAdder(float operand) {
   //srand(time(NULL));
   //float TER_ADD = 0.01;
   //flip each bit according to BER; Xun 08/17/17
   int i;
   float temp_res = operand; 
   double decision = (double)rand() / (double)RAND_MAX; 
   /* 
   float BER[32] = {0.1, };
   for (i = 0; i < 32; i++)
   {
       double decision = (double)rand() / (double)RAND_MAX; 
       if (decision < BER[i])
           temp_res = flip_float(temp_res, i);
   }
   return temp_res;
   */ 

   // flip a random bit position based on its BER; Xun 07/20/17
   if (decision < TER_ADD) 
   {
       int bit_pos = rand()%32; 
       float error = flip_float(operand, bit_pos);  
       return error;		
   }
   else 
       return operand;
}

inline float FlipMulti(float operand) {
   //srand(time(NULL));
   double decision = (double)rand() / (double)RAND_MAX; 
   //float TER = 0;
   if (decision < TER_MUL) 
   {
       int bit_pos = rand()%32; 
       float error = flip_float(operand, bit_pos);  
       return error;		
   }
   else 
       return operand; 
}


inline int32_t FlipAdder32(int32_t operand) {
	if ( count_adder > max_count_adder ) {
		count_adder = 0;
		max_count_adder = pd_adder(gen_adder);
		//int32_t error = genError32(operand);
                /* new flip method */ 
		srand(time(NULL));
		int bit_pos = rand()%32; 
		int32_t error = flip_int(operand, bit_pos);
		return error;		
	} else {
		count_adder++;
		return operand;
	}
}


/*
inline float FlipAdder(float operand) {
	if ( count_adder > max_count_adder ) {
		count_adder = 0;
		max_count_adder = pd_adder(gen_adder);
		//float error = genErrorDouble(ADDER_ERROR_RATE, operand);
		srand(time(NULL));
		int bit_pos = rand()%32; 
                float error = flip_float(operand, bit_pos);  
		return error;		
	} else {
		count_adder++;
		return operand;
	}
}
*/

/*
inline float FlipMulti(float operand) {
	if ( count_multi > max_count_multi ) {
	 	count_multi = 0;
		max_count_multi = pd_multi(gen_multi);
		//double error = genError32(operand);
		srand(time(NULL));
		int bit_pos = rand()%32; 
                float error = flip_float(operand, bit_pos);  
		return error;
	} else {
		count_multi++;
		return operand;
	}
}
*/

/*
inline double FlipMulti(double operand) {
	if ( count_multi > max_count_multi ) {
		count_multi = 0;
		max_count_multi = pd_multi(gen_multi);
		double error = genError32(operand);
		return error;
	} else {
		count_multi++;
		return operand;
	}
}
*/

inline int32_t FlipMulti32(int32_t operand) {
	if ( count_multi > max_count_multi ) {
		count_multi = 0;
		max_count_multi = pd_multi(gen_multi);
		int32_t error = genError32(operand);
		return error;
	} else {
		count_multi++;
		return operand;
	}
}



}
}
#endif

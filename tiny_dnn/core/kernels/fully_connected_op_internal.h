/*
    Copyright (c) 2016, Taiga Nomi, Edgar Riba
    All rights reserved.

    Use of this source code is governed by a BSD-style license that can be found
    in the LICENSE file.
*/
#pragma once

#include "tiny_dnn/core/params/fully_params.h"

#include <bitset>
#include <random>

namespace tiny_dnn {
namespace kernels {

//fully layer freq op 
inline std::map<std::tuple<std::string, std::string>, float> BF4(){
    std::map<std::tuple<std::string, std::string>, float> freq_pattern; 
    //write dic 
    
    freq_pattern[std::make_tuple("101111100", "001111110")] = -0.09375;
    freq_pattern[std::make_tuple("001111100", "101111110")] = -0.09375;
    freq_pattern[std::make_tuple("101111011", "001111110")] = -0.046875;
    freq_pattern[std::make_tuple("001111100", "001111110")] = 0.09375;
    freq_pattern[std::make_tuple("101111011", "101111110")] = 0.046875;
    freq_pattern[std::make_tuple("101111100", "101111110")] = 0.09375;
    freq_pattern[std::make_tuple("001111011", "101111110")] = -0.046875;
    freq_pattern[std::make_tuple("001111011", "001111110")] = 0.046875;
    freq_pattern[std::make_tuple("101111010", "001111110")] = -0.0234375;
    freq_pattern[std::make_tuple("101111010", "101111110")] = 0.0234375;
    freq_pattern[std::make_tuple("001111010", "001111110")] = 0.0234375;
    freq_pattern[std::make_tuple("001111010", "101111110")] = -0.0234375;
    freq_pattern[std::make_tuple("101111001", "001111110")] = -0.01171875;
    freq_pattern[std::make_tuple("001111001", "101111110")] = -0.01171875;
    freq_pattern[std::make_tuple("101111001", "101111110")] = 0.01171875;
    freq_pattern[std::make_tuple("001111001", "001111110")] = 0.01171875;
    freq_pattern[std::make_tuple("101111000", "001111110")] = -0.005859375;
    freq_pattern[std::make_tuple("001111000", "101111110")] = -0.005859375;
    freq_pattern[std::make_tuple("101111000", "101111110")] = 0.005859375;
    freq_pattern[std::make_tuple("001111101", "001111110")] = 0.1875;
    freq_pattern[std::make_tuple("001111000", "001111110")] = 0.005859375;
    freq_pattern[std::make_tuple("001111101", "101111110")] = -0.1875;
    freq_pattern[std::make_tuple("001110111", "101111110")] = -0.0029296875;
    freq_pattern[std::make_tuple("101110110", "001111110")] = -0.00146484375;
    freq_pattern[std::make_tuple("101111011", "001111101")] = -0.0234375;
    freq_pattern[std::make_tuple("101111100", "001111101")] = -0.046875;
    freq_pattern[std::make_tuple("001110111", "001111110")] = 0.0029296875;
    freq_pattern[std::make_tuple("101111011", "101111101")] = 0.0234375;
    freq_pattern[std::make_tuple("001111100", "101111101")] = -0.046875;
    freq_pattern[std::make_tuple("101110111", "101111110")] = 0.0029296875;
    /*
    freq_pattern[std::make_tuple("001111100", "001111101")] = 0.046875;
    freq_pattern[std::make_tuple("101111101", "001111110")] = -0.1875;
    freq_pattern[std::make_tuple("101111101", "101111110")] = 0.1875;
    freq_pattern[std::make_tuple("001110110", "001111110")] = 0.00146484375;
    freq_pattern[std::make_tuple("001111011", "001111101")] = 0.0234375;
    freq_pattern[std::make_tuple("001111011", "101111101")] = -0.0234375;
    freq_pattern[std::make_tuple("101111100", "101111101")] = 0.046875;
    freq_pattern[std::make_tuple("101110111", "001111110")] = -0.0029296875;
    freq_pattern[std::make_tuple("101111010", "001111101")] = -0.01171875;
    freq_pattern[std::make_tuple("101110110", "101111110")] = 0.00146484375;
    freq_pattern[std::make_tuple("001110110", "101111110")] = -0.00146484375;
    freq_pattern[std::make_tuple("101111010", "101111101")] = 0.01171875;
    freq_pattern[std::make_tuple("001111010", "001111101")] = 0.01171875;
    freq_pattern[std::make_tuple("101111011", "001111100")] = -0.01171875;
    freq_pattern[std::make_tuple("101111011", "101111100")] = 0.01171875;
    freq_pattern[std::make_tuple("001111010", "101111101")] = -0.01171875;
    freq_pattern[std::make_tuple("101110100", "001111110")] = -0.0003662109375;
    freq_pattern[std::make_tuple("001110101", "101111110")] = -0.000732421875;
    freq_pattern[std::make_tuple("001111100", "101111100")] = -0.0234375;
    freq_pattern[std::make_tuple("001111100", "001111100")] = 0.0234375;
    */
    return freq_pattern; 
}

//approximate bloom filter for fully layer 
int hit_fully = 0; 
int total_fully = 0; 
inline float check_BV_fully(float op1, float op2) {
    total_fully ++; 
    float temp_mul; 
    std::map<std::tuple<std::string, std::string>, float> freq_pattern;
    freq_pattern = BF4(); 
    std::string op1_str = floatToBinary(op1);
    std::string op2_str = floatToBinary(op2);
    if (freq_pattern.find(std::make_tuple(op1_str.substr(0,9), op2_str.substr(0,9))) != freq_pattern.end())
    {
       hit_fully ++; 
       temp_mul = freq_pattern[std::make_tuple(op1_str.substr(0,9), op2_str.substr(0,9))];
       //std::cout << "Hit " << op1 << " * " << op2 << " = " << temp_mul << std::endl; 
       return temp_mul; 
    }  
    else
    {
       double decision = (double)rand() / (double)RAND_MAX; 
       
       if(decision < 0.001)
       {
          temp_mul = -0.09375;  
          //std::cout << "decision is " << decision << ", temp_mul is " << temp_mul << std::endl;   
       }
       
       else 
          temp_mul = op1 * op2; 
       return temp_mul; 
    }
}


int fully_count = 0;  //initialize a counter; Xun 08/24/17  
inline void fully_connected_op_internal(const tensor_t &in_data,
                                        const vec_t &W,
                                        const vec_t &bias,
                                        tensor_t &out_data,
                                        const fully_params &params,
                                        const bool layer_parallelize) {
  //count the times fully connected layers are called; Xun 08/24/17 
  fully_count ++; 
  //printf("fully_count is %d\n", fully_count);
  //Intialize operands file; Xun 08/24/17
  FILE *op_MUL_file = fopen("./operands/fully_MUL_op_CNN.txt","a");
 
  for_i(layer_parallelize, in_data.size(), [&](int sample) {
    const vec_t &in = in_data[sample];
    vec_t &out      = out_data[sample];

    for (serial_size_t i = 0; i < params.out_size_; i++) {
         out[i] = float_t{0};
         for (serial_size_t c = 0; c < params.in_size_; c++) {
             if (PROFILE == true)                //if we need profile
             { 
                 if (fully_count < PROF_IMAGE)   //only profile PROF_IAMGE images 
                 {
                       
                    fprintf(op_MUL_file, "%f\t%f\n", W[c * params.out_size_ + i], in[c]);
                 }
             } 
             out[i] += W[c * params.out_size_ + i] * in[c]; //original formula 
             //round to nearest 0.01; Xun 08/30/17
             //float temp_mul = (int)((W[c * params.out_size_ + i] * in[c])/0.1) * 0.1;
             //float temp_mul = ((W[c * params.out_size_ + i] * in[c]));
             //float BV_res=check_BV_fully(W[c * params.out_size_ + i],in[c]); 
             //out[i] += BV_res; 
           }

      if (params.has_bias_) {
        out[i] += bias[i];
      }
    }
  });
  fclose(op_MUL_file);
}

inline void fully_connected_op_internal(const tensor_t &prev_out,
                                        const vec_t &W,
                                        tensor_t &dW,
                                        tensor_t &db,
                                        tensor_t &curr_delta,
                                        tensor_t &prev_delta,
                                        const fully_params &params,
                                        const bool layer_parallelize) {
  for (serial_size_t sample = 0; sample < prev_out.size(); sample++) {
    for (serial_size_t c = 0; c < params.in_size_; c++) {
      // propagate delta to previous layer
      // prev_delta[c] += current_delta[r] * W_[c * out_size_ + r]
      prev_delta[sample][c] += vectorize::dot(
        &curr_delta[sample][0], &W[c * params.out_size_], params.out_size_);
    }

    for_(layer_parallelize, 0, size_t(params.out_size_),
         [&](const blocked_range &r) {
           // accumulate weight-step using delta
           // dW[c * out_size + i] += current_delta[i] * prev_out[c]
           for (serial_size_t c = 0; c < params.in_size_; c++) {
             vectorize::muladd(&curr_delta[sample][r.begin()],
                               prev_out[sample][c], r.end() - r.begin(),
                               &dW[sample][c * params.out_size_ + r.begin()]);
           }

           if (params.has_bias_) {
             // vec_t& db = *in_grad[2];
             for (int i = r.begin(); i < r.end(); i++) {
               db[sample][i] += curr_delta[sample][i];
             }
           }
         });
  }
}

}  // namespace kernels
}  // namespace tiny_dnn

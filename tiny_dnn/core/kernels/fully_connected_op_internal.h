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

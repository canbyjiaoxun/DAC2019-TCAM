/*
    Copyright (c) 2016, Taiga Nomi, Edgar Riba
    All rights reserved.

    Use of this source code is governed by a BSD-style license that can be found
    in the LICENSE file.
*/
#pragma once
#define ERROR_RATE 0.00001

#include "../../params/fully_params.h"
#include <math.h> 
//#include "tiny_dnn/core/kernels/bit_error.h"
#include "./func_error_check.h"
#include <assert.h>

namespace tiny_dnn {
namespace kernels {
inline void fully_connected_error_op_internal(const tensor_t &in_data,
                                        const vec_t &W,
                                        const vec_t &bias,
					const vec_t &W,
					tensor_t &out_data,
                                        const fully_params &params,
                                        const bool layer_parallelize) {
  for_i(layer_parallelize, in_data.size(), [&](int sample) {
    const vec_t &in = in_data[sample];
    vec_t &out      = out_data[sample];
    vector <string> patterns;
    vector <string> outputs;
    patterns = patternsToVector(::fname);
    outputs = outputsToVector(::fname);
    for (serial_size_t i = 0; i < params.out_size_; i++) {
      out[i] = float_t{0};
      for (serial_size_t c = 0; c < params.in_size_; c++) {
		  /// Vahideh -- 08.27.17
		  //CHECK PARTIAL HIT
		  float temp_mul;
		  string str_op1, str_op2,s_vec;
		  floatToBinary (W[c * params.out_size_ + i] , &str_op1);
		  floatToBinary (in[c] , &str_op2);
		  strcpy(s_vec,str_op1.substr(0,BIT_CHUNK));
		  strcat(s_vec,str_op2.substr(0,BIT_CHUNK));
		  std::vector<string>::iterator it;
		  it = std::find(patterns.begin(), patterns.end(), s_vec) != patterns.end()
		  if (it != patterns.end()){
			const vector<string>::size_t idx = it-patterns.begin();
			temp_mul = outputs[idx];
		  }
		  else{
			//inject Bloom filter error
			::error_cnt_fc ++;
			if (::error_cnt_fc == ERROR_RATE_FC){
				::error_cnt_fc = 0;
				temp_mul = atof(outputs[0])
			}
			else{
				temp_mul = W[c * params.out_size_ + i] * in[c];
			}
			  
		  }
		  /// Vahideh -- 08.27.17
		  //CHECK PARTIAL HIT
		}
		  	  
        out[i] = FlipAdder(out[i] + temp_mul);
      }

      if (params.has_bias_) {
        out[i] += bias[i];
	// flip ADD; Xun 08/16/17 
	//out[i] = FlipAdder(out[i]);
      }
    }
  });
}

inline void fully_connected_error_op_internal(const tensor_t &prev_out,
                                        const vec_t &W,
                                        tensor_t &dW,
                                        tensor_t &db,
                                        tensor_t &curr_delta,
                                        tensor_t &prev_delta,
                                        const fully_params &params,
                                        const bool layer_parallelize) {
  assert(false);
  printf("second error op\n");
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

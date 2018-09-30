/*
    COPYRIGHT

    All contributions by Taiga Nomi
    Copyright (c) 2013, Taiga Nomi
    All rights reserved.

    All other contributions:
    Copyright (c) 2013-2016, the respective contributors.
    All rights reserved.

    Each contributor holds copyright over their respective contributions.
    The project versioning (Git) records all such contribution source
   information.

    LICENSE

    The BSD 3-Clause License


    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
   this
      list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    * Neither the name of tiny-dnn nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
   USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once
#include <bitset>
#include <assert.h>
#include <random>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <map>
#include <tuple>

namespace tiny_dnn {
namespace kernels {

//convert float to IEEE 754 string 
inline std::string floatToBinary(float x){
    union
    {
         float input;   // assumes sizeof(float) == sizeof(int)
         int   output;
    }    data;
    data.input = x;
    std::bitset<sizeof(float) * 8> bits(data.output);
    return bits.to_string(); 
}

//layer 1 freq op 
inline std::map<std::tuple<std::string, std::string>, float> BF1(){
    std::map<std::tuple<std::string, std::string>, float> freq_pattern; 
    freq_pattern[std::make_tuple("0000000000000", "1011111110000")] = -1.03125;
    freq_pattern[std::make_tuple("1011111010000", "1011111110000")] = -1.2890625;
    freq_pattern[std::make_tuple("1011111000110", "1011111110000")] = -1.20703125;
    freq_pattern[std::make_tuple("1011111000001", "1011111110000")] = -1.16796875;
    freq_pattern[std::make_tuple("1011110111100", "1011111110000")] = -1.142578125;
    freq_pattern[std::make_tuple("0011111001011", "1011111110000")] = -0.81640625;
    freq_pattern[std::make_tuple("1011111000100", "1011111110000")] = -1.19140625;
    freq_pattern[std::make_tuple("1011111001000", "1011111110000")] = -1.22265625;
    freq_pattern[std::make_tuple("0011110110001", "1011111110000")] = -0.962890625;
    freq_pattern[std::make_tuple("0011110111011", "1011111110000")] = -0.923828125;
    freq_pattern[std::make_tuple("0011111010001", "1011111110000")] = -0.7578125;
    freq_pattern[std::make_tuple("0011110101100", "1011111110000")] = -0.9755859375;
    freq_pattern[std::make_tuple("1011111000101", "1011111110000")] = -1.19921875;
    freq_pattern[std::make_tuple("1011111010010", "1011111110000")] = -1.3203125;
    freq_pattern[std::make_tuple("0011111000001", "1011111110000")] = -0.89453125;
    freq_pattern[std::make_tuple("0011111010011", "1011111110000")] = -0.7265625;
    freq_pattern[std::make_tuple("1011110111000", "1011111110000")] = -1.126953125;
    freq_pattern[std::make_tuple("1011111010110", "1011111110000")] = -1.3828125;
    freq_pattern[std::make_tuple("0011111001001", "1011111110000")] = -0.83203125;
    freq_pattern[std::make_tuple("1011111010011", "1011111110000")] = -1.3359375;
    freq_pattern[std::make_tuple("0011111000100", "1011111110000")] = -0.87109375;
    freq_pattern[std::make_tuple("0011110111000", "1011111110000")] = -0.935546875;
    freq_pattern[std::make_tuple("1011111010001", "1011111110000")] = -1.3046875;
    freq_pattern[std::make_tuple("0011110100010", "1011111110000")] = -0.9951171875;
    freq_pattern[std::make_tuple("0011111000101", "1011111110000")] = -0.86328125;
    freq_pattern[std::make_tuple("0011111001111", "1011111110000")] = -0.78515625;
    freq_pattern[std::make_tuple("0011110110100", "1011111110000")] = -0.951171875;
    freq_pattern[std::make_tuple("0011111000111", "1011111110000")] = -0.84765625;
    freq_pattern[std::make_tuple("1011111001011", "1011111110000")] = -1.24609375;
    freq_pattern[std::make_tuple("0011111010110", "1011111110000")] = -0.6796875;
    freq_pattern[std::make_tuple("1011110100001", "1011111110000")] = -1.0654296875;
    freq_pattern[std::make_tuple("0011111010100", "1011111110000")] = -0.7109375;
    freq_pattern[std::make_tuple("0011111011000", "1011111110000")] = -0.6484375;
    freq_pattern[std::make_tuple("1011110111111", "1011111110000")] = -1.154296875;
    freq_pattern[std::make_tuple("1011110001011", "1011111110000")] = -1.04467773438;
    freq_pattern[std::make_tuple("0011110101010", "1011111110000")] = -0.9794921875;
    freq_pattern[std::make_tuple("0011110110011", "1011111110000")] = -0.955078125;
    freq_pattern[std::make_tuple("0011110011101", "1011111110000")] = -1.00244140625;
    freq_pattern[std::make_tuple("1011110100000", "1011111110000")] = -1.0634765625;
    freq_pattern[std::make_tuple("1011110100010", "1011111110000")] = -1.0673828125;
    freq_pattern[std::make_tuple("0011110101101", "1011111110000")] = -0.9736328125;
    freq_pattern[std::make_tuple("0011110110110", "1011111110000")] = -0.943359375;
    freq_pattern[std::make_tuple("1011111001010", "1011111110000")] = -1.23828125;
    freq_pattern[std::make_tuple("1011111000111", "1011111110000")] = -1.21484375;
    freq_pattern[std::make_tuple("0011110100110", "1011111110000")] = -0.9873046875;
    freq_pattern[std::make_tuple("1011111001111", "1011111110000")] = -1.27734375;
    freq_pattern[std::make_tuple("0011111010111", "1011111110000")] = -0.6640625;
    freq_pattern[std::make_tuple("0011110011110", "1011111110000")] = -1.00146484375;
    freq_pattern[std::make_tuple("0011111001110", "1011111110000")] = -0.79296875;
    freq_pattern[std::make_tuple("1011111001101", "1011111110000")] = -1.26171875;
    return freq_pattern; 
}

//layer 2 freq op
inline std::map<std::tuple<std::string, std::string>, float> BF2(){
    std::map<std::tuple<std::string, std::string>, float> freq_pattern; 
    freq_pattern[std::make_tuple("0000000000000", "0011110111011")] = 0.107421875;
    freq_pattern[std::make_tuple("1011111000000", "0011111100111")] = 0.60546875;
    freq_pattern[std::make_tuple("1011111000000", "0011110111011")] = -0.021484375;
    freq_pattern[std::make_tuple("1011110111011", "0011110111011")] = 0.0;
    freq_pattern[std::make_tuple("0011110110110", "0011111010101")] = 0.423828125;
    freq_pattern[std::make_tuple("0011111000011", "0011111100111")] = 0.88671875;
    freq_pattern[std::make_tuple("0011110110111", "0011111010101")] = 0.427734375;
    freq_pattern[std::make_tuple("0011110111000", "1011110010011")] = 0.07666015625;
    freq_pattern[std::make_tuple("0011110110000", "1011110010011")] = 0.04541015625;
    freq_pattern[std::make_tuple("0011111010001", "1011111001110")] = 0.03515625;
    freq_pattern[std::make_tuple("1011110110100", "0011111100111")] = 0.654296875;
    freq_pattern[std::make_tuple("1011111000000", "0011111011011")] = 0.30078125;
    freq_pattern[std::make_tuple("0011110110111", "0011111100111")] = 0.826171875;
    freq_pattern[std::make_tuple("0011110110000", "0011111100111")] = 0.798828125;
    freq_pattern[std::make_tuple("0011111001001", "0011110111011")] = 0.306640625;
    freq_pattern[std::make_tuple("0011110111010", "0011111100111")] = 0.837890625;
    freq_pattern[std::make_tuple("0011111000100", "0011111100111")] = 0.89453125;
    freq_pattern[std::make_tuple("0011110111001", "0011111100111")] = 0.833984375;
    freq_pattern[std::make_tuple("0011110110000", "0011110111011")] = 0.171875;
    freq_pattern[std::make_tuple("0011110110010", "0011111100111")] = 0.806640625;
    freq_pattern[std::make_tuple("1011111001000", "0011110111011")] = -0.083984375;
    freq_pattern[std::make_tuple("0011110011111", "0011110111011")] = 0.13818359375;
    freq_pattern[std::make_tuple("1011110110010", "0011111100111")] = 0.662109375;
    freq_pattern[std::make_tuple("1011111000001", "1011111001110")] = -0.375;
    freq_pattern[std::make_tuple("0011111000010", "0011111100111")] = 0.87890625;
    freq_pattern[std::make_tuple("1011110100011", "0011111011011")] = 0.3916015625;
    freq_pattern[std::make_tuple("1011110110000", "0011111010101")] = 0.271484375;
    freq_pattern[std::make_tuple("0011110110010", "0011110111011")] = 0.1796875;
    freq_pattern[std::make_tuple("1011110100011", "0011111100111")] = 0.6962890625;
    freq_pattern[std::make_tuple("0011110110000", "1011111001110")] = -0.173828125;
    freq_pattern[std::make_tuple("1011111000010", "0011110111011")] = -0.037109375;
    freq_pattern[std::make_tuple("1011110110000", "1011110010011")] = -0.08349609375;
    freq_pattern[std::make_tuple("1011110110000", "0011110111011")] = 0.04296875;
    freq_pattern[std::make_tuple("1011111000001", "0011111010101")] = 0.19921875;
    freq_pattern[std::make_tuple("0011111000100", "0011110111011")] = 0.267578125;
    freq_pattern[std::make_tuple("1011110110111", "1011111001110")] = -0.330078125;
    freq_pattern[std::make_tuple("0011110110011", "0011111010101")] = 0.412109375;
    freq_pattern[std::make_tuple("0011110110001", "0011111100111")] = 0.802734375;
    freq_pattern[std::make_tuple("1011110101101", "0011111011011")] = 0.3720703125;
    freq_pattern[std::make_tuple("1011110101111", "1011110010011")] = -0.08056640625;
    freq_pattern[std::make_tuple("1011110110110", "0011111011011")] = 0.341796875;
    freq_pattern[std::make_tuple("0011110100101", "0011111010101")] = 0.3779296875;
    freq_pattern[std::make_tuple("0011110110010", "1011110010011")] = 0.05322265625;
    freq_pattern[std::make_tuple("1011111000110", "1011111001110")] = -0.4140625;
    freq_pattern[std::make_tuple("1011111001010", "0011110111011")] = -0.099609375;
    freq_pattern[std::make_tuple("1011111000000", "0011111010101")] = 0.20703125;
    freq_pattern[std::make_tuple("1011111000100", "0011110111011")] = -0.052734375;
    freq_pattern[std::make_tuple("0011111010001", "0011111011011")] = 0.703125;
    freq_pattern[std::make_tuple("0011110101000", "0011111010101")] = 0.3837890625;
    freq_pattern[std::make_tuple("0011111000011", "0011110111011")] = 0.259765625;
    return freq_pattern; 
}

//layer 3 freq op
inline std::map<std::tuple<std::string, std::string>, float> BF3(){
    std::map<std::tuple<std::string, std::string>, float> freq_pattern; 
    freq_pattern[std::make_tuple("0011110110000", "0011111100010")] = 0.642578125;
    freq_pattern[std::make_tuple("1011110110000", "1011110110110")] = -0.15234375;
    freq_pattern[std::make_tuple("0011110110000", "0011111100000")] = 0.580078125;
    freq_pattern[std::make_tuple("0011110110000", "0011111100001")] = 0.611328125;
    freq_pattern[std::make_tuple("1011110110001", "1011110110110")] = -0.15625;
    freq_pattern[std::make_tuple("1011110110010", "0011111100000")] = 0.443359375;
    freq_pattern[std::make_tuple("0011110110010", "1011110110110")] = -0.015625;
    freq_pattern[std::make_tuple("0011110110001", "0011111100000")] = 0.583984375;
    freq_pattern[std::make_tuple("0011110110000", "1011110110110")] = -0.0234375;
    freq_pattern[std::make_tuple("0011110110011", "0011111100000")] = 0.591796875;
    freq_pattern[std::make_tuple("0011110110100", "1011110110110")] = -0.0078125;
    freq_pattern[std::make_tuple("0011110110001", "0011111100010")] = 0.646484375;
    freq_pattern[std::make_tuple("0011110110000", "1011110110101")] = -0.01953125;
    freq_pattern[std::make_tuple("0011110110001", "0011111100001")] = 0.615234375;
    freq_pattern[std::make_tuple("0011110110011", "0011111100010")] = 0.654296875;
    freq_pattern[std::make_tuple("0011110100010", "1011110110110")] = -0.0517578125;
    freq_pattern[std::make_tuple("1011110110001", "1011110110101")] = -0.15234375;
    freq_pattern[std::make_tuple("1011110110000", "1011110110101")] = -0.1484375;
    freq_pattern[std::make_tuple("0011110110101", "0011111100000")] = 0.599609375;
    freq_pattern[std::make_tuple("0011110110001", "1011110110110")] = -0.01953125;
    freq_pattern[std::make_tuple("1011110110010", "0011111100001")] = 0.474609375;
    freq_pattern[std::make_tuple("1011110110000", "1011111000000")] = -0.193359375;
    freq_pattern[std::make_tuple("0011110110011", "0011111100001")] = 0.623046875;
    freq_pattern[std::make_tuple("1011110110000", "1011111100011")] = -0.673828125;
    freq_pattern[std::make_tuple("1011110110001", "1011110110111")] = -0.16015625;
    freq_pattern[std::make_tuple("1011111000001", "0011111010101")] = 0.19921875;
    freq_pattern[std::make_tuple("1011111000000", "1011110110110")] = -0.216796875;
    freq_pattern[std::make_tuple("1011110110000", "1011110110111")] = -0.15625;
    freq_pattern[std::make_tuple("0011110110000", "1011111000001")] = -0.072265625;
    freq_pattern[std::make_tuple("0011110110000", "1011111000000")] = -0.064453125;
    freq_pattern[std::make_tuple("0011110110011", "1011110110110")] = -0.01171875;
    freq_pattern[std::make_tuple("1011110110000", "1011111000001")] = -0.201171875;
    freq_pattern[std::make_tuple("0011110111001", "0011111100000")] = 0.615234375;
    freq_pattern[std::make_tuple("0011110110001", "1011110110101")] = -0.015625;
    freq_pattern[std::make_tuple("0011110110100", "1011111000001")] = -0.056640625;
    freq_pattern[std::make_tuple("1011110110100", "1011111000000")] = -0.208984375;
    freq_pattern[std::make_tuple("0011110100111", "1011110110110")] = -0.0419921875;
    freq_pattern[std::make_tuple("1011111000000", "0011111010101")] = 0.20703125;
    freq_pattern[std::make_tuple("1011110110001", "0011111010101")] = 0.267578125;
    freq_pattern[std::make_tuple("1011110110011", "1011111000000")] = -0.205078125;
    freq_pattern[std::make_tuple("0011111000000", "1011110110110")] = 0.041015625;
    freq_pattern[std::make_tuple("1011110110011", "1011110110110")] = -0.1640625;
    freq_pattern[std::make_tuple("0011110111001", "0011111100010")] = 0.677734375;
    freq_pattern[std::make_tuple("0011110110101", "1011110110110")] = -0.00390625;
    freq_pattern[std::make_tuple("1011110110011", "1011111000001")] = -0.212890625;
    freq_pattern[std::make_tuple("0011110110001", "1011111000000")] = -0.060546875;
    freq_pattern[std::make_tuple("1011110100001", "1011110110110")] = -0.1220703125;
    freq_pattern[std::make_tuple("0011110110010", "1011110110101")] = -0.01171875;
    freq_pattern[std::make_tuple("1011110110100", "0011111100000")] = 0.435546875;
    freq_pattern[std::make_tuple("1011111000000", "1011111000000")] = -0.2578125;
    return freq_pattern; 
}

//approximate bloom filter hit 
int hit = 0; 
int total = 0; 
inline float check_BV(float op1, float op2, int layer) {
    total ++; 
    float temp_mul; 
    std::map<std::tuple<std::string, std::string>, float> freq_pattern;
    if (layer == 1) 
       freq_pattern = BF1(); 
    else if (layer == 2)
       freq_pattern = BF2(); 
    else 
       freq_pattern = BF3(); 
    std::string op1_str = floatToBinary(op1);
    std::string op2_str = floatToBinary(op2);
    //std::cout << "op1: " << op1 << " " << op1_str.substr(0,13) << std::endl; 
    //std::cout << "op2: " << op2 << " " << op2_str.substr(0,13) << std::endl; 
    if (freq_pattern.find(std::make_tuple(op1_str.substr(0,13), op2_str.substr(0,13))) != freq_pattern.end())
    {
       hit ++; 
       //std::cout << "Hit " << op1 << op2 << std::endl; 
       temp_mul = freq_pattern[std::make_tuple(op1_str.substr(0,13), op2_str.substr(0,13))];
       //std::cout << "Hit: " << temp_mul << std::endl;
       return temp_mul; 
    }  
    else
       temp_mul = op1 * op2; 
       //std::cout << "Not Hit: " << temp_mul << std::endl; 
       return temp_mul; 
}

int conv_count = 0; 
inline void conv2d_op_internal(const tensor_t &in_data,
                               const vec_t &W,
                               const vec_t &bias,
                               tensor_t &out_data,
                               const core::conv_params &params,
                               const bool parallelize) {
  conv_count ++; 
  //std::cout << "conv count: " << conv_count << std::endl; 
  //std::cout << "total op: " << total << std::endl; 
  //std::cout << "hit op: "   << hit << std::endl; 
  //initialize profile file 
  FILE *op_MUL_file1 = fopen("./operands/conv2d_MUL_op_layer1_CNN","a");
  FILE *op_MUL_file2 = fopen("./operands/conv2d_MUL_op_layer2_CNN","a");
  FILE *op_MUL_file3 = fopen("./operands/conv2d_MUL_op_layer3_CNN","a");
  float temp_mul; 
  for_i(parallelize, in_data.size(), [&](int sample) {
    const vec_t &in = in_data[sample];
    vec_t &a        = out_data[sample];

    for (serial_size_t o = 0; o < params.out.depth_; o++) {
      for (serial_size_t inc = 0; inc < params.in.depth_; inc++) {
        if (!params.tbl.is_connected(o, inc)) continue;

        serial_size_t idx = 0;
        idx               = params.in.depth_ * o + inc;
        idx               = params.weight.get_index(0, 0, idx);
        const float_t *pw = &W[idx];

        idx               = params.in_padded.get_index(0, 0, inc);
        const float_t *pi = &in[idx];

        idx         = params.out.get_index(0, 0, o);
        float_t *pa = &a[idx];

        for (serial_size_t y = 0; y < params.out.height_; y++) {
          for (serial_size_t x = 0; x < params.out.width_; x++) {
            const float_t *ppw = pw;
            const float_t *ppi =
              pi + params.in_padded.width_ * (y * params.h_stride) +
              x * params.w_stride;
            float_t sum{0};

            // should be optimized for small kernel(3x3,5x5)
            for (serial_size_t wy = 0; wy < params.weight.height_;
                 wy++) {  // NOLINT
              for (serial_size_t wx = 0; wx < params.weight.width_;
                   wx++) {  // NOLINT
                idx = wy * params.in_padded.width_ + wx;
                float temp_ppw = *ppw++;   //add a temp variable for pointer-based value
                sum += temp_ppw * ppi[idx]; 
                //sum += *ppw++ * ppi[idx];   //original formula 
              
                //profile MUL operands; Xun 09/06/17 
                if (PROFILE == true)
                {
                    //profile layer-based operands; Xun 09/06/17
                    if (conv_count < PROF_IMAGE * 3)   //only profile PROF_IMAGE images
                    {
                        if (conv_count % 3 == 1)
                           fprintf(op_MUL_file1, "%f\t%f\n", temp_ppw, ppi[idx]);
                        if (conv_count % 3 == 2)
                           fprintf(op_MUL_file2, "%f\t%f\n", temp_ppw, ppi[idx]);
                        if (conv_count % 3 == 0)
                           fprintf(op_MUL_file3, "%f\t%f\n", temp_ppw, ppi[idx]);
                    }
                }
                
                // round to nearest 0.01; Xun 08/30/17 
                //float temp_mul = (int)((*ppw++ * ppi[idx])/0.01) * 0.01;     //round to nearest one-hundredth
                //temp_mul = check_BV(*ppw++, ppi[idx], conv_count % 3);
                //std::cout << "temp_mul: " << temp_mul << std::endl; 
                //sum += temp_mul;
              }
            }
            pa[y * params.out.width_ + x] += sum;
          }
        }
      }

      if (params.has_bias) {
        float_t *pa  = &a[params.out.get_index(0, 0, o)];
        float_t *paa = pa + params.out.width_ * params.out.height_;
        std::for_each(pa, paa, [&](float_t &f) { f += bias[o]; });
      }
    }
  });
  fclose(op_MUL_file1);
  fclose(op_MUL_file2);
  fclose(op_MUL_file3);
}

/******************************************************************/

template <typename tensor_t, typename vec_t>
void conv2d_op_internal(const tensor_t &prev_out,
                        const vec_t &W,
                        tensor_t &dW,
                        tensor_t &db,
                        tensor_t &curr_delta,
                        tensor_t &prev_delta,
                        const core::conv_params &params,
                        const bool parallelize) {
  typedef typename vec_t::value_type float_t;

  for_i(parallelize, prev_out.size(), [&](int sample) {
    // propagate delta to previous layer
    for (serial_size_t inc = 0; inc < params.in.depth_; inc++) {
      for (serial_size_t outc = 0; outc < params.out.depth_; outc++) {
        if (!params.tbl.is_connected(outc, inc)) continue;

        serial_size_t idx = 0;
        idx               = params.in.depth_ * outc + inc;
        idx               = params.weight.get_index(0, 0, idx);
        const float_t *pw = &W[idx];

        idx                       = params.out.get_index(0, 0, outc);
        const float_t *pdelta_src = &curr_delta[sample][idx];

        idx = params.in_padded.get_index(0, 0, inc);
        // float_t* pdelta_dst = &(*prev_delta)[sample][idx];
        float_t *pdelta_dst = &prev_delta[sample][idx];

        for (serial_size_t y = 0; y < params.out.height_; y++) {
          for (serial_size_t x = 0; x < params.out.width_; x++) {
            const float_t *ppw = pw;

            idx                       = y * params.out.width_ + x;
            const float_t ppdelta_src = pdelta_src[idx];

            float_t *ppdelta_dst =
              pdelta_dst + y * params.h_stride * params.in_padded.width_ +
              x * params.w_stride;

            for (serial_size_t wy = 0; wy < params.weight.height_;
                 wy++) {  // NOLINT
              for (serial_size_t wx = 0; wx < params.weight.width_;
                   wx++) {  // NOLINT
                idx = wy * params.in_padded.width_ + wx;
                ppdelta_dst[idx] += *ppw++ * ppdelta_src;
              }
            }
          }
        }
      }
    }

    // accumulate dw
    for (serial_size_t inc = 0; inc < params.in.depth_; inc++) {
      for (serial_size_t outc = 0; outc < params.out.depth_; outc++) {
        if (!params.tbl.is_connected(outc, inc)) continue;

        for (serial_size_t wy = 0; wy < params.weight.height_; wy++) {
          for (serial_size_t wx = 0; wx < params.weight.width_; wx++) {
            float_t dst{0};

            serial_size_t idx    = 0;
            idx                  = params.in_padded.get_index(wx, wy, inc);
            const float_t *prevo = &prev_out[sample][idx];

            idx                  = params.out.get_index(0, 0, outc);
            const float_t *delta = &curr_delta[sample][idx];

            if (params.w_stride > 1) {
              for (serial_size_t y = 0; y < params.out.height_; y++) {
                serial_size_t prevo_idx =
                  y * params.in_padded.width_ * params.h_stride;
                serial_size_t delta_idx = y * params.out.width_;

                for (serial_size_t x = 0; x < params.out.width_; x++) {
                  dst += prevo[prevo_idx + x * params.w_stride] *
                         delta[delta_idx + x];
                }
              }
            } else {
              for (serial_size_t y = 0; y < params.out.height_; y++) {
                dst += vectorize::dot(
                  prevo + y * params.in_padded.width_ * params.h_stride,
                  delta + y * params.out.width_, params.out.width_);
              }
            }

            idx = params.in.depth_ * outc + inc;
            dW[sample][params.weight.get_index(wx, wy, idx)] += dst;
          }
        }
      }
    }

    // accumulate db
    if (params.has_bias) {
      for (serial_size_t outc = 0; outc < params.out.depth_; outc++) {
        serial_size_t idx     = params.out.get_index(0, 0, outc);
        const float_t *delta  = &curr_delta[sample][idx];
        const float_t *deltaa = delta + params.out.width_ * params.out.height_;
        db[sample][outc] += std::accumulate(delta, deltaa, float_t{0});
      }
    }
  });
}

}  // namespace kernels
}  // namespace tiny_dnn

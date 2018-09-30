/*
    Copyright (c) 2013, Taiga Nomi
    All rights reserved.

    Use of this source code is governed by a BSD-style license that can be found
    in the LICENSE file.
*/
#include <iostream>
#include "tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;


static void construct_net(network<sequential>& nn) {
     nn << fully_connected_layer<tan_h>(32 * 32, 50) 
        << fully_connected_layer<tan_h>(50, 10); 
}


static void train_MLP(const std::string& data_dir_path) {
  network<sequential> nn; 
  gradient_descent optimizer;
  //adagrad optimizer; 
  construct_net(nn);


  std::cout << "load models..." << std::endl;

  // load MNIST dataset
  std::vector<label_t> train_labels, test_labels;
  std::vector<vec_t> train_images, test_images;

  parse_mnist_labels(data_dir_path + "/train-labels.idx1-ubyte", &train_labels);
  parse_mnist_images(data_dir_path + "/train-images.idx3-ubyte", &train_images,
                     -1.0, 1.0, 2, 2);
  parse_mnist_labels(data_dir_path + "/t10k-labels.idx1-ubyte", &test_labels);
  parse_mnist_images(data_dir_path + "/t10k-images.idx3-ubyte", &test_images,
                     -1.0, 1.0, 2, 2);

  std::cout << "start training" << std::endl;

  progress_display disp(static_cast<unsigned long>(train_images.size()));
  timer t;
  int minibatch_size = 10;
  int num_epochs     = 40;

  optimizer.alpha *=
    std::min(tiny_dnn::float_t(4),
             static_cast<tiny_dnn::float_t>(std::sqrt(minibatch_size)));
  printf("alpha: %f\n",optimizer.alpha);
  //optimizer.alpha = 0.001; 

  // create callback
  auto on_enumerate_epoch = [&]() {
    std::cout << t.elapsed() << "s elapsed." << std::endl;
    tiny_dnn::result res = nn.test(test_images, test_labels);
    std::cout << res.num_success << "/" << res.num_total << std::endl;

    //optimizer.alpha *= 0.85;  // decay learning rate
    //optimizer.alpha = std::max((tiny_dnn::float_t)0.00001, optimizer.alpha);

    disp.restart(static_cast<unsigned long>(train_images.size()));
    t.restart();
  };

  auto on_enumerate_minibatch = [&]() { disp += minibatch_size; };

  // training
  nn.train<mse>(optimizer, train_images, train_labels, minibatch_size,
                num_epochs, on_enumerate_minibatch, on_enumerate_epoch);

  std::cout << "end training." << std::endl;

  // test and show results
  nn.test(test_images, test_labels).print_detail(std::cout);

  // save network model & trained weights
  std::ofstream ofs("MLP-model_fp_orin");
  ofs << nn;
  //nn.save("LeNet-model_fp_orin");
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage : " << argv[0] << " path_to_data (example:../data)"
              << std::endl;
    return -1;
  }
  train_MLP(argv[1]);
  return 0;
}

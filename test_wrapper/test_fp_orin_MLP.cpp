#include <iostream>
#include "tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace std;


void construct_net(network<sequential> &nn) {
     nn << fully_connected_layer<tan_h>(32 * 32, 60) 
        << fully_connected_layer<tan_h>(60, 10); 
}



static void test_MLP(const std::string &dictionary, const std::string &data_dir_path) {
  network<sequential> nn;
  construct_net(nn);

  ifstream ifs(dictionary.c_str());
  ifs >> nn;
  //nn.load(dictionary);

  // load MNIST dataset
  std::vector<label_t> test_labels;
  std::vector<vec_t> test_images;
  parse_mnist_labels(data_dir_path + "/t10k-labels.idx1-ubyte", &test_labels);
  parse_mnist_images(data_dir_path + "/t10k-images.idx3-ubyte", &test_images, -1.0, 1.0, 2, 2);
  
  std::cout << "start testing" << std::endl;
  nn.test(test_images, test_labels).print_detail(std::cout);
  std::cout << "end testing" << std::endl;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage : " << argv[0] << " path_to_data (example:../data)"
              << std::endl;
    return -1;
  }
  test_MLP("MLP-model_fp_orin",argv[1]);
  return 0;
}

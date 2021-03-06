#include <iostream>
#include "tiny_dnn/tiny_dnn.h"

using namespace tiny_dnn;
using namespace tiny_dnn::activation;
using namespace std;


void construct_net(network<sequential> &nn) {
// connection table [Y.Lecun, 1998 Table.1]
#define O true
#define X false
  // clang-format off
  static const bool tbl[] = {O, X, X, X, O, O, O, X, X, O, O, O, O, X, O, O, O, O, X, X, X, O, O, O,
                             X, X, O, O, O, O, X, O, O, O, O, X, X, X, O, O, O, X, X, O, X, O, O, O,
                             X, O, O, O, X, X, O, O, O, O, X, X, O, X, O, O, X, X, O, O, O, X, X, O,
                             O, O, O, X, O, O, X, O, X, X, X, O, O, O, X, X, O, O, O, O, X, O, O, O};
// clang-format on
#undef O
#undef X

  // by default will use backend_t::tiny_dnn unless you compiled
  // with -DUSE_AVX=ON and your device supports AVX intrinsics
  core::backend_t backend_type = core::default_engine();

  // construct nets
  //
  // C : convolution
  // S : sub-sampling
  // F : fully connected
  nn << convolutional_error_layer<tan_h>(
          32, 32, 5, 1, 6, padding::valid, true, 1, 1,
          backend_type)  // C1, 1@32x32-in, 6@28x28-out
     << average_pooling_layer<tan_h>(28, 28, 6,
                                     2)  // S2, 6@28x28-in, 6@14x14-out
     << convolutional_error_layer<tan_h>(
          14, 14, 5, 6, 16, connection_table(tbl, 6, 16), padding::valid, true,
          1, 1,
          backend_type)  // C3, 6@14x14-in, 16@10x10-in
     << average_pooling_layer<tan_h>(10, 10, 16,
                                     2)  // S4, 16@10x10-in, 16@5x5-out
     << convolutional_error_layer<tan_h>(
          5, 5, 5, 16, 120, padding::valid, true, 1, 1,
          backend_type)  // C5, 16@5x5-in, 120@1x1-out
     << fully_connected_error_layer<tan_h>(
          120, 10, true, backend_type);  // F6, 120-in, 10-out
}



static void test_lenet(const std::string &dictionary, const std::string &data_dir_path) {
  network<sequential> nn;
  construct_net(nn);

  ifstream ifs(dictionary.c_str());
  ifs >> nn;
  //nn.load(dictionary);

  // load MNIST dataset
  std::vector<label_t> test_labels;
  std::vector<vec_t> test_images;

  parse_mnist_labels(data_dir_path + "/t10k-labels.idx1-ubyte", &test_labels);
  parse_mnist_images(data_dir_path + "/t10k-images.idx3-ubyte", &test_images,
                     -1.0, 1.0, 2, 2);
  
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
  test_lenet("LeNet-model_fp_orin",argv[1]);
  return 0;
}

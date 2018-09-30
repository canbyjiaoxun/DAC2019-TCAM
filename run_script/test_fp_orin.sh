#Launch script for running original LeNet-5 model with optional profiling fucntion
g++ -c test_fp_orin.cpp -I./ -pthread -std=c++11 -DPROFILE=false -DPROF_IMAGE=500 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=0.1 -DMULTI_ERROR_RATE=0.1 -DTER_ADD=0 -DTER_MUL=0
g++ test_fp_orin.o -o test_fp_orin -pthread -std=c++11 -DPROFILE=false -DPROF_IMAGE=500 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=0.1 -DMULTI_ERROR_RATE=0.1 -DTER_ADD=0 -DTER_MUL=0
./test_fp_orin examples/mnist 2>&1 | tee test_fp_orin.log


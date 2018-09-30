#we set the error rate to be 0 so just run the original network 

#nonused parameters 
error=0.1
TER_ADD=0
TER_MUL=0

g++ -c test_fp_orin_MLP.cpp -I./ -pthread -std=c++11 -DPROFILE=true -DPROF_IMAGE=400 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error} -DTER_ADD=${TER_ADD} -DTER_MUL=${TER_MUL}
g++ test_fp_orin_MLP.o -o test_fp_orin_MLP -pthread -std=c++11 -DPROFILE=true -DPROF_IMAGE=400 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error} -DTER_ADD=${TER_ADD} -DTER_MUL=${TER_MUL}
./test_fp_orin_MLP examples/mnist 2>&1 | tee test_fp_orin_MLP.log

for error in 0.002; do
#for error in 0.01 0.001 0.0001 0.00001 0.000001 0.0000001 0.00000001; do
	echo $error
	g++ -c train_fp_orin_MLP_v2.cpp -I./ -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error} -DTER_ADD=0 -DTER_MUL=0
	g++ train_fp_orin_MLP_v2.o -o train_fp_orin_MLP_v2 -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error} -DTER_ADD=0 -DTER_MUL=0

  ./train_fp_orin_MLP_v2 examples/mnist 2>&1 | tee train_fp_orin_MLP_v2.log
done

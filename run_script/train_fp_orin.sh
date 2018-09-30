for error in 0.002; do
#for error in 0.01 0.001 0.0001 0.00001 0.000001 0.0000001 0.00000001; do
	echo $error
	g++ -c train_fp_orin.cpp -I./ -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error}
	g++ train_fp_orin.o -o train_fp_orin -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error}

  ./train_fp_orin examples/mnist 2>&1 | tee ${error}.log.train_fp_orin
done

for error in 0.002; do
#for error in 0.01 0.001 0.0001 0.00001 0.000001 0.0000001 0.00000001; do
	echo $error
	g++ -c train_quantized_orin.cpp -I./ -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error}
	g++ train_quantized_orin.o -o train_quantized_orin -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error}

	./train_quantized_orin examples/mnist 2>&1 | tee train_quantized_orin.log
done

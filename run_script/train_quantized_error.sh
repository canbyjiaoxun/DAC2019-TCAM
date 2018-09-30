declare -a a_error=(0.07359 0.058888 0.026057 0.014194 0.004615 0.001308);
declare -a m_error=(0.116255 0.11986 0.125025 0.08926 0.09583 0.079165);

for index in 0 1 2 3 4 5; do
#for error in 0.00000000001; do
#for error in 0.5 0.2 0.1 0.05 0.02 0.01 0.005 0.002 0.001; do
#for error in 0.01 0.001 0.0001 0.00001 0.000001 0.0000001 0.00000001; do
	echo $a_error[$index]
	echo $m_error[$index]

	#echo $error
	g++ -c quantized_error.cpp -I./ -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${a_error[$index]} -DMULTI_ERROR_RATE=${m_error[$index]}
	g++ quantized_error.o -o quantized_error_${index} -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${a_error[$index]} -DMULTI_ERROR_RATE=${m_error[$index]}

	./quantized_error_${index} examples/mnist ${index} 2>&1 | tee p${index}.log & 
done

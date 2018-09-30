#for error in 0.2; do
#for error in 0.01 0.001 0.0001 0.00001 0.000001 0.0000001 0.00000001; do
error=0.1
for TER_MUL in 0.01 0.001 0.0001 0.00001; do 
    for TER_ADD in 0; do
        g++ -c test_fp_error_MLP.cpp -I./ -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error} -DTER_ADD=${TER_ADD} -DTER_MUL=${TER_MUL}
        g++ test_fp_error_MLP.o -o test_fp_error_MLP -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error} -DTER_ADD=${TER_ADD} -DTER_MUL=${TER_MUL}
        ./test_fp_error_MLP examples/mnist 2>&1 | tee test_fp_mul_error_MLP.${TER_MUL}.log
    done 
done

for TER_both in 0.1 0.01 0.001 0.0001 0.00001; do 
    g++ -c test_fp_error_MLP.cpp -I./ -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error} -DTER_ADD=${TER_both} -DTER_MUL=${TER_both}
    g++ test_fp_error_MLP.o -o test_fp_error_MLP -pthread -std=c++11 -DCNN_USE_GEMMLOWP=true -DCNN_REGISTER_LAYER_DESERIALIZER=true -DADDER_ERROR_RATE=${error} -DMULTI_ERROR_RATE=${error} -DTER_ADD=${TER_both} -DTER_MUL=${TER_both}
    ./test_fp_error_MLP examples/mnist 2>&1 | tee test_fp_both_error_MLP.${TER_both}.log
done 

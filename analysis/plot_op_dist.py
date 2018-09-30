#plot the pdf diagram of operands 

import matplotlib.pyplot as plt
from numpy.random import normal
import numpy as np

#read raw data 
op_file = open('../operands/op_MUL_file.txt')
file_lines = op_file.readlines() 
op_list = [] 
for line in file_lines:
    #op_list.append(float(line.split()[0]))
    op_list.append(float(line.split()[1]))

#form np array 
op_array = np.array(op_list)
weights_random = np.ones_like(op_array)/float(len(op_array))
plt.hist(op_array, bins=100, weights=weights_random, facecolor='green', alpha=0.5)

#plot 
plt.title("Operand Distribution")
plt.xlabel("Operands")
plt.ylabel("Probability")
plt.legend()
plt.show()
#plt.savefig('../figure/' + workload_name + '_input.pdf')


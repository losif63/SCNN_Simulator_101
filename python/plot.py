import numpy as np
from matplotlib import pyplot as plt

layers = np.array(["conv1_1", "conv1_2", "conv2_1", "conv2_2", "conv3_1", "conv3_2", "conv3_3", "conv4_1", "conv4_2", "conv4_3", "conv5_1", "conv5_2", "conv5_3"])
total_cycles = np.zeros(layers.size, dtype=int)
stall_cycles = np.zeros(layers.size, dtype=int)
valid_cycles = np.zeros(layers.size, dtype=int)

total_multops = np.zeros(layers.size, dtype=int)
valid_multops = np.zeros(layers.size, dtype=int)
mult_util = np.zeros(layers.size, dtype=float)

for layerIndex in range(layers.size):
    f = open("Results/vgg16/VGG16_" + layers[layerIndex])
    # f = open("Results/vgg16/VGG16_" + layers[layerIndex] + "_ver3x3")
    # f = open("Results/vgg16/VGG16_" + layers[layerIndex] + "_ver4x4")
    # f = open("Results/vgg16/VGG16_" + layers[layerIndex] + "_ver8x8")
    for line in f.readlines():
        print(line)
        if ('Total cycles spent:' in line) and ('-' not in line):
            total_cycles[layerIndex] = int(line[line.index(": ")+2:-1])
        if ('Total stalled cycles:' in line):
            stall_cycles[layerIndex] = int(line[line.index(": ")+2:-1])
        if ('Total active cycles:' in line):
            valid_cycles[layerIndex] = int(line[line.index(": ")+2:-1])
        
        if ('Total multiplication operations:' in line):
            total_multops[layerIndex] = int(line[line.index(": ")+2:-1])
        if('Valid multiplication operations:' in line):
            valid_multops[layerIndex] = int(line[line.index(": ")+2:-1])
    mult_util[layerIndex] = float(valid_multops[layerIndex])/float(total_multops[layerIndex])
    f.close()

print(total_cycles)
print(stall_cycles)
print(valid_cycles)

print(total_multops)
print(valid_multops)
print(mult_util)

plt.title("VGGNet")
plt.ylabel("Multiplier utilization")
plt.bar(layers, mult_util, color = 'b', align = 'center')
plt.xticks(rotation=90)
plt.show()

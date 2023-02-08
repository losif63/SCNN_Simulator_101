#!/bin/sh

# build.sh
# Author: Jaduk Suh
# Script follows here:

read -p "Enter PE array H: " PE_H
read -p "Enter PE array W: " PE_W

echo "Generating experimental data for PE array ${PE_H}x${PE_W}"

./SCNN config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_ver${PE_H}x${PE_W} 
./SCNN config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_ver${PE_H}x${PE_W}
./SCNN config/vgg16/vgg16| tee Results/vgg16/VGG16_ver${PE_H}x${PE_W}

./SCNN config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_ver${PE_H}x${PE_W}
./SCNN config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_ver${PE_H}x${PE_W}
./SCNN config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_ver${PE_H}x${PE_W}
./SCNN config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_ver${PE_H}x${PE_W}
./SCNN config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_ver${PE_H}x${PE_W}
./SCNN config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_ver${PE_H}x${PE_W}
./SCNN config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_ver${PE_H}x${PE_W}
./SCNN config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_ver${PE_H}x${PE_W}
./SCNN config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_ver${PE_H}x${PE_W}
./SCNN config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_ver${PE_H}x${PE_W}
./SCNN config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_ver${PE_H}x${PE_W}
./SCNN config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_ver${PE_H}x${PE_W}
./SCNN config/google/googleNet | tee Results/google/googleNet_ver${PE_H}x${PE_W}
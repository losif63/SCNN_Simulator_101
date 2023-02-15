#!/bin/sh

# build.sh
# Author: Jaduk Suh
# Script follows here:

# HALO="INPUT"
HALO="OUTPUT"

read -p "Enter PE array H: " PE_H
read -p "Enter PE array W: " PE_W

echo "Generating experimental data for PE array ${PE_H}x${PE_W}, ${HALO} halo"

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

# -----------------------------------------------------------------------------------------------------------------------------


# ./SCNN config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/googleNet | tee Results/google/googleNet_ver${PE_H}x${PE_W}_${HALO}_halo

# ./SCNN config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_ver${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16| tee Results/vgg16/VGG16_ver${PE_H}x${PE_W}_${HALO}_halo


# -----------------------------------------------------------------------------------------------------------------------------


# ./SCNN config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/google/googleNet | tee Results/google/googleNet_Xbar_scaleout_4_${HALO}_halo

# ./SCNN config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_Xbar_scaleout_4_${HALO}_halo
# ./SCNN config/vgg16/vgg16| tee Results/vgg16/VGG16_Xbar_scaleout_4_${HALO}_halo


# -----------------------------------------------------------------------------------------------------------------------------


# Start from here tomorrow
# ./SCNN config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/google/googleNet | tee Results/google/googleNet_Xbar_scaleout_1_${HALO}_halo

# ./SCNN config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_Xbar_scaleout_1_${HALO}_halo
# ./SCNN config/vgg16/vgg16| tee Results/vgg16/VGG16_Xbar_scaleout_1_${HALO}_halo


# -----------------------------------------------------------------------------------------------------------------------------


# ./SCNN config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/google/googleNet | tee Results/google/googleNet_FI${PE_H}x${PE_W}_${HALO}_halo

# ./SCNN config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_FI${PE_H}x${PE_W}_${HALO}_halo
# ./SCNN config/vgg16/vgg16| tee Results/vgg16/VGG16_FI${PE_H}x${PE_W}_${HALO}_halo


# -----------------------------------------------------------------------------------------------------------------------------



# ./SCNN config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_xbar_outq_4
# ./SCNN config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_xbar_outq_4
# ./SCNN config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_xbar_outq_4
# ./SCNN config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_xbar_outq_4
# ./SCNN config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_xbar_outq_4
# ./SCNN config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_xbar_outq_4
# ./SCNN config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_xbar_outq_4
# ./SCNN config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_xbar_outq_4
# ./SCNN config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_xbar_outq_4
# ./SCNN config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_xbar_outq_4
# ./SCNN config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_xbar_outq_4
# ./SCNN config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_xbar_outq_4
# ./SCNN config/google/googleNet | tee Results/google/googleNet_xbar_outq_4

# ./SCNN config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_xbar_outq_4
# ./SCNN config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_xbar_outq_4

















# ./SCNN4 config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_ver4x4_${HALO}_halo
# ./SCNN4 config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_ver4x4_${HALO}_halo

# ./SCNN2 config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_ver2x2_${HALO}_halo
# ./SCNN2 config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_ver2x2_${HALO}_halo

# ./SCNN1 config/google/inception_3a_1x1 | tee Results/google/inception_3a_1x1_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_3a_3x3 | tee Results/google/inception_3a_3x3_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_3a_3x3_reduce | tee Results/google/inception_3a_3x3_reduce_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_3a_5x5 | tee Results/google/inception_3a_5x5_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_3a_5x5_reduce | tee Results/google/inception_3a_5x5_reduce_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_3a_pool_proj | tee Results/google/inception_3a_pool_proj_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_5b_1x1 | tee Results/google/inception_5b_1x1_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_5b_3x3 | tee Results/google/inception_5b_3x3_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_5b_3x3_reduce | tee Results/google/inception_5b_3x3_reduce_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_5b_5x5 | tee Results/google/inception_5b_5x5_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_5b_5x5_reduce | tee Results/google/inception_5b_5x5_reduce_ver1x1_${HALO}_halo
# ./SCNN1 config/google/inception_5b_pool_proj | tee Results/google/inception_5b_pool_proj_ver1x1_${HALO}_halo





# ./SCNN4 config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_ver4x4_${HALO}_halo
# ./SCNN4 config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_ver4x4_${HALO}_halo

# ./SCNN2 config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_ver2x2_${HALO}_halo
# ./SCNN2 config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_ver2x2_${HALO}_halo

# ./SCNN1 config/vgg16/vgg16_conv1_1 | tee Results/vgg16/VGG16_conv1_1_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv1_2 | tee Results/vgg16/VGG16_conv1_2_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv2_1 | tee Results/vgg16/VGG16_conv2_1_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv2_2 | tee Results/vgg16/VGG16_conv2_2_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv3_1 | tee Results/vgg16/VGG16_conv3_1_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv3_2 | tee Results/vgg16/VGG16_conv3_2_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv3_3 | tee Results/vgg16/VGG16_conv3_3_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv4_1 | tee Results/vgg16/VGG16_conv4_1_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv4_2 | tee Results/vgg16/VGG16_conv4_2_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv4_3 | tee Results/vgg16/VGG16_conv4_3_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv5_1 | tee Results/vgg16/VGG16_conv5_1_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv5_2 | tee Results/vgg16/VGG16_conv5_2_ver1x1_${HALO}_halo
# ./SCNN1 config/vgg16/vgg16_conv5_3 | tee Results/vgg16/VGG16_conv5_3_ver1x1_${HALO}_halo
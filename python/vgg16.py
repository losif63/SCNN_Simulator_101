import numpy as np
import torch
from torchvision.models import vgg16, VGG16_Weights

for param in vgg16(weights=VGG16_Weights.DEFAULT).parameters():
    print(param.dim())





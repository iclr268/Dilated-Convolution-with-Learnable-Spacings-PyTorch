# Dilated-Convolution-with-Learnable-Spacings-PyTorch
Anonymous, iclr 268.

Dilated Convolution with Learnable Spacings (abbreviated to DCLS) is a novel convolution method based on gradient descent and interpolation. It could be seen as an improvement of the well known dilated convolution that has been widely explored in deep convolutional neural networks and which aims to inflate the convolutional kernel by inserting spaces between the kernel elements. 

In DCLS, the positions of the weights within the convolutional kernel are learned in a gradient-based manner, and the inherent problem of non-differentiability due to the integer nature of the positions in the kernel is solved by taking advantage of an interpolation method. 

For now, the code has only been implemented on [PyTorch](https://pytorch.org/), using Pytorch's C++ API and custom cuda extensions. 

- [Installation](#installation)
- [Usage](#usage)
- [Device Supports](#device-supports)
- [Publications and Citation](#publications-and-citation)
- [Contribution](#contribution)

## Installation

DCLS is based on PyTorch and CUDA. Please make sure that you have installed all the requirements before you install DCLS.

**Requirements**:
-   Pytorch version torch>=1.6.0. See [**torch**](https://pytorch.org/).
-   CUDA support CUDA>=10.0
-   gcc>=9.1.0

**Preferred versions**:
```bash
pip3 install torch==1.8.0+cu111 torchvision==0.9.0+cu111 -f https://download.pytorch.org/whl/torch_stable.html
```

**Install the latest developing version from the source codes**:

From [GitHub](https://github.com/iclr268/Dilated-Convolution-with-Learnable-Spacings-PyTorch):
```bash
git clone https://github.com/iclr268/Dilated-Convolution-with-Learnable-Spacings-PyTorch.git
cd Dilated-Convolution-with-Learnable-Spacings-PyTorch
python ./setup.py install --user
```

**Install the last stable version from** [**PyPI**](https://pypi.org/project/DCLS/):

```bash
coming soon
```

## Usage
Dcls methods could be easily used as a substitue of Pytorch's nn.Conv**n**d classical convolution method:

```python
import torch
from DCLS.construct.modules.Dcls import  Dcls2d

# With square kernels, equal stride and dilation
m = Dcls2d(16, 33, kernel_count=3, dilated_kernel_size=7).cuda()
input = torch.randn(20, 16, 50, 100).cuda()
output = m(input)
loss = output.sum()
loss.backward()
print(output, m.weight.grad, m.P.grad)
```
```python
import torch
from DCLS.construct.modules.Dcls import  Dcls1d 

# Will construct kernels of size 7x7 with 3 elements inside each kernel
m = Dcls1d(3, 16, kernel_count=3, dilated_kernel_size=7).cuda()
input = torch.rand(8, 3, 32).cuda()
output = m(input)
loss = output.sum()
loss.backward()
print(output, m.weight.grad, m.P.grad)
```

**DepthWiseConv2dImplicitGEMM for 2D-DCLS**:

For 2D-DCLS, to install and enable the DepthWiseConv2dImplicitGEMM, please follow the instructions of [RepLKNet](https://github.com/DingXiaoH/RepLKNet-pytorch#use-our-efficient-large-kernel-convolution-with-pytorch). Otherwise, Pytorch's native Conv2D method will be used.


## Device Supports
DCLS only supports Nvidia CUDA GPU devices for the moment. The CPU version has not been implemented yet.

-   [x] Nvidia GPU
-   [ ] CPU

Make sure to have your data and model on CUDA GPU.


## Contribution

This project is open source, therefore all your contributions are welcomed, whether it's reporting issues, finding and fixing bugs, requesting new features, and sending pull requests ...


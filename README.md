# SCNN Cycle-Level Simulator
> Template provided by 👨🏻‍🤝‍👨🏻 **[Ranggi Hwang](https://sites.google.com/view/ranggihwang/) & [Jinha Chung](https://sites.google.com/view/jinhachung)** from [VIA lab](https://sites.google.com/view/kaist-via/home)

> EE495 Individual Research Project
  
### Author Info
* [Jaduk Suh](https://github.com/losif63), student of School of Computing (SoC) & Electrical Engineering (EE) at Korean Advanced Institute of Science and Technology (KAIST)

### Development Info
* C/C++
* Python3
* Makefile / Shell script

---

## What is SCNN?

> SCNN is a domain-specific architecture specialized for accelerating sparse convolutional neural networks (CNN) in machine learning. SCNN stores input activation layers and weights in sparse format in order to enhance performance and power consumption. For more information, please refer to the following [paper](https://arxiv.org/pdf/1708.04485.pdf) written by professor Minsoo Rhu, Angshuman Parashar and others.

## What is a cycle-level simulator?
> Cycle level simulators are simulators made from modern programming languages such as C/C++, instead of traditional RTL languages such as Verilog or SystemVerilog. While not as accurate as RTL simulators, cycle-level simulators provide fast & easily configurable simulations of a specific hardware architecture. This enables researchers to conduct experiments under various environments, making it more suitable for research purposes.

## About this project
> This project holds an implmentation of a cycle-level simulator for the SCNN architecture, developed during my individual research program at [VIA LAB](https://sites.google.com/view/kaist-via/home). This simulator can run simulation experiments under various hardware configurations.

## Installation
```
git clone https://github.com/losif63/SCNN_Simulator_101
```

## Compilation & Running experiments
To create a binary executable file, simply type:
```
make
```
This command will create a binary exeucable file named `SCNN`. To run an experiment, simply type:
```
./SCNN {configuration_file_path}
```
For example, to run an experiment on VGGNet and store the result to a file:
```
./SCNN config/vgg16/vgg16 > Results/vgg16/vgg16_results
```

You can also modify the provided `build.sh` shell script to automatically run experiments!
```
./build.sh
```

## Testing
This project provides test cases used during development in the `test/test.cc` file. One could possibly also use the provided test cases when modifying the source code. To run the test cases, simply type:
```
make test
```

## Clearing repository
When clearing the repository, one can simply remove all compiled object code simply by:
```
make clean
```
Note that switching between input halo & output halo will require recompilation of all source files and it is mandatory to use the above command before doing so.

## Default configuration
* PE array: 8 x 8
* Multiplier array: 4 x 4
* Halo: Output halo
* Queue depth: 8
* Accumulator bank number: 2 x F x I



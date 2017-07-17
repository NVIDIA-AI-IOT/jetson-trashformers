# Jetson-Trashformers

<p align="center">
  <img src="https://github.com/shruthij28/jetson-trashformers/blob/master/images/robot.jpg" width="300" height="500">
</p>

### What is this project about?
The goal of this project is to use neural networks to train the [Robotis BioloidGP](http://en.robotis.com/index/product.php?cate_code=121510) to detect trash and throw it away in trash cans, effectively keeping the office environment clean. 

<!-- add image after resizing![Robot Pic](https://github.com/shruthij28/jetson-trashformers/blob/master/images/robot.jpg) -->

### How can I run this project?
```
git clone https://github.com/NVIDIA-Jetson/jetson-trashformers.git
cd jetson-trashformers
make
sh runDetect.sh
```
These three commands will clone the project to the computer so that it can be run and/or edited to the the user's liking, compile the program, and allow the user to run the program to pick up trash. This program can only be run on the Jetson TX2.

### What is CupNet?
CupNet is the neural network that we have created in order to detect cups. It has been trained on images of cups in multiple colors, as well as false positives to make the model more accurate. This neural network has been created and trained on [NVIDIA DIGITS](https://developer.nvidia.com/digits) using the Caffe framework. We used the help of [Dustin Franklin's Jetson Inference tutorial](https://github.com/dusty-nv/jetson-inference) to learn more about using DIGITS and creating our own neural network.

<p align="center">
  <img src="https://github.com/shruthij28/jetson-trashformers/blob/master/images/model26.png" width="500">
</p>

> This graph shows the model's statistics during the training period.

<p align="center">
  <img src="https://github.com/shruthij28/jetson-trashformers/blob/master/images/cup_tweet.png" width="500">
</p>

> The model learns to draw bounding boxes around cups through training. 

### Hardware Expectations?
* Robotis BioloidGP
* Orbitty Carrier Board
* Jetson TX2
* Logitech C270 Webcam
* USB2Dynamixel
* Zig2Serial

### Licensing?
* ROBOTIS:
<blockquote>
SDK OBTAINED FROM https://github.com/ROBOTIS-GIT/DynamixelSDK
on June 29 2017

Copyright (c) 2016, ROBOTIS CO., LTD.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

* Neither the name of ROBOTIS nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
</blockquote>

* ZigBee
<blockquote>
Source code available at http://support.robotis.com/en/software/zigbee_sdk/zig2serial/linux.htm

No license was found as of June 29 2017.
</blockquote>


### Libraries?
See 'lib' folder for the specific files. 
* libdetectnet-camera.so <!-- Rename with the new name for DetectNet Camera-->
  * A shared object library with an edited and compiled version of detectnet-camera.cpp from [Dustin's github](https://github.com/dusty-nv/jetson-inference).
* libdxl_sbc_cpp.so
  * A shared object library for the [Dynamixel servos](https://github.com/ROBOTIS-GIT/DynamixelSDK).
* libjetson-inference.so
  * A shared object library of [Dusty's jetson-inference](https://github.com/dusty-nv/jetson-inference).
* libzgb.so
  * A shared object library to control robot commands via [ZigBee](http://support.robotis.com/en/software/zigbee_sdk/zig2serial/linux.htm). 

<p align="center">
  <img src="https://github.com/shruthij28/jetson-trashformers/blob/master/images/teampic.jpg" width="500">
</p>

## Authors
* Ishan Mitra
* Shruthi Jaganathan
* Mark Theis 
* Michael Chacko

<!-- <center><img src="https://github.com/shruthij28/jetson-trashformers/blob/master/images/teampic.jpg" width="500"></center> -->
<!-- ![Team Pic](https://github.com/shruthij28/jetson-trashformers/blob/master/images/teampic.jpg =500x250) -->


<!--
### Add jetson-trashformers/lib to your library path
We will soon figure out a better way to handle these paths. For now, manually add lib via the export command:
```
export LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH
```

### To build Zigbee.so files:

For zgb, go to jetson-trashformers/util and run the commands:
```
g++ -c -fpic *.c
g++ -shared -o libzgb.so *.o
```
then move the resulting .so file to jetson-trashformers/lib:
```
mv ./libzgb.so ../lib
```

### Add libraries from detectnet-camera / jetson-inference
See the log.md file for instructions on how we got that to work. Imporoved instructions are in the works.
-->


<p align="center">
  <img src="https://github.com/NVIDIA-Jetson/jetson-trashformers/blob/master/images/trashformers_logo.png" />
</p>

### What is this project about?
Our project uses neural networks to train the [Robotis BioloidGP](http://en.robotis.com/index/product.php?cate_code=121510) to detect trash and throw it away in trash cans, effectively keeping the office environment clean. The current stage of the model allows for detection of white cups (as trash) in various backgrounds. The purpose of this project is to provide a use-case example for developers who may wish to use the Jetson™ platform. 

**The code in this repository has only been tested on the NVIDIA Jetson TX2.**

### How can I run this project?
```
git clone https://github.com/NVIDIA-Jetson/jetson-trashformers.git
cd jetson-trashformers
make
sh runDetect.sh
```
The first three commands clone and compile the program. The last command runs a script which starts the program. **This program can only be run on the Jetson TX2.**

When runDetect.sh is run, the robot's webcam is activated and begins searching for a cup. If no cup is found, it will turn and scan around until it finds a cup. Once it has done so, it will walk towards the cup, finding its orientation, and attempt to pick it up once within range. The robot then attempts scan for a trash can symbol (noramlly on trashcans) and will drop the cup infront of the trashcan.

### What is CupNet?
CupNet is the neural network that we have created in order to detect cups. It has been trained on images of cups in multiple colors, as well as false positives to make the model more accurate. This neural network has been created and trained on [NVIDIA DIGITS](https://developer.nvidia.com/digits) using the Caffe framework. We used the help of [Dustin Franklin's Jetson Inference tutorial](https://github.com/dusty-nv/jetson-inference) to learn more about using DIGITS and creating our own neural network.

<p align="center">
  <img src="https://github.com/nvidia-jetson/jetson-trashformers/blob/master/images/model26.png" width="500">
</p>

> This graph shows the model's statistics during the training period.

<p align="center">
  <img src="https://github.com/nvidia-jetson/jetson-trashformers/blob/master/images/cup_tweet.png" width="500">
</p>

> The model learns to draw bounding boxes around cups through training. 

### Hardware Expectations?
* Robotis BioloidGP
* Connect Tech Orbitty Carrier Board
* Jetson™ TX2
* Logitech C270 Webcam
* USB2Dynamixel
* Zig2Serial

[Find a Hardware setup guide here](https://github.com/NVIDIA-Jetson/jetson-trashformers/wiki/Hardware)

[Find a Linux 4 Tegra® with Connect Tech Carrier Board setup guide here](https://github.com/NVIDIA-Jetson/jetson-trashformers/wiki/Jetson%E2%84%A2-Flashing-and-Setup-Guide-for-a-Connect-Tech-Carrier-Board)

<p align="center">
  <img src="https://github.com/nvidia-jetson/jetson-trashformers/blob/master/images/our_robot.jpg" width="500">
</p>

### Libraries Used
See 'lib' folder for the specific files. 
* libdetectnet-camera.so <!-- Rename with the new name for DetectNet Camera-->
  * A shared object library with an edited and compiled version of detectnet-camera.cpp from [Dustin's github](https://github.com/dusty-nv/jetson-inference).
* libdxl_sbc_cpp.so
  * A shared object library for the [Dynamixel servos](https://github.com/ROBOTIS-GIT/DynamixelSDK).
* libjetson-inference.so
  * A shared object library of [Dustin's jetson-inference](https://github.com/dusty-nv/jetson-inference).
* libzgb.a
  * A shared object library to control robot commands via [ZigBee](http://support.robotis.com/en/software/zigbee_sdk/zig2serial/linux.htm). (This library is downloaded as a dependancy from the ROBOTIS website)

<p align="center">
  <img src="https://github.com/nvidia-jetson/jetson-trashformers/blob/master/images/teampic.jpg" width="500">
</p>

## Authors
(Left to Right from picture above)
* Ishan Mitra
* Shruthi Jaganathan
* Mark Theis 
* Michael Chacko

### Licenses Used
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

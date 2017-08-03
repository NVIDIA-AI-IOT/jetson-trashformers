#!/bin/bash

#export path for library path
export LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH

#set display to the monitor, regardless of ssh connection
DISPLAY=:0

#run main with custom params 
./main 1 8967


#export path for library path
export LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH

#set display to the monitor, regardless of ssh connection
DISPLAY=:0

#set NET for detectnet
NET=networks

#run main with detectnet params
./main

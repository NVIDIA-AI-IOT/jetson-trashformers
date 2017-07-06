
#export path for library path
export LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH

#set display to the monitor, regardless of ssh connection
DISPLAY=:0

#set NET for detectnet
NET=/home/nvidia/break-me/jetson-inference/build/aarch64/bin/networks

#run main with detectnet params
./main --prototxt=$NET/deploy.prototxt --model=$NET/snapshot_iter_1650.caffemodel --input_blob=data --output_cvg=coverage --output_bbox=bboxes

# jetson-trashformers

Repository for the Trasformers NVIDIA Embedded Intern Team!


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
See the log.txt file for instructions on how we got that to work. Imporoved instructions are in the works.



# jetson-trashformers

Repository for the Trasformers NVIDIA Embedded Intern Team!


## To build .so files:

For zgb, go to util and run the commands:
    g++ -c -fpic *.c
    g++ -shared -o libzgb.so *.o

then move the resulting .so file to the lib



You also may need to export lib to your library path:
    LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH

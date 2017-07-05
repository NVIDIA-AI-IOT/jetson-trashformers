TARGET		= main
LIBDIRS		+= -Llib -L/usr/local/cuda/lib64
OBJS		= main.cpp ./include/*.cpp
SRCS		= $(OBJS:.o=.cpp)
INCLUDEDIRS	+= -I./include -I./util
CFLAGS		= $(INCLUDEDIRS) -W -Wall -O2 -std=c++11 -pthread
LDFLAGS		= $(LIBDIRS) -ldetectnet-camera -ljetson-inference -lcudart -lzgb -ldxl_sbc_cpp 

CC			= g++

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
.c.o:
	$(CC) -c $< $(CFLAGS)
	
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "file deleted."

dep:
	gccmakedep $(SRCS)


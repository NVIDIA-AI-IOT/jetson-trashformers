TARGET		= main
LIBDIRS		+= -Llib
OBJS		= main.cpp ./include/*.cpp
SRCS		= $(OBJS:.o=.cpp)
INCLUDEDIRS	+= -I./include
CFLAGS		= -W -Wall -O2
#CFLAGS		= $(INCLUDEDIRS) -W -Wall -O2
LDFLAGS		= $(LIBDIRS) -lzgb -ldxl_sbc_cpp 

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


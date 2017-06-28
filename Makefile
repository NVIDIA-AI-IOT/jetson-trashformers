TARGET		= Humanoid
OBJS		= Humanoid.o
SRCS		= $(OBJS:.o=.c)
INCLUDEDIRS	+= -I./include
LIBDIRS		+= -L./lib
CFLAGS		= $(INCLUDEDIRS) -W -Wall -O2
LDFLAGS		= $(LIBDIRS) -lm -lzgb

CC			= g++

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	
.c.o:
	$(CC) -c $< $(CFLAGS)
	
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "file deleted."

dep:
	gccmakedep $(SRCS)


TARGET		= Humanoid
LIBDIRS		+= -L./lib
OBJS		= Humanoid.o
SRCS		= $(OBJS:.o=.c)
INCLUDEDIRS	+= -I./include
CFLAGS		= $(INCLUDEDIRS) -W -Wall -O2
LDFLAGS		= $(LIBDIRS) -lzgb

CC			= g++

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	
.c.o:
	$(CC) -c $< $(CFLAGS)
	
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "file deleted."

dep:
	gccmakedep $(SRCS)


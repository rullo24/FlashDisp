# defining compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -fsanitize=address -fstack-protector -Wno-unused-parameter
RAYGUI_FLAGS = -L./ext/raygui -fpic -DRAYGUI_IMPLEMENTATION
LIBS = -lraylib $(RAYGUI_FLAGS) -lm -lX11
# LIBS = -lraylib $(RAYGUI_FLAGS) -lm -lpthread -ldl -lGL -lrt -lX11

# defining relevant binary specs
TARGET = freq_disp 
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# basic rule for target binary build
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	rm -f $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS)
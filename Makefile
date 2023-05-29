TARGET = 13lab
CC = gcc
SRCS = main.c binary.c cheking.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
clean:
	rm -f $(TARGET) $(OBJS)
.c.o : binary.h cheking.h; $(CC) -c $*.c
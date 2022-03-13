TARGET := Server

CC := gcc

CSRCS :=$(wildcard *.c)

OBJS := $(patsubst %.c, %.o, $(CSRCS))

#INC := -I ./

#LIBS := -l

$(TARGET):$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) -c $< $(INC) -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
TARGET := Smarthome

CC := arm-linux-gcc

# CPP := g++ -std=c++11

CSRCS :=$(wildcard *.c)

# CPPSRCS :=$(wildcard *.cpp)

OBJS := $(patsubst %.c, %.o, $(CSRCS))

# OBJS += $(patsubst %.cpp, %.o, $(CPPSRCS))

INC := -I ./ -I ../INC

LIBS := -l pthread

$(TARGET):$(OBJS)
		$(CC) $^ $(LIBS) -o $@

%.o:%.c 
	$(CC) -c $< $(INC) -o $@

%.o:%.cpp 
	$(CPP) -c $< $(INC) -o $@

clean:
	rm -rf  $(OBJS)
	rm -rf $(TARGET)
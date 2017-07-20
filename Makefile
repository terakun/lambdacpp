CXX = g++
# FLAGS = -std=c++11 -O0 -g -fopenmp
FLAGS = -std=c++11 -O2
INCLUDE = 
LIBS = 

TARGET = main
SRCS = main.cc parser.cc expression.cc

OBJS = $(patsubst %.cc,%.o,$(SRCS))

.cc.o:
	$(CXX) $(FLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJS)
		$(CXX) $(FLAGS) $(FLAG) -o $@ $(OBJS) $(LIBS)

clean:
	rm $(TARGET) $(OBJS)

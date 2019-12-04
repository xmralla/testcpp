default : all

RM = rm -f
SRC = main.cpp
BIN = testcpp

CXXFLAGS = -g

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(BIN)

clean:
	$(RM) $(BIN)

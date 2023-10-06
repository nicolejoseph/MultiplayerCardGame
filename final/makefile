CXX = g++

CXXFLAGS = -std=c++14 -Wall

SRCS = player.cpp card.cpp deck.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = myprogram

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

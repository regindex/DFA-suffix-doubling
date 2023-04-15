TARGET=$(patsubst %.cpp,%,$(wildcard *.cpp))

all: ${TARGET}

%: %.cpp
	g++ $< -O3 -std=c++14 -o $@

CXX=g++
CXXFLAGS=-std=c++11 -Isrc/ -g
LDFLAGS=-g -lev -lpthread

all: bin/test_request_response bin/hatttp

clean:
	rm -f *.o
	rm -f bin/*

bin/hatttp: response.o main.o
	$(CXX) response.o main.o -o bin/hatttp $(LDFLAGS)

bin/test_request_response: request.o response.o test_request_response.o
	$(CXX) request.o response.o test_request_response.o -o bin/test_request_response $(LDFLAGS)

request.o: src/request.cpp
	$(CXX) $(CXXFLAGS) -c src/request.cpp

response.o: src/response.cpp
	$(CXX) $(CXXFLAGS) -c src/response.cpp

test_request_response.o: tests/test_request_response.cpp
	$(CXX) $(CXXFLAGS) -c tests/test_request_response.cpp

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp

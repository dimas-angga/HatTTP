CXX=g++
CXXFLAGS=-std=c++11 -Isrc/ -g
LDFLAGS=-g -lev -lpthread

all: bin/test_request_response bin/test_server bin/hatttp

clean:
	rm -f *.o
	rm -f bin/*

bin/hatttp: request.o response.o server.o main.o
	$(CXX) request.o response.o server.o main.o -o bin/hatttp $(LDFLAGS)

bin/test_request_response: request.o response.o test_request_response.o
	$(CXX) request.o response.o test_request_response.o -o bin/test_request_response $(LDFLAGS)

bin/test_server: request.o response.o server.o test_server.o
	$(CXX) request.o response.o server.o test_server.o -o bin/test_server $(LDFLAGS)

request.o: src/request.cpp
	$(CXX) $(CXXFLAGS) -c src/request.cpp

response.o: src/response.cpp
	$(CXX) $(CXXFLAGS) -c src/response.cpp
	
server.o: src/server.cpp
	$(CXX) $(CXXFLAGS) -c src/server.cpp

test_request_response.o: tests/test_request_response.cpp
	$(CXX) $(CXXFLAGS) -c tests/test_request_response.cpp

test_server.o: tests/test_server.cpp
	$(CXX) $(CXXFLAGS) -c tests/test_server.cpp

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp

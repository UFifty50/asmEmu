srcFiles = $(wildcard src/cpp/*.cpp)
objFiles = $(patsubst src/cpp/%.cpp, build/%.o, $(srcFiles))
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Isrc/include
CXX = g++-10
TARGET = asmAsm

run: build
	./build/$(TARGET)

build: $(objFiles)
	$(CXX) $(CXXFLAGS) -o build/$(TARGET) $(objFiles)

build/%.o: src/cpp/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

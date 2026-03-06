CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Isrc -IApp -IInterface -ICLI

SRCS = \
	src/Chromosome.cpp \
	src/Point.cpp \
	src/Population.cpp \
	src/Fitness.cpp \
	src/MathUtils.cpp \
	src/Selection.cpp \
	src/Crossover.cpp \
	src/Mutation.cpp \
	src/GAUtils.cpp \
	App/App.cpp \
	Interface/UICli.cpp \
	CLI/main.cpp

TARGET = BestPoint

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

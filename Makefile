CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -IClasses -IUtil -IApp -IInterface -ICLI

SRCS = \
	Classes/Chromosome.cpp \
	Classes/Point.cpp \
	Classes/Population.cpp \
	Classes/Fitness.cpp \
	Classes/MathUtils.cpp \
	Classes/Selection.cpp \
	Classes/Crossover.cpp \
	Classes/Mutation.cpp \
	Util/GAUtils.cpp \
	App/App.cpp \
	Interface/UICli.cpp \
	CLI/main.cpp

TARGET = BestPoint

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

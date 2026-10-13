CXX      = c++
CXXFLAGS = -std=c++11 -Wall -Isrc -Iapp -Iinterface -Icli

SRCS = \
	src/chromosome.cpp \
	src/point.cpp \
	src/population.cpp \
	src/fitness.cpp \
	src/math_utils.cpp \
	src/selection.cpp \
	src/crossover.cpp \
	src/mutation.cpp \
	src/ga_utils.cpp \
	app/app.cpp \
	interface/ui_cli.cpp \
	cli/main.cpp

TARGET = BestPoint

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)


CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -IClasses -IUtil -IApp -IInterface -ICLI

SRCS = \
	Classes/Cromossomo.cpp \
	Classes/Ponto.cpp \
	Classes/Populacao.cpp \
	Classes/Fitness.cpp \
	Classes/Calculo.cpp \
	Classes/Selecao.cpp \
	Classes/Crossover.cpp \
	Classes/Mutacao.cpp \
	Util/AGUtil.cpp \
	App/AppAG.cpp \
	Interface/GerenteInterfaceCLI.cpp \
	CLI/main.cpp

TARGET = BestPoint

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

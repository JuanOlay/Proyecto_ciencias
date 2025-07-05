CXX = g++
CXXFLAGS = -g -Wall -std=c++17

# Buscar recursivamente todos los .cpp en el proyecto
SRCS = $(shell find . -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)

TARGET = programa.exe

all: $(TARGET)

# Regla para enlazar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar cada archivo .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

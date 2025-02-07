# Compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -std=c++17 -Wall -O2 -I.

# Bibliotecas
LDFLAGS = -lfreeglut -lopengl32 -lglu32

# Arquivos fonte
SRCS = main.cpp player.cpp enemy.cpp map.cpp

# Nome do executável
TARGET = doom.exe

# Regra principal
all: $(TARGET)

# Linkagem dos arquivos objeto
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Limpeza dos arquivos gerados
clean:
	del $(TARGET)

.PHONY: all clean
CC      = g++
CFLAGS  = -Wall -O2
LDFLAGS = -lfreeglut -lglu32 -lopengl32
TARGET  = doom.exe
SOURCES = enemy.cpp player.cpp map.cpp menu.cpp main.cpp

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	del /Q $(TARGET)

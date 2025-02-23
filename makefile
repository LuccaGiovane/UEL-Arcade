CC      = g++
CFLAGS  = -Wall -O2
LDFLAGS = -lfreeglut -lglu32 -lopengl32 -lwinmm
TARGET  = pewpew.exe
SOURCES = enemy.cpp player.cpp map.cpp menu.cpp main.cpp

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	del /Q $(TARGET)

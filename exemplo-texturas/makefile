CC      = g++
CFLAGS  = -O2 
LDFLAGS = -lfreeglut -lglu32 -lopengl32 -lglaux
TARGET  = main
SOURCES = teste.cpp

#all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	del /Q $(TARGET)

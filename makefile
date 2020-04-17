SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJECTS=$(SOURCES:%.cpp=%.o)
TARGET=main
LIBS=-lCGAL -lgmp -lmpfr -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

all: $(TARGET)
$(TARGET): $(OBJECTS) $(HEADERS)
	@echo "Now Generating $(TARGET) ..."
	g++ $(OBJECTS) $(LIBS) -o $(TARGET)
%.o: %.cpp $(HEADERS)
	@echo "Now Compiling $< ..."
	g++ -I. -c $< -o $@
clean:
	rm *.o *.exe *.bak
explain:
	@echo "Headers: $(HEADERS)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Target: $(TARGET)"
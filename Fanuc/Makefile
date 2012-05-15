CXX           = g++
TARGET        = FanucCustom
CHILDVERSION  = 0
PVERSION	  = 1
VERSION       = $(PVERSION).$(CHILDVERSION)
OBJECTS		  = $(TARGET).o $(TARGET)IF.o
SO			  = ld -shared -soname

all: $(TARGET)

$(TARGET):
	$(CXX) -fPIC -g -c -Wall $(TARGET).cpp
	$(CXX) -fPIC -g -c -Wall $(TARGET)IF.cpp
	$(SO) $(TARGET).so.$(PVERSION) -o $(TARGET).so.$(VERSION) -lc $(OBJECTS)
	
clean:
	rm -f *.o
	rm -f *.so.*
CC:=g++
exe:=test
src_dir:=.$(pwd)/src
lib_dir:=.$(pwd)/lib
obj:=main.o LEDController.o $(lib_dir)/libws2811.so
FL:=-Wl,-rpath
WSHEADERFL:=-I

all:$(obj)
	$(CC) -o $(exe) $(obj) $(FL)=$(lib_dir)
	$(MAKE) clean

%.o:$(src_dir)/%.cpp
	$(CC) -c $(WSHEADERFL) $(lib_dir) $^ -o $@

.PHONY:clean

clean:
	rm *.o

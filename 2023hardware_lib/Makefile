CC = g++

SRC = src
INC = include
LIB = lib

OBJ = obj
BIN = bin

# CLINKER = -Wl,-rpath
CFLAGS = -std=c++14
CINCS = -I$(INC)
CLIBS = 

all : directory main
	# $(CC) -o $(exe) $(obj) $(FL)=$(lib_dir)
	# $(MAKE) clean

umb : directory umb_main
	# $(CC) -o $(exe) $(obj) $(FL)=$(lib_dir)
	# $(MAKE) clean

LED : directory LEDmain
	# $(CC) -o $(exe) $(obj) $(FL)=$(lib_dir)
	# $(MAKE) clean

LED_umb : directory LEDmain_umb
	# $(CC) -o $(exe) $(obj) $(FL)=$(lib_dir)
	# $(MAKE) clean

OF : directory OFmain
	# $(CC) -o $(exe) $(obj) $(FL)=$(lib_dir)
	# $(MAKE) clean

directory : 
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

main : LEDController_umb.o LEDController.o OFController.o main.o
	$(CC) -o $(BIN)/main \
		$(OBJ)/main.o \
		$(OBJ)/LEDController.o \
		$(OBJ)/LEDController_umb.o \
		$(OBJ)/OFController.o \
		-lws2811 \
		$(CFLAGS) $(CINCS) $(CLIBS)
		# -L$(LIB) -lws2811 \

umb_main : LEDController_umb.o LEDController.o OFController.o umb_main.o
	$(CC) -o $(BIN)/main \
		$(OBJ)/umb_main.o \
		$(OBJ)/LEDController.o \
		$(OBJ)/LEDController_umb.o \
		$(OBJ)/OFController.o \
		-lws2811 \
		$(CFLAGS) $(CINCS) $(CLIBS)
		# -L$(LIB) -lws2811 \

LEDmain : LEDController_umb.o LEDController.o OFController.o LEDmain.o
	$(CC) -o $(BIN)/main \
		$(OBJ)/LEDmain.o \
		$(OBJ)/LEDController.o \
		$(OBJ)/LEDController_umb.o \
		$(OBJ)/OFController.o \
		-lws2811 \
		$(CFLAGS) $(CINCS) $(CLIBS)
		# -L$(LIB) -lws2811 \

LEDmain_umb : LEDController_umb.o LEDController.o OFController.o LEDmain_umb.o
	$(CC) -o $(BIN)/main \
		$(OBJ)/LEDmain_umb.o \
		$(OBJ)/LEDController.o \
		$(OBJ)/LEDController_umb.o \
		$(OBJ)/OFController.o \
		-lws2811 \
		$(CFLAGS) $(CINCS) $(CLIBS)
		# -L$(LIB) -lws2811 \

OFmain : LEDController_umb.o LEDController.o OFController.o OFmain.o
	$(CC) -o $(BIN)/main \
		$(OBJ)/OFmain.o \
		$(OBJ)/LEDController.o \
		$(OBJ)/LEDController_umb.o \
		$(OBJ)/OFController.o \
		-lws2811 \
		$(CFLAGS) $(CINCS) $(CLIBS)
		# -L$(LIB) -lws2811 \

main.o :
	$(CC) -c $(SRC)/main.cpp -o $(OBJ)/main.o \
	 	$(CFLAGS) $(CINCS)

umb_main.o :
	$(CC) -c $(SRC)/umb_main.cpp -o $(OBJ)/umb_main.o \
	 	$(CFLAGS) $(CINCS)

LEDmain.o : 
	$(CC) -c $(SRC)/LEDmain.cpp -o $(OBJ)/LEDmain.o \
		$(CFLAGS) $(CINCS)

LEDmain_umb.o : 
	$(CC) -c $(SRC)/LEDmain_umb.cpp -o $(OBJ)/LEDmain_umb.o \
		$(CFLAGS) $(CINCS)

OFmain.o : 
	$(CC) -c $(SRC)/OFmain.cpp -o $(OBJ)/OFmain.o \
		$(CFLAGS) $(CINCS)

LEDController.o : 
	$(CC) -c $(SRC)/LEDController.cpp -o $(OBJ)/LEDController.o \
		$(CFLAGS) $(CINCS)

LEDController_umb.o :
	$(CC) -c $(SRC)/LEDController_umb.cpp -o $(OBJ)/LEDController_umb.o \
		$(CFLAGS) $(CINCS)

OFController.o :
	$(CC) -c $(SRC)/OFController.cpp -o $(OBJ)/OFController.o \
		$(CFLAGS) $(CINCS)


# %.o:$(src_dir)/%.cpp
# 	$(CC) -c $(WSHEADERFL) $(lib_dir) $^ -o $@

.PHONY:clean

clean:
	rm *.o

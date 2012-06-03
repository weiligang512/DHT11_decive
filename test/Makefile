
OBJ = DHT11User.o
SRC = DHT11User.c
INC = DHT11User.h

CROSS = arm-linux-gcc

FLAGS = -Wall

DHT11User: $(OBJ) $(INC)
	$(CROSS) -o DHT11User $(OBJ) $(FLAGS)
DHT11User.o:$(SRC) $(INC)
	$(CROSS) -c $(SRC) -o $(OBJ) $(FLAGS)
clean:
	@rm -rf DHT11User *.o *~

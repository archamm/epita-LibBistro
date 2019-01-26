CC = g++
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17
EXEC_NAME = binLibBistro
OBJ_FILES = src/main.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<





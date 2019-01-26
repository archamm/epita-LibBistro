CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
EXEC_NAME = main
OBJ_FILES = src/scan-bistro.o src/parse-bistro.o src/parse-driver.o src/main.o

all: $(EXEC_NAME)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES)

clean :
	$(RM) $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)

%.cc: %.ll
	flex -f -o $@ -c $^
%.cc %.hh: %.yy
	bison $^ -o $*.cc --defines=$*.hh





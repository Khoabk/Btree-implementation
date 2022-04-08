INC = -Iinclude
LIB = -lm


SRC = src
OBJ = obj
INCLUDE = include

CXX = g++
DEBUG = -g
CXXFLAGS = -Wall -c $(DEBUG)
LXXFLAGS = -Wall $(DEBUG)


vpath %.cpp $(SRC)
vpath %.h $(INCLUDE)

MAKE = $(CXX) $(INC)

Btr_OBJ = $(addprefix $(OBJ)/, main.o Queue.o Btree.o Bnode.o Elem.o)
HEADER = $(wildcard $(INCLUDE)/*.h)




Btree_op: $(Btr_OBJ)
	@echo $(HEADER)
	$(MAKE) $(LXXFLAGS) -o $@ $^ $(LIB)


run_program:
	@echo ------ Btree program ------
	./Btree_op


$(OBJ)/%.o: %.cpp $(HEADER)
	$(MAKE) $(CXXFLAGS) $< -o $@



.PHONY : clean
clean:
	rm Btree_op $(OBJ)/*.o


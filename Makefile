NAME = expert-system

OS := $(shell uname)
ifeq ($(OS),Darwin)
  CXX=clang++
  INCLUDE_AND_LIBS = -I $(HOME)/.brew/Cellar/boost/1.67.0_1/include \
					-L $(HOME)/.brew/Cellar/boost/1.67.0_1/lib \
					-I include
  FLAGS = -std=c++11 -Wall -Wextra -Werror \
			-lboost_filesystem  -lboost_system  -lboost_program_options \
			-pthread -lboost_thread-mt -Wno-unused-command-line-argument \
			-Wno-unused -Wno-unused-parameter -O2
else
  CXX=g++
  INCLUDE_AND_LIBS = -I include 
  FLAGS = -std=c++11 -Wall -Wextra -Werror \
			-lboost_filesystem  -lboost_system -lboost_program_options \
			-pthread -lboost_thread -Wno-unused-command-line-argument \
			-Wno-unused -Wno-unused-parameter -O2
endif

OBJDIR = obj/

SRCDIR = src/

_SRC = 	main.cpp \
		CLI.cpp \
		Fact.cpp \

SRC = $(addprefix $(SRCDIR), $(_SRC))

OBJ = $(addprefix $(OBJDIR),$(_SRC:.cpp=.o))

all: make_dir $(NAME)

make_dir:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) $(FLAGS) $(INCLUDE_AND_LIBS) -o $@ -c $<

$(NAME): $(OBJ) $(SRC)
	$(CXX) $(FLAGS) $(INCLUDE_AND_LIBS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: compile_test
	$(CXX) $(FLAGS) -o mtest test/main.o

test_clean:
	rm -rf test/main.o
	rm -rf mtest

compile_test:
	$(CXX) $(FLAGS) -o test/main.o -c test/main.cpp


grammar: compile_grammar
	$(CXX) $(FLAGS) $(INCLUDE_AND_LIBS) -o grammar test/grammar.o

grammar_clean:
	rm -rf test/grammar.o
	rm -rf grammar

compile_grammar:
	$(CXX) $(FLAGS) $(INCLUDE_AND_LIBS) -o test/grammar.o -c test/grammar.cpp
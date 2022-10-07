BIN = c-
AR = ar rvs
CC = g++ --std=c++17 -g

# Changed this to multiple compile steps that can be executed at the same time

AST_DIR = .ast.d
AST_SRCS = AST/*.cpp AST/*/*.cpp AST/*/*/*.cpp
AST_HDRS = AST/*.hpp AST/*/*.hpp AST/*/*/*.hpp
OPTIONS_DIR = .options.d
OPTIONS_SRCS = Options/*.cpp Options/*/*.cpp
OPTIONS_HDRS = Options/*.hpp Options/*/*.hpp
SYMTBL_DIR = .symtbl.d
SYMTBL_SRCS = SymbolTable/*.cpp
SYMTBL_HDRS = SymbolTable/*.hpp
SEMCHCK_DIR = .semchck.d
SEMCHCK_SRCS = SemanticsChecker/*.cpp
SEMCHCK_HDRS = SemanticsChecker/*.hpp

SRCS = $(BIN).y $(BIN).l $(AST_SRCS) $(OPTIONS_SRCS) $(SYMTBL_SRCS) $(SEMCHCK_SRCS) strutil.cpp
HDRS = $(AST_HDRS) $(OPTIONS_HDRS) $(SYMTBL_HDRS) $(SEMCHCK_HDRS) strutil.hpp scanType.hpp
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS) $(AST_DIR) $(OPTIONS_DIR) $(SYMTBL_DIR) $(SEMCHCK_DIR)
	$(CC) strutil.cpp *.o -o $(BIN)
	$(MAKE) clean

lex.yy.c : $(BIN).l $(BIN).tab.h
	flex -o lex.yy.c $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y -o $(BIN).tab.c

$(AST_DIR):
	$(CC) -c $(AST_SRCS)
	mkdir $(AST_DIR)

$(OPTIONS_DIR):
	$(CC) -c $(OPTIONS_SRCS)
	mkdir $(OPTIONS_DIR)

$(SYMTBL_DIR):
	$(CC) -c $(SYMTBL_SRCS)
	mkdir $(SYMTBL_DIR)

$(SEMCHCK_DIR):
	$(CC) -c $(SEMCHCK_SRCS)
	mkdir $(SEMCHCK_DIR)

clean :
	rm -f *.o
	rm -f lex.yy.c lex.yy.o $(BIN).tab.c $(BIN).tab.o $(BIN).tab.h $(BIN).output
	rm -rf $(AST_DIR) $(OPTIONS_DIR) $(SYMTBL_DIR) $(SEMCHCK_DIR)

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile
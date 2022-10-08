BIN = c-
AR = ar rvs
CC = g++ --std=c++17 -g

Tree_DIR = .Tree.d
Tree_SRCS = Tree/*.cpp Tree/*/*.cpp Tree/*/*.cpp
Tree_HDRS = Tree/*.hpp Tree/*/*.hpp Tree/*/*.h
OPTIONS_DIR = .options.d
OPTIONS_SRCS = Options/*.cpp Options/*/*.cpp
OPTIONS_HDRS = Options/*.hpp Options/*/*.hpp
SEMCHCK_DIR = .semchck.d
SEMCHCK_SRCS = Semantics/*.cpp
SEMCHCK_HDRS = Semantics/*.h

SRCS = $(BIN).y $(BIN).l $(Tree_SRCS) $(OPTIONS_SRCS) $(SYMTBL_SRCS) $(SEMCHCK_SRCS) helpers.cpp
HDRS = $(Tree_HDRS) $(OPTIONS_HDRS) $(SYMTBL_HDRS) $(SEMCHCK_HDRS) helpers.h scanType.h
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS) $(Tree_DIR) $(OPTIONS_DIR) $(SYMTBL_DIR) $(SEMCHCK_DIR)
	$(CC) helpers.cpp *.o -o $(BIN)
	$(MAKE) cleanJunk

lex.yy.c : $(BIN).l $(BIN).tab.h
	flex -o lex.yy.c $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y -o $(BIN).tab.c

$(Tree_DIR):
	$(CC) -c $(Tree_SRCS)
	mkdir $(Tree_DIR)

$(OPTIONS_DIR):
	$(CC) -c $(OPTIONS_SRCS)
	mkdir $(OPTIONS_DIR)

$(SYMTBL_DIR):
	$(CC) -c $(SYMTBL_SRCS)
	mkdir $(SYMTBL_DIR)

$(SEMCHCK_DIR):
	$(CC) -c $(SEMCHCK_SRCS)
	mkdir $(SEMCHCK_DIR)

cleanJunk :
	rm -f *.o
	rm -f lex.yy.c lex.yy.o $(BIN).tab.c $(BIN).tab.o $(BIN).tab.h $(BIN).output
	rm -rf $(Tree_DIR) $(OPTIONS_DIR) $(SYMTBL_DIR) $(SEMCHCK_DIR)

clean :
	rm -f c-
	$(MAKE) cleanJunk

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile

CXX = g++
CXXFLAGS = --std=c++17 #-ly

FLEX = flex
FLEXFLAGS =
FLEXSRCS = $(PRJ).l
FLEXCPPS = lex.yy.c

BISON = bison
BISONFLAGS = -d -t -v
BISONSRCS = $(PRJ).y
BISONCPPS = $(PRJ).tab.c
BISONHDRS = $(PRJ).tab.h

OPTIONHDRS = options/*.hpp
OPTIONSRCS = options/*.cpp

ASTHDRS = ast/subclasses/hpp/*.hpp ast/ast.hpp ast/node.hpp
ASTSRCS = ast/node.cpp ast/subclasses/cpp/*.cpp


HDRS = types.hpp $(OPTIONHDRS) $(ASTHDRS)
SRCS = $(OPTIONSRCS) $(ASTSRCS)

PRJ = c-

$(PRJ): $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS) $(HDRS) $(SRCS)
	$(CXX) $(FLEXCPPS) $(BISONCPPS) $(SRCS) $(CXXFLAGS) -o $(PRJ)

qc: # quick clean, remove everything but binary and .tar
	rm $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS)

clean:
	rm $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS) $(PRJ) $(PRJ).tar $(PRJ).output

tar: $(SRCS) $(HDRS) makefile
	tar -cvf $(PRJ).tar $(SRCS) $(HDRS) makefile

$(BISONCPPS): $(BISONSRCS)
	$(BISON) $(BISONFLAGS) $(PRJ).y

$(FLEXCPPS): $(FLEXSRCS) $(BISONCPPS) $(BISONHDRS)
	$(FLEX) $(FLEXFLAGS) $(PRJ).l

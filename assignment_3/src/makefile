CXX = g++
CXXFLAGS = --std=c++17 -g

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

ASTHDRS = ast/hpp/*.hpp ast/hpp/*/*.hpp ast/ast.hpp
ASTSRCS = ast/cpp/*.cpp ast/cpp/*/*.cpp

TYPESHDRS = types/hpp/*.hpp types/types.hpp
TYPESSRC = types/cpp/*.cpp

ERRORHDRS = error/error.hpp
ERRORSRCS =

SYMTABLEHDRS = symTable/*.hpp
SYMTABLESRCS = symTable/*.cpp

SEMANTICHDRS = semantics/*.hpp
SEMANTICSRCS = semantics/*.cpp

HDRS = $(OPTIONHDRS) $(ASTHDRS) $(TYPESHDRS) $(ERRORHDRS) $(SYMTABLEHDRS) $(SEMANTICHDRS)
SRCS = $(OPTIONSRCS) $(ASTSRCS) $(TYPESSRC) $(ERRORSRCS) $(SYMTABLESRCS) $(SEMANTICSRCS)

PRJ = c-

$(PRJ): $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS) $(HDRS) $(SRCS)
	$(CXX) $(FLEXCPPS) $(BISONCPPS) $(SRCS) $(CXXFLAGS) -o $(PRJ)

qc: # quick clean, remove everything but binary and .tar
	rm $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS)

clean:
	rm $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS) $(PRJ) $(PRJ).tar $(PRJ).output

tar: $(SRCS) $(HDRS) makefile $(BISONSRCS) $(FLEXSRCS)
	tar -cvf $(PRJ).tar $(SRCS) $(HDRS) makefile $(BISONSRCS) $(FLEXSRCS)

$(BISONCPPS): $(BISONSRCS)
	$(BISON) $(BISONFLAGS) $(BISONSRCS)

$(FLEXCPPS): $(FLEXSRCS) $(BISONCPPS) $(BISONHDRS)
	$(FLEX) $(FLEXFLAGS) $(FLEXSRCS)

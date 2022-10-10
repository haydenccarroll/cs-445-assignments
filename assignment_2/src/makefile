CXX = g++
CXXFLAGS = --std=c++17 #-ly

FLEX = flex
FLEXFLAGS =
FLEXSRCS = $(PRJ).l
FLEXCPPS = lex.yy.c

BISON = bison
BISONFLAGS = -d -t
BISONSRCS = $(PRJ).y
BISONCPPS = $(PRJ).tab.c
BISONHDRS = $(PRJ).tab.h

OPTIONHDRS = options/*.hpp
OPTIONSRCS = options/*.cpp

HDRS = scanType.hpp $(OPTIONHDRS)
SRCS = $(OPTIONSRCS)

PRJ = c-

$(PRJ): $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS) $(HDRS) $(SRCS)
	$(CXX) $(FLEXCPPS) $(BISONCPPS) $(CXXFLAGS) -o $(PRJ)

qc: # quick clean, remove everything but binary and .tar
	rm $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS)

clean:
	rm $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS) $(PRJ) $(PRJ).tar

tar: $(SRCS) $(HDRS) makefile
	tar -cvf $(PRJ).tar $(SRCS) $(HDRS) makefile

$(BISONCPPS): $(BISONSRCS)
	$(BISON) $(BISONFLAGS) $(PRJ).y

$(FLEXCPPS): $(FLEXSRCS) $(BISONCPPS) $(BISONHDRS)
	$(FLEX) $(FLEXFLAGS) $(PRJ).l

CXX = g++
CXXFLAGS = --std=c++17 #-ly

FLEX = flex
FLEXFLAGS =
FLEXCPPS = lex.yy.c

BISON = bison
BISONFLAGS = -d -t
BISONCPPS = $(PRJ).tab.c
BISONHDRS = $(PRJ).tab.h

HDRS = scanType.hpp
SRCS = $(PRJ).l $(PRJ).y

PRJ = c-

$(PRJ): $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS)
	$(CXX) $(FLEXCPPS) $(BISONCPPS) $(CXXFLAGS) -o $(PRJ)

qc: # quick clean, remove everything but binary and .tar
	rm $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS)

clean:
	rm $(FLEXCPPS) $(BISONCPPS) $(BISONHDRS) $(PRJ) $(PRJ).tar

tar: $(SRCS) $(HDRS) makefile
	tar -cvf $(PRJ).tar $(SRCS) $(HDRS) makefile

$(BISONCPPS): $(PRJ).y
	$(BISON) $(BISONFLAGS) $(PRJ).y

$(FLEXCPPS): $(PRJ).l $(BISONCPPS) $(BISONHDRS)
	$(FLEX) $(FLEXFLAGS) $(PRJ).l

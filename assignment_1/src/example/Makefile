CXX = g++
CXXFLAGS = #-ly

FLEX = FLEX
FLEXFLAGS =
FLEXGENS = lex.yy.c

BISON = BISON
BISONFLAGS = -d
BISONGENS = y.tab.c y.tab.h

PRJ = c-

$(PRJ): $(FLEXGENS) $(BISONGENS)
	$(CXX) $(FLEXGENS) $(BISONGENS) $(CXXFLAGS) -o $(PRJ)

clean:
	rm $(lexGENS) $(yaccGENS) $(PRJ)

$(BISONGENS): $(PRJ).y
	$(BISON) $(BISONFLAGS) $(PRJ).y

$(FLEXGENS): $(PRJ).l $(BISONGENS)
	$(FLEX) $(FLEXFLAGS) $(PRJ).l

#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#  Mika Peer Shalem, mpeersha
#  
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAIN2          = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
SOURCE2        = $(MAIN2).cpp
OBJECT2        = $(MAIN2).o
ADT_TEST       = $(ADT)Client
ADT_TEST2      = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(MAIN2): $(OBJECT2) $(ADT_OBJECT)
	$(LINK) $(MAIN2) $(OBJECT2) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(ADT_TEST2): $(ADT_TEST2).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST2) $(ADT_TEST2).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(OBJECT2): $(SOURCE2) $(ADT_HEADER)
	$(COMPILE) $(SOURCE2)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_TEST2).o: $(ADT_TEST2).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST2).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(MAIN2) $(ADT_TEST) $(ADT_TEST2) $(OBJECT) $(OBJECT2) $(ADT_TEST).o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(MAIN2)Check: $(MAIN2)
	$(MEMCHECK) $(MAIN2) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)

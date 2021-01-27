mkfile_path = $(abspath $(lastword $(MAKEFILE_LIST)))
THISDIR := $(dir $(mkfile_path))

LDFLAGS=-L$(THISDIR)libzim/build/src -L$(THISDIR)lexbor
LIBS=-lzim -llexbor-html -llexbor-dom
INC=-I$(THISDIR)libzim/build/include -I$(THISDIR)libzim/include -I$(THISDIR)lexbor/source
CXXFLAGS=-std=c++11

all:	run
	echo "done"


clean::
	rm -f *.o *.core textextractor

textextractor:	textextractor.cpp
	g++ $(CXXFLAGS) $(INC) $(LDFLAGS) -o $@ textextractor.cpp $(LIBS)


run:    textextractor 
	LD_LIBRARY_PATH="./libzim/build/src:./lexbor" ./textextractor wikipedia_en_100_mini_2021-01.zim

CXX=mingw32-g++
CXXFLAGS=-Wall -O3 -mwindows -mconsole
SRC=$(wildcard $(SRCDIR)/*.cpp)
BIN=$(patsubst %.cpp,$(BINDIR)/%,$(SRC:$(SRCDIR)/%=%))
BINDIR=bin
SRCDIR=src

$(BINDIR)/%: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
all: mkdir $(BIN)
clean:
	rm -r $(BINDIR)/*
mkdir:
	test -d $(BINDIR) || mkdir $(BINDIR)
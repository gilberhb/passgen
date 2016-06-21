OBJECTS:=main.o
HEADERS:=
CXXFLAGS:=-O3 -std=c++11

LDFLAGS:=-lboost_locale -lboost_program_options
LD:=g++

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

passgen: $(OBJECTS)
	$(LD) $(OBJECTS) -o passgen $(LDFLAGS)


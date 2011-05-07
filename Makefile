
SRC=$(wildcard spec/*.cpp)
OBJ=$(SRC:.cpp=.o)

CPPFLAGS+=-Wall -Wextra -pedantic -g

run: specsuite
	./specsuite

specsuite: $(OBJ)
	$(LINK.cpp) $^ -o $@


clean:
	$(RM) $(OBJ) specsuite


spec/spec_wtf8.o: wtf8.h spec/spec.h


CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix obj/, $(CPP_FILES:.cpp=.o))

MACRO_FLAGS := -DflagLOG_DEBUG

CC_FLAGS := -O2 -std=c++11 $(MACRO_FLAGS) -g
LD_FLAGS := -static

bin: $(OBJ_FILES)
	g++-4.8 -o $@ $^ $(LD_FLAGS)

obj/%.o: %.cpp
	mkdir -p obj
	g++-4.8 $(CC_FLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm obj/*

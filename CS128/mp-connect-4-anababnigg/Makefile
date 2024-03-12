INCLUDES=-I includes/
CXXFLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O1 -gdwarf-4 -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always -Wno-error=unused-parameter
CXX=clang++

clean:
	rm -f bin/*

exec: ./src/main.cc ./src/board.cc ./includes/board.hpp
	$(CXX) $(CXXFLAGS) ./src/main.cc ./src/board.cc -o bin/exec

obj/tests_main.o: ./tests/tests_main.cc ./includes/board.hpp
	$(CXX) -std=c++20 -Iincludes -gdwarf-4 -fstandalone-debug -O0 -Wall -Wextra -pedantic -c ./tests/tests_main.cc -o $@

tests: ./tests/tests.cc ./src/board.cc ./includes/board.hpp ./obj/tests_main.o
	$(CXX) -std=c++20 -Iincludes -gdwarf-4 -fstandalone-debug -O0 -Wall -Wextra -pedantic ./tests/tests.cc ./src/board.cc ./obj/tests_main.o -o bin/tests

src/%.cc: includes/%.hpp
	touch $@

.DEFAULT_GOAL := exec
.PHONY: tests clean exec
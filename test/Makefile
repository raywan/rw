O_LEVEL := 0
SRC_FILES := main.cpp
CC := g++

.PHONY: run_rw_test
run_rw_test: $(SRC_FILES)
	time $(CC) -std=c++11 -pthread -ggdb -O$(O_LEVEL) $(SRC_FILES) -o $@

O_LEVEL := 0
SRC_FILES := main.cpp

.PHONY: run_rw_test
run_rw_test: $(SRC_FILES)
	time g++ -std=c++11 -pthread -O$(O_LEVEL) $(SRC_FILES) -o $@


# clang:
# 	time clang++ -std=c++11 main.cpp foo.cpp -o main

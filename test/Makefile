O_LEVEL := 0
SRC_FILES := main.cpp foo.cpp v2_test.cpp v3_test.cpp v4_test.cpp m4_test.cpp

run_rw_test: $(SRC_FILES)
	time g++ -std=c++11 -O$(O_LEVEL) $(SRC_FILES) -o $@

# clang:
# 	time clang++ -std=c++11 main.cpp foo.cpp -o main

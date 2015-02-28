
CXXFLAGS=-Wall -Werror -Wno-unused-function -Iincludes/

all:
	@mkdir -p bin
	@echo "G++:     " `g++ --version | head -n 1`
	@echo "Clang++: " `clang++ --version | head -n 1`
	@echo "Machine: " `uname -rp`
	@echo
	
	@echo -n " simple_example.cpp   Expect build failure with G++             "
	@ ! g++ ${CXXFLAGS} simple_example.cpp -o bin/simple_gxx 2>/dev/null
	@echo "[OK]"
	@echo -n " simple_example.cpp   Expect build success with G++ c++0x       "
	@g++ ${CXXFLAGS} -std=c++0x simple_example.cpp -o bin/simple_gxx_cxx0x
	@echo "[OK]"
	@echo -n " simple_example.cpp   Expect build success with G++ gnu++11     "
	@g++ ${CXXFLAGS} -std=gnu++11 simple_example.cpp -o bin/simple_gxx_gnuxx11
	@echo "[OK]"
	@echo -n " simple_example.cpp   Expect build success with G++ c++11       "
	@g++ ${CXXFLAGS} -std=c++11 simple_example.cpp -o bin/simple_gxx_cxx11
	@echo "[OK]"
	@echo
	
	@echo -n " simple_example.cpp   Expect build failure with Clang++         "
	@ ! clang++ ${CXXFLAGS} simple_example.cpp -o bin/simple_clangxx 2>/dev/null
	@echo "[OK]"
	@echo -n " simple_example.cpp   Expect build success with Clang++ c++0x   "
	@clang++ ${CXXFLAGS} -std=c++0x simple_example.cpp -o bin/simple_clangxx_cxx0x
	@echo "[OK]"
	@echo -n " simple_example.cpp   Expect build success with Clang++ gnu++11 "
	@clang++ ${CXXFLAGS} -std=gnu++11 simple_example.cpp -o bin/simple_clangxx_gnuxx11
	@echo "[OK]"
	@echo -n " simple_example.cpp   Expect build success with Clang++ c++11   "
	@clang++ ${CXXFLAGS} -std=c++11 simple_example.cpp -o bin/simple_clangxx_cxx11
	@echo "[OK]"
	@echo
	
	@echo -n " logging_example.cpp  Expect build failure with G++             "
	@ ! g++ ${CXXFLAGS} logging_example.cpp -o bin/logging_gxx 2>/dev/null
	@echo "[OK]"
	@echo -n " logging_example.cpp  Expect build success with G++ c++0x       "
	@g++ ${CXXFLAGS} -std=c++0x logging_example.cpp -o bin/logging_gxx_cxx0x
	@echo "[OK]"
	@echo -n " logging_example.cpp  Expect build success with G++ gnu++11     "
	@g++ ${CXXFLAGS} -std=gnu++11 logging_example.cpp -o bin/logging_gxx_gnuxx11
	@echo "[OK]"
	@echo -n " logging_example.cpp  Expect build success with G++ c++11       "
	@g++ ${CXXFLAGS} -std=c++11 logging_example.cpp -o bin/logging_gxx_cxx11
	@echo "[OK]"
	@echo
	
	@echo -n " logging_example.cpp  Expect build failure with Clang++         "
	@ ! clang++ ${CXXFLAGS} logging_example.cpp -o bin/logging_clangxx 2>/dev/null
	@echo "[OK]"
	@echo -n " logging_example.cpp  Expect build success with Clang++ c++0x   "
	@clang++ ${CXXFLAGS} -std=c++0x logging_example.cpp -o bin/logging_clangxx_cxx0x
	@echo "[OK]"
	@echo -n " logging_example.cpp  Expect build success with Clang++ gnu++11 "
	@clang++ ${CXXFLAGS} -std=gnu++11 logging_example.cpp -o bin/logging_clangxx_gnuxx11
	@echo "[OK]"
	@echo -n " logging_example.cpp  Expect build success with Clang++ c++11   "
	@clang++ ${CXXFLAGS} -std=c++11 logging_example.cpp -o bin/logging_clangxx_cxx11
	@echo "[OK]"
	@echo

clean:
	@rm -rf bin

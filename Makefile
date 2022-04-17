# Required packages:
# Ubuntu 20.04: clang-12

# CC=~/llvm-project/build/bin/clang
# CXX=~/llvm-project/build/bin/clang++
# OPT=~/llvm-project/build/bin/opt
# LLVM_CONFIG=~/llvm-project/build/bin/llvm-config
# LLC=~/llvm-project/build/bin/llc

CC=clang
CXX=clang++-12
OPT=opt-12
LLVM_CONFIG=llvm-config-12
LLC=llc-12

CFLAGS=-O0 -Werror -Wall -pedantic -fno-inline-functions -fPIC
LDLIBS=-lm

IDIR=include

BENCH=binary_trees
# BENCH=intrinsics
# BENCH=indirect_call
# BENCH=llvm_intrinsics

PASS_NAME=farguments_info
PASS_FUNC_NAME=farguments_info_functions

BENCH_PATH=tests/$(BENCH)
PASS_PATH=src/$(PASS_NAME)
PASS_FUNC_PATH=src/$(PASS_FUNC_NAME)
PASS_OBJ_PATH=obj/$(PASS_NAME)

ARGSLIM=NO

$(PASS_OBJ_PATH).so: $(PASS_PATH).cpp $(PASS_FUNC_PATH).cpp 
	$(CXX) $(CFLAGS) -I$(IDIR) `$(LLVM_CONFIG) --cxxflags` -shared -fPIC $(PASS_PATH).cpp $(PASS_FUNC_PATH).cpp -o $@

.PHONY: run-bench
run-bench: $(BENCH_PATH).c $(PASS_OBJ_PATH).so
	$(CC) $(CFLAGS) -S -emit-llvm -o $(BENCH_PATH).orig.ll $<
ifeq ($(ARGSLIM), NO)
	$(OPT) -load ./$(PASS_OBJ_PATH).so -S -$(PASS_NAME) < $(BENCH_PATH).orig.ll > $(BENCH_PATH).ll
else
	$(OPT) -load ./$(PASS_OBJ_PATH).so -S -$(PASS_NAME) --args-limit=$(ARGSLIM) < $(BENCH_PATH).orig.ll > $(BENCH_PATH).ll
endif

.PHONY: clean
clean:
	rm -f $(BENCH_PATH) \
	      obj/*.so \
	      ../tests/*.ll ../tests/*.s

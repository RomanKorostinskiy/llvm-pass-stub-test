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

CFLAGS=-O2 -Werror -Wall -pedantic -fno-inline-functions -fPIC
LDLIBS=-lm

BENCH=binary_trees
# BENCH=intrinsics
# BENCH=example
# BENCH=llvm_intrinsics

BENCH_PATH=../tests/$(BENCH)

PASS_NAME=farguments_info

ARGSLIM=NO

$(PASS_NAME).so: $(PASS_NAME).cpp
	$(CXX) $(CFLAGS) `$(LLVM_CONFIG) --cxxflags` -shared -fPIC -g -o $@ $<

.PHONY: run-bench
run-bench: $(BENCH_PATH).c $(PASS_NAME).so
	$(CC) $(CFLAGS) -S -emit-llvm -o $(BENCH_PATH).orig.ll $<
ifeq ($(ARGSLIM), NO)
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) < $(BENCH_PATH).orig.ll > $(BENCH_PATH).ll
else
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) --args-limit=$(ARGSLIM) < $(BENCH_PATH).orig.ll > $(BENCH_PATH).ll
endif
# 	$(LLC) -O2 --relocation-model=pic -o $(BENCH_PATH).s $(BENCH_PATH).ll
# 	$(CC) $(LDLIBS) $(BENCH_PATH).s -o $(BENCH_PATH)

.PHONY: run-bench-debug
run-bench-debug: $(BENCH_PATH).c $(PASS_NAME).so
	$(CC) $(CFLAGS) -S -emit-llvm -o $(BENCH_PATH).orig.ll $<
ifeq ($(ARGSLIM), NO)
	$(OPT) -enable-new-pm=0 -load-pass-plugin ./$(PASS_NAME).so -S -$(PASS_NAME) < $(BENCH_PATH).orig.ll > $(BENCH_PATH).ll
else
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) --args-limit=$(ARGSLIM) < $(BENCH_PATH).orig.ll > $(BENCH_PATH).ll
endif

.PHONY: clean
clean:
	rm -f $(BENCH_PATH) \
	      *.so \
	      ../tests/*.ll ../tests/*.s
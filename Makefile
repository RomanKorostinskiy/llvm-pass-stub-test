# Required packages:
# Ubuntu 20.04: clang-12
CC=clang-12
CXX=clang++-12
OPT=opt-12
LLVM_CONFIG=llvm-config-12
LLC=llc-12

CFLAGS=-O0 -Werror -Wall -pedantic -fno-inline-functions -fPIC
LDLIBS=-lm

# BENCH=tests/binary_trees
# BENCH=tests/simple_test
BENCH=tests/example

# PASS_NAME=fname_printer
# PASS_NAME=farguments_counter
PASS_NAME=farguments_limiter

ARGSLIM=2

$(PASS_NAME).so: $(PASS_NAME).cpp
	$(CXX) $(CFLAGS) `$(LLVM_CONFIG) --cxxflags` -shared -fPIC -o $@ $<


$(BENCH): $(BENCH).c $(PASS_NAME).so
	$(CC) $(CFLAGS) -S -emit-llvm -o $(BENCH).orig.ll $<
ifeq ($(PASS_NAME),farguments_limiter)
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) --args-limit=$(ARGSLIM) < $(BENCH).orig.ll > $(BENCH).ll
else
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) < $(BENCH).orig.ll > $(BENCH).ll
endif
	$(LLC) -O2 --relocation-model=pic -o $(BENCH).s $(BENCH).ll
	$(CC) $(LDLIBS) $(BENCH).s -o $@

.PHONY: clean
clean:
	rm -f $(BENCH) \
	      $(PASS_NAME).so \
	      $(BENCH).orig.ll $(BENCH).ll $(BENCH).s 
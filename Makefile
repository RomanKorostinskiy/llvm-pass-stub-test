# Required packages:
# Ubuntu 20.04: clang-12
CC=clang-12
CXX=clang++-12
OPT=opt-12
LLVM_CONFIG=llvm-config-12
LLC=llc-12

CFLAGS=-O2 -Werror -Wall -pedantic -fno-inline-functions -fPIC
LDLIBS=-lm

BENCH1=tests/binary_trees
BENCH2=tests/simple_test
BENCH3=tests/example

PASS_NAME=farguments_counter
#PASS_NAME=fname_printer

$(PASS_NAME).so: $(PASS_NAME).cpp
	$(CXX) $(CFLAGS) `$(LLVM_CONFIG) --cxxflags` -shared -fPIC -o $@ $<

$(BENCH1): $(BENCH1).c $(PASS_NAME).so
	$(CC) $(CFLAGS) -S -emit-llvm -o $(BENCH1).orig.ll $<
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) < $(BENCH1).orig.ll > $(BENCH1).ll
	$(LLC) -O2 --relocation-model=pic -o $(BENCH1).s $(BENCH1).ll
	$(CC) $(LDLIBS) $(BENCH1).s -o $@

$(BENCH2): $(BENCH2).c $(PASS_NAME).so
	$(CC) $(CFLAGS) -S -emit-llvm -o $(BENCH2).orig.ll $<
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) < $(BENCH2).orig.ll > $(BENCH2).ll
	$(LLC) -O2 --relocation-model=pic -o $(BENCH2).s $(BENCH2).ll
	$(CC) $(LDLIBS) $(BENCH2).s -o $@

$(BENCH3): $(BENCH3).c $(PASS_NAME).so
	$(CC) $(CFLAGS) -S -emit-llvm -o $(BENCH3).orig.ll $<
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) < $(BENCH3).orig.ll > $(BENCH3).ll
	$(LLC) -O2 --relocation-model=pic -o $(BENCH3).s $(BENCH3).ll
	$(CC) $(LDLIBS) $(BENCH3).s -o $@

.PHONY: clean
clean:
	rm -f $(BENCH1) \
	      $(BENCH2) \
	      $(BENCH3) \
	      $(PASS_NAME).so \
	      $(BENCH1).orig.ll $(BENCH1).ll $(BENCH1).s \
	      $(BENCH2).orig.ll $(BENCH2).ll $(BENCH2).s \
	      $(BENCH3).orig.ll $(BENCH3).ll $(BENCH3).s

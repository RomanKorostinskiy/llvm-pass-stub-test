# Required packages:
# Ubuntu 20.04: clang-11 gcc-aarch64-linux-gnu g++-aarch64-linux-gnu qemu-user
# Ubuntu 18.04 (change 11 to 10): clang-10 gcc-aarch64-linux-gnu g++-aarch64-linux-gnu qemu-user
CC=clang-11
CXX=clang++-11
OPT=opt-11
LLVM_CONFIG=llvm-config-11
LLC=llc-11

CFLAGS=-O2 -Werror -Wall -pedantic -fno-inline-functions -fPIC
LDLIBS=-lm

BENCH=binary_trees
PASS_NAME=fname_printer

$(PASS_NAME).so: $(PASS_NAME).cpp
	$(CXX) $(CFLAGS) `$(LLVM_CONFIG) --cxxflags` -shared -fPIC -o $@ $<

$(BENCH): $(BENCH).c $(PASS_NAME).so
	$(CC) $(CFLAGS) -S -emit-llvm -o $(BENCH).orig.ll $<
	$(OPT) -load ./$(PASS_NAME).so -S -$(PASS_NAME) < $(BENCH).orig.ll > $(BENCH).ll
	$(LLC) -O2 --relocation-model=pic -o $(BENCH).s $(BENCH).ll
	$(CC) $(LDLIBS) $(BENCH).s -o $@

.PHONY: clean
clean:
	rm -f $(BENCH) \
	      $(PASS_NAME).so \
	      $(BENCH).orig.ll $(BENCH).ll $(BENCH).s

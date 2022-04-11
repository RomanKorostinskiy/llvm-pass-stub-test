# llvm-pass-stub-test
Simple pass, that can counts the maximum number of arguments used in direct and indirect function calls. It can also take an arguments limit and give a warning message if the function has a call with more arguments than the limit. This pass does not change the code.

## How to build and run pass
- To run the pass, you need to be in the folder ```llvm-pass-stub-test/farguments_info``` and execute the command ```$make run-bench```
- To change the benchmark file, you should change ```BENCH``` variable in the Makefile to ```<bench-name>```. Where ```<bench-name>``` is the name of bench file in the folder ```llvm-pass-stub-test/tests```
- To start arguments limiting mode, you should change ```ARGSLIM``` variable in the Makefile to limit of arguments that you want. That brings to use comand line argument ```--args-limit=$(ARGSLIM)```. If you want to return the maximum number of arguments counting mode, you must change the ```ARGSLIM``` variable in the Makefile to ```NO``` or ```-1```
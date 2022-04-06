#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "llvm/Support/CommandLine.h"
// #include "llvm/Support/Error.h"
#include "stdlib.h"

using namespace llvm;

 static cl::opt<int>
     ArgsLimit("args-limit", cl::init(-1), 
                     cl::desc("The limit of function call arguments"));

namespace {
struct FArgumentsInfo : public FunctionPass {
  static char ID;

  FArgumentsInfo() : FunctionPass(ID) {}

  void PrintLimitExceedingMessage(Function *F) {
    if (F == nullptr) {
      llvm::errs() << '\t' << " Exceeding the arguments limit occured in "
        << "indirect function call " << "\n";
    } else {
      llvm::errs() << '\t' << " Exceeding the arguments limit occured in \'"
        << F->getName() << "\' function call " << "\n";
    }
  }

  void PrinMaxArgsMessage(Function *F, int max_args_amount) {
    if (max_args_amount == -1) {
      llvm::errs() << "\tNo calls in this function\n";
    } else if (F == nullptr) {
      llvm::errs() << '\t' << " Maximum arguments number " << max_args_amount
        << " in indirect function call " << "\n";
    } else {
      llvm::errs() << '\t' << " Maximum arguments number " << max_args_amount
        << " in \'" << F->getName() << "\' function call " << "\n";
    }
  }

  void FArgumentsLimiter(Function &F) {
    for (auto &BB: F) {
      for (auto &I: BB) {
        if (I.getOpcode() == Instruction::Call) {
          CallInst* call_inst = cast<CallInst>(&I);
          int args_amount = call_inst->arg_size();
          if (args_amount > ArgsLimit) {
            llvm::errs() << "In Function " << F.getName() << ":\n";
            PrintLimitExceedingMessage(call_inst->getCalledFunction());
            return;
          }
        }
      }
    }
  }

  void FArgumentsCouner(Function &F) {
    int max_args_amount = -1;
    Function* called_function = nullptr;

    for (auto &BB: F) {
      for (auto &I: BB) {
        if (I.getOpcode() == Instruction::Call) {
          CallInst* call_inst = cast<CallInst>(&I);
          int args_amount = call_inst->arg_size();
          if (args_amount > max_args_amount) {
            called_function = call_inst->getCalledFunction();
            max_args_amount = args_amount;
          }
        }
      }
    }

    llvm::errs() << "In Function " << F.getName() << ":\n";
    PrinMaxArgsMessage(called_function, max_args_amount);

  }

  bool runOnFunction(Function &F) override {
    if (ArgsLimit >= 0) {
      FArgumentsLimiter(F);
    } else if (ArgsLimit == -1){
      FArgumentsCouner(F);
    } else {
      llvm::errs() << "error: wrong arguments limit\n";
      exit(EXIT_FAILURE); //TODO: use llvm/Support/Error.h
    }
    return false;
  }
}; // end of struct FArgumentsInfo
}  // end of anonymous namespace

char FArgumentsInfo::ID = 0;
static RegisterPass<FArgumentsInfo> X("farguments_info", "FArgumentsInfo Pass",
                                   true /* Only looks at CFG */,
                                   false /* Analysis Pass */);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new FArgumentsInfo()); });

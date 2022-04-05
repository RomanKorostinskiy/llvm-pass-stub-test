#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct FArgumentsCounter : public FunctionPass {
  static char ID;
  FArgumentsCounter() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
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

    if (max_args_amount == -1) {
      llvm::errs() << "\tNo calls in this function\n";
    } else if (called_function == nullptr) {
      llvm::errs() << '\t' << " Maximum arguments number " << max_args_amount
        << " in indirect function call " << "\n";
    } else {
      llvm::errs() << '\t' << " Maximum arguments number " << max_args_amount
        << " in \'" << called_function->getName() << "\' function call " << "\n";
    }

    return false;
  }
}; // end of struct FArgumentsCounter
}  // end of anonymous namespace

char FArgumentsCounter::ID = 0;
static RegisterPass<FArgumentsCounter> X("farguments_counter", "FArgumentsCounter Pass",
                                   true /* Only looks at CFG */,
                                   false /* Analysis Pass */);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new FArgumentsCounter()); });

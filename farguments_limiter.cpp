#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "llvm/Support/CommandLine.h"

using namespace llvm;

 static cl::opt<unsigned>
     ArgsLimit("args-limit", cl::Required, 
                     cl::desc("The limit of function call arguments"));

namespace {
struct FArgumentsLimiter : public FunctionPass {
  static char ID;

  FArgumentsLimiter() : FunctionPass(ID) {}

  void PrintLimitExceedingMessage(Function* F) {
    if (F == nullptr) {
      llvm::errs() << '\t' << " Exceeding the arguments limit occured in "
        << "indirect function call " << "\n";
    } else {
      llvm::errs() << '\t' << " Exceeding the arguments limit occured in \'"
        << F->getName() << "\' function call " << "\n";
    }
  }

  bool runOnFunction(Function &F) override {
    for (auto &BB: F) {
      for (auto &I: BB) {
        if (I.getOpcode() == Instruction::Call) {
          CallInst* call_inst = cast<CallInst>(&I);
          unsigned args_amount = call_inst->arg_size();
          if (args_amount > ArgsLimit) {
            llvm::errs() << "In Function " << F.getName() << ":\n";
            PrintLimitExceedingMessage(call_inst->getCalledFunction());
            return false;
          }
        }
      }
    }
    return false;
  }
}; // end of struct FArgumentsLimiter
}  // end of anonymous namespace

char FArgumentsLimiter::ID = 0;
static RegisterPass<FArgumentsLimiter> X("farguments_limiter", "FArgumentsLimiter Pass",
                                   true /* Only looks at CFG */,
                                   false /* Analysis Pass */);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new FArgumentsLimiter()); });

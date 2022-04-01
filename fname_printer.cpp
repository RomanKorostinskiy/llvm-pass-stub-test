#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct FNamePrinter : public FunctionPass {
  static char ID;
  FNamePrinter() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    llvm::errs() << F.getName() << "\n";
    return false;
  }
}; // end of struct FNamePrinter
}  // end of anonymous namespace

char FNamePrinter::ID = 0;
static RegisterPass<FNamePrinter> X("fname_printer", "FNamePrinter Pass",
                                   false /* Only looks at CFG */,
                                   false /* Analysis Pass */);

static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new FNamePrinter()); });

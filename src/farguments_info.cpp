#include "../include/farguments_info.h"

using namespace llvm;

static cl::opt<int> 
  ArgsLimit("args-limit", cl::init(ArgsCntrMode),
            cl::desc("the limit of function call arguments"));

namespace {
struct FArgumentsInfo : public FunctionPass {
  static char ID;

  FArgumentsInfo() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    if (ArgsLimit >= 0) {
      argumentsLimiter(F, ArgsLimit);
    } else if (ArgsLimit == ArgsCntrMode) {
      argumentsCouner(F);
    } else {
      llvm::errs() << "error: wrong arguments limit.\n";
      exit(EXIT_FAILURE);
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

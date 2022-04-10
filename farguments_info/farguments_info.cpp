#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Casting.h"
// #include "llvm/Support/Error.h"
#include "stdlib.h"
// #include "sstream"

using namespace llvm;

enum Constants {
  NO_FUNCTION_CALLS = -2,
  ARGS_CNTR_MODE    = -1
};

static cl::opt<int>
   ArgsLimit("args-limit", cl::init(ARGS_CNTR_MODE), 
                   cl::desc("The limit of function call arguments"));

namespace {

bool isAssumeLikeIntrinsic(Intrinsic::ID intr_id) { //TODO: fix calling this method from the library
  switch (intr_id) {
  default: break;
  case Intrinsic::assume:
  case Intrinsic::sideeffect:
  case Intrinsic::pseudoprobe:
  case Intrinsic::dbg_declare:
  case Intrinsic::dbg_value:
  case Intrinsic::dbg_label:
  case Intrinsic::invariant_start:
  case Intrinsic::invariant_end:
  case Intrinsic::lifetime_start:
  case Intrinsic::lifetime_end:
  case Intrinsic::experimental_noalias_scope_decl:
  case Intrinsic::objectsize:
  case Intrinsic::ptr_annotation:
  case Intrinsic::var_annotation:
    return true;
  }
  return false;
}

struct FArgumentsInfo : public FunctionPass {
  static char ID;

  FArgumentsInfo() : FunctionPass(ID) {}

  void PrintLimitExceedingMessage(std::string call_inst_msg) {
      llvm::errs() << '\t' << " Exceeding the arguments limit occured "
      "in " << call_inst_msg << "\n";
  }

  void PrinMaxArgsMessage(std::string call_inst_msg, int max_args_amount) {
    if (max_args_amount == NO_FUNCTION_CALLS) {
      llvm::errs() << "\tNo calls in this function\n";
    } else {
      llvm::errs() << '\t' << " Maximum arguments number " << max_args_amount
        << " in " << call_inst_msg << "\n";
    }
  }

  void GenerateCallInstructionMessage(CallInst* CallInst, std::string &msg_str) { //TODO: make simple instruction generation
    if (CallInst == nullptr) {
      return;
    }
    llvm::raw_string_ostream call_inst_msg(msg_str); //TODO: How to use llvm:raw_ostream constructor
    Function* called_func = CallInst->getCalledFunction();
    if (called_func == nullptr) {
      call_inst_msg << "indirect function call: " << "... call ... ";
    } else {
      call_inst_msg << "function call: ";

      if (cast<Value>(CallInst)->hasName()) {
        call_inst_msg << cast<Value>(CallInst)->getNameOrAsOperand() << " = ... call ... " ;
      } else {
        call_inst_msg << "<No name>" << " ... call ... ";
      }

      call_inst_msg << called_func->getName() << " ... ";
    }

    msg_str = call_inst_msg.str();
  }

  void FArgumentsLimiter(Function &F) {
    for (auto &BB: F) {
      for (auto &I: BB) {
        if (I.getOpcode() == Instruction::Call) {
          CallInst* call_inst = cast<CallInst>(&I);
          if (isAssumeLikeIntrinsic(call_inst->getIntrinsicID()) ||
            call_inst->isInlineAsm()) {
            continue;
          }
          int args_amount = call_inst->arg_size();
          if (args_amount > ArgsLimit) {
            llvm::errs() << "In Function " << F.getName() << ":\n";
            std::string call_inst_msg;
            GenerateCallInstructionMessage(call_inst, call_inst_msg);
            PrintLimitExceedingMessage(call_inst_msg);
            return;
          }
        }
      }
    }
  }

  void FArgumentsCouner(Function &F) {
    int max_args_amount = NO_FUNCTION_CALLS;
    CallInst* max_args_call_inst = nullptr;

    for (auto &BB: F) {
      for (auto &I: BB) {
        if (I.getOpcode() == Instruction::Call) {
          CallInst* call_inst = cast<CallInst>(&I);
          if (isAssumeLikeIntrinsic(call_inst->getIntrinsicID()) ||
            call_inst->isInlineAsm()) {
            continue;
          }
          int args_amount = call_inst->arg_size();
          if (args_amount > max_args_amount) {
            max_args_call_inst = call_inst;
            max_args_amount = args_amount;
          }
        }
      }
    }

    llvm::errs() << "In Function " << F.getName() << ":\n";
    std::string call_inst_msg;
    GenerateCallInstructionMessage(max_args_call_inst, call_inst_msg);
    PrinMaxArgsMessage(call_inst_msg, max_args_amount);
  }

  bool runOnFunction(Function &F) override {
    if (ArgsLimit >= 0) {
      FArgumentsLimiter(F);
    } else if (ArgsLimit == ARGS_CNTR_MODE) {
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

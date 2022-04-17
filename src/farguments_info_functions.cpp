#include "farguments_info.h"

using namespace llvm;

void argumentsLimiter(Function &F, int ArgsLimit) {
  for (auto &BB: F) {
    for (auto &I: BB) {
      if (I.getOpcode() != Instruction::Call) continue;

      CallInst* CallInstruction = cast<CallInst>(&I);
      if (isIgnoredCallInstruction(CallInstruction)) continue;

      int ArgsAmount = CallInstruction->arg_size();
      if (isMemIntrinsicWithIsvolatileFlag(CallInstruction->getIntrinsicID()))
        --ArgsAmount;
      if (ArgsAmount > ArgsLimit) {
        llvm::errs() << "In Function " << F.getName() << ":\n";
        printLimitExceedingMessage(CallInstruction);
        return;
      }
    }
  }
}
void argumentsCouner(Function &F) {
  int MaxArgsAmount = NoFunctionCalls;
  CallInst* MaxArgsCallInstruction = nullptr;

  for (auto &BB: F) {
    for (auto &I: BB) {
      if (I.getOpcode() != Instruction::Call) continue;

      CallInst* CallInstruction = cast<CallInst>(&I);
      if (isIgnoredCallInstruction(CallInstruction)) continue;

      int ArgsAmount = CallInstruction->arg_size();
      if (isMemIntrinsicWithIsvolatileFlag(CallInstruction->getIntrinsicID()))
        --ArgsAmount;
      if (ArgsAmount > MaxArgsAmount) {
        MaxArgsCallInstruction = CallInstruction;
        MaxArgsAmount = ArgsAmount;
      }
    }
  }

  llvm::errs() << "In Function " << F.getName() << ":\n";
  printMaxArgsMessage(MaxArgsCallInstruction, MaxArgsAmount);
}

void printLimitExceedingMessage(CallInst* CallInstruction) {
  std::string str = "";
  llvm::raw_string_ostream CallInstMsg(str);
  CallInstruction->print(CallInstMsg);

  llvm::errs() << "\t Exceeding the arguments limit occured";
  if (CallInstruction->isIndirectCall())
    llvm::errs() << " in indirect function call:";
  else
    llvm::errs() << " in function call:";
  llvm::errs() << CallInstMsg.str() << "\n";
}
void printMaxArgsMessage(CallInst* CallInstruction, int MaxArgsAmount) {
  if (MaxArgsAmount == NoFunctionCalls) {
    llvm::errs() << "\tNo calls in this function\n";
    return;
  }

  std::string str = "";
  llvm::raw_string_ostream CallInstMsg(str);
  CallInstruction->print(CallInstMsg);

  llvm::errs() << "\t Maximum arguments number " << MaxArgsAmount;
  if (CallInstruction->isIndirectCall())
    llvm::errs() << " in indirect function call:";
  else
    llvm::errs() << " in function call:";
  llvm::errs() << CallInstMsg.str() << "\n";
}

bool isIgnoredCallInstruction(CallInst* CallInstruction) {
  if (CallInstruction->isInlineAsm() ||
      isAssumeLikeIntrinsic(CallInstruction->getIntrinsicID())) {
    return true;
  }
  return false;
}
bool isAssumeLikeIntrinsic(Intrinsic::ID IntrinsicId) { //TODO: fix calling this method from the library
  switch (IntrinsicId) {
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
bool isMemIntrinsicWithIsvolatileFlag(Intrinsic::ID IntrinsicId) {
  switch (IntrinsicId) {
    default: break;
    case Intrinsic::memset:
    case Intrinsic::memcpy:
    case Intrinsic::memcpy_inline:
    case Intrinsic::memmove:
    return true;
  }
  return false;
}

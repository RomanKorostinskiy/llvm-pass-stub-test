#pragma once

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "stdlib.h"

enum Constants {
  NoFunctionCalls = -2,
  ArgsCntrMode    = -1
};

using namespace llvm;

void argumentsLimiter(Function &F, int ArgsLimit);
void argumentsCouner(Function &F);

void printLimitExceedingMessage(CallInst* CallInstruction);
void printMaxArgsMessage(CallInst* CallInstruction, int MaxArgsAmount);

bool isAssumeLikeIntrinsic(Intrinsic::ID IntrinsicId);
bool isMemIntrinsicWithIsvolatileFlag(Intrinsic::ID IntrinsicId);
bool isIgnoredCallInstruction(CallInst* CallInstruction);

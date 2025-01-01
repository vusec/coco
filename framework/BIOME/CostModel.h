#include <cstddef>
#include <cstdlib>

#include "llvm/ADT/Optional.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"

using namespace llvm;

/// Utility function that reports an error and exits.
inline void reportUnsupported(Instruction &I) {
    errs().changeColor(raw_ostream::Colors::RED) << "error: ";
    errs().resetColor();
    errs() << "Unsupported instruction: " << I;
    exit(1);
}

inline unsigned instructionCacheSize() { return 8; }

inline unsigned getCycleCount(Instruction &I) {
    if (BinaryOperator *BO = dyn_cast<BinaryOperator>(&I)) {
        switch(BO->getOpcode()) {
        case BinaryOperator::BinaryOps::Mul: return 5;
        case BinaryOperator::BinaryOps::Sub: return 4;
        case BinaryOperator::BinaryOps::Add: return 4;
        case BinaryOperator::BinaryOps::Shl: return 4;
        case BinaryOperator::BinaryOps::AShr: return 4;
        case BinaryOperator::BinaryOps::LShr: return 4;
        case BinaryOperator::BinaryOps::And: return 4;
        case BinaryOperator::BinaryOps::Or: return 4;
        case BinaryOperator::BinaryOps::Xor: return 4;
        // Make division stuff expensive like on a real processor.
        case BinaryOperator::BinaryOps::SDiv: return 9;
        case BinaryOperator::BinaryOps::UDiv: return 9;
        case BinaryOperator::BinaryOps::SRem: return 9;
        case BinaryOperator::BinaryOps::URem: return 9;
        default:
            break; // Not supported.
        }
    }

    if (isa<GetElementPtrInst>(I)) return 4;
    if (isa<CmpInst>(I)) return 5;

    if (isa<SExtInst>(I)) return 1;
    if (isa<ZExtInst>(I)) return 1;
    if (isa<TruncInst>(I)) return 1;

    // Casts are free.
    if (isa<BitCastInst>(I)) return 0;
    if (isa<PtrToIntInst>(I)) return 0;

    // We make calls cheap, as the real cost is that they flush the icache
    // when they jump to a new instruction.
    // For simplicity, we keep external library functions cheap.
    if (CallInst *Call = dyn_cast<CallInst>(&I))
        return 1U + Call->getNumOperands();

    // Memory ops.
    if (isa<AllocaInst>(I)) return 2;
    if (isa<LoadInst>(I)) return 4;
    if (isa<StoreInst>(I)) return 4;

    // Control flow stuff.
    if (isa<BranchInst>(I)) return 10;
    if (isa<SwitchInst>(I)) return 10;
    if (isa<ReturnInst>(I)) return 7;
    if (isa<SelectInst>(I)) return 15;

    // Vector stuff.
    if (isa<ExtractValueInst>(I)) return 7;
    if (isa<InsertValueInst>(I)) return 7;

    if (isa<FreezeInst>(I)) return 0;

    // Assume that PHI nodes are not actually lowered to real instructions.
    if (isa<PHINode>(I)) return 0;
    if (isa<UnreachableInst>(I)) return 0;
    reportUnsupported(I);
    return 0;
}
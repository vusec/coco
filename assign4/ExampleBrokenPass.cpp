#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace
{
  struct ExampleBrokenPass : PassInfoMixin<ExampleBrokenPass>
  {
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &)
    {
      if (F.isDeclaration())
        return PreservedAnalyses::all();

      bool Changed = false;
      for (BasicBlock &BB : F) {
        for (Instruction &I : BB) {
            if (LoadInst *L = dyn_cast<LoadInst>(&I)) {
                Type *t = IntegerType::get(F.getContext(), 32);
                if (L->getType() != t)
                    continue;
                L->replaceAllUsesWith(ConstantInt::get(t, 1, /*IsSigned=*/false));
                L->eraseFromParent();
                return PreservedAnalyses::none();
            }
        }
      }
      
      return PreservedAnalyses::all();
    }
  };
} // namespace

// This is just boilerplate to register the pass.
// Do do not need to modify this code.
extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
  return {LLVM_PLUGIN_API_VERSION, "ExampleBrokenPass", LLVM_VERSION_STRING,
          [](PassBuilder &PB)
          {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>)
                {
                  if (Name == "ExampleBrokenPass")
                  {
                    FPM.addPass(ExampleBrokenPass());
                    return true;
                  }
                  return false;
                });
          }};
}
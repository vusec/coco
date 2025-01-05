#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct CocoADCE : PassInfoMixin<CocoADCE> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {\
    // Dummy code for depth first visiting of blocks.
    df_iterator_default_set<BasicBlock *> Reachable;
    for (BasicBlock *BB : depth_first_ext(&F, Reachable)) {
    }

    return PreservedAnalyses::all();
  }
};
} // namespace

// This is just boilerplate to register the pass.
// Do do not need to modify this code.
extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CocoADCE", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "coco-adce") {
                    FPM.addPass(CocoADCE());
                    return true;
                  }
                  return false;
                });
          }};
}
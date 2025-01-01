#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Analysis/ValueTracking.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
struct CocoLICM : PassInfoMixin<CocoLICM> {
  Loop *curLoop = nullptr;
  DominatorTree *DT = nullptr;
  LoopInfo *LI = nullptr;
  PreservedAnalyses run(LoopNest &L, LoopAnalysisManager &AM,
                        LoopStandardAnalysisResults &AR, LPMUpdater &U) {
    LI = &AR.LI;
    DT = &AR.DT;
    curLoop = &L.getOutermostLoop();
    // TODO
    return PreservedAnalyses::none();
  }
};
} // namespace

// This is just boilerplate to register the pass.
// Do do not need to modify this code.
extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "coco-licm", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, LoopPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "coco-licm") {
                    FPM.addPass(CocoLICM());
                    return true;
                  }
                  return false;
                });
          }};
}
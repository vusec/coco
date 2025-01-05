#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Analysis/CallGraph.h"


using namespace llvm;

namespace {
struct CocoInlinerPass : PassInfoMixin<CocoInlinerPass> {
  bool tryInline(Function &f, CallInst &call) {;
    InlineFunctionInfo info;
    auto InlineRes = InlineFunction(call, info);
    assert(InlineRes.isSuccess() && "Expected inlining to succeed");
    return true;
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
    CallGraph cg(M);
    for (auto  &funcAndNode : cg) {
      Function *f = const_cast<Function *>(funcAndNode.first);
      // TODO
    }
    return PreservedAnalyses::all();
  }
};
} // namespace

// This is just boilerplate to register the pass.
// Do do not need to modify this code.
extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CocoInliner", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &PM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "coco-inliner") {
                    PM.addPass(CocoInlinerPass());
                    return true;
                  }
                  return false;
                });
          }};
}
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include "CostModel.h"

using namespace llvm;

static const char *biomePrefix = "[CYCLE COUNT]";

namespace {
struct BIOMEPass : PassInfoMixin<BIOMEPass> {


  struct InstToInstrument {
    Instruction *Inst = nullptr;
    unsigned cycleCount = 0;
    std::size_t index = 0;
    std::string getInfoStr() const {
        std::string buffer;
        llvm::raw_string_ostream result(buffer);
        result << biomePrefix;
        result << " cycles: " << cycleCount << " idx: " << index << " inst: " << *Inst;
        return buffer;
    }
  };
  std::vector<InstToInstrument> toInstrument;

  Module *M = nullptr;
  LLVMContext *C = nullptr;
  llvm::Type *charType = nullptr;
  llvm::Type *ptrInt = nullptr;
  llvm::PointerType *strType = nullptr;
  std::size_t instructionIndex = 0;

  Function *getPutsFunc() {
    if (Function *existing = M->getFunction("puts"))
        return existing;
    const unsigned addrSpace = 0;
    std::vector<llvm::Type *> putsArgs = {strType};
    bool varArg = false;
    FunctionType *putsType = FunctionType::get(IntegerType::get(*C, 32), putsArgs, varArg);
    Function *putsFunc = Function::Create(putsType, GlobalValue::ExternalLinkage, addrSpace, "puts", M);
    return putsFunc;
  }

  void instrument(InstToInstrument &I) {
    IRBuilder<> builder(I.Inst);
    Value *str = builder.CreateGlobalString(I.getInfoStr(), "biome_info");
    str = builder.CreatePointerCast(str, strType);
    std::vector<Value *> printArgs = {str};
    builder.CreateCall(FunctionCallee(getPutsFunc()), printArgs, "biome_print");

    // Add a unique annotation. We use this later to identify each line
    // in the simple biome.py visualizer. THis is just here to make each
    // line have unique content.
    I.Inst->addAnnotationMetadata("BIOME-ID:" + std::to_string(I.index));
  }

  void analyze(Instruction &I) {
    InstToInstrument instrument;
    instrument.Inst = &I;
    instrument.cycleCount = getCycleCount(I);
    if (instrument.cycleCount == 0)
      return;
    instrument.index = instructionIndex++;
    toInstrument.push_back(instrument);
  }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
    this->M = &M;
    this->C = &M.getContext();
    charType = IntegerType::get(*C, 8);
    ptrInt = IntegerType::get(*C, 64);
    strType = PointerType::get(charType, /*addrSpace=*/0);

    for (Function &F : M) {
      for (BasicBlock &BB : F)
        for (Instruction &I : BB)
          analyze(I);
    }

    std::size_t instIndex = 0; 
    for (InstToInstrument &I : toInstrument)
      instrument(I);

    return PreservedAnalyses::all();
  }
};
} // namespace

extern "C" LLVM_ATTRIBUTE_WEAK llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "BIOME", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &PM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "biome") {
                    PM.addPass(BIOMEPass());
                    return true;
                  }
                  return false;
                });
          }};
}
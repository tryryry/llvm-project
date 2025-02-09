#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Transforms/Scalar/SCCP.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

int main(int argc, char **argv) {
    // 初始化LLVM上下文
    LLVMContext Context;
    SMDiagnostic Err;

    // 加载IR文件
    std::unique_ptr<Module> M = parseIRFile(argv[1], Err, Context);
    if (!M) {
        Err.print(argv[0], errs());
        return 1;
    }

    // 创建PassManager
    FunctionPassManager FPM;
    FunctionAnalysisManager FAM;
    ModulePassManager MPM;
    ModuleAnalysisManager MAM;

    // 注册分析
    PassBuilder PB;
    PB.registerModuleAnalyses(MAM);
    PB.registerFunctionAnalyses(FAM);
    
    // 添加SCCP Pass
    FPM.addPass(SCCPPass());
    
    // 遍历模块中的每个函数
    for (Function &F : *M) {
        // 打印原始IR
        errs() << "Before SCCP:\n";
        F.print(errs());
        errs() << "\n";

        // 运行SCCP
        FPM.run(F, FAM);

        // 打印优化后的IR
        errs() << "After SCCP:\n";
        F.print(errs());
        errs() << "\n";
    }

    return 0;
}
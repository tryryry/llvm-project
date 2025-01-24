## 常量传播分析
### 编译test.cpp
```
clang -O0 -emit-llvm -S test.cpp -o test.ll
```

### 运行SCCP并输出优化后的IR
```
opt -passes=sccp -S test.ll -o test.sccp.ll
```

### 如果想看到分析过程，可以添加debug信息
```
../build/bin/opt -passes=sccp -debug-pass-manager -S test.ll -o test.sccp.ll
```

### 编译RunSCCP.cpp
```
SDK_PATH=$(xcrun --show-sdk-path)
../build/bin/clang++ RunSCCP.cpp \
    -stdlib=libc++ \
    -isystem ${SDK_PATH}/usr/include/c++/v1 \
    -isystem ${SDK_PATH}/usr/include \
    -L${SDK_PATH}/usr/lib \
    -L/opt/homebrew/lib \
    `../build/bin/llvm-config --cxxflags --ldflags --libs all --system-libs` \
    -Wl,-rpath,/opt/homebrew/lib \
    -o run-sccp
```

#### 运行程序
```
./run-sccp test.ll
```

### 调试
```
gdb --args ./run-sccp test.ll
```

#### 设置断点
```
b llvm::SCCPPass::run
b llvm::SCCPInstVisitor::visitInstruction
```

#### 运行程序
```
r
```
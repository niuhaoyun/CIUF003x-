# CIU32F003 CMake Project

## 需要安装的工具

在另一台电脑上编译本工程，需要准备：

- CMake 3.20 或更新版本
- Ninja
- Arm GNU Toolchain，也就是包含 `arm-none-eabi-gcc.exe` 的工具链
- 如果需要用 VS Code 调试，还需要安装 J-Link Software，并安装 VS Code 扩展 `Cortex-Debug`

## 推荐配置方式

推荐把下面两个目录加入系统 `PATH`：

```powershell
D:\Program Files (x86)\Toolchain\ninja
D:\Program Files (x86)\Toolchain\arm-gnu-toolchain-15.2.rel1\bin
```

也可以额外设置环境变量：

```powershell
ARM_GNU_TOOLCHAIN_ROOT=D:\Program Files (x86)\Toolchain\arm-gnu-toolchain-15.2.rel1
```

本工程的 `cmake/arm-none-eabi-gcc.cmake` 会优先使用 `ARM_GNU_TOOLCHAIN_ROOT/bin`，如果没有设置，就从 `PATH` 中查找 `arm-none-eabi-*` 工具。

## 编译命令

```powershell
cmake --preset debug
cmake --build --preset debug
```

Release 版本：

```powershell
cmake --preset release
cmake --build --preset release
```

生成文件在：

```text
build/debug/
build/release/
```

## 每个人自己的本机路径

不要把个人电脑上的绝对路径写进 `CMakePresets.json`。如果某个人不想改系统 `PATH`，可以复制：

```text
CMakeUserPresets.example.json
```

为：

```text
CMakeUserPresets.json
```

然后把里面的 `ARM_GNU_TOOLCHAIN_ROOT` 和 `PATH` 改成自己电脑上的路径。

`CMakeUserPresets.json` 已经加入 `.gitignore`，适合放每个人自己的配置，不建议提交到仓库。

## 打包给别人时

建议打包源码和配置文件，不要打包这些生成目录或产物：

```text
build/
.cache/
.vscode/.cmaketools.json
*.elf
*.hex
*.bin
*.map
*.lst
```

如果想做“解压即可编译”的离线包，可以把 CMake、Ninja、Arm GNU Toolchain 放到项目内的 `tools/` 目录，再用 `CMakeUserPresets.json` 指向这些相对路径。

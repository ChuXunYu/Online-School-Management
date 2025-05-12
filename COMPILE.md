# 编译指南

本文档提供了编译和运行在线校园管理系统的详细步骤。

## 前提条件

确保您的系统已安装：

1. C/C++编译器（如GCC、MinGW或Visual Studio）
2. 基本的命令行工具

## Windows系统下编译

### 使用MinGW编译

1. 打开命令提示符（CMD）或PowerShell
2. 导航到项目目录
3. 运行以下命令编译程序：

```
gcc 主函数.cpp -o 校园管理系统.exe -fexec-charset=UTF-8 -finput-charset=UTF-8
```

4. 编译完成后，运行生成的可执行文件：

```
.\校园管理系统.exe
```

### 使用Visual Studio编译

1. 打开Visual Studio
2. 创建新的C++控制台应用程序
3. 将`主函数.cpp`添加到项目中
4. 在项目属性中设置字符集为"使用Unicode字符集"
5. 编译并运行项目

## Linux系统下编译

1. 打开终端
2. 导航到项目目录
3. 运行以下命令编译程序：

```
g++ 主函数.cpp -o campus_management -fexec-charset=UTF-8 -finput-charset=UTF-8
```

4. 编译完成后，运行生成的可执行文件：

```
./campus_management
```

## MacOS系统下编译

1. 打开终端
2. 导航到项目目录
3. 运行以下命令编译程序：

```
clang++ 主函数.cpp -o campus_management -fexec-charset=UTF-8 -finput-charset=UTF-8
```

4. 编译完成后，运行生成的可执行文件：

```
./campus_management
```

## 编译问题排查

如果您在编译过程中遇到问题，请检查：

1. 确保编译器支持C++11或更高版本
2. 确保正确设置了字符编码（UTF-8）
3. 如果出现"未定义的引用"错误，请检查是否包含了所有必要的头文件

## 注意事项

- 本程序使用了Windows特定的头文件`<windows.h>`和函数如`Sleep()`，在Linux或MacOS上编译时可能需要进行相应修改
- 在非Windows系统上，您可能需要替换`<windows.h>`并使用POSIX兼容的函数 
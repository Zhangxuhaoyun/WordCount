#include <stdio.h>
#include <ctype.h> // for isalnum
#include <string.h> // for strcmp
#include <stdlib.h> // for atoi, exit

// ��������
void countAndPrint(const char* filename, char parameter);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("ʹ�÷���: %s [-c|-w] [filename]\n", argv[0]);
        return 1;
    }

    char param = argv[1][1]; // ��ȡ����������ĸ�����������ʽ��ȷ��

    if (param != 'c' && param != 'w') {
        printf("����������ʹ��'-c'ͳ���ַ�����'-w'ͳ�Ƶ�������\n");
        return 1;
    }

    countAndPrint(argv[2], param);

    return 0;
}

void countAndPrint(const char* filename, char parameter) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ� '%s'��\n", filename);
        exit(1);
    }

    int charCount = 0, wordCount = 0;
    int prevCharWasSeparator = 1; // ��ʼ��Ϊ1����ʾ�ļ���ʼʱĬ��ǰһ���ַ��Ƿָ���

    int currentChar;
    while ((currentChar = fgetc(file)) != EOF) {
        charCount++; // ͳ�������ַ�

        // ����Ƿ�Ϊ���ʵĿ�ʼ����ǰ�ַ����ǿո�򶺺ţ���ǰһ���ǣ�
        if (!isspace(currentChar) && currentChar != ',' && prevCharWasSeparator) {
            wordCount++;
        }
        
        prevCharWasSeparator = isspace(currentChar) || currentChar == ','; 
    }

    fclose(file);

    if (parameter == 'c') {
        printf("�ַ�����%d\n", charCount);
    } else if (parameter == 'w') {
        printf("��������%d\n", wordCount);
    }
}

#include "stdio.h"
#include "stdlib.h"
int main()
{
    FILE *inputFP, *outputFP;
    char c;
    int i = 0;

    bool firstFlag = false;      // 有没有遇到第一个 「/」
    bool secondFlag = false;     // 有没有遇到第二个 「/」
    bool firstStarFlag = false;  // true 的情况是遇到了 「/*」
    bool secondStarFlag = false; // true 的情况是遇到了 「/* xxxxx *」
    bool quotationFlag = false;  // true 是遇到了 「"」此时引号内部的注释不可以去掉

    if ((inputFP = fopen("input.cpp", "r")) == NULL) // input.cpp为任意带注释的C程序
    {
        printf("file cannot be opened\n");
        exit(1);
    }
    if ((outputFP = fopen("output.cpp", "w")) == NULL) // ouput.cpp为去掉注释后的程序
    {
        printf("file cannot be writed\n");
        exit(1);
    }

    while ((c = fgetc(inputFP)) != EOF)
    {

        if (c == '/' && !firstFlag && !secondStarFlag && !quotationFlag) // 第一次遇到的 「/」 不在 「"」中
        {
            firstFlag = true; // 遇到了第一个 「/」
            continue;
        }
        else if (c == '/' && firstFlag && !quotationFlag) // 第二次遇到的 「/」
        {
            secondFlag = true;
            firstFlag = false;
            continue;
        }
        else if (c == '*' && firstFlag && !quotationFlag) // 遇到 「/*」的情况
        {
            firstStarFlag = true;
            firstFlag = false;
            continue;
        }
        else if (c == '"' && !firstFlag && !quotationFlag)
        {
            quotationFlag = true; // 遇到第一个「"」
        }
        else if (c == '"' && quotationFlag)
        {
            quotationFlag = false; // 遇到 「" xxxx "」
        }
        if (secondFlag) //  遇到 「//」的情况
        {
            if (c != '\n') // 不是回车就跳过
            {
                continue;
            }
            else
            {
                secondFlag = false; // 是回车就跳出判断
            }
        }
        if (firstStarFlag) // 遇到「/*」的情况
        {
            if (c != '*' && !secondStarFlag) // 普通字符跳过
            {
                continue;
            }
            else if (c == '*') // 第二个*
            {
                secondStarFlag = true; // 遇到了第二个「/* xxx *」
                continue;
            }
            if (secondStarFlag && c == '/') // 遇到了「/* xxx */」表明结束
            {
                firstFlag = false;
                secondFlag = false;
                firstStarFlag = false;
                secondStarFlag = false;
                quotationFlag = false;
                continue;
            }
        }
        printf("%c", c);
        fputc(c, outputFP);
    }
    fclose(inputFP);
    fclose(outputFP);
    return 0;
}
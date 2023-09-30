#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include<readline/readline.h>
#include<readline/history.h>
#include"ku.h"
#define CLOSE "\001\033[0m\002"                 // 关闭所有属性
#define BLOD  "\001\033[1m\002"                 // 强调、加粗、高亮
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: 背景，y: 前景
int main()
{
    zhan*a,*b;
    creatzhan(&a);
    creatzhan(&b);
    printf("欢迎是用简易加减乘除计算器，请输入表达式： \n");
  while(1)
    {
        stackelem *input=readline(BEGIN(49,23)"interaction>");
        if(isdigit(input[0]))
        {
            int c=change(input,&a,&b);
            if(c==1)
            {
                break;
            }
            calculate(&a);
            if(c==1)
            {
                break;
            }
        }
        else if(*input=='?'||input=="help"||*input=='h')
        {
            printf("result>");
            printf("这是一个可以进行加减乘除的计算器\n");
            printf("help或者h可以查看帮助\n");
            printf("quit或q结束使用\n");
            printf("enter键计算表达式\n");
            printf("不能输入=号\n");
        }
        else if(strcmp(input,"quit")==0||*input=='q')
        {
            break;
        }
        else
        {
            printf("result>error");
            continue;
        }
        add_history(input);
    }
    free_all(&a);
    free_all(&b);
    return 0;
}
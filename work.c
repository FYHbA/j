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
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"  // x: 背景，y: 前景
#define CHECK
int main()
{
    read_history(NULL);
    char op[]={'+','-','*','/','(',')'};
    zhan*a,*b;
    printf("欢迎是用简易加减乘除计算器，请输入表达式： \n");
    while(1)
    {
        creatzhan(&a);
        creatzhan(&b);
        stackelem *input=readline(BEGIN(49,34)"interaction>"CLOSE);
        if(isdigit(input[0])||strchr(op,input[0]))
        {
            #ifdef CHECK
                printf("%s\n",input);
            #endif
            int c=change(input,&a,&b);
            if(c==1)
            {
                free_all(&a);
                free_all(&b);
                free(input);
                continue;
            }
            calculate(&a);
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
            free_all(&a);
            free_all(&b);
            free(input);
            break;
        }
        else
        {
            free_all(&a);
            free_all(&b);
            free(input);
            printf("result>error\n");
            continue;
        }
        add_history(input);
        write_history(NULL);
        free_all(&a);
        free_all(&b);
        free(input);
    }
    return 0;
}

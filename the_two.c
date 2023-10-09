//本文件是用于与二进制计算的相关函数，包括中缀转后缀和计算两个函数
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include"ku.h"
#define CHECK

#include <stdio.h>

void dec2bin(int dec)
{
    if(dec > 1)
        dec2bin(dec/2);
    FILE*write=fopen("result.txt","a+");
    printf("%d", dec%2);
    fprintf(write,"%d",dec%2);
    fclose(write);
}
status change_two(stackelem c[],stack**a,stack**b)//中缀转后缀表达式
{
    FILE*write=fopen("result.txt","a+");
    stackelem*j=NULL;
    j=malloc(1);
    char op[]={'+','-','*','/'};
    for(int i=0;c[i]!='\0';i++)
    {
        if(c[i]=='1'||c[i]=='0')
        {
            *j=c[i];
            push(a,&j);
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            while(c[i+1]=='1'||c[i+1]=='0')
            {
                *j=c[i+1];
                push(a,&j);
                i++;
                    while(c[i+1]==' ')
                {
                    i++;
                    continue;
                }
            }
            (*a)->top++;
            (*a)->top[0]=' ';
        }
        else if(c[i]=='+'||c[i]=='-')
        {
            while(strchr(op,(*b)->top[0]))
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
            }
            *j=c[i];
            push(b,&j);
        }
        else if(c[i]=='&')
        {
            while(strchr(op,(*b)->top[0])||(*b)->top[0]=='&')
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
            }
            *j=c[i];
            push(b,&j);
        }
        else if(c[i]=='^')
        {
            while(strchr(op,(*b)->top[0])||(*b)->top[0]=='&'||(*b)->top[0]=='^')
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
            }
            *j=c[i];
            push(b,&j);
        }
        else if(c[i]=='|')
        {
            while(strchr(op,(*b)->top[0])||(*b)->top[0]=='&'||(*b)->top[0]=='^'||(*b)->top[0]=='|')
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
            }
            *j=c[i];
            push(b,&j);
        }
        else if (c[i]=='*'||c[i]=='/')
        {
            while((*b)->top[0]=='*'||(*b)->top[0]=='/')
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
            }
            *j=c[i];
            push(b,&j);
        }
        else if(c[i]=='(')
        {
            *j=c[i];
            push(b,&j);
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            if(c[i+1]=='\0')
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);   
                free(j); 
                return ERROR;
            }
        }
        else if(c[i]==')')
        {
            if((*b)->top[0]=='(')
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);   
                free(j); 
                return ERROR;
            }
            while((*b)->top[0]!='(')
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
                if((*b)->top[-1]=='\0')
                {
                    printf("result>表达式有误\n");
                    fprintf(write,"%s\n","表达式有误");
                    fclose(write);   
                    free(j); 
                    return ERROR;
                }
            }
            pop(b,&j);
        }
        else if(c[i]==' ')
        {
            continue;
        }
        else
        {
            printf("result>表达式有误\n");
            fprintf(write,"%s\n","表达式有误");
            fclose(write);
            free(j);
            return ERROR;
        }
    }
    while((*b)->top!=(*b)->base)
    {
        pop(b,&j);
        push(a,&j);
        (*a)->top++;
        (*a)->top[0]=' ';
    }
    free(j);
    j=NULL;
    fclose(write);
    #ifdef CHECK
       printf("%s\n",(*a)->base);
    #endif
    return OK;
}
status calculate_two(stack**a)//后缀计算函数
{
    FILE*write=fopen("result.txt","a+");
    int k[10];
    int s=-1;
    int num1,num2;
    char*p=strtok((*a)->base," ");
    int i,sum=0;
    while(p!=NULL)
    {
        if(isdigit(p[0]))
        {
            for(i=0;p[i]!='\0'&&i<31;i++)
            {
                sum=2*sum+(p[i]-48);       //这里的48等价于'0'
            }
            s++;
            k[s]=sum;
            sum=0;
            #ifdef CHECK
                printf("%d\n",k[s]);
            #endif
        }
        else if(*p=='+')
        { 
            if(s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            else if(s==0)
            {
                k[s]=k[s];
            }
            else
            {
                num2=k[s];
                s--;
                num1=k[s];
                k[s]=num1+num2;
            }  
        }
        else if(*p=='-')
        {
            if(s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            else if(s==0)
            {
                k[s]=-k[s];
            }
            else
            {
                num2=k[s];
                s--;
                num1=k[s];
                k[s]=num1-num2;
            }  
        }
        else if(*p=='*')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1*num2;
        }
        else if(*p=='/')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            if(num2==0)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            else
            k[s]=num1/num2;
        }
        else if(*p=='&')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1&num2;
        }
        else if(*p=='^')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1^num2;
        }
        else if(*p=='|')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1|num2;
        }
        p=strtok(NULL," ");
    }
    #ifdef CHECK
        printf("%d\n",k[0]);
    #endif
    printf("result> ");
    fclose(write);
    dec2bin(k[0]);
    write=fopen("result.txt","a+");
    fprintf(write,"\n");
    fclose(write);
    printf("\n");
    return OK;
}
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include"ku.h"
#include<math.h>
status change(stackelem c[],zhan**a,zhan**b)//中缀转后缀表达式
{
    FILE*write=fopen("result.txt","a+");
    stackelem*j=NULL;
    j=malloc(1);
    char op[]={'+','-','*','/'};
    for(int i=0;c[i]!='\0';i++)
    {
        if(isdigit(c[i])||c[i]=='.')
        {
            *j=c[i];
            push(a,&j);
            while(isdigit(c[i+1])||c[i+1]=='.')
            {
                *j=c[i+1];
                push(a,&j);
                i++;
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
        }
        else if(c[i]==')')
        {
            while((*b)->top[0]!='(')
            {
                pop(b,&j);
                push(a,&j);
                (*a)->top++;
                (*a)->top[0]=' ';
            }
            pop(b,&j);
        }
        else if(c[i]==' ')
        {
            continue;
        }
        
        else
        {
            printf("result>表达式有错误\n");
            fprintf(write,"%s\n","表达式有错误");
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
    return OK;
}
status calculate(zhan**a)//后缀计算函数
{
    FILE*write=fopen("result.txt","a+");
    double k[10];
    int s=-1;
    double num1,num2;
    char*p=strtok((*a)->base," ");
    while(p!=NULL)
    {
        if(isdigit(p[0]))
        {
            s++;
            k[s]=atof(p);
        }
        else if(*p=='+')
        { 
            if(s==-1)
            {
                printf("result>表达式有误\n");
                 fprintf(write,"%s\n","表达式有误");
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
                printf("%lf\n",k[0]);
            }  
        }
        else if(*p=='*')
        {
            if(s==0||s==-1)
            {
                printf("result>表达式有误\n");
                 fprintf(write,"%s\n","表达式有误");
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
                return ERROR;
            }
            num2=k[s];
            s--;
            num1=k[s];
            if(num2==0)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                return ERROR;
            }
            else
            k[s]=num1/num2;
        }
        p=strtok(NULL," ");
    }
    if(ceil(k[0]) == floor(k[0]))
    {
        int i=(int)k[0];
        printf("result> %d\n",i);
        fprintf(write,"%d\n",i);
    }
    else
    {
        printf("result> %lf\n",k[0]);
        fprintf(write,"%lf\n",k[0]);
    }
    fclose(write);
    return OK;
}
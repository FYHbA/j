//本文件用于定义16进制中缀转后缀的函数和计算16进制数的函数，包括中缀转后缀和计算两个函数
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include"ku.h"
//#define CHECK

#include <stdio.h>
status change_hex(stackelem c[],stack**a,stack**b)//中缀转后缀表达式
{
    FILE*write=fopen("result.txt","a+");
    stackelem*j=NULL;
    j=malloc(1);
    char op[]={'+','-','*','/'};
    char zi[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    for(int i=0;c[i]!='\0';i++)
    {
        if(strchr(zi,c[i]))
        {
            *j=c[i];
            push(a,&j);
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            while(isdigit(c[i+1])||isalpha(c[i+1]))
            {
                if(strchr(zi,c[i+1]))
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
                else
                break;
            }
            (*a)->top++;
            (*a)->top[0]=' ';
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            if(c[i+1]=='(')
            {
                while((*b)->top[0]=='*'||(*b)->top[0]=='/')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                *j='*';
                push(b,&j);
            }
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
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            if(c[i+1]=='\0'||c[i+1]==')')
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
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            if(c[i+1]=='(')
            {
                while((*b)->top[0]=='*'||(*b)->top[0]=='/')
                {
                    pop(b,&j);
                    push(a,&j);
                    (*a)->top++;
                    (*a)->top[0]=' ';
                }
                *j='*';
                push(b,&j);
            }
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
        #ifdef CHECK
            printf("%s\n",(*a)->base);
            printf("%s\n",(*b)->base);
        #endif
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
       printf("%s\n",(*b)->base);
    #endif
    return OK;
}
status calculate_hex(stack**a)//后缀计算函数
{
    FILE*write=fopen("result.txt","a+");
    long unsigned int k[10];
    int s=-1;
    long int num1,num2;
    char*p=strtok((*a)->base," ");
    int i;
    while(p!=NULL)
    {
        if(isdigit(p[0])||isalpha(p[0]))
        {
            s++;
            sscanf(p,"%lX",&k[s]);
            #ifdef CHECK
                printf("%lX\n",k[s]);
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
        p=strtok(NULL," ");
    }
    #ifdef CHECK
        printf("%lX\n",k[0]);
    #endif

    printf("result> %lX\n",k[0]);
    fprintf(write,"%lX\n",k[0]);
    fclose(write);
    return OK;
}
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include"ku.h"
#include<math.h>
//#define CHECK
status change(stackelem c[],stack**a,stack**b)//中缀转后缀表达式
{
    FILE*write=fopen("result.txt","a+");
    stackelem*j=NULL;
    int t=0;
    j=malloc(1);
    char op[]={'+','-','*','/'};
    for(int i=0;c[i]!='\0';i++)
    {
        if(isdigit(c[i])||c[i]=='.')
        {
            *j=c[i];
            push(a,&j);
            while(c[i+1]==' ')
            {
                i++;
                continue;
            }
            while(isdigit(c[i+1])||c[i+1]=='.')
            {
                if(c[i+1]=='.')
                {
                    t++;
                }
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
            if(t>1)
            {
                printf("result>表达式有误\n");
                fprintf(write,"%s\n","表达式有误");
                fclose(write);                   
                return ERROR;
            }
            else
            t=0;
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
            if(c[i+1]=='-')
            {
                i++;
                *j=c[i];
                push(a,&j);
                while(c[i+1]==' ')
                {
                    i++;
                    continue;
                }
                while(isdigit(c[i+1])||c[i+1]=='.')
                {
                    if(c[i+1]=='.')
                    {
                       t++;
                    }
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
                if(t>1)
                {
                    printf("result>表达式有误\n");
                    fprintf(write,"%s\n","表达式有误");
                    fclose(write);                   
                    return ERROR;
                }
                else
                t=0;
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
status calculate(stack**a)//后缀计算函数
{
    FILE*write=fopen("result.txt","a+");
    double k[10];
    int s=-1;
    double num1,num2;
    char*p=strtok((*a)->base," ");
    while(p!=NULL)
    {
        if(isdigit(p[0])||isdigit(p[1]))
        {
            s++;
            k[s]=atof(p);
            #ifdef CHECK
                printf("%lf\n",k[s]);
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
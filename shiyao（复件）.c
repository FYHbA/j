#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include<readline/readline.h>
#include<readline/history.h>
#define CLOSE "\001\033[0m\002"                 // 关闭所有属性
#define BLOD  "\001\033[1m\002"                 // 强调、加粗、高亮
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"
typedef char stackelem;
typedef struct zhan
{
    stackelem *base;
    stackelem *top;
    int size;
}zhan;
typedef enum status
{
    OK,
    ERROR
}status;
status creatzhan(zhan **stack)
{
    *stack=(zhan*)malloc(sizeof(zhan));
    (*stack)->base=(stackelem*)malloc(sizeof(stackelem)*30);
    (*stack)->top=(*stack)->base;
    if (!(*stack)->base)
    {
        return ERROR;
    }
    (*stack)->base[0]=' ';
    (*stack)->size=0;
    return OK;
}
status visit(zhan *stack)//访问函数
{
    printf("%s",stack->base);
    return OK;
}
status push(zhan **stack,stackelem **pelem)//入栈
{
    if(!pelem)
    {
        return ERROR;
    }
    (*stack)->top++;
    (*stack)->top[0]=**pelem;   
    (*stack)->size++;
    return OK;
}

bool empty(zhan *stack)//通过返回值判断栈是否为空
{
    return stack->size==0;
}
status pop(zhan **stack,stackelem **pelem)//出栈
{
    if(empty(*stack))
    {
        return ERROR;
    }
    else
    {
        **pelem=*(*stack)->top;
        *(*stack)->top='\0';
        (*stack)->top --;
        (*stack)->size--;
        return OK;
    }

}
void clear(zhan **stack)//清空栈
{
    (*stack)->top=(*stack)->base;
    *(*stack)->top='\0';
    (*stack)->size=0;
}
void free_all(zhan **stack)//释放栈元素
{
    free((*stack)->base);
    free(*stack);
}
int length(zhan *stack)//求栈长度
{
    return stack->size;
}
status get_top(zhan **stack,stackelem **pelem)//取栈顶元素
{
    if(empty(*stack))
    {
        return ERROR;
    }
    **pelem=*(*stack)->top;
    return OK;
}
status traverse(zhan *stack,status visit(zhan *stack))
{
    if(stack->base!=NULL)
    {
        visit(stack);
        return OK;
    }
    else
    return ERROR;   
}

status change(stackelem c[],zhan**a,zhan**b)//中缀转后缀表达式
{
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
            printf("result>warm\n");
            continue;
        }
        
        else
        {
            printf("result>表达式有错误\n");
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
    int num1,num2;
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
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1+num2;
        }
        else if(*p=='-')
        {
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1-num2;
        }
        else if(*p=='*')
        {
            num2=k[s];
            s--;
            num1=k[s];
            k[s]=num1*num2;
        }
        else if(*p=='/')
        {
            num2=k[s];
            s--;
            num1=k[s];
            if(num2==0)
            {
                printf("result>错误，除数不能为0\n");
                return ERROR;
            }
            else
            k[s]=num1/num2;
        }
        p=strtok(NULL," ");
    }
    printf("result> %lf\n",k[0]);
    fprintf(write,"%lf\n",k[0]);
    return OK;
}
int main()
{
    zhan*a,*b;
    creatzhan(&a);
    creatzhan(&b);
    printf("欢迎是用简易加减乘除计算器，请输入表达式： ");
    stackelem input[10];
    scanf("%s",input);
    change(input,&a,&b);
    calculate(&a);
    free_all(&a);
    free_all(&b);
    return 0;
}
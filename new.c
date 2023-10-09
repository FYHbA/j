//本文件用于栈的相关函数的定义.
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include"ku.h"

status StackInit(stack **sta)
{
    *sta=(stack*)malloc(sizeof(stack));
    (*sta)->base=(stackelem*)malloc(sizeof(stackelem)*300);
    (*sta)->top=(*sta)->base;
    if (!(*sta)->base)
    {
        return ERROR;
    }
    (*sta)->base[0]=' ';
    (*sta)->size=0;
    return OK;
}
status visit(stack *sta)//访问函数
{
    printf("%s",sta->base);
    return OK;
}
status push(stack **sta,stackelem **pelem)//入栈
{
    if(!pelem)
    {
        return ERROR;
    }
    (*sta)->top++;
    (*sta)->top[0]=**pelem;   
    (*sta)->size++;
    return OK;
}

bool empty(stack *sta)//通过返回值判断栈是否为空
{
    return sta->size==0;
}
status pop(stack **sta,stackelem **pelem)//出栈
{
    if(empty(*sta))
    {
        return ERROR;
    }
    else
    {
        **pelem=*(*sta)->top;
        *(*sta)->top='\0';
        (*sta)->top --;
        (*sta)->size--;
        return OK;
    }

}
void clear(stack **sta)//清空栈
{
    (*sta)->top=(*sta)->base;
    *(*sta)->top='\0';
    (*sta)->size=0;
}
void free_all(stack **sta)//释放栈元素
{
    free((*sta)->base);
    free(*sta);
}
int length(stack *sta)//求栈长度
{
    return sta->size;
}
status get_top(stack **sta,stackelem **pelem)//取栈顶元素
{
    if(empty(*sta))
    {
        return ERROR;
    }
    **pelem=*(*sta)->top;
    return OK;
}
status traverse(stack *sta,status visit(stack*sta))
{
    if(sta->base!=NULL)
    {
        visit(sta);
        return OK;
    }
    else
    return ERROR;   
}
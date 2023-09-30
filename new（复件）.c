#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include"ku.h"

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
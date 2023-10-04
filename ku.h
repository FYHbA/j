#ifndef KU_H
#define KU_H
typedef char stackelem;
typedef struct stack
{
    stackelem *base;
    stackelem *top;
    int size;
}stack;
typedef enum status
{
    OK,
    ERROR
}status;
status visit(stack *sta);
status StackInit(stack **sta);
status push(stack **sta,stackelem **pelem);//入栈
status pop(stack **sta,stackelem **pelem);//出栈
bool empty(stack*sta);
void clear(stack **sta);
void free_all(stack **sta);//释放栈元素
int length(stack *sta);
status get_top(stack **sta,stackelem **pelem); 
status traverse(stack *sta,status visit(stack *sta));
status change(stackelem c[],stack**a,stack**b);
status calculate(stack**a);
#endif
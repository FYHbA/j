#ifndef KU_H
#define KU_H
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
status visit(zhan *stack);
status creatzhan(zhan **stack);
status push(zhan **stack,stackelem **pelem);//入栈
status pop(zhan **stack,stackelem **pelem);//出栈
bool empty(zhan*stack);
void clear(zhan **stack);
void free_all(zhan **stack);//释放栈元素
int length(zhan *stack);
status get_top(zhan **stack,stackelem **pelem); 
status traverse(zhan *stack,status visit(zhan *stack));
status change(stackelem c[],zhan**a,zhan**b);
status calculate(zhan**a);
#endif
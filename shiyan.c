#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
int main()
{
    int ret = system("make");
    assert(ret != -1);
    ret = system("./project -t result.txt < test.txt");
    assert(ret != -1);
    system("diff -y -w result.txt answer.txt");
    return 0;
}
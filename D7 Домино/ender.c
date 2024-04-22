#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char connections[49];

typedef struct List
{
    struct List* next;
    int value;
} LIST, *HLIST;

void push(HLIST list, int value)
{
    HLIST temp = malloc(sizeof(LIST));
    *temp = *list;
    list->next = temp;
    list->value = value;
}

void push_or_create(HLIST* list, int value)
{
    if(!*list)
    {
        (*list) = malloc(sizeof(LIST));
        (*list)->value = value;
        (*list)-> next = NULL;
    }
    else push(*list, value);
}

HLIST root = NULL;
void dfs(char pos)
{
    for(char i = 0; i < 7; i++)
    {
        if(connections[pos*7+i])
        {
            connections[pos*7+i]--;
            connections[i*7+pos]--;
            dfs(i);
        }
    }
    push_or_create(&root,pos);
}

int main()
{
    FILE *fIn, *fOut;
    fIn = fopen("input.txt", "r");
    fOut = fopen("output.txt", "w");
    char buff[7];
    memset(buff,0,7);
    memset(connections,0,49);
    char next,start,temp;
    fscanf(fIn,"%c",&start);
    start-='0';
    temp = start;
    buff[start] ^= 1;
    int size = 1;
    while(fscanf(fIn,"%c",&next) != EOF && next != '\0')
    {
        size++;
        next-='0';
        buff[next]^=1;
        if(temp != -1)
        {
            connections[temp*7+next]++;
            connections[next*7+temp]++;
            temp = -1;
        }
        else temp = next;
    }
    char summ = 0;
    for(char i = 0; i < 7; i++)
    {
        summ += buff[i];
        if(buff[i]) start = i;
    }
    if(summ > 2)
    {
        fprintf(fOut,"NO");
        return 0;
    }
    dfs(start);
    for(char i = 0; i < 49; i++)
    {
        if(connections[i])
        {
            fprintf(fOut,"NO");
            return 0;
        }
    }
    while(root->next)
    {
        fprintf(fOut,"%d%d",root->value, root->next->value);
        root = root->next;
        if(root->next)fprintf(fOut,"-");
    }
    return 0;
}

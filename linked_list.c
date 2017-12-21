#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_elem_
{
    struct list_elem_ * next;
    int elem;
} list_elem;

typedef struct list_
{
    list_elem * top;
    unsigned long long int size;
} list;

void add_elem(list * lst, int elem_)
{
    list_elem * new_el = malloc(sizeof(list_elem));
    if(0 == lst->size)
        new_el->next = NULL;
    else
        new_el->next = lst->top;
    new_el->elem = elem_;
    lst->top = new_el;
    lst->size++;
}

void show_list(list * lst)
{
    list_elem * start = lst->top;
    while(NULL != lst->top)
    {
        printf("%d ", lst->top->elem);
        lst->top = lst->top->next;
    }
    printf("\n");
    lst->top = start;    
}

double calc_average(list * lst)
{
    double sum = 0;
    list_elem * start = lst->top;
    while(NULL != lst->top)
    {
        sum += lst->top->elem;
        lst->top = lst->top->next;
    }
    lst->top = start;
    return sum / lst->size;
}

void remove_extra(list * lst, double average)
{
    list_elem * tmp;
    while(lst->top != NULL && lst->top->elem > average)
    {
        tmp = lst->top->next;
        free(lst->top);
        lst->top = tmp;
    }
    list_elem * start = lst->top;
    list_elem * prev = lst->top;
    while(NULL != lst->top)
    {
        if(lst->top->elem <= average)
        {
            prev = lst->top;
            lst->top = lst->top->next;
        }
        else
        {
            prev->next = lst->top->next;
            free(lst->top);
            lst->top = prev->next;
        }
    }
    lst->top = start;
}

void write_to_file(list * lst, FILE * out)
{
    list_elem * start = lst->top;
    while(NULL != lst->top)
    {
        fprintf(out, "%d ", lst->top->elem);
        lst->top = lst->top->next;
    }
    lst->top = start;
}

void free_list(list * lst)
{
    list_elem * tmp;
    while(NULL != lst->top)
    {
        tmp = lst->top->next;
        free(lst->top);
        lst->top = tmp;
    }
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        printf("Wrong number of arguments.\n");
        return 1;
    }
    FILE * out = fopen(argv[argc - 1], "w");
    char num[11];
    printf("Enter 32-bit integer number or \"end\" for calculating average.\n");
    list lst_ = {NULL, 0};
    list * lst = &lst_;
    scanf("%s", &num);
    while(strcmp("end", num))
    {
        int elem_ = atoi(num);
        add_elem(lst, elem_);
        scanf("%s", &num);
    }
    //show_list(lst);
    double average = calc_average(lst);
    //show_list(lst);
    remove_extra(lst, average);
    //show_list(lst);
    write_to_file(lst, out);
    free_list(lst);
}

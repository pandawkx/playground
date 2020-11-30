#include "list.h"

#include <stdlib.h>
#include <stdio.h>

// build with : gcc -o main main.c

struct task_node_t
{
    int task_id;
    struct list_head list_node;
};

int main()
{
    struct task_node_t *p_task;
    struct task_node_t *p_task_tmp;
    int i;

    //init list head
    LIST_HEAD(task_list_head);

    //insert 100 elements(from head)
    for(i=0; i<100; ++i)
    {
        struct task_node_t *p_task = (struct task_node_t *)malloc(sizeof(p_task));
        p_task->task_id = i;
        INIT_LIST_HEAD(&p_task->list_node);
        list_add(&p_task->list_node, &task_list_head);
    }

    //insert 100 elements(from tail)
    for(i=100; i<200; ++i)
    {
        struct task_node_t *p_task = (struct task_node_t *)malloc(sizeof(p_task));
        p_task->task_id = i;
        INIT_LIST_HEAD(&p_task->list_node);
        list_add_tail(&p_task->list_node, &task_list_head);
    }
    
    //foreach and print
    list_for_each_entry(p_task, &task_list_head, list_node)
    {
        printf("task_id = %d\n", p_task->task_id);
    }

    //foreach and print(reverse)
    list_for_each_entry_reverse(p_task, &task_list_head, list_node)
    {
        printf("task_id = %d\n", p_task->task_id);
    }

    //delete odd elements
    list_for_each_entry_safe(p_task, p_task_tmp, &task_list_head, list_node)
    {
        if(p_task->task_id % 2 == 1)
        {
            list_del(&p_task->list_node);
            free(p_task);
        }
    }
 
    //foreach and print
    list_for_each_entry(p_task, &task_list_head, list_node)
    {
        printf("task_id = %d\n", p_task->task_id);
    }

    //delete event elements
    list_for_each_entry_safe(p_task, p_task_tmp, &task_list_head, list_node)
    {
        if(p_task->task_id % 2 == 0)
        {
            list_del(&p_task->list_node);
            free(p_task);
        }
    }
 
    if(list_empty(&task_list_head))
        printf("list is empty !\n");
    else
        printf("list is not empty !\n");

    return 0;
}
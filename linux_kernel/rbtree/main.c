#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>

// build with : gcc -o main main.c

struct task_node_t
{
    int task_id;
    struct rb_node node;
};

int task_insert(struct rb_root *p_root, struct task_node_t *p_task)
{
    struct rb_node **p_new = &p_root->rb_node;
    struct rb_node *p_parent = NULL;
    struct task_node_t *p_this;

    while (*p_new) 
    {
        p_this = container_of(*p_new, struct task_node_t, node);
        p_parent = *p_new;
        if (p_task->task_id < p_this->task_id)
            p_new = &((*p_new)->rb_left);
        else if (p_task->task_id > p_this->task_id)
            p_new = &((*p_new)->rb_right);
        else
            return 0;
    }

    rb_link_node(&p_task->node, p_parent, p_new);
    rb_insert_color(&p_task->node, p_root);

    return 1;
}

struct task_node_t *task_search(struct rb_root *p_root, int task_id)
{
	struct rb_node *p_node = p_root->rb_node;
    struct task_node_t *p_task;

	while (p_node) 
    {
		p_task = container_of(p_node, struct task_node_t, node);
		if (task_id < p_task->task_id)
			p_node = p_node->rb_left;
		else if (task_id > p_task->task_id)
			p_node = p_node->rb_right;
		else
			return p_task;
	}
	return NULL;
}

int main()
{
    int i;
    struct task_node_t *p_task;
    struct rb_root task_tree = RB_ROOT;

    //插入100个元素
    for (i=0; i < 100; i++) 
    {
        p_task = (struct task_node_t *)malloc(sizeof(struct task_node_t));
        p_task->task_id = 100 -1 - i;
        task_insert(&task_tree, p_task);
    }
    
    //search
    for(i=0;i<100;i++)
    {
        p_task = task_search(&task_tree, i);
        printf("%d %d\n", i, p_task->task_id);
    }

    //遍历
    struct rb_node *p_node;
    for (p_node = rb_first(&task_tree); p_node; p_node = rb_next(p_node))
        printf("task_id=%d\n", rb_entry(p_node, struct task_node_t, node)->task_id);

    return 0;
}
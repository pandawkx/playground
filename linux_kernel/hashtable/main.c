#include "hlist.h"

#include <stdlib.h>
#include <stdio.h>

// build with : gcc -o main main.c

#define HTBL_BKT_CNT 7
#define ORDER_CNT 100

struct order_node_t
{
    long hkey;
    long order_ref;
    struct hlist_node hnode;
};

static inline int hash_func(int order_no)
{
    return order_no % HTBL_BKT_CNT;
}

int main()
{
    //hashtable buckets
    struct hlist_head h_ord_tbl[HTBL_BKT_CNT];

    int i;
    int ord_no;
    int bkt_idx;
    struct order_node_t *p_ord;

    //init buckets
    for (i = 0 ; i < HTBL_BKT_CNT ; i++) 
    {
        INIT_HLIST_HEAD(&h_ord_tbl[i]);
    }

    //add elements to table
    for (ord_no = 0 ; ord_no < ORDER_CNT ; ord_no++) 
    {
        p_ord = (struct order_node_t *)malloc(sizeof(struct order_node_t));
        p_ord->hkey = ord_no;
        p_ord->order_ref = ord_no;
        INIT_HLIST_NODE(&p_ord->hnode);

        bkt_idx = hash_func(ord_no);
        hlist_add_head(&p_ord->hnode, &h_ord_tbl[bkt_idx]);
    }

    //search from hashtable
    for (ord_no = 0 ; ord_no < ORDER_CNT ; ord_no++) 
    {
        bkt_idx = hash_func(ord_no);
        hlist_for_each_entry(p_ord, &h_ord_tbl[bkt_idx], hnode)
        {
            if (p_ord->hkey == ord_no)
                printf("%ld, %ld\n", ord_no, p_ord->order_ref);
        }
    }

    //hashtable foreach
    for (bkt_idx = 0 ; bkt_idx < HTBL_BKT_CNT ; bkt_idx++) 
    {
        hlist_for_each_entry(p_ord, &h_ord_tbl[bkt_idx], hnode)
            printf("%ld\n", p_ord->order_ref);
    }

    return 0;
}
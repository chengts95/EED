/* A custom doubly linked list implemenation */
# include "basicfun.h"

#include <stdlib.h>

/* Insert an element X into the list at location specified by NODE */
void insert(list *node, int x)
{
    list *temp;
    if (node==NULL)
    {
        printf("\n Error!! asked to enter after a NULL pointer, hence exiting \n");
        exit(1);
    }
    temp =new list;
    temp->index = x;
    temp->child = node->child;
    temp->parent = node;
    if (node->child != NULL)
    {
        node->child->parent = temp;
    }
    node->child = temp;
}

/* Delete the node NODE from the list */
list* del (list *node)
{
    list *temp;
    if (node==NULL)
    {
      exit(1);
    }
    temp =new list;
    temp = node->parent;
    temp->child = node->child;
    if (temp->child!=NULL)
    {
       temp->child->parent = temp;
    }
    delete node;
    return (temp);
}

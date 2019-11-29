#include "list_mtm.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_t {
    ListElement element;
    struct node_t *next;
} *Node;

struct List_t {
    Node head;
    Node *iterator;
    CopyListElement copyElement;
    FreeListElement freeElement;
};

/*
 * Creates a new node and initializes it with a copy of element
 * @param element - the element to be copied into the new node
 * @param copyElement - function pointer to be used for copying element
 * @param node - pointer to the new node that will be created
 * @return: LIST_OUT_OF_MEMORY if any allocation has failed, LIST_SUCCESS
 * otherwise and node will point to the new node created.
 */
static ListResult nodeCreate(ListElement element,
                             CopyListElement copyElement, Node *node) {
    assert(node != NULL && copyElement != NULL);
    *node = NULL;
    Node new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return LIST_OUT_OF_MEMORY;
    }
    ListElement new_element = copyElement(element);
    if (new_element == NULL) {
        free(new_node);
        return LIST_OUT_OF_MEMORY;
    }
    new_node->element = new_element;
    new_node->next = NULL;
    *node = new_node;
    return LIST_SUCCESS;
}

/*
 * destroys a node and frees internal allocations
 * @param node - the node to be destroyed
 * @param freeElement - function pointer to be used for removing element
 */
static void nodeDestroy(Node node, FreeListElement freeElement) {
    assert(node!=NULL);
    if (node->element != NULL) {
        freeElement(node->element);
    }
    free(node);
}

/*
 * @param list - original list
 * @param new_list - a copy of the original list
 * listSetIterator: sets the new_list iterator as the iterator of the
 * original list,the function assumes that neither of the parameters are NULL.
 */
static void listSetIterator(List list, List new_list) {
    assert(list != NULL && new_list != NULL);
    if (list->iterator == NULL) {
        new_list->iterator = NULL;
        return;
    }
    Node ptr1 = list->head;
    Node ptr2 = new_list->head;
    while (ptr1 != NULL) {
        if (list->iterator && *(list->iterator) == ptr1) {
            new_list->iterator = &ptr2;
            return;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
}

/*****************************************************************************/
List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
    if (copyElement == NULL || freeElement == NULL) {
        return NULL;
    }
    List list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->iterator = NULL;
    list->copyElement = copyElement;
    list->freeElement = freeElement;
    return list;
}

List listCopy(List list) {
    if (list == NULL) {
        return NULL;
    }
    List new_list = listCreate(list->copyElement, list->freeElement);
    if (new_list == NULL) {
        return NULL;
    }
    Node ptr = list->head;
    while (ptr != NULL) {
        ListResult insert_result = listInsertLast(new_list, ptr->element);
        if (insert_result != LIST_SUCCESS) {
            listDestroy(new_list);
            return NULL;
        }
        ptr = ptr->next;
    }
    listSetIterator(list, new_list);
    return new_list;
}

int listGetSize(List list) {
    if (list == NULL) {
        return -1;
    }
    int size = 0;
    Node ptr = list->head;
    while (ptr != NULL) {
        size++;
        ptr = ptr->next;
    }
    return size;
}

ListElement listGetFirst(List list) {
    if (list == NULL) {
        return NULL;
    }
    if (list->head == NULL) {
        list->iterator = NULL;
        return NULL;
    }
    list->iterator = &(list->head);
    return list->head->element;
}

ListElement listGetNext(List list) {
    if (list == NULL) {
        return NULL;
    }
    if (!(list->iterator) || !(*list->iterator) || !(*list->iterator)->next) {
        list->iterator = NULL;
        return NULL;
    }
    list->iterator = &((*list->iterator)->next);
    return (*list->iterator)->element;
}

ListElement listGetCurrent(List list) {
    if (list == NULL || list->iterator == NULL || (*(list->iterator)) == NULL) {
        return NULL;
    }
    return (*(list->iterator))->element;
}

ListResult listInsertFirst(List list, ListElement element) {
    if (list == NULL || element == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node new_node = NULL;
    ListResult result = nodeCreate(element, list->copyElement, &new_node);
    if (result != LIST_SUCCESS) {
        return result;
    }
    new_node->next = list->head;
    list->head = new_node;
    return LIST_SUCCESS;
}

ListResult listInsertLast(List list, ListElement element) {
    if (list == NULL || element == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node new_node = NULL;
    ListResult result = nodeCreate(element, list->copyElement, &new_node);
    if (result != LIST_SUCCESS) {
        return result;
    }
    if (list->head == NULL) {
        list->head = new_node;
        return LIST_SUCCESS;
    }
    Node ptr = list->head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = new_node;
    return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element) {
    if (list == NULL || element == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if (list->iterator == NULL || (*list->iterator) == NULL) {
        return LIST_INVALID_CURRENT;
    }
    Node node = NULL;
    ListResult copy_of_element_result = nodeCreate(element,
                                                   list->copyElement, &node);
    if (copy_of_element_result == LIST_OUT_OF_MEMORY) {
        return copy_of_element_result;
    }
    if (list->head == (*list->iterator)) {
    #ifndef NDEBUG
        ListResult list_result =
    #endif
                listInsertFirst(list, node);
        assert(list_result == LIST_SUCCESS);
    } else {
        Node ptr = list->head;
        while (&(ptr->next) != list->iterator) {
            ptr = ptr->next;
        }
        node->next = *(list->iterator);
        list->iterator= &(node->next);
        ptr->next = node;
    }
    return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element) {
    if (list == NULL || element == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if (list->iterator == NULL || (*list->iterator) == NULL) {
        return LIST_INVALID_CURRENT;
    }
    Node node = NULL;
    if (nodeCreate(element, list->copyElement, &node)
        == LIST_OUT_OF_MEMORY) {
        return LIST_OUT_OF_MEMORY;
    }
    Node iterator_next = (*list->iterator)->next;
    node->next = iterator_next;
    (*list->iterator)->next = node;
    return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list) {
    if (list == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    if (list->iterator == NULL || (*list->iterator) == NULL) {
        return LIST_INVALID_CURRENT;
    }
    Node to_delete = (*list->iterator);
    if ((*list->iterator) == list->head) {
        list->head = to_delete->next;
    } else {
        Node ptr = list->head;
        while (ptr->next != (*list->iterator)) {
            ptr = ptr->next;
        }
        ptr->next = to_delete->next;
    }
    nodeDestroy(to_delete, list->freeElement);
    list->iterator = NULL;
    return LIST_SUCCESS;
}

ListResult listSort(List list, CompareListElements compareElement,
                    ListSortKey key) {
    if (list == NULL || compareElement == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node ptr1 = list->head;
    if (ptr1 != NULL) {
        for (; ptr1->next != NULL; ptr1 = ptr1->next) {
            for (Node ptr2 = ptr1->next; ptr2 != NULL; ptr2 = ptr2->next) {
                if (compareElement(ptr1->element, ptr2->element, key) > 0) {
                    ListElement temp = ptr1->element;
                    ptr1->element = ptr2->element;
                    ptr2->element = temp;
                }
            }
        }
    }
    return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key) {
    if (list == NULL || filterElement == NULL) {
        return NULL;
    }
    List filtered_list = listCreate(list->copyElement, list->freeElement);
    if (filtered_list == NULL) {
        return NULL;
    }
    Node ptr = list->head;
    while (ptr != NULL) {
        ListElement current_element = ptr->element;
        if (filterElement(current_element, key)) {
            ListResult result = listInsertLast(filtered_list, current_element);
            if (result != LIST_SUCCESS) {
                listDestroy(filtered_list);
                return NULL;
            }
        }
        ptr = ptr->next;
    }
    filtered_list->iterator=NULL;
    return filtered_list;
}

ListResult listClear(List list) {
    if (list == NULL) {
        return LIST_NULL_ARGUMENT;
    }
    Node ptr = list->head;
    while (ptr != NULL) {
        Node to_delete = ptr;
        ptr = ptr->next;
        nodeDestroy(to_delete, list->freeElement);
    }
    list->head = NULL;
    list->iterator = NULL;
    return LIST_SUCCESS;
}

void listDestroy(List list) {
    if (list == NULL) {
        return;
    }
    listClear(list);
    free(list);
}







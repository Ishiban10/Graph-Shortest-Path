//-----------------------//
// Name: Ishaan Das      //
// CruzID: isdas         //
// Assignment Name: pa2  // 
//-----------------------//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "List.h"


typedef struct NodeObj {
    int index;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef struct NodeObj* Node;

Node newNode(int index) {
    Node newNode = malloc(sizeof(NodeObj));
    if (newNode != NULL) {
        newNode->index = index;
        newNode->next = NULL;
        newNode->prev = NULL;
        return newNode;
    } else {
        printf("Node Error: calling newNode() on a NULL Node reference\n");
        exit(EXIT_FAILURE);
        //return NULL;
    }
}

void freeNode(Node *n) {
    free(*n);
    *n = NULL;
}

void printNode(Node n) {
    printf("Num: %i\n", n->index);
    if (n->next != NULL) { 
        printf("Next: %i\n", n->next->index);
    }
    if (n->prev != NULL) {
        printf("Prev: %i\n", n->prev->index);
    }
}

typedef struct ListObj {
    Node head;
    Node tail;
    Node cursor;
    int length;
    int cursorInd;
} ListObj;

//typedef struct ListObj* List;



List newList(void) {
    List newList = malloc(sizeof(ListObj));
    if (newList != NULL) {
        Node head = newNode(-1);
        Node tail = newNode(-1);
        head->next = tail;
        head->prev = NULL;
        tail->prev = head;
        tail->next = NULL;

        newList->head = head;
        newList->tail = tail;
        newList->cursor = NULL;
        newList->length = 0;
        newList->cursorInd = -1;
        return newList;
    } else {
        printf("List Error: calling newList() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }

}

void freeList(List *pL) {
    if (pL != NULL && *pL != NULL) {
        if ((*pL)->head != NULL && (*pL)->tail != NULL) {
            Node current = (*pL)->head;
            Node previous;
            while (current != NULL) {
                previous = current;
                current = current->next;
                freeNode(&previous);
            }
            free(*pL);
            *pL = NULL;
        }
        else {
            free(*pL);
            *pL = NULL;
        }
    }
    else {
        printf("List Error: calling freeList() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}



int length(List L) {
    if (L != NULL) {
        return L->length;
    } else {
        printf("List Error: calling length() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

int index(List L) {
    if (L != NULL) {
        if (L->cursor != NULL) {
            return L->cursorInd;
        } else {
            return -1;
        }
    } else {
        printf("List Error: calling index() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

int front(List L) {
    if (L != NULL) {
        if (L->length >= 1) {
            return L->head->next->index;
        } else {
            printf("List Error: calling front() on an emtpy List\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("List Error: calling front() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

int back(List L) {
    if (L != NULL) {
        if (L->length >= 1) {
            return L->tail->prev->index;
        } else {
            printf("List Error: calling back() on an empty List\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("List Error: calling back() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

int get(List L) {
    if (L != NULL) {
        if (L->length >= 1 && L->cursorInd >= 0) {
            return L->cursor->index;
        } else {
            if (L->cursorInd < 0) {
                printf("List Error: calling get() when cursor out of bounds of list\n");
            } 
            
            if (L->length < 1){
                printf("List Error: calling get() on an empty List\n");
            }
            exit(EXIT_FAILURE);
        }
            
    } else {
        printf("List Error: calling get() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

bool equals(List A, List B) {
    if (A != NULL && B != NULL) {
        int lengthA = length(A);
        int lengthB = length(B);
        if (lengthA != lengthB) {
            return false;
        } else {
            Node currentA = A->head->next;
            Node currentB = B->head->next;
            while (currentA->next != NULL && currentB->next != NULL) {
                if (currentA->index != currentB->index) {
                    return false;
                }
                currentA = currentA->next;
                currentB = currentB->next;
            }
            return true;
        }
    } else if (A == NULL && B == NULL) {
        return true;
    } else {
        return false;
    }  
}

void clear(List L) {
    if (L != NULL) {
        Node start = L->head->next;
        while (start->next != NULL) {
            Node temp = start->next;
            freeNode(&start);
            start = temp;
        }
        L->head->next = L->tail;
        L->tail->prev = L->head;
	L->cursor = NULL;
	L->cursorInd = -1;
        L->length = 0;
    } else {
        printf("List Error: calling clear() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void set(List L, int x) {
    if (L != NULL) {
        if (L->length > 0 && L->cursorInd >= 0) {
            L->cursor->index = x;
        } else {
            if (L->length <= 0) {
                printf("List Error: calling set() on an empty List\n");
            }

            if (L->cursorInd < 0) {
                printf("List Error: calling set() when cursor out of bounds of list\n");
            }
                       
            exit(EXIT_FAILURE);
        }
    } else {
        printf("List Error: calling set() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void moveFront(List L) {
    if (L != NULL) {
        if (L->length > 0) {
            L->cursor = L->head->next;
            L->cursorInd = 0;
        } else {
            printf("List Error: calling moveFront() on an empty List\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("List Error: calling moveFront() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void moveBack(List L) {
    if (L != NULL) {
        if (L->length > 0) {
            L->cursor = L->tail->prev;
            int len = L->length;
            L->cursorInd = len-1;
        } else {
            printf("List Error: calling moveBack() on an empty List\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("List Error: calling moveBack() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void movePrev(List L) {
    if (L != NULL) {    
        if (L->cursor != NULL) {
            if (L->cursorInd > 0) {
                Node temp = L->cursor->prev;
                L->cursor = temp;
                L->cursorInd -= 1;
            } else if (L->cursorInd == 0) {
                L->cursor = NULL;
                L->cursorInd = -1;
            }
        } else {
            printf("List Error: calling movePrev() when cursor undefined\n");
            exit(EXIT_FAILURE);
        }
    } else {
        //error message if list is null
        printf("List Error: calling movePrev() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void moveNext(List L) {
    if (L != NULL) {    
        if (L->cursor != NULL) {
            int len = L->length;
            if (L->cursorInd < (len-1)) {
                Node temp = L->cursor->next;
                L->cursor = temp;
                L->cursorInd += 1;
            } else if (L->cursorInd == (len-1)) {
                L->cursor = NULL;
                L->cursorInd = -1;
            }
        } else {
            printf("List Error: calling moveNext() when cursor undefined\n");
            exit(EXIT_FAILURE);
        }
    } else {
        //error message if list is null
        printf("List Error: calling moveNext() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void prepend(List L, int x) {
    if (L != NULL) {
        Node new = newNode(x);

        new->prev = L->head;
        Node oldHeadNext = L->head->next;
        new->next = oldHeadNext;

        L->head->next = new;
        oldHeadNext->prev = new;

        if (L->cursorInd >= 0) {
            L->cursorInd += 1;
        }

        L->length += 1;
        
    } else {
        printf("List Error: calling prepend() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void append(List L, int x) {
    if (L != NULL) {
        Node new = newNode(x);
        new->next = L->tail;

        Node oldTailPrev = L->tail->prev;
        new->prev = oldTailPrev;

        oldTailPrev->next = new;
        L->tail->prev = new;
        
        L->length++;

    } else {
        printf("List Error: calling append() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void insertBefore(List L, int x) {
    if (L != NULL) {
        int len = length(L);
        int ind = index(L);
        if (len > 0 && ind >= 0) {
            Node new = newNode(x);
            new->next = L->cursor;
            Node oldCursPrev = L->cursor->prev;
            new->prev = oldCursPrev;

            oldCursPrev->next = new;
            L->cursor->prev = new;

            L->cursorInd += 1;

            L->length += 1;

        } else {
            if (len <= 0) {
                printf("List Error: calling insertBefore() on an empty List\n");
            }

            if (ind < 0) {
                printf("List Error: calling insertBefore() when cursor out of bounds of list\n");
            }

            exit(EXIT_FAILURE);
        }
    } else {
        printf("List Error: calling insertBefore() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void insertAfter(List L, int x) {
    if (L != NULL) {
        int len = length(L);
        int ind = index(L);
        if (len > 0 && ind >= 0) {
            Node new = newNode(x);
            new->prev = L->cursor;
            Node oldCursNext = L->cursor->next;
            new->next = oldCursNext;

            L->cursor->next = new;
            oldCursNext->prev = new;

            L->length += 1;
        } else {
            if (len <= 0) {
                printf("List Error: calling insertAfter() on an empty List\n");
            }

            if (ind < 0) {
                printf("List Error: calling insertAfter() when cursor out of bounds of list\n");
            }

            exit(EXIT_FAILURE);            
        }
    } else {
        printf("List Error: calling insertAfter() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void deleteFront(List L) {
    if (L != NULL) {
        int len = length(L);
        if (len > 0) {
            //check what happens if deleted node is the cursor

            Node oldHeadNext = L->head->next;
            Node newHeadNext = oldHeadNext->next;
            L->head->next = newHeadNext;
            newHeadNext->prev = L->head;
            freeNode(&oldHeadNext);
	    
	    if (L->cursorInd == 0 && L->cursor != NULL) {
	    	L->cursorInd = -1;
		L->cursor = NULL;
	    }
		
	    if (L->cursorInd >= 1 && L->cursor != NULL) {
		L->cursorInd -= 1;
	    }
	    
            L->length -= 1;
        } else {
            printf("List Error: calling deleteFront() on an empty List\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("List Error: calling deleteFront() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void deleteBack(List L) {
    if (L != NULL) {
        int len = length(L);
        if (len > 0) {
            //check what happens if deleted node is the cursor

            Node oldTailPrev = L->tail->prev;
            Node newTailPrev = oldTailPrev->prev;
            L->tail->prev = newTailPrev;
            newTailPrev->next = L->tail;
            freeNode(&oldTailPrev);

	    int len = length(L);
	    if (L->cursorInd == len-1 && L->cursor != NULL) {
		L->cursorInd = -1;
		L->cursor = NULL;
	    }
 
            L->length -= 1;

        }  else {
            printf("List Error: calling deleteBack() on an empty List\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("List Error: calling deleteBack() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void delete(List L) {
    if (L != NULL) {
        int len = length(L);
        int ind = index(L);

        if (len > 0 && ind >= 0) {
            Node oldCursPrev = L->cursor->prev;
            Node oldCursNext = L->cursor->next;
            
            oldCursNext->prev = oldCursPrev;
            oldCursPrev->next = oldCursNext;

            freeNode(&L->cursor);
            L->cursorInd = -1;

            L->length -= 1;
        } else {
            if (len <= 0) {
                printf("List Error: calling delete() on an empty List\n");
            }

            if (ind < 0) {
                printf("List Error: calling delete() when cursor out of bounds of list\n");
            }

            exit(EXIT_FAILURE);     
        }
    } else {
        printf("List Error: calling delete() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

void printList(FILE* out, List L) {
    if (L != NULL && out != NULL) {
        Node current = L->head->next;
        while (current->next != NULL) {
            fprintf(out, "%i\n", current->index);
            current = current->next;
        }
    } else {
        if (L == NULL) {
            printf("List Error: calling printList() on a NULL List reference\n");
        }

        if (out == NULL) {
            printf("List Error: calling printList() on a NULL output file reference\n");
        }

        exit(EXIT_FAILURE);
    }
}

List copyList(List L) {
    if (L != NULL) {
        List nL = newList();

        Node current = L->head->next;
        while (current->next != NULL) {
            append(nL, current->index);
            current = current->next;
        }

        return nL;
    } else {
        printf("List Error: calling copyList() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
}

List concatList(List A, List B) {
    if (A != NULL && B != NULL) {
        List newA = copyList(A);
        List newB = copyList(B);

        Node aTailPrev = newA->tail->prev;
        Node bHeadNext = newB->head->next;

        aTailPrev->next = bHeadNext;
        bHeadNext->prev = aTailPrev;

        freeNode(&(newA->tail));
        freeNode(&(newB->head));

        return newA;

    } else if (A != NULL && B == NULL) {
        List newA = copyList(A);
        return newA;
    } else if (A == NULL && B != NULL) {
        List newB = copyList(B);
        return newB;
    } else {
        printf("List Error: calling concatList() on two NULL List references\n");
        exit(EXIT_FAILURE);
    }
}

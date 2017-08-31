

#ifndef NULL
#define NULL 0L
#endif /* ~NULL */

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif /* ~TRUE */

#ifdef WIN32
#define DIR_SEP '\\'
#else /* ~WIN32 */
#define DIR_SEP '/'
#endif /* WIN32 */

#ifndef max
#define max(A,B) (((A)>(B)) ? (A) : (B))
#define min(A,B) (((A)>(B)) ? (B) : (A))
#endif /* ~max */

#ifndef round
#define round(X) (((X) >= 0) ? (int)((X)+0.5) : (int)((X)-0.5))
#endif /* ~round */

#ifndef MAXPATHLENGTH
#define MAXPATHLENGTH 256
#endif /* ~MAXPATHLENGTH */



#ifndef _List_H_
#define _List_H_




typedef struct tagListElem {
    void *obj;
    struct tagListElem *next;
    struct tagListElem *prev;
} ListElem;

typedef struct tagList {
    int num_members;
    ListElem anchor;

    /* */
    int  (*Length)(struct tagList * list);
    int  (*Empty)(struct tagList * list);

    int  (*Append)(struct tagList * list, void* object);
    int  (*Prepend)(struct tagList * list, void* object);
    void (*Unlink)(struct tagList * list, ListElem* element);
    void (*UnlinkAll)(struct tagList * list);
    int  (*InsertBefore)(struct tagList * list, void*, ListElem* element);
    int  (*InsertAfter)(struct tagList * list, void*, ListElem* element);

    ListElem *(*First)(struct tagList * list);
    ListElem *(*Last)(struct tagList * list);
    ListElem *(*Next)(struct tagList * list, ListElem *cur);
    ListElem *(*Prev)(struct tagList * list, ListElem *cur);

    ListElem *(*Find)(struct tagList * list, void *obj);
} List;

extern int  ListLength(List* list);
extern int  ListEmpty(List* list);

extern int  ListAppend(List* list, void* object);
extern int  ListPrepend(List* list, void* object);
extern void ListUnlink(List* list, ListElem* element);
extern void ListUnlinkAll(List* list);
extern int  ListInsertAfter(List* list, void* object, ListElem* element);
extern int  ListInsertBefore(List* list, void* object, ListElem* element);

extern ListElem *ListFirst(List* list);
extern ListElem *ListLast(List* list);
extern ListElem *ListNext(List* list, ListElem* element);
extern ListElem *ListPrev(List* list, ListElem* element);

extern ListElem *ListFind(List* list, void* object);

extern int ListInit(List* list);

#endif /*_List_H_*/





#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>


#include "List.h"



 
/* ---------------------------------------------- */


//Initialize the list into an empty list. Returns TRUE if all is well and returns FALSE if there is an error initializing the list.
int ListInit(List* list){
    
    list->anchor.obj = NULL;
    list->anchor.next = NULL;
    list->anchor.prev = NULL;
    list->num_members = 0;

    if(list->anchor.obj == NULL && list->num_members == 0){
        return 1;
    }
    else {
        return 0;
    }
    
}


//Returns TRUE if the list is empty. Returns FALSE otherwise
int  ListEmpty(List* list){
    
    if(list->num_members == 0){ 
        return 1;
    }
    else{
        return 0;
    }
    
}




//Returns the number of elements in the list.
int  ListLength(List* list){

	return list->num_members;
 }






//append
int  ListAppend(List* list, void* object){
     
     ListElem * NewElem = (ListElem*)malloc (sizeof (ListElem));
     NewElem->obj = object;

     NewElem->next = &list->anchor;
    
     if(list->anchor.next == NULL || list->anchor.next == &list->anchor){      //empty list
         NewElem->prev = &list->anchor;
         list->anchor.prev = NewElem;
         list->anchor.next = NewElem;
     } 
     else{
         NewElem->prev = list->anchor.prev;  //non empty list
         list->anchor.prev->next = NewElem;
         list->anchor.prev = NewElem;
     }
     
     list->num_members++;// update num members
     
     if( list->anchor.prev->obj == object){
        
        return 1;
     }
     else{
        return 0;
     }
}



int  ListPrepend(List* list, void* object){
    
    ListElem * NewElem = (ListElem*)malloc (sizeof (ListElem));
    NewElem->obj = object;
    NewElem->prev = &list->anchor;
    
    if(list->anchor.prev == NULL ||list->anchor.prev == &list->anchor){      //empty list
        NewElem->next = &list->anchor;
        list->anchor.prev = NewElem;
        list->anchor.next = NewElem;
    }
    else{
        NewElem->next = list->anchor.next;  //non empty list
        list->anchor.next->prev = NewElem;
        list->anchor.next = NewElem;
    }

    list->num_members++;// update num members
    
    
    if( list->anchor.next->obj == object){
        
        return 1;
    }
    else{
        return 0;
    }
}




//Unlink and delete elem from the list. Please do not delete the object pointed to by elem and do not check if elem is on the list.

void ListUnlink(List* list, ListElem* element){
    
    
    if(list->anchor.next == NULL || list->anchor.next == &list->anchor || element ==NULL){  //empty list or NULL element
        return; //NULL;
    }
    
    element->prev->next = element->next;
    element->next->prev = element->prev;
    free(element);  //free 
     
    list->num_members--;// update num members
    return;  // NULL;
}







//Unlink and delete all elements from the list and make the list empty. Please do not delete the objects pointed to by the list elements.
void ListUnlinkAll(List* list){
    
    if(list->anchor.next == NULL || list->anchor.next == &list->anchor){  //empty list
        return; // NULL;
    }
    
    ListElem * elem = list->anchor.next;
    
    while (elem != &list->anchor) {  //will stop when only anchor is left
        ListElem * del = elem;
        elem = elem->next;
        free(del);  //free
    }
    
    
    list->anchor.next = NULL; //reset list
    list->anchor.prev = NULL;
    list->num_members = 0;

    return; // NULL;  //only anchor left
    
    

    
}






// Insert obj between elem and elem->prev. If elem is NULL, then this is the same as Prepend(). This function returns TRUE if the operation is performed successfully and returns FALSE otherwise. Please do not check if elem is on the list.
int  ListInsertBefore(List* list, void* object, ListElem* element){
    
    if(list->anchor.next == NULL || list->anchor.next == &list->anchor || element ==NULL){  //empty list or NULL elem
        ListPrepend(list, object);
        return 1;
    }
    
    ListElem * NewElem = (ListElem*)malloc (sizeof (ListElem));
    NewElem->obj = object;
    NewElem->next = element;
    NewElem->prev = element->prev;
    
    element->prev->next = NewElem;
    element ->prev = NewElem;

    list->num_members++;// update num members
    
    if( element->prev->obj == object){
        
        return 1;
    }
    else{
        return 0;
    }


}



//Insert obj between elem and elem->next. If elem is NULL, then this is the same as Append(). This function returns TRUE if the operation is performed successfully and returns FALSE otherwise. Please do not check if elem is on the list.
int  ListInsertAfter(List* list, void* object, ListElem* element){
        
        if(list->anchor.next == NULL || list->anchor.next == &list->anchor || element ==NULL){      //empty list or NULL elem
            ListAppend(list, object); 
            return 1;
        }
      
        
        ListElem * NewElem = (ListElem*)malloc (sizeof (ListElem));
        NewElem->obj = object;
        NewElem->prev = element;
        NewElem->next = element->next;

        element->next->prev = NewElem;
        element->next = NewElem;
        
        list->num_members++;// update num members
        
        if( element->next->obj == object){
            
            return 1;
        }
        else{
            return 0;
        }
        
        
}




//Returns the first list element or NULL if the list is empty.
ListElem *ListFirst(List* list){
    if(list ->num_members > 0){		
    	return list->anchor.next;
    }
    else{
	return NULL;
    }
}



//Returns the last list element or NULL if the list is empty.
ListElem *ListLast(List* list){
    if(list->num_members > 0){
    	return list->anchor.prev; 
    }
    else{
	return NULL;
    }
}



//Returns elem->next or NULL if elem is the last item on the list. Please do not check if elem is on the list.
ListElem *ListNext(List* list, ListElem* element){
    
    if(list->num_members > 0 && element != ListLast(list)){
        return element->next;
    }
    else{
        return NULL;
    }
    
}


//Returns elem->prev or NULL if elem is the first item on the list. Please do not check if elem is on the list
ListElem *ListPrev(List* list, ListElem* element){
    
    if(list->num_members > 0 && element != ListFirst(list)){
        return element->prev;
    }
    else{
        return NULL;
    }
}




//Returns the list element elem such that elem->obj == obj. Returns NULL if no such element can be found.
ListElem *ListFind(List* list, void* object){
    
    
    if(list->num_members == 0 || object == NULL){  //empty list
        return NULL;
    }
    
    ListElem * elem = list->anchor.next;
       
    while (elem != &list->anchor) {  //will stop when gets back to the anchor 
            if(elem->obj == object){
		return elem; //return element           	
	    }
            elem = elem->next;
    }
       
   return NULL;  //obj not in list
}



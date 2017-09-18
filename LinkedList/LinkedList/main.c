#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
}node;

typedef struct list{
    int size;
    node* head;
}list;

void insert(list* list, int value);
void insertAt(list* list, int value, int position);
void delete(list* list, int position);
int search(list* list, int value);
void update(list* list, int value, int position);
void print_list(list* list);

int main(void) {
    
    //Initialize LinkedList
    list* LinkedList = (list*)malloc(sizeof(list));
    LinkedList->size = 0;
    LinkedList->head = NULL;
    
    //Test for insert() & print_list()
    insert(LinkedList, 5);
    print_list(LinkedList);
    insert(LinkedList, 7);
    print_list(LinkedList);
    insert(LinkedList, 9);
    print_list(LinkedList);
    insert(LinkedList, 11);
    print_list(LinkedList);
    insert(LinkedList, 13);
    print_list(LinkedList);
    
    //Test for insertAt()
    insertAt(LinkedList, 6, 3);
    print_list(LinkedList);
    
    //Test for delete()
    delete(LinkedList, 2);
    print_list(LinkedList);
    
    //Test for search()
    int searchResult = search(LinkedList, 6);
    printf("Value 6 is located index %d.\n\n", searchResult);
    
    //Test for update()
    printf("Before index 3 update...\n");
    print_list(LinkedList);
    update(LinkedList, 1234, 3);
    printf("After index 3 update...\n");
    print_list(LinkedList);
    return 0;
}

void insert(list* list, int value) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->value = value;
    newnode->next = NULL;
    
    if(list->size == 0) {
        newnode->next = list->head;
        list->head = newnode;
    } else {
        node* temp = list->head;
        while (temp->next!=NULL) {
            temp = temp->next;
        }
        newnode->next = temp->next;
        temp->next = newnode;
    }
    list->size++;
}

void insertAt(list* list, int value, int position) {
    printf("Insert index %d of linked list\n", position);
    printf("------------------------------------\n");
    
    node* newnode = (node*)malloc(sizeof(node));
    newnode->value = value;
    newnode->next = NULL;
    
    node* temp = list->head;
    while (position-1 != 1) {
        temp = temp->next;
        position--;
    }
    newnode->next = temp->next;
    temp->next = newnode;
    
    list->size++;
}

void delete(list* list, int position) {
    printf("Delete index %d of linked list\n", position);
    printf("------------------------------------\n");
    if(position<1 || position>(list->size)) {
        printf("delete() : out of index ( n = %d )\n", position);
        return;
    }
    node* delNode = list->head;
    
    if (position == 1) {
        list->head = delNode->next;
        free(delNode);
    } else {
        for (int i = 1; i < position-1; i++) {
            delNode = delNode->next;
        }
        node* temp = delNode->next;
        delNode->next = temp->next;
        free(temp);
    }
    
    list->size--;
}

int search(list* list, int value) {
    int position = 1;
    node* temp = list->head;
    
    while (temp->value != value) {
        temp = temp->next;
        position++;
    }
    
    return position;
}

void update(list* list, int value, int position) {
    node* temp = list->head;
    while (position != 1) {
        temp = temp->next;
        position--;
    }
    
    temp->value = value;
}

void print_list(list* list) {
    node* temp = list->head;
    printf("List size = %d\n", list->size);
    while (temp != NULL) {
        printf("[%d] ", temp->value);
        temp = temp->next;
    }
    printf("\n\n");
}

#include <stdio.h>
#include <stdlib.h>
typedef struct listNode{
    int data;
    struct listNode *next;
}listNode;
typedef struct list{
    int length;
    listNode *next;
    struct listNode *end;
}list;
union data{
    int i;
    double x;
    char str[16];
};
list* list_init();
listNode* list_node_init();
void list_append_node(list* list,listNode* listNode);
void list_delete_node(list* list,listNode* listNode);
void list_show(list* list);
void list_free(list* list);
int main() {
    list* list = list_init();
    listNode* listNode = list_node_init();
    listNode->data = 123;
    list_append_node(list,listNode);

    struct listNode* listNo = list_node_init();
    listNo->data = 123456;
    list_append_node(list,listNo);
    list_delete_node(list,listNode);
    list_show(list);
    list_free(list);

    printf("success");

    union data a ={1},b={"123"},c={1.1};
    union data aa[100]={a,b,c};
    printf("%d\n",aa[0]);
    printf("%s\n",aa[1]);
    return 0;
}
list* list_init(){
    list* listVar = malloc( sizeof(list) );
    listVar->length = 0;

    return listVar;
}
listNode* list_node_init(){
    listNode* ln = malloc( sizeof(listNode) );
    ln->next = NULL;
    return ln;
}
void list_append_node(list* list,listNode* listNode){

    //printf("%d",listNode->data);
    //printf("%d\n",list->length);
    if( list->length == 0 ){
        list->next = listNode;
    }else{
        //printf("123123\n");
        list->end->next = listNode;

    }
    list->end = listNode;
    list->length++;
}
void list_delete_node(list* listVar,listNode* listNodeVar){
    if( listVar->length == 0 ){
        return;
    }
    listNode* ln = listVar->next;
    while( ln != NULL && ln->next != NULL ){
        printf("%d , %d \n",ln->next,listNodeVar);
        if( ln->next == listNodeVar ){
            ln->next = listNodeVar->next;
            free(listNodeVar);
            break;
        }
        return;
    }
}
void list_show(list* list){
    printf("有多少个%d节点\n",list->length);
    listNode* ln = list->next;
    int i=1;
    while( 1 ){
        if( ln == NULL ){
            break;
        }
        printf("%d    %d\n",i,ln->data);
        i++;
        //printf("%d\n",ln->next);
        ln = ln->next;
    }
}
void list_free(list* list){
    listNode* ln = list->next;
    listNode* next;
    while( ln != NULL ){
        next = ln->next;
        free(ln);
        ln = next;
    }
    free(list);
}

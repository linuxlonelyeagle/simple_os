#include "./../lib/list.h"
#include "./../lib/interrupt.h"

void list_init(struct list* list) {
    list->head.prev = 0;
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
    list->tail.next = 0;
}
// 把链表元素elem插入到before之前
void list_insert_before(struct list_elem* before, struct list_elem* elem) {
    enum  intr_status old_status = intr_disable();
    before->prev->next = elem;
    elem->prev = before->prev;
    elem->next = before;
    before->prev = elem;
    intr_set_status(old_status);
} 
// 添加元素到列表表首
void list_push(struct list* plist, struct list_elem* elem) {
    list_insert_before(plist->head.next,elem);
}

// 追加元素到链表队尾
void list_append(struct list* plist, struct list_elem* elem) {
    list_insert_before(&plist->tail,elem);
}

void list_remove(struct list_elem* pelem) {
    enum intr_status old_status = intr_disable();
    pelem->prev->next = pelem->next;
    pelem->next->prev = pelem->prev;
    intr_set_status(old_status);
}

//将链表第一个元素弹出并且返回
struct list_elem* list_pop(struct list* plist) {
    struct list_elem* elem = plist->head.next;
    list_remove(elem);
    return elem;
}

int elem_find(struct list* plist, struct list_elem* obj_elem) {
    struct list_elem* elem = plist->head.next;
    while (elem != &plist->tail) {
        if (elem == obj_elem) {
            return 1;
        } 
        elem = elem->next;
    }
    return 0;
}

struct list_elem* list_traversal(struct list* plist, function func,int arg) {
    struct list_elem* elem = plist->head.next;
    if (list_empty(plist)) {
        return 0;
    }
    while (elem != &plist->tail) {
        if (func(elem,arg)) {
            return elem;
        }
        elem = elem->next;
    }
    return 0;
}



uint32_t list_len(struct list* plist) {
    struct list_elem* elem = plist->head.next;
    uint32_t length = 0;
    while (elem != &plist->tail) {
        length++;
        elem = elem->next;
    }
    return length;
}

int list_empty(struct list* plist) {
    return (plist->head.next == &plist->tail ? 1:0);
}



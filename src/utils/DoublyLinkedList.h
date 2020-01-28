#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <memory>

template<typename T>
struct DoublyLinkedList;

template<typename T>
struct DoublyLinkedListNode;

template<typename T> 
using DoublyLinkedListNodePtr = std::shared_ptr<DoublyLinkedListNode<T>>;

template<typename T>
struct DoublyLinkedListNode {
    T data;
    DoublyLinkedListNodePtr<T> previous;
    DoublyLinkedListNodePtr<T> next;

    DoublyLinkedListNode(T);
};

template<typename T>
struct DoublyLinkedList {
    size_t _size;
    DoublyLinkedListNodePtr<T> head;

    void remove();
    void insertAfter(T);
    void insertBefore(T);
    void goNext();
    void goPrevious();
    size_t size();
    T& data();

    ~DoublyLinkedList();
};
#endif
#include "DoublyLinkedList.h"

template<typename T>
DoublyLinkedListNode<T>::DoublyLinkedListNode(T _data) 
    : data(_data), previous(this), next(this) {}

template<typename T>
void DoublyLinkedList<T>::remove() {
    _size--;
    if (head->next == head) {
        head = nullptr;
        return;
    }
    head->next->previous = head->previous;
    head->prev->next = head->next;
    head = head->previous;
}

template<typename T>
void DoublyLinkedList<T>::insertAfter(T data) {
    _size++;
    DoublyLinkedListNodePtr<T> newNode(new DoublyLinkedListNode<T>(data));
    if (head == nullptr) {
        head = newNode;
        return;
    }
    DoublyLinkedListNodePtr<T> currentNext = head->next;
    head->next = newNode;
    currentNext->previous = newNode;
    newNode->next = currentNext;
    newNode->previous = head;
}

template<typename T>
void DoublyLinkedList<T>::insertBefore(T data) {
    _size++;
    DoublyLinkedListNodePtr<T> newNode(new DoublyLinkedListNode<T>(data));
    if (head == nullptr) {
        head = newNode;
        return;
    }
    DoublyLinkedListNodePtr<T> currentPrevious = head->previous;
    head->previous = newNode;
    currentPrevious->next = newNode;
    newNode->previous = currentPrevious;
    newNode->next = head;
}

template<typename T>
void DoublyLinkedList<T>::goNext() {
    head = head->next;
}

template<typename T>
void DoublyLinkedList<T>::goPrevious() {
    head = head->previous;
}

template<typename T>
size_t DoublyLinkedList<T>::size() {
    return _size;
}

template<typename T>
T& DoublyLinkedList<T>::data() {
    return head->data;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head != nullptr) {
        remove();
    }
}
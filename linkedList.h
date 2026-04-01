#ifndef LABA2_LINKEDLIST_H
#define LABA2_LINKEDLIST_H
#include <stdexcept>

#include "i_enumerator.h"
template <class T>
class LinkedList {

private:
    struct Node {
        T data; // T здесь используем для хранения объекта, поэтому не ссылка
        Node *next;//

        Node(T value) {
            data = value;
            next = nullptr;
        }
    };

    Node *head;
    Node *tail;
    int length;

public:
    // constructors
    LinkedList(const T *element, int count);
    LinkedList();
    LinkedList(const LinkedList& list);

    // destructor
    ~LinkedList();

    // Decomposition
    const T& GetFirst() const;
    const T& GetLast() const;
    const T& Get(int index) const;
    const T& GetHead() const;

    LinkedList<T>* GetSubList(int startIndex, int endIndex); // сл этап

    int GetLength() const;

    // Operations
    void Append(const T& element); // добавить в конец
    void Prepend(const T& element); // добавить в начало
    void InsertAt(const T& element, int index); // добавить в заданную позицию // сл этап

    LinkedList<T>* Concat(LinkedList<T> *list);

    // итератор
    class ListEnumerator : public IEnumerator<T> {

    public:
        ListEnumerator(const Node *head)
            : current(head) {}

        bool HasNext() override {
            return current != nullptr;
        }

        const T& Next() override {
            const T& value = current->data;

            current = current->next;

            return value;
        }

    private:
        const Node *current;
    };

};

/*============ КОНСТРУКТОРЫ ============*/

template<class T>
LinkedList<T>::LinkedList(const T *element, int count) {
    if (count < 0)
        throw std::out_of_range("Index out of range");
    head = nullptr;
    tail = nullptr;
    length = 0;

    for (int i = 0; i < count; i++) {
        Append(element[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList& list) {
    head = nullptr;
    tail = nullptr;
    length = 0;

    Node *current = list.head;
    while (current != nullptr) {
        Append(current->data);
        current = current->next;
    }
}

/*============ ДЕСТРУКТОР ============*/

template<class T>
LinkedList<T>::~LinkedList() {

    Node *current = head;

    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

/*============ ГЕТТЕРЫ ============*/

template<class T>
const T& LinkedList<T>::GetFirst() const{
    if (length == 0)
        throw std::out_of_range("Empty list");
    return head->data;
}

template<class T>
const T& LinkedList<T>::GetLast() const {
    if (length == 0)
        throw std::out_of_range("Empty list");
    return tail->data;
}

template<class T>
const T& LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("Empty list");

    Node *current = head;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<class T>
int LinkedList<T>::GetLength() const{
    return length;
}

template<class T>
const T &LinkedList<T>::GetHead() const {
    return head;
}

template<class T>
LinkedList<T> *LinkedList<T>::GetSubList(int startIndex, int endIndex) {
    if (startIndex < 0 || startIndex >= length || startIndex > endIndex || endIndex >= length)
        throw std::out_of_range("Index out of range");

    LinkedList<T> *newList = new LinkedList<T>(); // нужно ли выделять память или передать как параметр?

    Node *current = head;
    for (int i = 0; i < startIndex; i++) {
        current = current->next;
    }

    for (int i = startIndex; i <= endIndex; i++) {
        newList->Append(current->data);
        current = current->next;
    }

    return newList;
}

/*============ ОПЕРАЦИИ ============*/

template<class T>
void LinkedList<T>::Append(const T& element) {

    Node *newNode = new Node(element);

    if (length == 0) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    length++;
}

template<class T>
void LinkedList<T>::Prepend(const T& element) {

    Node *newNode = new Node(element);

    newNode->next = head;
    head = newNode;

    if (length == 0) {
        tail = newNode;
    }
    length++;
}

template<class T>
void LinkedList<T>::InsertAt(const T& element, int index) {
    if (index < 0 || index > length)
        throw std::out_of_range("Index out of range");

    if (index == 0) {
        Prepend(element);
        return;
    }
    if (index == length) {
        Append(element);
        return;
    }

    Node *prev = head;

    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }

    Node *newNode = new Node(element);

    newNode->next = prev->next;
    prev->next = newNode;

    length++;
}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *list) {

    LinkedList<T> *concatList = new LinkedList<T>(*this);

    Node *current = list->head;
    while (current != nullptr) {
        concatList->Append(current->data);
        current = current -> next;
    }

    return concatList;
}


#endif //LABA2_LINKEDLIST_H
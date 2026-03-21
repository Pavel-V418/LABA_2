#ifndef LABA2_LINKEDLIST_H
#define LABA2_LINKEDLIST_H
#include <stdexcept>

template <class T>
class LinkedList {
public:
    // constructors
    LinkedList(T *element, int count);
    LinkedList();
    LinkedList(const LinkedList& list);

    // destructor
    ~LinkedList();

    // Decomposition
    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;

    LinkedList<T>* GetSubList(int startIndex, int endIndex); // сл этап

    int GetLength() const;

    // Operations
    void Append(T element); // добавить в конец
    void Prepend(T element); // добавить в начало
    void InsertAt(int index, T element); // добавить в заданную позицию // сл этап

    LinkedList<T>* Concat(LinkedList<T> *list); // сл этап

private:
    struct Node {
        T data;
        Node *next;//

        Node(T value) {
            data = value;
            next = nullptr;
        }
    };

    Node *head;
    Node *tail;
    int length;
};

/*============ КОНСТРУКТОРЫ ============*/

template<class T>
LinkedList<T>::LinkedList(T *element, int count) {
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
T LinkedList<T>::GetFirst() const{
    if (length == 0)
        throw std::out_of_range("Empty list");
    return head->data;
}

template<class T>
T LinkedList<T>::GetLast() const {
    if (length == 0)
        throw std::out_of_range("Empty list");
    return tail->data;
}

template<class T>
T LinkedList<T>::Get(int index) const {
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
void LinkedList<T>::Append(T element) {

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
void LinkedList<T>::Prepend(T element) {

    Node *newNode = new Node(element);

    newNode->next = head;
    head = newNode;

    if (length == 0) {
        tail = newNode;
    }
    length++;
}

template<class T>
void LinkedList<T>::InsertAt(int index, T element) {
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


#endif //LABA2  _LINKEDLIST_H
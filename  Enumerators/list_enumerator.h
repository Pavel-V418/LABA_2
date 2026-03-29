#ifndef LABA2_LIST_ENUMERATOR_H
#define LABA2_LIST_ENUMERATOR_H

#include <list>

#include "../i_enumerator.h"
#include "../linkedList.h"

template<class T>
class ListEnumerator : public IEnumerator<T> {

public:
    ListEnumerator(typename LinkedList<T>::Node *head);

    bool HasNext() override;
    const T& Next() override;

private:
    typename LinkedList<T>::Node *current;

};

template<class T>
ListEnumerator<T>::ListEnumerator(typename LinkedList<T>::Node *head)
    : current(head) {}

template<class T>
bool ListEnumerator<T>::HasNext() {
    return current != nullptr;
}

template<class T>
const T &ListEnumerator<T>::Next() {
    if (!HasNext()) {
        throw std::out_of_range("ListEnumerator::Next");
    }

    const T& value = current->data;

    current = current->next;

    return value;
}
#endif //LABA2_LIST_ENUMERATOR_H
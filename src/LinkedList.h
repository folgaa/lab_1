#ifndef LAB1_2_0_LINKEDLIST_H
#define LAB1_2_0_LINKEDLIST_H

#include <iostream>
#include "Sequence.h"

using namespace std;

template <class T> class LinkedList {
public:
    class Data{
    public:
        T data;
        Data* next{NULL};
        Data(T Item): data(Item){}
    };

    Data* head{NULL};
    Data* tail{NULL};
    int size{0};

    LinkedList(T* Items, int count);

    LinkedList();

    LinkedList (const LinkedList <T> & list);

    T & get_first();

    T & get_last();

    T & get(int index);

    LinkedList<T>* get_sub_list(int StartIndex, int EndIndex);

    int get_length();

    void append(const T & Item);

    void prepend(const T & Item);

    void insert_at(const T & Item, int Index);

    LinkedList<T>* concat(LinkedList<T> *list);


    //iterator/////////////////////////////////
    class Iterator{ friend class LinkedList;
    private:
        Data* p;
        Iterator() : p(nullptr) {};

    public:

        Iterator(Data* new_data) : p(new_data) {};

        Iterator& operator++() {
            p = p->next;
            return (*this);
        }

        Iterator operator++(int) {
            Iterator result = *this;
            ++(*this);
            return result;
        }

        Iterator operator+() {
            Iterator result= p->next;
            return result;
        }

        bool operator!=(Iterator it) {
            return (p != it.p);
        }

        bool operator==(Iterator it) {
            return (p == it.p);
        }

        const T& operator*() {
            return this->p->data;
        }

    };
    //.
    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return nullptr;
    }

    Iterator end_() {
        return Iterator(tail);
    }

    void bubble_sort(Iterator begin, Iterator end, bool(*cmp)(T, T));

    void swap_it(Iterator it1, Iterator it2);

    Iterator par_last(Iterator start, Iterator end, bool(*cmp)(T, T));

    void quick_sort(Iterator start, Iterator end, bool(*cmp)(T, T));

    void split(Iterator head, Iterator& f, Iterator& s);

    void merge_sort(Iterator& head, bool(*cmp)(T, T));

    Iterator merge(Iterator f, Iterator s, bool(*cmp)(T, T));

    void quick_sort_it_(bool (*cmp)(T,T));

    void merge_sort_it_(bool(*cmp)(T, T));

    void bubble_sort_it_(bool(*cmp)(T, T));
};

template <typename T>
LinkedList<T>::LinkedList(T* Items, int count): size(count){ //копирует элементы из переданного массива
    Data* tmp = NULL;
    Data* prev = new Data(Items[0]);
    this->head = prev;

    for(int i = 1; i < count; i++){
        tmp = new Data(Items[i]);
        prev->next = tmp;
        prev = tmp;
    }
    this->tail = tmp;
}

template <typename T>
LinkedList<T>::LinkedList(){} //создаёт пустой список

template <typename T>
LinkedList<T>::LinkedList(const LinkedList <T> & list){
    head = list.head;
    tail = list.tail;
    size = list.size;
}

template <typename T>
T & LinkedList<T>::get_first() {
    if(this == NULL){
        puts("Linked list is empty!");
        exit(2);
    }
    return this->head->data;
}

template <typename T>
T & LinkedList<T>::get_last() {
    if(this == NULL){
        puts("Linked list is empty!");
        exit(2);
    }
    return this->tail->data;
}

template <typename T>
T & LinkedList<T>::get(int index) {
    if(index < 0 || index >= size){
        puts("Index out of range!");
        exit(1);
    }
    Data* tmp = this->head;
    for(int i = 0; i < index; i++){
        tmp = tmp->next;
    }
    return tmp->data;
}

template <typename T>
LinkedList<T>* LinkedList<T>::get_sub_list(int StartIndex, int EndIndex) {
    if (StartIndex < 0 || StartIndex >= size || EndIndex < 0 || EndIndex >= size){
        puts("Index out of range!");
        return 0;
    }
    T Items[EndIndex - StartIndex + 1];
    for(int i = StartIndex; i <= EndIndex; i++){
        Items[i - StartIndex] = get(i);
    }
    LinkedList<T>* SubList = new LinkedList<T>(Items, EndIndex - StartIndex + 1);
    return SubList;
}

template <typename T>
int LinkedList<T>::get_length() {
    return size;
}

template <typename T>
void LinkedList<T>::append(const T & Item) {
    Data* tmp = new Data(Item);
    this->tail->next = tmp;
    this->tail = tmp;
    size++;
}

template <typename T>
void LinkedList<T>::prepend(const T & Item) {
    Data* tmp = new Data(Item);
    tmp->next = this->head;
    this->head = tmp;
    size++;
}

template <typename T>
void LinkedList<T>::insert_at(const T & Item, int Index) {
    if(Index < 0 || Index >= size){
        puts("Index out of range!");
        return;
    }
    if(Index == 0){
        prepend(Item);
    }
    if(Index == size - 1){
        append(Item);
    }
    Data* NewEl = new Data(Item);
    Data* ptr = this->head;
    Data* prev = ptr;
    for(int i = 0; i < Index; i++){
        prev = ptr;
        ptr = ptr->next;
    }
    prev->next = NewEl;
    NewEl->next = ptr;
    size++;
}

template <typename T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T> *list) {
    this->tail->next = list->head;
    this->tail = list->tail;
    size = this->size + list->size;
    return this;
}

template <typename T>
void LinkedList<T>::swap_it(Iterator it1, Iterator it2)
{
    T tmp;
    tmp = it1.p->data;
    it1.p->data = it2.p->data;
    it2.p->data = tmp;
}


template <typename T>
void LinkedList<T>::bubble_sort(Iterator begin, Iterator end, bool(*cmp)(T, T))
{
    for(Iterator i = begin; i != end; i++)
    {
        for(Iterator j = begin; j != i; j++)
        {
            if(cmp(*j, *i))
            {
                swap_it(i, j);
            }
        }
    }
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::par_last(Iterator start, Iterator end, bool(*cmp)(T, T))
{
    if (start == end || start == NULL || end == NULL)
        return start;

    Iterator pivot_prev = start;
    Iterator curr = start;
    T pivot = *end;

    while (start != end) {
        if (cmp(pivot, *start)) {
            pivot_prev = curr;
            T temp = curr.p->data;
            curr.p->data = start.p->data;
            start.p->data = temp;
            ++curr;
        }
        start = ++start;
    }

    T temp = curr.p->data;
    curr.p->data = pivot;
    end.p->data = temp;

    return pivot_prev;
}

template <typename T>
void LinkedList<T>::quick_sort(Iterator start, Iterator end, bool(*cmp)(T, T))
{
    if(start == NULL || start == end|| start == +end)
        return;

    Iterator pivot_prev = par_last(start, end, cmp);
    quick_sort(start, pivot_prev, cmp);

    if (pivot_prev != NULL && pivot_prev == start)
        quick_sort(pivot_prev.p->next, end, cmp);

    else if (pivot_prev != NULL
             && pivot_prev.p->next != NULL)
        quick_sort((++pivot_prev).p->next, end, cmp);
}

template <typename T>
void LinkedList<T>::split(Iterator head, Iterator& f, Iterator& s) {
    Iterator slow = head, fast = head;
    ++fast;
    while (fast != NULL)
    {
        ++fast;
        if (fast != NULL)
        {
            ++slow;
            ++fast;
        }
    }
    Iterator tmp = slow;
    ++tmp;
    f = head;
    s = tmp;
    slow.p->next = NULL;
}

template<typename T>
void LinkedList<T>::merge_sort(Iterator& head, bool(*cmp)(T, T)) {
    Iterator head_ = head, f, s;
    Iterator tmp = head;
    ++tmp;
    if ((head_ == NULL) || (tmp == NULL))
        return;
    split(head_, f, s);
    merge_sort(f, cmp);
    merge_sort(s, cmp);
    head = merge(f, s, cmp);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::merge(Iterator f, Iterator s, bool(*cmp)(T, T)) {
    Iterator result = NULL;
    if (f == NULL)
        return s;
    if (s == NULL)
        return f;
    if (cmp(*f, *s)) {
        result = s;
        ++s;
    }
    else {
        result = f;
        ++f;
    }
    Iterator tmp = result;
    while (f != NULL && s != NULL) {
        if (cmp(*f, *s)) {
            tmp.p->next = s.p;
            ++s;
        }
        else {
            tmp.p->next = f.p;
            ++f;
        }
        ++tmp;
    }
    if (f != NULL) {
        tmp.p->next = f.p;
    }
    if (s != NULL) {
        tmp.p->next = s.p;
    }
    return result;
}

template <typename T>
void LinkedList<T>::merge_sort_it_(bool(*cmp)(T, T)) {
    Iterator head_ = begin();
    merge_sort(head_, cmp);
    head = head_.p;
}

template <typename T>
void LinkedList<T>::quick_sort_it_(bool (*cmp)(T,T))
{
    quick_sort(this->begin(), this->end_(), cmp);
}

template <typename T>
void LinkedList<T>::bubble_sort_it_(bool (*cmp)(T,T))
{
    bubble_sort(this->begin(), this->end(), cmp);
}

#endif //LAB1_2_0_LINKEDLIST_H

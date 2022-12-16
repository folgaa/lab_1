#ifndef LAB1_2_0_LINKEDLISTSEQUENCE_H
#define LAB1_2_0_LINKEDLISTSEQUENCE_H

#include "LinkedList.h"
#include "Sequence.h"

template <class T> class LinkedListSequence: public Sequence<T>{
private:
    LinkedList<T>* items2;

public:
    LinkedListSequence(T* Items, int count);

    LinkedListSequence();

    LinkedListSequence(const LinkedListSequence<T> & array);

    T & get_first() const override;

    T & get_last() const override;

    T  & get(int index) const override;

    LinkedListSequence<T> *get_subsequence(int startIndex, int endIndex) const override;

    int get_length() const override;

    void append(const T & item) const override;

    void prepend(const T & item) const override;

    void insert_at(const T & item, int index) const override;

    LinkedListSequence(LinkedListSequence&& other) noexcept;

    LinkedListSequence<T>& operator = (LinkedListSequence && other) noexcept;

    void quick_sort_it(bool (*cmp)(T,T));

    void merge_sort_it(bool(*cmp)(T, T));

    void bubble_sort_it(bool(*cmp)(T, T));

    void print();
};

template <typename T>
LinkedListSequence<T>::LinkedListSequence(T* Items, int count): items2(new LinkedList<T>(Items, count)){
}

template <typename T>
LinkedListSequence<T>::LinkedListSequence(): items2(new LinkedList<T>())
{}

template <typename T>
LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence<T> & array){
    items2 = array.items2;
}

template <typename T>
T & LinkedListSequence<T>::get_first() const {
    return this->items2->get_first();
}

template <typename T>
T & LinkedListSequence<T>::get_last() const{
    return this->items2->get_last();
}

template <typename T>
T  & LinkedListSequence<T>::get(int index) const{
    return  this->items2->get(index);
}

template<class T>
LinkedListSequence<T> *LinkedListSequence<T>::get_subsequence(int startIndex, int endIndex) const {
    T new_items[endIndex - startIndex + 1];
    for(int i = 0; i < endIndex - startIndex + 1; i++){
        new_items[i] = this->items2->get(i + startIndex);
    }
    LinkedListSequence<T>* SubSeq = new LinkedListSequence<T>(new_items, endIndex - startIndex + 1);
    return SubSeq;
}

template<class T>
int LinkedListSequence<T>::get_length() const {
    return this->items2->get_length();
}

template<class T>
void LinkedListSequence<T>::append(const T & item) const {
    this->items2->append(item);
}

template<class T>
void LinkedListSequence<T>::prepend(const T & item) const {
    this->items2->prepend(item);
}

template<class T>
void LinkedListSequence<T>::insert_at(const T & item, int index) const {
    this->items2->insert_at(item, index);
}

template <typename T>
LinkedListSequence<T>::LinkedListSequence(LinkedListSequence&& other) noexcept{
    items2 = other.items2;
    other.items2 = NULL;
}

template <typename T>
LinkedListSequence<T>& LinkedListSequence<T>::operator = (LinkedListSequence && other) noexcept{
    if(this != &other){
        delete[] items2;
        items2 = other.items;
        other.items = NULL;
    }
    return *this;
}

template <typename T>
void LinkedListSequence<T>::quick_sort_it(bool (*cmp)(T,T))
{
    this->items2->quick_sort_it_(cmp);
}

template <typename T>
void LinkedListSequence<T>::merge_sort_it(bool(*cmp)(T, T))
{
    this->items2->merge_sort_it_(cmp);
}

template <typename T>
void LinkedListSequence<T>::bubble_sort_it(bool(*cmp)(T, T))
{
    this->items2->bubble_sort_it_(cmp);
}

template <typename T>
void LinkedListSequence<T>::print()
{
    for(int i = 0; i < this->get_length(); i++)
    {
        cout << this->items2->get(i) << " ";
    }
}

#endif //LAB1_2_0_LINKEDLISTSEQUENCE_H

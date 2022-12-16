#ifndef LAB1_2_0_ARRAYSEQUENCE_H
#define LAB1_2_0_ARRAYSEQUENCE_H

#include "DynamicArray.h"
#include "Sequence.h"
#include <ctime>

using namespace std;

template <class T> class ArraySequence: public Sequence<T>{
private:
    DynamicArray<T>* items;

public:
    ArraySequence(T* Items, int count);

    ArraySequence<T> *get_subsequence(int startIndex, int endIndex) const override;

    int get_length() const override;

    void append(const T & item) const override;

    void prepend(const T & item) const override;

    void insert_at(const T & item, int index) const override;

    ArraySequence();

    ArraySequence (const ArraySequence<T> & array);

    ArraySequence(ArraySequence&& other) noexcept;

    T & get_first() const override;

    T & get_last() const override;

    T & get(int index) const override;

    ArraySequence& operator = (ArraySequence && other) noexcept;

    void quick_sort_it(bool (*cmp)(T,T));

    void merge_sort_it(bool (*cmp)(T,T));

    void bubble_sort_it(bool (*cmp)(T,T));

    void print();
};

template <typename T>
ArraySequence<T>::ArraySequence(T* Items1, int count) {
    items = new DynamicArray<T>(Items1, count);
}

template <typename T>
ArraySequence<T>::ArraySequence(): items(new DynamicArray<T>(0)){
}

template <typename T>
ArraySequence<T>:: ArraySequence(const ArraySequence<T> & array){
    items = array.items;
}

template <typename T>
ArraySequence<T>::ArraySequence(ArraySequence&& other) noexcept{
    items = other.items;
    other.items = NULL;
}

template <typename T>
T & ArraySequence<T>::get_first() const{
    return this->items->get(0);
}

template <typename T>
T & ArraySequence<T>::get_last() const{
    return this->items->get(this->items->capacity - 1);
}

template <typename T>
T & ArraySequence<T>::get(int index) const{
    return  this->items->get(index);
}

template<class T>
ArraySequence<T> *ArraySequence<T>::get_subsequence(int startIndex, int endIndex) const {
    T new_items[endIndex - startIndex + 1];
    for(int i = startIndex; i <= endIndex; i++){
        new_items[i - startIndex] = this->items->Items[i];
    }
    ArraySequence<T>* SubSeq = new ArraySequence<T>(new_items, endIndex - startIndex + 1);
    return SubSeq;
}

template<class T>
int ArraySequence<T>::get_length() const {
    return this->items->get_size();
}

template<class T>
void ArraySequence<T>::append(const T & item) const {
    this->insert_at(item, this->items->capacity);
}

template<class T>
void ArraySequence<T>::prepend(const T & item) const {
    this->insert_at(item, 0);
}

template<class T>
void ArraySequence<T>::insert_at(const T & item, int index) const {
    this->items->resize(this->get_length() + 1);
    for(int i = this->get_length(); i >= index; i --){
        this->items->Items[i] = this->items->Items[i - 1];
    }
    this->items->set(index, item);
}

template <typename T>
ArraySequence<T>& ArraySequence<T>::operator = (ArraySequence && other) noexcept{
    if(this != &other){
        delete[] items;
        items = other.items;
        other.items = NULL;
    }
    return *this;
}

template <typename T>
void ArraySequence<T>::quick_sort_it(bool (*cmp)(T,T))
{
    this->items->quick_sort_it_(cmp);
}

template <typename T>
void ArraySequence<T>::merge_sort_it(bool (*cmp)(T,T))
{
    this->items->merge_sort_it_(cmp);
}

template <typename T>
void ArraySequence<T>::bubble_sort_it(bool (*cmp)(T,T))
{
    this->items->bubble_sort_it_(cmp);
}

template <typename T>
void ArraySequence<T>::print()
{
    for(int i = 0; i < this->get_length(); i++)
    {
        cout << this->get(i) << " ";
    }
}

#endif //LAB1_2_0_ARRAYSEQUENCE_H

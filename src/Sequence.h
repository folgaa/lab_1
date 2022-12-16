#ifndef LAB1_2_0_SEQUENCE_H
#define LAB1_2_0_SEQUENCE_H

#include <iostream>

template <class T> class Sequence{
public:
    virtual T & get_first() const = 0;
    virtual T & get_last() const = 0;
    virtual T & get(int index) const = 0;
    virtual Sequence<T>* get_subsequence(int startIndex, int endIndex) const = 0;
    virtual int get_length() const = 0;
    virtual void append(const T & item) const = 0;
    virtual void prepend(const T & item) const = 0;
    virtual void insert_at(const T & item, int index) const = 0;
    T & operator [] (int i);
    virtual void quick_sort_it(bool (*cmp)(T, T)) = 0;
    virtual void merge_sort_it(bool (*cmp)(T,T)) = 0;
    virtual void bubble_sort_it(bool (*cmp)(T,T)) = 0;
    virtual void print() = 0;
};

template <typename T>
T & Sequence<T>::operator[](int i) {
    if(i < 0 || i >= this->get_length()){
        puts("Index out of range!");
        exit(1);
    }
    return this->get(i);
}

#endif //LAB1_2_0_SEQUENCE_H

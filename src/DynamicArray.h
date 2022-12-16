#ifndef LAB1_2_0_DYNAMICARRAY_H
#define LAB1_2_0_DYNAMICARRAY_H

#include <iostream>
#include <vector>
#include "ArraySequence.h"
using namespace std;

template <class T> class DynamicArray{
    template<typename K>friend class ArraySequence;
private:
    int size;
    int capacity;
    T* Items;

    DynamicArray(T* Items1, int count);

    DynamicArray(int size1);

    DynamicArray(const DynamicArray<T> &arr);

    T & get(int index);

    int get_size();

    void set(int index, const T & value);

    void resize(int newsize);

    //iterator////////////////////
    class Iterator
    {
        friend class DynamicArray;
    private:
        T *p;
        Iterator(T* p1) : p(p1) {};
        Iterator() : p(nullptr) {};
    public:

        T& operator*()
        {
            return *p;
        }

        Iterator& operator++()
        {
            ++p;
            return *this;
        }

        Iterator operator++(int)
        {
            return Iterator(p++);
        }

        Iterator& operator--()
        {
            --p;
            return *this;
        }

        Iterator operator--(int)
        {
            return Iterator(p--);
        }

        T* base() const
        {
            return p;
        }

        friend bool operator==(const Iterator&it1, const Iterator&it2)
        {
            return it1.base() == it2.base();
        }
        friend bool operator!=(const Iterator&it1, const Iterator&it2)
        {
            return it1.base() != it2.base();
        }
        friend bool operator <(const Iterator&it1, const Iterator&it2)
        {
            return it1.base() < it2.base();
        }
        friend bool operator >(const Iterator&it1, const Iterator&it2)
        {
            return it1.base() > it2.base();
        }
        friend bool operator <=(const Iterator&it1, const Iterator&it2)
        {
            return it1.base() <= it2.base();
        }
        friend bool operator >=(const Iterator&it1, const Iterator&it2)
        {
            return it1.base() >= it2.base();
        }
        friend Iterator operator+(const Iterator&it, std::size_t n)
        {
            return DynamicArray<T>::Iterator(it.base() + n);
        }
        friend Iterator operator-(const Iterator&it, std::size_t n)
        {
            return DynamicArray<T>::Iterator(it.base() - n);
        }
    };

    //.

    Iterator begin()
    {
        return Iterator(Items);
    }
    Iterator end()
    {
        return Iterator(Items + capacity);
    }

    Iterator end_()
    {
        return Iterator(Items + capacity - 1);
    }

    void quick_sort_it(Iterator beg, Iterator e, bool (*cmp)(T,T));

    void merge_sort_it(Iterator begin, Iterator end, bool(*cmp)(T, T));

    Iterator split(Iterator begin, Iterator end);

    void merge_it(Iterator begin, Iterator middle, Iterator end, bool(*cmp)(T, T));

    void bubble_sort_it(Iterator begin, Iterator end, bool(*cmp)(T, T));

    void quick_sort_it_(bool (*cmp)(T,T));

    void merge_sort_it_(bool(*cmp)(T, T));

    void bubble_sort_it_(bool(*cmp)(T, T));
};


template <typename T>
DynamicArray<T>::DynamicArray(T* Items1, int count){
    Items = new T[count];
    for(int i = 0; i < count; i++){
        Items[i] = Items1[i];
    }
    size = count;
    capacity = count;
}
template <typename T>
DynamicArray<T>:: DynamicArray(int size1){
    Items = new T[size1];
    size = size1;
    capacity = 0;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &arr){
    Items = new T[arr.size];
    for(int i = 0; i < size; i++){
        *(Items + sizeof(T) * i) = *(arr.Items + sizeof(T) * i);
    }
    size = arr.size;
    capacity = arr.capacity;
}

template <typename T>
T & DynamicArray<T>::get(int index){
    if(index < 0 || index >= capacity){
        cout << "Index out of range!";
        exit(1);
    }
    if(capacity == 0){
        puts("Array is empty!");
    }
    return Items[index];
}

template <typename T>
int DynamicArray<T>::get_size(){
    return capacity;
}

template <typename T>
void DynamicArray<T>::set(int index, const T &value){
    if(index < 0 || index >= size){
        cout << "Index out of range!";
        return;
    }
    Items[index] = value;
    capacity++;
}

template <typename T>
void DynamicArray<T>::resize(int newsize){
    T* el = new T[this->capacity];
    for(int i = 0; i < this->capacity; i++){
        el[i] = this->get(i);
    }
    Items = el;
    size = newsize;
}

//quick_sort/////////////////

template <typename T>
void DynamicArray<T>::quick_sort_it(Iterator beg, Iterator e, bool (*cmp)(T,T))
{
    if(e <= beg) return;
    Iterator pivot = beg;
    Iterator middle = beg + 1;

    for(Iterator i = beg + 1; i != e; ++i)
    {
        if(cmp(*pivot, *i))
        {
            auto tmp = *i;
            *i = *middle;
            *middle = tmp;
            ++middle;
        }
    }
    auto tmp = *beg;
    *beg = *(middle-1);
    *(middle-1) = tmp;
    quick_sort_it(beg, middle-1, cmp);
    quick_sort_it(middle, e, cmp);
}

//merge_sort////////////////

template <typename T>
void DynamicArray<T>::merge_sort_it(Iterator begin, Iterator end, bool(*cmp)(T, T))
{
    if (begin < end)
    {
        Iterator middle = split(begin, end);
        merge_sort_it(begin, middle, cmp);
        Iterator tmp = middle + 1;
        merge_sort_it(tmp, end, cmp);
        merge_it(begin, middle, end, cmp);
    }
};

template <typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::split(Iterator begin, Iterator end)
{
    if (begin == NULL) return NULL;
    Iterator slow = begin, fast = begin;
    ++fast;
    if (begin == end)
        return end;
    while (fast != end)
    {
        ++fast;
        if (fast != end)
        {
            ++slow;
            ++fast;
        }
        else ++slow;
    }
    return slow;
}

template <typename T>
void DynamicArray<T>::merge_it(Iterator begin, Iterator middle, Iterator end, bool(*cmp)(T, T))
{
    Iterator middle_2 = middle + 1;
    Iterator sub_1 = middle;
    Iterator sub_2 = end;
    Iterator ind_sub_1 = begin, ind_sub_2 = middle_2;
    int ind_merge = 0;
    vector<T> merged_vector;

    while ((ind_sub_1 <= sub_1) && (ind_sub_2 <= sub_2))
    {
        if (cmp(*(ind_sub_1), *(ind_sub_2)))
        {
            merged_vector.push_back(*(ind_sub_2));
            ++ind_sub_2;
        }
        else
        {
            merged_vector.push_back(*(ind_sub_1));
            ++ind_sub_1;
        }
        ++ind_merge;
    }

    while (ind_sub_1 <= sub_1)
    {
        merged_vector.push_back(*(ind_sub_1));
        ++ind_sub_1;
        ++ind_merge;
    }

    while (ind_sub_2 <= sub_2)
    {
        merged_vector.push_back(*(ind_sub_2));
        ++ind_sub_2;
        ++ind_merge;
    }

    int counter = 0;
    for (Iterator ptr = begin; ptr <= end; ++ptr)
    {
        *(ptr.p) = merged_vector[counter];
        ++counter;
    }
}

//bubble_sort//////////////////

template <typename T>
void DynamicArray<T>::bubble_sort_it(Iterator begin, Iterator end, bool(*cmp)(T, T))
{
    for (Iterator i = begin; i != end; ++i)
        for (Iterator j = begin; j < i; ++j)
            if (cmp(*j, *i))
            {
                T tmp = *i;
                *i = *j;
                *j = tmp;
            }
}


//for out////////////////

template<typename T>
void DynamicArray<T>::bubble_sort_it_(bool(*cmp)(T, T))
{
    this->bubble_sort_it(this->begin(), this->end(), cmp);
}

template<typename T>
void DynamicArray<T>::merge_sort_it_(bool(*cmp)(T, T))
{
    this->merge_sort_it(this->begin(), --this->end(), cmp);
}

template<typename T>
void DynamicArray<T>::quick_sort_it_(bool (*cmp)(T,T))
{
    this->quick_sort_it(this->begin(), this->end(), cmp);
}
#endif //LAB1_2_0_DYNAMICARRAY_H

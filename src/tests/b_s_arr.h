#ifndef LAB1_2_0_B_S_ARR_H
#define LAB1_2_0_B_S_ARR_H

#include "..//ArraySequence.h"
#include "..//cmp.h"

void test1()
{
    int *items = new int[20];
    for (int j = 0; j < 20; j++)
        items[j] = rand();

    ArraySequence arr(items, 20);

    cout << "Sequence before sorting:" << endl;
    arr.print();
    cout << endl;
    arr.bubble_sort_it(cmp_int_pos_ord);
    cout << "Sequence after sorting:" << endl;
    arr.print();
    cout << endl;
}


#endif //LAB1_2_0_B_S_ARR_H

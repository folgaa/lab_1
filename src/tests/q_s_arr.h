#ifndef LAB1_2_0_Q_S_ARR_H
#define LAB1_2_0_Q_S_ARR_H

#include "..//ArraySequence.h"
#include "..//cmp.h"

void test2()
{
    int *items = new int[20];
    for (int j = 0; j < 20; j++)
        items[j] = rand();

    ArraySequence arr(items, 20);

    cout << "Sequence before sorting:" << endl;
    arr.print();
    cout << endl;
    arr.quick_sort_it(cmp_int_pos_ord);
    cout << "Sequence after sorting:" << endl;
    arr.print();
    cout << endl;
}

#endif //LAB1_2_0_Q_S_ARR_H

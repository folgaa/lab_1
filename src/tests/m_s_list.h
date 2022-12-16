#ifndef LAB1_2_0_M_S_LIST_H
#define LAB1_2_0_M_S_LIST_H

#include "..//LinkedListSequence.h"
#include "..//cmp.h"

void test6()
{
    int *items = new int[20];
    for (int j = 0; j < 20; j++)
        items[j] = rand();

    LinkedListSequence arr(items, 20);

    cout << "Sequence before sorting:" << endl;
    arr.print();
    cout << endl;
    arr.merge_sort_it(cmp_int_pos_ord);
    cout << "Sequence after sorting:" << endl;
    arr.print();
    cout << endl;
}

#endif //LAB1_2_0_M_S_LIST_H

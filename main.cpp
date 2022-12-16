#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "src/ArraySequence.h"
#include "src/LinkedListSequence.h"
#include "src/cmp.h"
#include "src/DynamicArray.h"
#include "src/LinkedList.h"
#include "src/tests/b_s_arr.h"
#include "src/tests/q_s_arr.h"
#include "src/tests/m_s_arr.h"
#include "src/tests/b_s_list.h"
#include "src/tests/q_s_list.h"
#include "src/tests/m_s_list.h"

int main() {
    srand(time(NULL));
    ofstream fout("C://Activators//sorts.txt");
    int step_0, step_1;

    while(1)
    {
        cout << "1) Sort data" << endl;
        cout << "2) Compare sorts" << endl;
        cout << "3) Tests" << endl;
        cout << "4) Quit" << endl;

        cin >> step_0;

        switch (step_0)
        {
            case 1:
            {
                cout << "Enter sequence length: ";
                int lenght;
                cin >> lenght;

                int *items = new int[lenght];
                for (int i = 0; i < lenght; i++)
                    items[i] = rand();

                ArraySequence<int> arr1(items, lenght);
                Sequence<int> *seq = &arr1;

                cout << "Which sort do you want?" << endl;
                cout << "1) Bubble sort" << endl;
                cout << "2) Quick sort" << endl;
                cout << "3) Merge sort" << endl;
                cin >> step_1;

                switch (step_1) {
                    case 1:
                        cout << "Sequence before sorting:" << endl;
                        seq->print();
                        cout << endl;
                        clock_t t1;
                        t1 = clock();
                        seq->bubble_sort_it(cmp_int_pos_ord);
                        t1 = clock() - t1;
                        cout << t1 << endl;
                        cout << "Sequence after sorting:" << endl;
                        seq->print();
                        cout << endl;
                        break;

                    case 2:
                        cout << "Sequence before sorting:" << endl;
                        seq->print();
                        cout << endl;
                        clock_t t2;
                        t2 = clock();
                        seq->quick_sort_it(cmp_int_pos_ord);
                        t2 = clock() - t2;
                        cout << "time: " << t2 << endl;
                        cout << "Sequence after sorting:" << endl;
                        seq->print();
                        cout << endl;
                        break;

                    case 3:
                        cout << "Sequence before sorting:" << endl;
                        seq->print();
                        cout << endl;
                        clock_t t3;
                        t3 = clock();
                        seq->merge_sort_it(cmp_int_pos_ord);
                        t3 = clock() - t3;
                        cout << "time: " << t3 << endl;
                        cout << "Sequence after sorting:" << endl;
                        seq->print();
                        cout << endl;
                        break;

                    default:
                        cout << "This option doesn't exist!" << endl;
                        break;
                }
                break;
            }

            case 2: {
                double bs = 0, qs = 0, ms = 0;
                for(int i = 10000; i <= 100000; i = i + 10000)
                {
                    int *items1 = new int[i];
                    for (int j = 0; j < i; j++)
                        items1[j] = rand();

                    int *items2 = new int[i];
                    for (int j = 0; j < i; j++)
                        items2[j] = rand();

                    int *items3 = new int[i];
                    for (int j = 0; j < i; j++)
                        items3[j] = rand();

                    LinkedListSequence<int> arr1(items1, i);
                    LinkedListSequence<int> arr2(items2, i);
                    LinkedListSequence<int> arr3(items3, i);
                    Sequence<int> *seq1 = &arr1;
                    Sequence<int> *seq2 = &arr2;
                    Sequence<int> *seq3 = &arr3;

                    clock_t t;
                    t = clock();
                    seq1->bubble_sort_it(cmp_int_pos_ord);
                    t = clock() - t;
                    bs = t;
                    cout << bs << endl;

                    clock_t t2;
                    t2 = clock();
                    seq2->quick_sort_it(cmp_int_pos_ord);
                    t2 = clock() - t2;
                    qs = t2;
                    cout << qs << endl;

                    t = clock();
                    seq3->merge_sort_it(cmp_int_pos_ord);
                    t = clock() - t;
                    ms = t;
                    cout << ms << endl;
                    fout << i << " " << bs << " " << qs << " " << ms << " " << "\n";
                }
                fout.close();
                break;
            }

            case 3:
            {
                int test;
                cout << "Choose test: " << endl;
                cout << "1) Bubble sort(ArraySequence)" << endl;
                cout << "2) Quick sort(ArraySequence)" << endl;
                cout << "3) Merge sort(ArraySequence)" << endl;
                cout << "4) Bubble sort(LinkedListSequence)" << endl;
                cout << "5) Quick sort(LinkedListSequence)" << endl;
                cout << "6) Merge sort(LinkedListSequence)" << endl;
                cin >> test;

                switch(test)
                {
                    case 1:
                    {
                        test1();
                        break;
                    }
                    case 2:
                    {
                        test2();
                        break;
                    }
                    case 3:
                    {
                       test3();
                        break;
                    }
                    case 4:
                    {
                        test4();
                        break;
                    }
                    case 5:
                    {
                        test5();
                        break;
                    }
                    case 6:
                    {
                        test6();
                        break;
                    }
                }
                break;
            }

            case 4:
                exit(42);

            default:
                cout << "This option doesn't exist!" << endl;
                break;
        }
    }
    return 0;
}
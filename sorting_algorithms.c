#include <stdio.h>

int pass = 0;

void print_array(int *p_input, int *p_final, int length, int selection) {
    enum months {JANUARY=1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY};
    enum months january = JANUARY;
    printf("%s", selection == 0 ? "before sorting: " : "after sorting: ");
    for (int *i = p_input; i < p_final; i++) {
        printf("%s%d%s", (i == p_input) ? "[" : "", *i, (i == (p_final - 1)) ? "]\n" : ", ");
    }
}

/*1! = 1 = 1 * 0!
  2! = 1 * 2 = 1 * 2!
  3! = 1 * 2 * 3 = 3 * 2!
*/
int recursive_factorial(int number) {
    if (number == 0) {
        return 1;
    }
    return number * recursive_factorial(number - 1);
}

int iterative_factorial(int number) {
    int factorial = 1;
    if (number > 0) {
        for (int i = 1; i <= number; factorial *= i, i++);
    }
    return factorial;
}

void swap(int *x, int *y) {
    if (*x != *y) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }
}

void counting_sort(int input[]) {
    int minimum = 0, maximum = 0;
    int length = sizeof(input) / sizeof(int);
    for (int i = 0; i < 10; i++) {
        maximum = input[i] > maximum ? input[i] : maximum;
        minimum = input[i] < minimum ? input[i] : minimum;
    }

    int c_length = maximum - minimum;
    int counting_array[maximum - minimum];
    for (int i = 0; i < c_length; i++) {
        counting_array[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        counting_array[input[i] - minimum]++;
    }
    for (int i = 0, count = 0; i <= maximum; i++) {
        while (counting_array[i - minimum] > 0 && count < 10) {
            input[count++] = i;
            counting_array[i -minimum]--;
        }
    }
}

int partition(int input[], int start, int end) {
    int pivot = input[start];
    int i = start, j = end;
    while (i < j) {
        while (i < j && input[--j] >= pivot);
        if (i < j) {
            input[i] = input[j];
        }
        while (i < j && input[++i] <= pivot);
        if (i < j) {
            input[j] = input[i];
        }
    }
    input[j] = pivot;
    return j;
}

void quick_sort(int input[], int start, int end) {
    if (end - start < 2) {
        return;
    }
    
    int pivot_index = partition(input, start, end);
    quick_sort(input, start, pivot_index);
    quick_sort(input, pivot_index + 1, end);
}

void merge(int input[], int start, int mid, int end) {
    if (input[mid - 1] <= input[mid]) {
        return;
    }

    int i = start, j = mid, temp_index = 0;
    int length = end - start;
    int temp[length];

    for (int k = 0; k < length; k++) {
        temp[k] = 0;
    }
    
    while (i < mid && j < end) {
        temp[temp_index++] = input[i] <= input[j] ? input[i++] : input[j++];
    }

    if (i < mid) {
        int flag = start + temp_index;
        while (i < mid) {
            input[flag++] = input[i++];
        }
    }

    for (int k = 0; k < temp_index; k++) {
        input[start++] = temp[k];
    }
}

void merge_sort(int input[], int start, int end) {
    if (end - start < 2) {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort(input, start, mid);
    merge_sort(input, mid, end);
    merge(input, start, mid, end);
}

//void insertion_sort(int *p_input, int *p_final);

void shell_sort(int *p_input, int *p_final) {
    int shifts = 0;
    for (int gap = (p_final - p_input) / 2; gap > 0; gap /= 2) {
        // the code commented below shows that when the gap becomes equal to one then shell sort becomes insertion sort
        /*if (gap == 1) {
            printf("the gap equals %d after %d shits\n", gap, shifts);
            insertion_sort(p_input, p_final);
            return;
        }*/
        for (int *first_unsorted_index = p_input + gap; first_unsorted_index < p_final; first_unsorted_index++) {
            int new_element = *first_unsorted_index;
            int *i = NULL;
            for (i = first_unsorted_index; *(i - gap) > new_element && i > p_input; i -= gap) {
                *i = *(i - gap);
                shifts++;
            }
            *i = new_element;
        }
    }
    printf("%d shifts were required\n", shifts);
}

void insertion_sort(int *p_input, int *p_final) {
    int shifts = 0;
    for (int *first_unsorted_index = p_input + 1; first_unsorted_index < p_final; first_unsorted_index++) {
        int new_element = *first_unsorted_index;
        int *i = NULL;
        for (i = first_unsorted_index; *(i - 1) > new_element && i > p_input; i--) {
            shifts++;
            *i = *(i - 1);
        }
        *i = new_element;
    }
    printf("%d shits were required\n", shifts);
}

void selection_sort(int *p_input, int *p_final) {
    for (int *last_unsorted_index = p_final - 1, *largest = p_input; last_unsorted_index > p_input; last_unsorted_index--, largest = p_input) {
        for (int *i = p_input + 1; i <= last_unsorted_index; i++) {
            largest = *largest < *i ? i : largest;
        }
        swap(largest, last_unsorted_index);
    }
}

void advanced_bubble_sort(int *p_input, int *p_final) {
    int swaps = 0;
    for (int *last_unsorted_index = p_final; last_unsorted_index > p_input; last_unsorted_index--) {
        for (int gap = (p_final - p_input) / 2; gap > 0; gap /= 2) {
            for (int *i = p_input; i < last_unsorted_index && (i + gap) <= last_unsorted_index; i++) {
                if (*i > *(i + gap)) {
                    swaps++;
                    swap(i, i + gap);
                }
            }
        }
    }
    printf("%d swaps were required\n", swaps);
}

void bubble_sort(int *p_input, int *p_final) {
    int swaps = 0;
    for (int *last_unsorted_index = p_final - 1; last_unsorted_index > p_input; last_unsorted_index--) {
        for (int *i = p_input; i < p_final; i++) {
            if (*i > *(i + 1)) {
                swap(i, i + 1);
                swaps++;
            }
        }
    }
    printf("%d swaps were required\n", swaps);
}

int main(int argc, char *argv[]) {

    int input[7] = {20, 35, -15, 7, 55, 1, -22};
    int c_input[10] = {2, 5, 9, 8, 2, 8, 7, 10, 4, 3};
    int length = sizeof(input) / sizeof(int);
    int c_length = sizeof(c_input) / sizeof(int);
    int *p_input = input, *p_final = p_input + length;
    int *p_cinput = c_input, *p_cfinal = c_input + c_length;

    print_array(p_input, p_final, length, 0);
    quick_sort(input, 0, 7);
    //shell_sort(p_input, p_final);
    print_array(p_input, p_final, length, 1);

    print_array(p_cinput, p_cfinal, c_length, 0);
    counting_sort(c_input);
    print_array(p_cinput, p_cfinal, 10, 1);
    /* int number = 7;
    printf("%d! equals %d\n", number, iterative_factorial(number));
    printf("%d! equals %d\n", number, recursive_factorial(number)); */

    return 0;
}
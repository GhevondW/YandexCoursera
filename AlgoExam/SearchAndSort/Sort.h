#ifndef _SORT_H_
#define _SORT_H_

#include <vector>

namespace algo
{
    namespace sort
    {

        template<class T>
        struct DefaultComparator
        {
            bool operator()(const T& obj1, const T& obj2)
            {
                return obj1 > obj2;
            }
        };

        /**
            BoubbleSort O(n^2)
            https://www.programiz.com/dsa/bubble-sort

            Number of comparisons: (n - 1) + (n - 2) + (n - 3) +.....+ 1 = n(n - 1) / 2 nearly equals to n^2
            Complexity: O(n^2)

            Also, we can analyze the complexity by simply observing the number of loops. There are 2 loops so the complexity is n*n = n^2
            Time Complexities:

            Worst Case Complexity:O(n^2)
                If we want to sort in ascending order and the array is in descending order then, the worst case occurs.

            Best Case Complexity:O(n)
                If the array is already sorted, then there is no need for sorting.

            Average Case Complexity:O(n2)
                It occurs when the elements of the array are in jumbled order (neither ascending nor descending).

            Space Complexity:
            Space complexity is O(1) because an extra variable temp is used for swapping.
            In the optimized algorithm, the variable swapped adds to the space complexity thus, making it O(2).

            Bubble Sort Applications
                Bubble sort is used in the following cases where
                1. the complexity of the code does not matter.
                2. a short code is preferred.
        */
        template<class T, class Comparator = DefaultComparator<T>>
        void Bubble(std::vector<T>& arr)
        {
            Comparator cmp;
            size_t n = arr.size();

            for (size_t i = 0; i < n - 1; i++)
            {
                bool swaps = false;
                for (size_t j = 0; j < n - i - 1; j++)
                {
                    swaps = true;
                    if(cmp(arr[j], arr[j + 1])){
                        std::swap(arr[j], arr[j + 1]);
                    }
                }
                if(!swaps) return;
            }
        }


        /**
            SelectionSort O(n^2)
            https://www.programiz.com/dsa/selection-sort

            Number of comparisons: (n - 1) + (n - 2) + (n - 3) + ..... + 1 = n(n - 1) / 2 nearly equals to n^2.

            Complexity = O(n^2)

            Also, we can analyze the complexity by simply observing the number of loops. There are 2 loops so the complexity is n*n = n^2.

            Time Complexities:
            Worst Case Complexity: O(n^2)
                If we want to sort in ascending order and the array is in descending order then, the worst case occurs.
            
            Best Case Complexity: O(n^2)
                It occurs when the array is already sorted
            
            Average Case Complexity: O(n^2)
                It occurs when the elements of the array are in jumbled order (neither ascending nor descending).

            Selection Sort Applications
                The selection sort is used when:

                1. a small list is to be sorted
                2. cost of swapping does not matter
                3. checking of all the elements is compulsory
                4. cost of writing to a memory matters like in flash memory (number of writes/swaps is O(n) as compared to O(n^2) of bubble sort)
        */
        template<class T, class Comparator = DefaultComparator<T>>
        void Selection(std::vector<T>& arr)
        {
            Comparator cmp;
            size_t n = arr.size();

            for (size_t i = 0; i < n - 1; i++)
            {
                int pivot_index = i;
                for (size_t j = i + 1; j < n; j++)
                {
                    if(cmp(arr[pivot_index], arr[j])){
                        pivot_index = j;
                    }
                }
                std::swap(arr[i], arr[pivot_index]);
            }
        }

        /**
            InsertionSort O(n^2)
            https://www.programiz.com/dsa/insertion-sort

            Time Complexities

            .Worst Case Complexity: O(n^2)
                Suppose, an array is in ascending order, and you want to sort it in descending order. In this case, worst case complexity occurs.
                Each element has to be compared with each of the other elements so, for every nth element, (n-1) number of comparisons are made.
                Thus, the total number of comparisons = n*(n-1) ~ n^2
            .Best Case Complexity: O(n)
                When the array is already sorted, the outer loop runs for n number of times whereas the inner loop does not run at all. So, there are only n number of comparisons. Thus, complexity is linear.
            .Average Case Complexity: O(n2)
                It occurs when the elements of an array are in jumbled order (neither ascending nor descending).
            
            .Space Complexity
                Space complexity is O(1) because an extra variable key is used.

            .Insertion Sort Applications
                The insertion sort is used when:
                the array is has a small number of elements
                there are only a few elements left to be sorted
        */
        template<class T, class Comparator = DefaultComparator<T>>
        void Insertion(std::vector<T>& arr)
        {
            Comparator cmp;
            size_t n = arr.size();

            for (size_t i = 1; i < n; i++)
            {
                int key = arr[i];
                int j = i - 1;

                // Compare key with each element on the left of it until an element smaller than
                // it is found.
                // For descending order, change key<array[j] to key>array[j].
                while (key < arr[j] && j >= 0) {
                    arr[j + 1] = arr[j];
                    --j;
                }
                arr[j + 1] = key;
            }
        }

        /**
            MergeSort O(n*log(n))
            https://www.programiz.com/dsa/merge-sort
            Merge Sort Complexity
            Time Complexity
            Best Case Complexity: O(n*log n)
            Worst Case Complexity: O(n*log n)
            Average Case Complexity: O(n*log n)

            Space Complexity
                The space complexity of merge sort is O(n).

            Merge Sort Applications
                Inversion count problem
                External sorting
                E-commerce applications
        */

        template<class T, class Comparator>
        void _MergeSort(std::vector<T>& arr, size_t begin, size_t end);

        template<class T, class Comparator = DefaultComparator<T>>
        void Merge(std::vector<T>& arr)
        {
            _MergeSort<T, Comparator>(arr, 0, arr.size() - 1);
        }

        template<class T, class Comparator>
        void _Merge(std::vector<T>& arr, size_t begin, size_t middle, size_t end)
        {
            size_t length_left = middle - begin + 1;
            size_t length_right = end - middle;

            T L[length_left], R[length_right];

            for (int i = 0; i < length_left; i++)
                L[i] = arr[begin + i];

            for (int j = 0; j < length_right; j++)
                R[j] = arr[middle + 1 + j];

            int iter_left = 0;
            int iter_right = 0;
            int iter_result = begin;

            Comparator cmp;

            while (iter_left < length_left && iter_right < length_right)
            {
                if(!cmp(L[iter_left], R[iter_right])){
                    arr[iter_result] = L[iter_left];
                    ++iter_left;
                }
                else{
                    arr[iter_result] = R[iter_right];
                    ++iter_right;
                }

                ++iter_result;
            }

            while (iter_left < length_left) {
                arr[iter_result] = L[iter_left];
                ++iter_left;
                ++iter_result;
            }

            while (iter_right < length_right) {
                arr[iter_result] = R[iter_right];
                ++iter_right;
                ++iter_result;
            }
        }

        template<class T, class Comparator>
        void _MergeSort(std::vector<T>& arr, size_t begin, size_t end)
        {
            if(begin < end){
                size_t middle = (begin + end) >> 1;
                _MergeSort<T, Comparator>(arr, begin, middle);
                _MergeSort<T, Comparator>(arr, middle + 1, end);
                _Merge<T, Comparator>(arr, begin, middle, end);
            }
        }

        /**
            HeapSort O(n*log(n))
            https://www.programiz.com/dsa/heap-sort

            Heap Sort Complexity
                Heap Sort has O(nlog n) time complexities for all the cases ( best case, average case, and worst case).

                Let us understand the reason why. The height of a complete binary tree containing n elements is log n

                As we have seen earlier, to fully heapify an element whose subtrees are already max-heaps,
                we need to keep comparing the element with its left and right children and pushing it downwards until it reaches a point
                where both its children are smaller than it.

                In the worst case scenario, we will need to move an element from the root to the leaf node making a multiple of log(n) comparisons and swaps.

                During the build_max_heap stage, we do that for n/2 elements so the worst case complexity of the build_heap step is n/2*log n ~ nlog n.

                During the sorting step, we exchange the root element with the last element and heapify the root element.
                For each element, this again takes log n worst time because we might have to bring the element all the way from the root to the leaf.
                Since we repeat this n times, the heap_sort step is also nlog n.

                Also since the build_max_heap and heap_sort steps are executed one after another,
                the algorithmic complexity is not multiplied and it remains in the order of nlog n.

                Also it performs sorting in O(1) space complexity. Compared with Quick Sort,
                it has a better worst case ( O(nlog n) ). Quick Sort has complexity O(n^2) for worst case. But in other cases,
                Quick Sort is fast. Introsort is an alternative to heapsort that combines quicksort and heapsort to retain advantages of both:
                worst case speed of heapsort and average speed of quicksort.

            Heap Sort Applications
                Systems concerned with security and embedded systems such as Linux Kernel use Heap Sort because of the O(n log n) 
                upper bound on Heapsort's running time and constant O(1) upper bound on its auxiliary storage.

                Although Heap Sort has O(n log n) time complexity even for the worst case, it doesn't have more applications 
                ( compared to other sorting algorithms like Quick Sort, Merge Sort ). However, its underlying data structure, heap, 
                can be efficiently used if we want to extract the smallest (or largest) from
                the list of items without the overhead of keeping the remaining items in the sorted order. For e.g Priority Queues.

        */

        template<class T, class Comparator>
        void _Heapify(std::vector<T>& arr, const size_t n, const size_t index)
        {
            Comparator cmp;
            if(index >= n) return;

            const int left = 2*index + 1;
            const int right = 2*index + 2;

            int largest = index;
            if(left < n && cmp(arr[left], arr[largest])){
                largest = left;
            }

            if(right < n && cmp(arr[right], arr[largest])){
                largest = right;
            }

            if(largest != index){
                std::swap(arr[largest], arr[index]);
                _Heapify<T, Comparator>(arr, n, largest);
            }
        }

        

        template<class T, class Comparator = DefaultComparator<T>>
        void Heap(std::vector<T>& arr)
        {
            for (int i = arr.size() / 2 - 1; i >= 0; --i)
            {
                _Heapify<T, Comparator>(arr, arr.size(), i);
            }

            //Heap sort
            for (int i = arr.size() - 1; i >= 0; --i)
            {
                std::swap(arr[0], arr[i]);
                _Heapify<T, Comparator>(arr, i, 0);
            }
        }

        /**
            HeapSort O(n*log(n))
            https://www.programiz.com/dsa/quick-sort

            Quicksort Complexity
            Time Complexities

            Worst Case Complexity [Big-O]: O(n^2)
                It occurs when the pivot element picked is either the greatest or the smallest element.
                This condition leads to the case in which the pivot element lies in an extreme end of the sorted array. 
                One sub-array is always empty and another sub-array contains n - 1 elements. Thus, quicksort is called only on this sub-array.
                However, the quick sort algorithm has better performance for scattered pivots.
            Best Case Complexity [Big-omega]: O(n*log n)
                It occurs when the pivot element is always the middle element or near to the middle element.
            Average Case Complexity [Big-theta]: O(n*log n)
                It occurs when the above conditions do not occur.

            Space Complexity
                The space complexity for quicksort is O(log n).


            Quicksort is implemented when
                the programming language is good for recursion.
                time complexity matters.
                space complexity matters.

        */

        template<class T, class Comparator>
        int _Partition(std::vector<T>& arr, const int begin, const int end)
        {
            // int pivot = arr[end];
            int i = (begin - 1);

            // Put the elements smaller than pivot on the left 
            // and greater than pivot on the right of pivot
            for (int j = begin; j < end; j++) {
                if (arr[j] <= arr[end]/*pivot*/) {
                    i++;
                    std::swap(arr[i], arr[j]);
                }
            }

            std::swap(arr[i + 1], arr[end]);
            return (i + 1);
        }

        template<class T, class Comparator = DefaultComparator<T>>
        void _Quick(std::vector<T>& data, const int begin, const int end)
        {
            if(end > begin){
                int pivot = _Partition<T, Comparator>(data, begin, end);
                _Quick<T, Comparator>(data, begin, pivot - 1);
                _Quick<T, Comparator>(data, pivot + 1, end);
            }
        }

        template<class T, class Comparator = DefaultComparator<T>>
        void Quick(std::vector<T>& data)
        {
            _Quick(data, 0, data.size() - 1);
        }

    };
} // namespace algo


#endif
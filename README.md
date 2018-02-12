# includes_unordered
Check if one unordered range includes all elements of another unordered range


## Overview
C++ standard library `<algorithm>` provides function: [`std::includes`](http://en.cppreference.com/w/cpp/algorithm/includes). It checks if every element from one sorted range is found within the other sorted range. However unsorted ranges are not supported.

Often is is desired to **check if every element from one unsorted range is found within the other unsorted range**. Function **`includes_unsorted`** serves this purpose.

## includes_unsorted
#### 1:
```c++
template <typename InputIt1, typename InputIt2>
bool includes_unordered(
    InputIt1 first1,
    InputIt1 last1,
    InputIt2 first2,
    InputIt2 last2);
``` 

#### 2:
```c++
template <typename InputIt1, typename InputIt2, typename Equivalence>
bool includes_unordered(
    InputIt1 first1,
    InputIt1 last1,
    InputIt2 first2,
    InputIt2 last2,
    Equivalence equiv)
``` 
Returns true if every element from the unsorted range `[first2, last2)` is found within the unsorted range `[first1, last1)`. Also returns true if `[first2, last2)` is empty.

2) accepts custom equivalence function object

### Parameters
 |  Parameters | Description |
 | ------------- | ------------- |
 |**`first1`**, **`last1`** | the range of elements to examine |
 |**`first2`**, **`last2`** | the range of elements to search for |
 |**`equiv`** | equivalence function object: returns **`true`** if the first argument is equal to the second |
 
### Type requirements and preconditions
- `InputIt1`, `InputIt2` must meet the requirements of [InputIterator](http://en.cppreference.com/w/cpp/concept/InputIterator).
- (1) Types in ranges should be [EqualityComparable](http://en.cppreference.com/w/cpp/concept/EqualityComparable)

### Return value

**`true`** if every element from `[first2, last2)` is a member of `[first1, last1)`. 

### Complexity

At most (N<sub>1</sub>! - (N<sub>1</sub> - N<sub>2</sub>)!) comparisons, where N<sub>1</sub> = `std::distance(first1, last1)` and N<sub>2</sub> = `std::distance(first2, last2)`. 

### Exceptions

If the algorithm fails to allocate memory, `std::bad_alloc` is thrown. 

### Implementation

```c++
template <typename InputIt1, typename InputIt2>
bool includes_unordered(
    InputIt1 first1,
    InputIt1 last1,
    InputIt2 first2,
    InputIt2 last2)
{
    for(; first2 != last2; ++first2)
    {
        InputIt1 it1;
        for(it1 = first1; it1 != last1; ++it1)
        {
            if(*first2 == *it1)
                break;
        }
        if(it1 == last1)
            return false;
    }
    return true;
}
```
```c++
template <typename InputIt1, typename InputIt2, typename Equivalence>
bool includes_unordered(
    InputIt1 first1,
    InputIt1 last1,
    InputIt2 first2,
    InputIt2 last2,
    Equivalence equiv)
{
    for(; first2 != last2; ++first2)
    {
        InputIt1 it1;
        for(it1 = first1; it1 != last1; ++it1)
        {
            if(equiv(*first2, *it1))
                break;
        }
        if(it1 == last1)
            return false;
    }
    return true;
}
```

### Example
```c++
#include "includes_unordered.hpp"

#include <iostream>
#include <unordered_set>

int main()
{
    std::unordered_set<int> set = {{0, 1, 2, 3, 4, 5}};
    std::unordered_set<int> subset{{2, 2, 4}};
    const bool is_set_incude_subset =
        includes_unordered(set.begin(), set.end(), subset.begin(), subset.end());
    const bool is_subset_incude_set =
        includes_unordered(subset.begin(), subset.end(), set.begin(), set.end());
    std::cout << is_set_incude_subset << " " << is_subset_incude_set;
}
```
Output:
```
1 0
```

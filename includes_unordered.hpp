#ifndef INCLUDES_UNORDERED_HPP
#define INCLUDES_UNORDERED_HPP

#include <iterator>

/*!
 * Returns true if every element from the unsorted range [first2, last2)
 * is found within the unsorted range [first1, last1).
 * Also returns true if [first2, last2) is empty.
 */
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

/*!
 * Returns true if every element from the unsorted range [first2, last2)
 * is found within the unsorted range [first1, last1).
 * Also returns true if [first2, last2) is empty.
 */
template <class InputIt1, typename InputIt2, typename Equivalence>
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

#endif // INCLUDES_UNORDERED_HPP

#ifndef MINIATURE_STL_ALGO_H
#define MINIATURE_STL_ALGO_H

// 这个头文件包含了 mystl 的一系列算法

#include <cstddef>
#include <ctime>

#include "algobase.h"
#include "../01_allocators/memory.h"
#include "../03_algorithms/functional.h"
#include "../03_algorithms/heap_algo.h"

namespace mystl
{

/*****************************************************************************************/
// all_of
// 检查[first, last)内是否全部元素都满足一元操作 unary_pred 为 true 的情况，满足则返回 true
/*****************************************************************************************/
template <typename InputIter, typename UnaryPredicate>
bool all_of(InputIter first, InputIter last, UnaryPredicate pred)
{
    while (first != last)
    {
        if (!pred(*first))
        {
            return false;
        }
        ++first;
    }
    return true;
}

/*****************************************************************************************/
// any_of
// 检查[first, last)内是否存在某个元素满足一元操作 unary_pred 为 true 的情况，满足则返回 true
/*****************************************************************************************/
template <typename InputIter, typename UnaryPredicate>
bool any_of(InputIter first, InputIter last, UnaryPredicate pred)
{
    while (first != last)
    {
        if (pred(*first))
        {
            return true;
        }
        ++first;
    }
    return false;
}

/*****************************************************************************************/
// none_of
// 检查[first, last)内是否全部元素都不满足一元操作 unary_pred 为 true 的情况，满足则返回 true
/*****************************************************************************************/
template <typename InputIter, typename UnaryPredicate>
bool none_of(InputIter first, InputIter last, UnaryPredicate pred)
{
    while (first != last)
    {
        if (pred(*first))
        {
            return false;
        }
        ++first;
    }
    return true;
}

/*****************************************************************************************/
// count
// 对[first, last)区间内的元素与给定值进行比较，缺省使用 operator==，返回元素相等的个数
/*****************************************************************************************/
template <typename InputIter, typename Type>
typename mystl::iterator_traits<InputIter>::difference_type count(InputIter first, InputIter last, const Type & value)
{
    typename mystl::iterator_traits<InputIter>::difference_type n = 0;
    for (; first != last; ++first)
    {
        if (*first == value)
        {
            ++n;
        }
    }
    return n;
}

/*****************************************************************************************/
// count_if
// 对[first, last)区间内的每个元素都进行一元 pred 操作，返回结果为 true 的个数
/*****************************************************************************************/
template <typename InputIter, typename UnaryPredicate>
typename mystl::iterator_traits<InputIter>::difference_type count_if(InputIter first, InputIter last, UnaryPredicate pred)
{
    typename mystl::iterator_traits<InputIter>::difference_type n = 0;
    for (; first != last; ++first)
    {
        if (pred(*first))
        {
            ++n;
        }
    }
    return n;
}

/*****************************************************************************************/
// find
// 在[first, last)区间内找到等于 value 的元素，返回指向该元素的迭代器
/*****************************************************************************************/
template <typename InputIter, typename Type>
InputIter find(InputIter first, InputIter last, const Type & value)
{
    for (; first != last; ++first)
    {
        if (*first == value)
        {
            break;
        }
    }
    return first;
}

/*****************************************************************************************/
// find_if
// 在[first, last)区间内找到第一个令一元操作 unary_pred 为 true 的元素并返回指向该元素的迭代器
/*****************************************************************************************/
template <typename InputIter, typename UnaryPredicate>
InputIter find_if(InputIter first, InputIter last, UnaryPredicate pred)
{
    while (first != last && !pred(*first))
    {
        ++first;
    }
    return first;
}

/*****************************************************************************************/
// find_if_not
// 在[first, last)区间内找到第一个令一元操作 unary_pred 为 false 的元素并返回指向该元素的迭代器
/*****************************************************************************************/
template <typename InputIter, typename UnaryPredicate>
InputIter find_if_not(InputIter first, InputIter last, UnaryPredicate pred)
{
    while (first != last && pred(*first))
    {
        ++first;
    }
    return first;
}

/*****************************************************************************************/
// search
// 在[first1, last1)中查找[first2, last2)的首次出现点
/*****************************************************************************************/
template <typename ForwardIter1, typename ForwardIter2>
ForwardIter2 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2)
{
    auto d1 = mystl::distance(first1, last1);
    auto d2 = mystl::distance(first2, last2);
    if (d1 < d2)
    {
        return last1;
    }
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2)
    {
        if (*current1 == *current2)
        {
            ++current1;
            ++current2;
        }
        else 
        {
            if (d1 == d2)
            {
                return last1;
            }
            else 
            {
                current1 = ++first;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
}

template <typename ForwardIter1, typename ForwardIter2, typename BinaryPredicate>
ForwardIter2 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, BinaryPredicate pred)
{
    auto d1 = mystl::distance(first1, last1);
    auto d2 = mystl::distance(first2, last2);
    if (d1 < d2)
    {
        return last1;
    }
    auto current1 = first1;
    auto current2 = first2;
    while (current2 != last2)
    {
        if (pred(*current1, *current2))
        {
            ++current1;
            ++current2;
        }
        else 
        {
            if (d1 == d2)
            {
                return last1;
            }
            else 
            {
                current1 = ++first;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
}

/*****************************************************************************************/
// search_n
// 在[first, last)中查找连续 n 个 value 所形成的子序列，返回一个迭代器指向该子序列的起始处
/*****************************************************************************************/
template <typename ForwardIter, typename Diff, typename Type>
ForwardIter search_n(ForwardIter first, ForwardIter last, Diff count, const Type & value)
{
    if (n <= 0)
    {
        return first;
    }
    else 
    {
        first = mystl::find(first, last, value);
        while (first != last)
        {
            auto m = n - 1;
            auto i = first;
            ++i;
            while (i != last && m != 0 && *i == value)
            {
                ++i;
                --m;
            }
            if (m == 0)
            {
                return first;
            }
            else 
            {
                first = mystl::find(i, last, value);
            }
        }
        return last;
    }
}

template <typename ForwardIter, typename Diff, typename Type, typename BinartPredicate>
ForwardIter search_n(ForwardIter first, ForwardIter last, Diff count, const Type & value, BinartPredicate pred)
{
    if (n <= 0)
    {
        return first;
    }
    else
    {
        while (first != last)
        {
            if (comp(*first, value))
            {
                break;
            }
            ++first;
        }
        while (first != last)
        {
            auto m = n - 1;
            auto i = first;
            ++i;
            while (i != last && m != 0 && comp(*i, value))
            {
                ++i;
                --m;
            }
            if (m == 0)
            {
                return first;
            }
            else
            {
                while (i != last)
                {
                    if (comp(*i, value))
                    {
                        break;
                    }
                    ++i;
                }
                first = i;
            }
        }
        return last;
    }
}

}   // end namespace mystl

#endif  // end MINIATURE_STL_ALGO_H
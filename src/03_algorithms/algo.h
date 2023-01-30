#ifndef MINIATURE_STL_ALGO_H
#define MINIATURE_STL_ALGO_H

// 这个头文件包含了 mystl 的一系列算法

#include <cstddef>
#include <cstdlib>
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
// search
// 在[first1, last1)中查找[first2, last2)的首次出现点
/*****************************************************************************************/
template <typename ForwardIter1, typename ForwardIter2>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2)
{
    ForwardIter1 current1;
    ForwardIter2 current2;

    while (first1 != last1)
    {
        if (*first1 == *first2)
        {
            current1 = first1;
            current2 = first2;

            while (current1 != last2)
            {
                if (*current1 != *current2) {
                    break;
                }
                ++current1;
                ++current2;
            }
            if (current1 == last2) {
                return first1;
            }
        }
        ++first1;
    }
    return first1;
}


template <typename ForwardIter1, typename ForwardIter2, typename BinaryPredicate>
ForwardIter1 search(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, BinaryPredicate pred)
{
    ForwardIter1 current1;
    ForwardIter2 current2;

    while (first1 != last1)
    {
        if (pred(*first1, *first2))
        {
            current1 = first1;
            current2 = first2;

            while (current1 != last2)
            {
                if (*current1 != *current2) {
                    break;
                }
                ++current1;
                ++current2;
            }
            if (current1 == last2) {
                return first1;
            }
        }
        ++first1;
    }
    return first1;   
}

/*****************************************************************************************/
// search_n
// 在[first1, last1)中查找连续 n 个 value 所形成的子序列,返回一个迭代器指向该子序列的起始处
/*****************************************************************************************/
template <typename ForwardIter, typename Diff, typename Type>
ForwardIter search_n(ForwardIter first, ForwardIter last, Diff count, const Type & value)
{
    ForwardIter current;
    Diff n;

    while (first != last)
    {
        if (*first == value) 
        {
            current = first;
            n = 0;
            while (n < count && *current == value)
            {
                ++current;
                ++n;
            }
            if (n == count)
            {
                return first;
            }
        }
        ++first;
    }
    return first;
}

template <typename ForwardIter, typename Diff, typename Type, typename BinaryPredicate>
ForwardIter search_n(ForwardIter first, ForwardIter last, Diff count, const Type & value, BinaryPredicate pred)
{
    ForwardIter current;
    Diff n;

    while (first != last)
    {
        if (pred(*first, value)) 
        {
            current = first;
            n = 0;
            while (n < count && *current == value)
            {
                ++current;
                ++n;
            }
            if (n == count)
            {
                return first;
            }
        }
        ++first;
    }
    return first;
}

/*****************************************************************************************/
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
// find_end
// 在[first1, last1)中查找[first2, last2) 最后一次出现的地方,若不存在返回 last1
/*****************************************************************************************/
// find_end 的 forward_iterator_tag 的版本
template <typename ForwardIter1, typename ForwardIter2>
ForwardIter1 find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, mystl::forward_iterator_tag, mystl::forward_iterator_tag)
{
    ForwardIter1 current1;
    ForwardIter2 current2;
    ForwardIter1 result = last1;

    while (first1 != last1)
    {
        if (*first1 == *first2)
        {
            current1 = first1;
            current2 = first2;

            while (*current1 == *current2 && current2 != last2)
            {
                ++current1;
                ++current2;
            }
            if (current2 == last2)
            {
                result = first1;
            }
        }
        ++first1;
    }
    return result;
}

// find_end 的 bidirectional_iterator_tag 的版本

template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter1 find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1, BidirectionalIter2 first2, BidirectionalIter2 last2, mystl::bidirectional_iterator_tag, mystl::bidirectional_iterator_tag)
{
    BidirectionalIter1 current1;
    BidirectionalIter2 current2;

    while (last1 != first1)
    {
        if (*(last1 - 1) == *(last2 - 1))
        {
            current1 = last1;
            current2 = last2;

            while (*(current1 - 1) == *(current2 - 1) && current2 != first2)
            {
                --current1;
                --current2;
            }
            if (current2 == first2)
            {
                return current1;
            }
        }
        --last1;
    }
    return last1;
}

template <typename ForwardIter1, typename ForwardIter2>
ForwardIter1 find_end(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2)
{
    typedef typename mystl::iterator_traits<ForwardIter1>::iterator_category Category1;
    typedef typename mystl::iterator_traits<ForwardIter2>::iterator_category Category2;
    return find_end_dispatch(first1, last1, first2, last2, Category1(), Category2());
}

// 重载
template <typename ForwardIter1, typename ForwardIter2, typename BinaryPredicate>
ForwardIter1 find_end_dispatch(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, BinaryPredicate pred, mystl::forward_iterator_tag, mystl::forward_iterator_tag)
{
    if (first2 == last2)
    {
        return last1;
    }
    ForwardIter1 result = last1;
    while (true)
    {
        auto new_result = mystl::search(first1, last1, first2, last2, pred);
        if (new_result == last1)
        {
            return result;
        }
        else  
        {
            result = new_result;
            first1 = new_result;
            ++first1;
        }
    }
}

template <typename BidirectionalIter1, typename BidirectionalIter2, typename BinaryPredicate>
BidirectionalIter1 find_end_dispatch(BidirectionalIter1 first1, BidirectionalIter1 last1, BidirectionalIter2 first2, BidirectionalIter2 last2, BinaryPredicate pred, mystl::bidirectional_iterator_tag, mystl::bidirectional_iterator_tag)
{
    typedef reverse_iterator<BidirectionalIter1> reviter1;
    typedef reverse_iterator<BidirectionalIter2> reviter2;
    reviter1 rlast1(first1);
    reviter2 rlast2(first2);
    reviter1 rresult = mystl::search(reviter1(last1), rlast1, reviter2(last2), rlast2, pred);
    if (rresult == rlast1)
    {
        return last1;
    }
    else
    {
        auto result = rresult.base();
        mystl::advance(result, -mystl::distance(first2, last2));
        return result;
    }
}

template <typename ForwardIter1, typename ForwardIter2, typename BinaryPredicate>
ForwardIter1 find_end(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, BinaryPredicate pred)
{
    typedef typename iterator_traits<ForwardIter1>::iterator_category Category1;
    typedef typename iterator_traits<ForwardIter2>::iterator_category Category2;
    return mystl::find_end_dispatch(first1, last1, first2, last2, pred, Category1(), Category2());
}

/*****************************************************************************************/
// find_first_of
// 在[first1, last1)中查找[first2, last2) 中的某些元素,返回指向第一次出现的元素的迭代器
/*****************************************************************************************/
template <typename ForwardIter1, typename ForwardIter2>
ForwardIter1 find_first_of(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2)
{
    while (first1 != last1)
    {
        if (mystl::find(first2, last2, *first1) != last2)
        {
            return first1;
        }
        ++first1;
    }
    return last1;
}

template <typename ForwardIter1, typename ForwardIter2, typename BinaryPredicate>
ForwardIter1 find_first_of(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, BinaryPredicate pred)
{
    ForwardIter2 current2;
    while (first1 != last1)
    {
        current2 = first2;
        while (current2 != last2)
        {
            if (pred(*first1, *current2))
            {
                return first1;
            }
            ++current2;
        }
        ++first1;
    }
    return last1;
}

/*****************************************************************************************/
// adjacent_find
// 找出第一对匹配的相邻元素，缺省使用 operator== 比较，若找到返回一个迭代器，指向这对元素的第一个元素
/*****************************************************************************************/
template <typename ForwardIter>
ForwardIter adjacent_find(ForwardIter first, ForwardIter last)
{
    ForwardIter next = first;
    if (first == last || ++next == last)
    {
        return last;
    }

    while (next != last)
    {
        if (*first == *next)
        {
            return first;
        }
        ++first;
        ++next;
    }
    return last;
}

template <typename ForwardIter, typename BinaryPredicate>
ForwardIter adjacent_find(ForwardIter first, ForwardIter last, BinaryPredicate pred)
{
    ForwardIter next = first;
    if (first == last || ++next == last)
    {
        return last;
    }

    while (next != last)
    {
        if (pred(*first, *next))
        {
            return first;
        }
        ++first;
        ++next;
    }
    return last;
}

/*****************************************************************************************/
// for_each
// 使用一个汉书对象 f 对 [first, last) 区间内每个元素执行一个 operator() 操作，但不能改变元素的内容
// f() 可以返回一个值，但该值会被忽略
/*****************************************************************************************/
template <typename InputIter, typename Function>
Function for_each(InputIter first, InputIter last, Function func)
{
    while (first != last)
    {
        *first = func(*first);
        ++first;
    }
    return func;
}

/*****************************************************************************************/
// lower_bound
// 在[first, last) 已排序中查找第一个不小于 value 的元素，并返回他的迭代器，若没有则返回 last
/*****************************************************************************************/
// lower_bound 的 forward_iterator_tag 版本
template <typename ForwardIter, typename Type>
ForwardIter lower_bound_dispatch(ForwardIter first, ForwardIter last, const Type & value, mystl::forward_iterator_tag)
{
    auto len = mystl::distance(first, last);
    auto half = len;
    ForwardIter middle;

    while (len > 0)
    {
        half = len >> 1;            // half = len / 2
        middle = first;
        mystl::advance(middle, half);
        if (*middle < value)
        {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else 
        {
            len = half;
        }
    }
    return first;
}

// lower_bound 的 random_access_iterator_tag 版本
template <typename RandomIter, typename Type>
RandomIter lower_bound_dispatch(RandomIter first, RandomIter last, const Type & value, mystl::random_access_iterator_tag)
{
    auto len = last - first;
    auto half = len;
    RandomIter middle;

    while (len > 0)
    {
        half = len >> 1;
        middle = first + half;
        if (*middle < value)
        {
            first = middle + 1;
            len = len - half - 1;
        }
        else 
        {
            len = half;
        }
    }
    return first;
}

template <typename ForwardIter, typename Type>
ForwardIter lower_bound(ForwardIter first, ForwardIter last, const Type & value)
{
    return lower_bound_dispatch(first, last, value, mystl::iterator_category(first));
}

// 重载
// lower_bound 的forward_iterator_tag 版本
template <typename ForwardIter, typename Type, typename BinaryPredicate>
ForwardIter lower_bound_dispatch(ForwardIter first, ForwardIter last, const Type & value, BinaryPredicate pred, mystl::forward_iterator_tag)
{
    typedef typename mystl::iterator_traits<ForwardIter>::difference_type diff_type;
    
    diff_type len = mystl::distance(first, last);
    diff_type half = len;
    ForwardIter middle;

    while (len > 0)
    {
        half = len >> 1;
        mystl::advance(middle, half);
        
        if (!prd(*middle, value))
        {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else 
        {
            len = half;
        }
    }
    return first;
    
}
// lower_bound 的 random_access_iterator_tag 版本
template <typename RandomIter, typename Type, typename BinaryPredicate>
RandomIter lower_bound_dispatch(RandomIter first, RandomIter last, const Type & value, BinaryPredicate pred, mystl::random_access_iterator_tag)
{
    typedef typename mystl::iterator_traits<RandomIter>::difference_type diff_type;
    
    diff_type len = last - first;
    diff_type half = len;
    RandomIter middle;

    while (len > 0)
    {
        half = len >> 1;
        middle = first + len;
        
        if (!pred(*middle, value))
        {
            first = middle + 1;
            len = len - half - 1;
        }
        else 
        {
            len = half;
        }
    } return first;
}

template <typename ForwardIter, typename Type, typename BinaryPredicate>
ForwardIter lower_bound(ForwardIter first, ForwardIter last, const Type & value)
{
    return lower_bound_dispatch(first, last, value, mystl::iterator_category(first));
}

/*****************************************************************************************/
// upper_bound
// 在[first, last) 已排序中查找第一个大于 value 的元素，并返回他的迭代器，若没有则返回 last
/*****************************************************************************************/
// upper_bound 的 forward_iterator_tag 版本
template <typename ForwardIter, typename Type>
ForwardIter upper_bound_dispatch(ForwardIter first, ForwardIter last, const Type & value, mystl::forward_iterator_tag)
{
    typedef typename mystl::iterator_traits<ForwardIter>::difference_type diff_type;

    diff_type len = mystl::distance(first, last);
    diff_type half = len;
    ForwardIter middle;

    while (len > 0)
    {
        half = len >> 1;
        middle = first;
        mystl::advance(middle, half);

        if (*middle <= value)
        {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else 
        {
            len = half;
        }
    }
    return first;
}
// upper_bound 的 random_access_iterator_tag 版本
template <typename RandomIter, typename Type>
RandomIter upper_bound_dispatch(RandomIter first, RandomIter last, const Type & value, mystl::random_access_iterator_tag)
{
    typedef typename mystl::iterator_traits<RandomIter>::difference_type diff_type;

    diff_type len = last - first;
    diff_type half = len;
    RandomIter middle;

    while (len > 0)
    {
        half = len >> 1;
        middle = first + half;
        
        if (*middle <= value)
        {
            first = middle + 1;
            len = len - half - 1;
        }
        else 
        {
            len = half;
        }
    }
    return first;
}
template <typename ForwardIter, typename Type>
ForwardIter upper_bound(ForwardIter first, ForwardIter last, const Type & value)
{
    return upper_bound_dispatch(first, last, value, mystl::iterator_category(first));
}

// 重载
// upper_bound 的 forward_iterator_tag 版本
template <typename ForwardIter, typename Type, typename BinaryPredicate>
ForwardIter upper_bound_dispatch(ForwardIter first, ForwardIter last, const Type & value, BinaryPredicate pred, mystl::forward_iterator_tag)
{
    typedef typename mystl::iterator_traits<ForwardIter>::difference_type diff_type;

    diff_type len = mystl::distance(first, last);
    diff_type half = len;
    ForwardIter middle;

    while (len > 0)
    {
        half = len >> 1;
        middle = first;
        mystl::advance(middle, half);

        if (pred(*middle, value))
        {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else 
        {
            len = half;
        }
    }
    return first;
}

/// upper_bound 的 random_access_iterator_tag 版本
template <typename RandomIter, typename Type, typename BinaryPredicate>
RandomIter upper_bound_dispatch(RandomIter first, RandomIter last, const Type & value, BinaryPredicate pred, mystl::random_access_iterator_tag)
{
    typedef typename mystl::iterator_traits<RandomIter>::difference_type diff_type;

    diff_type len = last - first;
    diff_type half = len;
    RandomIter middle;

    while (len > 0)
    {
        half = len >> 1;
        middle = first + half;
        
        if (pred(*middle, value))
        {
            first = middle + 1;
            len = len - half - 1;
        }
        else 
        {
            len = half;
        }
    }
    return first;
}

template <typename ForwardIter, typename Type, typename BinaryPredicate>
ForwardIter upper_bound(ForwardIter first, ForwardIter last, const Type & value, BinaryPredicate pred)
{
    return upper_bound_dispatch(first, last, value, mystl::iterator_category(first));
}

/*****************************************************************************************/
// binary_search
// 二分查找，若在[first, last) 已排序内有等同于 value 的元素，返回 true，否则返回 false
/*****************************************************************************************/
template <typename ForwardIter, typename Type>
bool binary_search(ForwardIter first, ForwardIter last, const Type & value)
{
    ForwardIter iter = mystl::lower_bound(first, last, value);
    return iter != last && *iter == value;
}

template <typename ForwardIter, typename Type, typename BinaryPredicate>
bool binary_search(ForwardIter first, ForwardIter last, const Type & value, BinaryPredicate pred)
{
    ForwardIter iter = mystl::lower_bound(first, last, value);
    return iter != last && pred(*iter, value);
}

/*****************************************************************************************/
// equal_range
// 查找以排序 [first, last) 区间中与 value 相等的元素所形成的区间，返回一对迭代器指向区间首位
// 第一个迭代器指向第一个不小于 value 的元素，第二个迭代器指向第一个大于 value 的元素
/*****************************************************************************************/
// equal_range 的 forward_iterator_tag 版本
template <typename ForwardIter, typename Type>
mystl::pair<ForwardIter, ForwardIter> equal_range_dispatch(ForwardIter first, ForwardIter last, const Type & value, mystl::forward_iterator_tag)
{
    typedef typename mystl::iterator_traits<ForwardIter>::difference_type diff_type;

    diff_type len = mystl::distance(first, last);
    diff_type half = len;
    ForwardIter middle, left, right;

    while (len > 0)
    {
        half = len >> 1;
        middle = first;
        mystl::advance(middle, half);

        if (*middle < value)
        {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else if (*middle > value)
        {
            len = half;
        }
        else 
        {
            left = mystl::lower_bound(first, last, value);
            mystl::advance(first, len);
            right = mystl::upper_bound(++middle, first, value);
            return mystl::pair<ForwardIter, ForwardIter>(left, right);
        }
    }
    return mystl::pair<ForwardIter, ForwardIter>(last, last);
}
// equal_range 的 random_access_iterator_tag 版本
template <typename RandomIter, typename Type>
mystl::pair<RandomIter, RandomIter> equal_range_dispatch(RandomIter first, RandomIter last, const Type & value, mystl::random_access_iterator_tag)
{
    typedef typename iterator_traits<RandomIter>::difference_type diff_type;

    diff_type len = last - first;
    diff_type half = len;
    RandomIter middle;
    RandomIter left;
    RandomIter right;

    while (len > 0)
    {
        half = len >> 1;
        middle = first + half;

        if (*middle < value)
        {
            first = middle + 1;
            len = len - half - 1;
        }
        else if (*middle > value)
        {
            len = half;
        }
        else 
        {
            left = mystl::lower_bound(first, middle, value);
            right = mystl::upper_bound(++middle, first + len, value);
            return mystl::pair<RandomIter, RandomIter>(left, right);
        }
    }
    return mystl::pair<RandomIter, RandomIter>(last, last);
}

template <typename ForwardIter, typename Type>
mystl::pair<ForwardIter, ForwardIter> equal_range(ForwardIter first, ForwardIter last, const Type & value)
{
    return equal_range_dispatch(first, last, value, mystl::iterator_category(first));
}

// equal_range 的 forward_iterator_tag 版本
template <typename ForwardIter, typename Type, typename Compare>
mystl::pair<ForwardIter, ForwardIter> equal_range_dispatch(ForwardIter first, ForwardIter last, const Type & value, Compare pred, mystl::forward_iterator_tag)
{
    typedef typename mystl::iterator_traits<ForwardIter>::difference_type diff_type;

    diff_type len = mystl::distance(first, last);
    diff_type half = len;
    ForwardIter middle, left, right;

    while (len > 0)
    {
        half = len >> 1;
        middle = first;
        mystl::advance(middle, half);

        if (pred(*middle, value))
        {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else if (pred(value, *middle))
        {
            len = half;
        }
        else 
        {
            left = mystl::lower_bound(first, last, value);
            mystl::advance(first, len);
            right = mystl::upper_bound(++middle, first, value);
            return mystl::pair<ForwardIter, ForwardIter>(left, right);
        }
    }
    return mystl::pair<ForwardIter, ForwardIter>(last, last);
}
// equal_range 的 random_access_iterator_tag 版本
template <typename RandomIter, typename Type, typename Compare>
mystl::pair<RandomIter, RandomIter> equal_range_dispatch(RandomIter first, RandomIter last, const Type & value, Compare pred, mystl::random_access_iterator_tag)
{
    typedef typename iterator_traits<RandomIter>::difference_type diff_type;

    diff_type len = last - first;
    diff_type half = len;
    RandomIter middle;
    RandomIter left;
    RandomIter right;

    while (len > 0)
    {
        half = len >> 1;
        middle = first + half;

        if (pred(*middle, value))
        {
            first = middle + 1;
            len = len - half - 1;
        }
        else if (pred(value, *middle))
        {
            len = half;
        }
        else 
        {
            left = mystl::lower_bound(first, middle, value);
            right = mystl::upper_bound(++middle, first + len, value);
            return mystl::pair<RandomIter, RandomIter>(left, right);
        }
    }
    return mystl::pair<RandomIter, RandomIter>(last, last);
}
// 重载
template <typename ForwardIter, typename Type, typename Compare>
mystl::pair<ForwardIter, ForwardIter> equal_range(ForwardIter first, ForwardIter last, const Type & value, Compare pred)
{
    return equal_range_dispatch(first, last, value, pred, mystl::iterator_category(first));
}

/*****************************************************************************************/
// generate
// 将函数对象 gen 的运算结果对 [first, last) 的每个元素赋值
/*****************************************************************************************/
template <typename ForwardIter, typename Generator>
void generate(ForwardIter first, ForwardIter last, Generator gen)
{
    while (first != last)
    {
        *first = gen();
        ++first;
    }
}

/*****************************************************************************************/
// generate_n
// 用函数对象 gen 连续对 n 个元素赋值
/*****************************************************************************************/
template <typename OutputIter, typename Diff, typename Generator>
void generate_n(OutputIter first, Diff count, Generator gen)
{
    Diff n = 0;
    while (n < count)
    {
        *first = gen();
        n++;
    }
}

/*****************************************************************************************/
// includes
// 判断两个已排序序列，序列一 S1 是否包含序列 S2
/*****************************************************************************************/
template <typename InputIter1, typename InputIter2>
bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
{
    while (first1 != last1 && first2 != last2)
    {
        if (*first1 > *first2)
        {
            return false;
        }
        else if (*first1 < *first2)
        {
            ++first1;
        }
        else 
        {
            ++first1;
            ++first2;
        }
    }
    return first2 == last2;
}

template <typename InputIter1, typename InputIter2, typename Compare>
bool includes(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, Compare pred)
{
    while (first1 != last1 && first2 != last2)
    {
        if (pred(*first2, *first1))
        {
            return false;
        }
        else if (pred(*first1, *first2))
        {
            ++first1;
        }
        else 
        {
            ++first1;
            ++first2;
        }
    }
    return first2 == last2;
}

/*****************************************************************************************/
// is_heap
// 检查 [first, last) 内元素是否为一个堆，若是返回 true， 反之返回 false
/*****************************************************************************************/
template <typename RandomIter>
bool is_heap(RandomIter first, RandomIter last)
{
    typedef typename mystl::iterator_traits<RandomIter>::difference_type diff_type;

    diff_type len = mystl::distance(first, last);
    auto parent = 0;
    auto child = 1;

    while (child < len)
    {
        if (first[parent] < first[child])
        {
            return false;
        }
        if ((child & 1) == 0)
        {
            ++parent;
        }
    } 
    return true;
}

template <typename RandomIter, typename Compare>
bool is_heap(RandomIter first, RandomIter last, Compare pred)
{
    typedef typename mystl::iterator_traits<RandomIter>::difference_type diff_type;

    diff_type len = mystl::distance(first, last);
    auto parent = 0;
    auto child = 1;

    while (child < len)
    {
        if (first[parent] < first[last])
        {
            return false;
        }
        if ((child & 1) == 0)
        {
            ++parent;
        }
    }
    return true;
}

/*****************************************************************************************/
// is_sorted
// 检查 [first, last) 内的元素是否为升序，若是为 true， 反之为 false
/*****************************************************************************************/
template <typename ForwardIter>
bool is_sorted(ForwardIter first, ForwardIter last)
{
    if (first == last)
    {
        return true;
    }

    ForwardIter next = first;
    ++next;

    while (next != last)
    {
        if (*first > *next)
        {
            return false;
        }
        ++first;
        ++next;
    }
    return true;
}

template <typename ForwardIter, typename Compare>
bool is_sorted(ForwardIter first, ForwardIter last, Compare pred)
{
    if (first == last)
    {
        return true;
    }

    ForwardIter next = first;
    ++next;

    while (next != last)
    {
        if (!pred(*first, *next))
        {
            return false;
        }
        ++first;
        ++next;
    }
    return true;
}

/*****************************************************************************************/
// median
// 找出三个值的中间值
/*****************************************************************************************/
template <typename Type>
const Type & median(const Type & left, const Type & mid, const Type & right)
{
    if (left < mid)
    {
        if (mid < right)
        {
            return mid;
        }
        else if (left < right)
        {
            return right;
        }
        else 
        {
            return left;
        }
    }
    else if (left < right)
    {
        return left;
    }
    else if (mid < right)
    {
        return right;
    }
    else 
    {
        return mid;
    }
}

// 重载
template <typename Type, typename Compare>
const Type & median(const Type & left, const Type & mid, const Type & right, Compare pred)
{
    if (pred(left, mid))
    {
        if (pred(mid, right))
        {
            return mid;
        }
        else if (pred(left, right))
        {
            return right;
        }
        else 
        {
            return left;
        }
    }
    else if (pred(left, right))
    {
        return left;
    }
    else if (pred(mid, right))
    {
        return right;
    }
    else 
    {
        return mid;
    }
}

/*****************************************************************************************/
// max_element
// 返回一个迭代器，指向序列中最大的元素
/*****************************************************************************************/
template <typename ForwardIter>
ForwardIter max_element(ForwardIter first, ForwardIter last)
{
    if (first == last)
    {
        return first;
    }

    auto result = first;
    while (++first != last)
    {
        if (*result < *first)
        {
            result = first;
        }
    }
    return result;
}

template <typename ForwardIter, typename Compare>
ForwardIter max_element(ForwardIter first, ForwardIter last, Compare pred)
{
    if (first == last)
    {
        return first;
    }

    auto result = first;
    while (++first != last)
    {
        if (pred(*result, *first))
        {
            result = first;
        }
    }
    return result;
}

/*****************************************************************************************/
// min_element
// 返回一个迭代器，指向序列中最小的元素
/*****************************************************************************************/
template <typename ForwardIter>
ForwardIter min_element(ForwardIter first, ForwardIter last)
{
    if (first == last)
    {
        return first;
    }
    auto result = first;
    while (++first != last)
    {
        if (*result > *first)
        {
            result = first;
        }
    }
    return result;
}

template <typename ForwardIter, typename Compare>
ForwardIter min_element(ForwardIter first, ForwardIter last, Compare pred)
{
    if (first == last)
    {
        return first;
    }
    auto result = first;
    while (++first != last)
    {
        if (pred(*result, *first))
        {
            result = first;
        }
    }
    return result;
}
/*****************************************************************************************/
// swap_ranges
// 将[first1, last1)从 first2 开始，交换相同个数元素
// 交换的区间长度必须相同，两个序列不能互相重叠，返回一个迭代器指向序列二最后一个被交换元素的下一位置
/*****************************************************************************************/
template <typename ForwardIter1, typename ForwardIter2>
ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
{
    auto temp = mystl::move(*first1);
    while (first1 != last1)
    {
        temp = mystl::move(*first1);
        *first1 = mystl::move(*first2);
        *first2 = mystl::move(temp);

        ++first1;
        ++first2;
    }
    return first2;
}

/*****************************************************************************************/
// transform
// 第一个版本以函数对象 unary_op 作用于[first, last)中的每个元素并将结果保存至 result 中
// 第二个版本以函数对象 binary_op 作用于两个序列[first1, last1)、[first2, last2)的相同位置
/*****************************************************************************************/
template <typename InputIter, typename OutputIter, typename UnaryFunction>
OutputIter transform(InputIter first, InputIter last, OutputIter result, UnaryFunction func)
{
    while (first != last)
    {
        *result = func(*first);
        ++first;
        ++result;
    }
    return result;
}

template <typename InputIter1, typename InputIter2, typename OutputIter, typename BinaryPredicate>
OutputIter transform(InputIter1 first1, InputIter1 last1, InputIter2 first2, OutputIter result, BinaryPredicate pred)
{
    while (first1 != last1)
    {
        *result = pred(*first1, first2);
        ++first1;
        ++first2;
        ++result;
    }
    return result;
}

/*****************************************************************************************/
// remove_copy
// 移除区间内与指定 value 相等的元素，并将结果复制到以 result 标示起始位置的容器上
/*****************************************************************************************/
template <typename InputIter, typename OutputIter, typename Type>
OutputIter remove_copy(InputIter first, InputIter last, OutputIter result, const Type & value)
{
    while (first != last)
    {
        if (value == *first)
        {
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
}

/*****************************************************************************************/
// remove
// 移除所有与指定 value 相等的元素
// 并不从容器中删除这些元素，所以 remove 和 remove_if 不适用于 array
/*****************************************************************************************/
template <typename ForwardIter, typename Type>
ForwardIter remove(ForwardIter first, ForwardIter last, const Type & value)
{
    first = mystl::find(first, last, value);
    auto next = first;
    return first == last ? first : mystl::remove_copy(++next, last, first, value);
}

/*****************************************************************************************/
// remove_copy_if
// 移除区间内所有令一元操作 unary_pred 为 true 的元素，并将结果复制到以 result 为起始位置的容器上
/*****************************************************************************************/
template <typename InputIter, typename OutputIter, typename UnaryPredicate>
OutputIter remove_copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate pred)
{
    while (first != last)
    {
        if (!pred(*first))
        {
            *result = *first;
            ++result;
        }
        ++first;
    }
    return result;
}

/*****************************************************************************************/
// remove_if
// 移除区间内所有令一元操作 unary_pred 为 true 的元素
/*****************************************************************************************/
template <typename ForwardIter, typename UnaryPredicate>
ForwardIter remove_if(ForwardIter first, ForwardIter last, UnaryPredicate pred)
{
    first = mystl::find_if(first, last, pred);
    auto next = first;
    first == last ? first : mystl::remove_copy_if(++next, last, first, pred);
}

/*****************************************************************************************/
// replace
// 将区间内所有的 old_value 都以 new_value 替代
/*****************************************************************************************/
template <typename ForwardIter, typename Type>

void replace(ForwardIter first, ForwardIter last, const Type & oldVal, const Type & newVal)
{
    while (first != last)
    {
        if (oldVal == *first)
        {
            *first = newVal;
        }
        ++first;
    }
}

/*****************************************************************************************/
// replace_copy
// 行为与 replace 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变
/*****************************************************************************************/
template <typename InputIter, typename OutputIter, typename Type>
OutputIter replace_copy(InputIter first, InputIter last, OutputIter result, const Type & oldVal, const Type & newVal)
{
    while (first != last)
    {
        *result = oldVal == *first ? newVal : *first;
        ++first;
        ++result;
    }
    return result;
}

/*****************************************************************************************/
// replace_copy_if
// 行为与 replace_if 类似，不同的是将结果复制到 result 所指的容器中，原序列没有改变
/*****************************************************************************************/
template <typename InputIter, typename OutputIter, typename UnaryPredicate, typename Type>
OutputIter replace_copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate pred, const Type & value)
{
    while (first != last)
    {
        if (pred(*first))
        {
            *first = value;
            *result = value;
        }
        else
        {
            *result = value;
        }
        ++first;
        ++result;
    }
    return result;
}

/*****************************************************************************************/
// replace_if
// 将区间内所有令一元操作 unary_pred 为 true 的元素都用 new_value 替代
/*****************************************************************************************/
template <typename ForwardIter, typename UnaryPredicate, typename Type>
void replace_if(ForwardIter first, ForwardIter last, UnaryPredicate pred, const Type & value)
{
    for (; first != last; ++first)
    {
        if (pred(*first))
        {
            *first = value;
        }
    }
}


/*****************************************************************************************/
// reverse
// 将[first, last)区间内的元素反转
/*****************************************************************************************/
// reverse_dispatch 的 bidirectional_iterator_tag 版本
template <typename BidirectioalIter>
void reverse_dispatch(BidirectioalIter first, BidirectioalIter last, mystl::bidirectional_iterator_tag)
{
    while (true)
    {
        if (first == last || first == --last)
        {
            return;
        }
        mystl::iter_swap(first, last);
    }
}
// reverse_dispatch 的 random_access_iterator_tag 版本
template <typename RandomIter>
void reverse_dispatch(RandomIter first, RandomIter last, mystl::random_access_iterator_tag)
{
    while (first < last)
    {
        mystl::iter_swap(first, last);
    }
}

template <typename BidirectioalIter>
void reverse(BidirectioalIter first, BidirectioalIter last)
{
    reverse_dispatch(first, last, mystl::iterator_category(first));
}

/*****************************************************************************************/
// reverse_copy
// 行为与 reverse 类似，不同的是将结果复制到 result 所指容器中
/*****************************************************************************************/
template <typename BidirectioalIter, typename OutputIter>
OutputIter reverse_copy(BidirectioalIter first, BidirectioalIter last, OutputIter result)
{
    while (first != last)
    {
        --last;
        *result = *last;
        ++result;
    }
    return result;
}

/*****************************************************************************************/
// random_shuffle
// 将[first, last)内的元素次序随机重排
// 重载版本使用一个产生随机数的函数对象 rand
/*****************************************************************************************/
template <typename RandomIter>
void random_shuffle(RandomIter first, RandomIter last)
{
    if (first == last)
    {
        return;
    }
    srand(time(NULL));
    for (auto iter = first + 1; iter != last; ++iter)
    {
        mystl::iter_swap(iter, first + (rand() % (iter - first + 1)));
    }
}
// 重载版本使用一个产生随机数的函数对象 rand
template <typename RandomIter, typename RandomNumberGenerator>
void random_shuffle(RandomIter first, RandomIter last, RandomNumberGenerator & rand)
{
    if (first == last)
    {
        return;
    }
    auto len = mystl::distance(first, last);
    for (auto iter = first + 1; iter != last; ++iter)
    {
        mystl::iter_swap(iter, first + (rand(iter - first + 1) % len));
    }
}

/*****************************************************************************************/
// rotate
// 将[first, middle)内的元素和 [middle, last)内的元素互换，可以交换两个长度不同的区间
// 返回交换后 middle 的位置
/*****************************************************************************************/
// rotate_dispatch 的 forward_iterator_tag 版本
template <typename ForwardIter>
void rotate_dispatch(ForwardIter first, ForwardIter middle, ForwardIter lastk, mystl::forward_iterator_tag)
{
    auto first2 = middle;
    do
    {
        mystl::swap(*first++, *first2++);
        if (first == middle)
        {
            middle = first2;
        }
    } while(first2 != last);
    
    auto result = first;
    first2 = middle;
    while (first2 != last)
    {
        mystl::swap(*first++, *first2++);
        if (first == middle)
        {
            middle = first2;
        }
        else if (first2 == last)
        {
            first2 = middle;
        }
    }
    return result;
}
// rotate_dispatch 的 bidirectional_iterator_tag 版本
template <typename BidirectionalIter>
void rotate_dispatch(BidirectionalIter first, BidirectionalIter middle, BidirectionalIter last, mystl::bidirectional_iterator_tag)
{
    mystl::reverse_dispatch(first, middle, mystl::bidirectional_iterator_tag());
    mystl::reverse_dispatch(middle, last, mystl::bidirectional_iterator_tag());
    while (first != middle && middle != last)
    {
        mystl::swap(*first++, *--last);
    }
    if (first == middle)
    {
        mystl::reverse_dispatch(middle, last, mystl::bidirectional_iterator_tag());
        return last;
    }
    else
    {
        mystl::reverse_dispatch(first, middle, mystl::bidirectional_iterator_tag());
        return first;
    }
}

// 求最大公因数
template <typename Type>
Type rgcd(Type m, Type n)
{
    while (n != 0)
    {
        auto t = m % n;
        m = n;
        n = t;
    }
    return m;
}


// rotate_dispatch 的 random_access_iterator_tag 版本
template <typename RandomIter>
RandomIter rotate_dispatch(RandomIter first, RandomIter middle, RandomIter last, mystl::random_access_iterator_tag)
{
    auto n = last - first;
    auto l = middle - first;
    auto r = n - l;
    auto result = first + (last - middle);
    if (l == r)
    {
        mystl::swap_range(first, middle, middle);
        return result;
    }
    auto cycle_time = rgcd(n, l);
    for (auto i = 0; i < cycle_time; ++i)
    {
        auto temp = *first;
        auto p = first;
        if (l < r)
        {
            for (auto j = 0; j < r / cycle_time; ++j)
            {
                if (p > first + r)
                {
                    *p = *(p - r);
                    p -= r;
                }
                *p = *(p + l);
                    p += l;
            }
        }
        else 
        {
            for (auto j = 0; j < l / cycle_time - 1; ++j)
            {
                if (p < last - l)
                {
                    *p = *(p + l);
                    p += l;
                }
                *p = *(p - r);
                p -= r;
            }
        }
        *p = temp;
        ++first;
    }
    return result;
}

template <typename ForwardIter>
ForwardIter retate(ForwardIter first, ForwardIter middle, ForwardIter last)
{
    if (first == middle) 
    {
        return last;
    } 
    if (middle == last)
    {
        return first;
    }
    return mystl::rotate_dispatch(first, middle, last, mystl::iterator_category(first));
}

/*****************************************************************************************/
// rotate_copy
// 行为与 rotate 类似，不同的是将结果复制到 result 所指的容器中
/*****************************************************************************************/
template <typename ForwardIter, typename OutputIter>
ForwardIter rotate_copy(ForwardIter first, ForwardIter middle, ForwardIter last, OutputIter result)
{
    return mystl::copy(first, middle, mystl::copy(middle, last, result));
}

/*****************************************************************************************/
// is_permutation  !!!!
// 判断[first1,last1)是否为[first2, last2)的排列组合
/*****************************************************************************************/
template <class ForwardIter1, class ForwardIter2, class BinaryPred>
bool is_permutation_aux(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, BinaryPred pred)
{
    constexpr bool is_ra_it = mystl::is_random_access_iterator<ForwardIter1>::value && mystl::is_random_access_iterator<ForwardIter2>::value;
    if (is_ra_it)
    {
        auto len1 = last1 - first1;
        auto len2 = last2 - first2;
        if (len1 != len2)
            return false;
    }

  // 先找出相同的前缀段
    for (; first1 != last1 && first2 != last2; ++first1, (void) ++first2)
    {
        if (!pred(*first1, *first2))
            break;
    }
    if (is_ra_it)
    {
        if (first1 == last1)
            return true;
    }
    else
    {
        auto len1 = mystl::distance(first1, last1);
        auto len2 = mystl::distance(first2, last2);
        if (len1 == 0 && len2 == 0)
            return true;
        if (len1 != len2)
            return false;
    }

    // 判断剩余部分
    for (auto i = first1; i != last1; ++i)
    {
        bool is_repeated = false;
        for (auto j = first1; j != i; ++j)
        {
            if (pred(*j, *i))
            {
                is_repeated = true;
                break;
            }
        }

        if (!is_repeated)
        {
            // 计算 *i 在 [first2, last2) 的数目
            auto c2 = 0;
            for (auto j = first2; j != last2; ++j)
            {
                if (pred(*i, *j))
                    ++c2;
            }
            if (c2 == 0)
                return false;

            // 计算 *i 在 [first1, last1) 的数目
            auto c1 = 1;
            auto j = i;
            for (++j; j != last1; ++j)
            {
                if (pred(*i, *j))
                    ++c1;
            }
            if (c1 != c2)
                return false;
        }
    }
    return true;
}

template <class ForwardIter1, class ForwardIter2, class BinaryPred>
bool is_permutation(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2, BinaryPred pred)
{
    return is_permutation_aux(first1, last1, first2, last2, pred);
}

template <class ForwardIter1, class ForwardIter2>
bool is_permutation(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2, ForwardIter2 last2)
{
    typedef typename iterator_traits<ForwardIter1>::value_type v1;
    typedef typename iterator_traits<ForwardIter2>::value_type v2;
    static_assert(std::is_same<v1, v2>::value, "the type should be same in mystl::is_permutation");
    return is_permutation_aux(first1, last1, first2, last2, mystl::equal_to<v1>());
}

/*****************************************************************************************/
// next_permutation  
// 取得[first, last)所标示序列的下一个排列组合，如果没有下一个排序组合，返回 false，否则返回 true
/*****************************************************************************************/
template <typename BidirectionalIter>
bool next_permutation(BidirectionalIter first, BidirectionalIter last)
{
    auto i = last;
    if (first == last || first == --i)
    {
        return false;
    }
    while (true)
    {
        auto ii = i;
        if (*--i < *ii)
        {
            auto j = last;
            while (!(*i < *--j)) {}
            mystl::iter_swap(i, j);
            mystl::reverse(ii, last);
            return true;
        }
        if (i == first)
        {
            mystl::reverse(first, last);
            return false;
        }
    }
}
// 重载版本使用函数对象 comp 代替比较操作
template <typename BidirectionalIter, typename Compare>
bool next_permutation(BidirectionalIter first, BidirectionalIter last, Compare pred)
{
    auto i = last;
    if (first == last || first == --i)
    {
        return false;
    }
    while (true)
    {
        auto ii = i;
        if (*--i < *ii)
        {
            auto j = last;
            while (!pred(*i < *--j)) {}
            mystl::iter_swap(i, j);
            mystl::reverse(ii, last);
            return true;
        }
        if (i == first)
        {
            mystl::reverse(first, last);
            return false;
        }
    }
}

/*****************************************************************************************/
// prev_permutation
// 取得[first, last)所标示序列的上一个排列组合，如果没有上一个排序组合，返回 false，否则返回 true
/*****************************************************************************************/
template <class BidirectionalIter>
bool prev_permutation(BidirectionalIter first, BidirectionalIter last)
{
    auto i = last;
    if (first == last || first == --i)
        return false;
    for (;;)
    {
        auto ii = i;
        if (*ii < *--i)
        {                 // 找到第一对大于关系的元素
            auto j = last;
            while (!(*--j < *i)) {}
            mystl::iter_swap(i, j);       // 交换i，j
            mystl::reverse(ii, last);     // 将 ii 之后的所有元素反转
            return true;
        }
        if (i == first)
        {
            mystl::reverse(first, last);
            return false;
        }
    }
}

// 重载版本使用函数对象 comp 代替比较操作
template <class BidirectionalIter, class Compared>
bool prev_permutation(BidirectionalIter first, BidirectionalIter last, Compared comp)
{
    auto i = last;
    if (first == last || first == --i)
        return false;
    for (;;)
    {
        auto ii = i;
        if (comp(*ii, *--i))
        {
            auto j = last;
            while (!comp(*--j, *i)) {}
            mystl::iter_swap(i, j);       // 交换i，j
            mystl::reverse(ii, last);     // 将 ii 之后的所有元素反转
            return true;
        }
        if (i == first)
        {
            mystl::reverse(first, last);
            return false;
        }
    }
}

/*****************************************************************************************/
// merge
// 将两个经过排序的集合 S1 和 S2 合并起来置于另一段空间，返回一个迭代器指向最后一个元素的下一位置
/*****************************************************************************************/














}   // end namespace mystl

#endif  // end MINIATURE_STL_ALGO_H

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




}   // end namespace mystl

#endif  // end MINIATURE_STL_ALGO_H

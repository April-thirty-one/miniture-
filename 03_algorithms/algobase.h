//
// Created by yapeng-cheng on 23-1-10.
//

#ifndef MINIATURE_STL_ALGOBASE_H
#define MINIATURE_STL_ALGOBASE_H

//// 这个头文件包含了 mystl 的基本算法

#include <cstring>

#include "../02_iterators/iterator.h"
#include "../01_allocators/util.h"

namespace mystl
{

/*****************************************************************************************/
// max
// 取二者中的较大值，语义相等时保证返回第一个参数
/*****************************************************************************************/
template <typename Type>
const Type & max(const Type & left, const Type & right)
{
    return left > right ? left : right;
}

// 重载版本使用函数对象 comp 代替比较操作
template <typename Type, typename BinaryPredicate>
const Type & max(const Type & left, const Type & right, BinaryPredicate pred)
{
    return pred(left, right) ? left : right;
}

// template <typename Type>
// const Type & max(initializer_list<Type> list) 
// {
        // ...
// }

// template <typename Type, typename BinaryPredicate>
// const Type & max(initializer_list<Type> list, BinaryPredicate pred) 
// {
        // ...
// }


/*****************************************************************************************/
// min
// 取二者中的较小值，语义相等时保证返回第一个参数
/*****************************************************************************************/
template <typename Type>
const Type & min(const Type & left, const Type & right)
{
    return left < right ? left : right;
}

// 重载版本使用函数对象 comp 代替比较操作
template <typename Type, typename BinaryPredicate>
const Type & min(const Type & left, const Type & right, BinaryPredicate pred)
{
    return pred(left, right) ? left : right;
}

// template<typename Type>
// Type min(initializer_list<Type> ilist)
// {
        // ...
// }

// template<typename Type, typename BinaryPredicate>
// Type min(initializer_list<Type> ilist,BinaryPredicate pred)
// {
        // ...
// }


/*****************************************************************************************/
// iter_swap
// 将两个迭代器所指对象对调
/*****************************************************************************************/
template <typename ForwardIterator1, typename ForwardIterator2>
void iter_swap(ForwardIterator1 left, ForwardIterator2 right)
{
    mystl::swap(*left, *right);
}




/*****************************************************************************************/
// copy
// 把 [first, last)区间内的元素拷贝到 [result, result + (last - first))内
// 
/*****************************************************************************************/
// 注意：和 MyTinySTL 中的 copy 发布不同
// input_iterator_tag 版本
template <typename InputIter, typename OutputIter>
OutputIter unchecked_copy_cat(InputIter first, InputIter last, OutputIter destBeg, mystl::input_iterator_tag)
{
    for(; first != last; ++first, ++destBeg)
    {
        *destBeg = *first;
    }
    return destBeg;
}

// random_access_iterator_tag 版本
template <typename InputIter, typename OutputIter>
OutputIter unchecked_copy_cat(InputIter first, InputIter last, OutputIter desBeg, mystl::random_access_iterator_tag)
{
    for (int i = last - first; i > 0; --i, ++first, ++desBeg)       // !! auto i = ...
    {
        *desBeg = *first;
    }
    return desBeg;
}

template <typename InputIter, typename OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter desBeg)
{
    unchecked_copy_cat(first, last, desBeg, mystl::iterator_category(first));
}


/*****************************************************************************************/
// copy_backward
// 将 [first, last)区间内的元素拷贝到 [destEnd - (last - first), destEnd)内
/*****************************************************************************************/
// 注意：和 MyTinySTL 中的 copy_backward 发布不同
// unchecked_copy_backward_cat 的 bidirectional_iterator_tag 版本
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2 unchecked_copy_backward_cat(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 destEnd, mystl::bidirectional_iterator_tag)
{
    while (first != last)
    {
        *--destEnd = *--last;
    }
    return destEnd;
}

// unchecked_copy_backward_cat 的 random_access_iterator_tag 版本
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
BidirectionalIterator2 unchecked_copy_backward_cat(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 destEnd, mystl::random_access_iterator_tag)
{
    for (int n = last - first; n > 0; --n)
    {
        *--destEnd = *--last;
    }
    return destEnd;
}

template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2 copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 desEnd)
{
    unchecked_copy_backward_cat(first, last, desEnd, mystl::iterator_category(first));
}

/*****************************************************************************************/
// copy_if
// 把[first, last)内满足一元操作 unary_pred 的元素拷贝到以 result 为起始的位置上
/*****************************************************************************************/
template <typename InputIter, typename OutputIter, typename UnaryPredicate>
OutputIter copy_if(InputIter first, InputIter last, OutputIter dest, UnaryPredicate pred)
{
    while (first != last)
    {
        if (pred(*first) == true)
        {
            *dest = *first;
            ++dest;
        }   
        ++first;
    }
    return dest;
}

/*****************************************************************************************/
// copy_n
// 复制指定数量的元素。
// 返回元素已被复制到的输出迭代器。 它与 dest 参数的返回值相等
/*****************************************************************************************/
// 注意：和 MyTinySTL 中的 copy_backward 发布不同
template <typename InputIter, typename OutputIter, typename Size>
OutputIter copy_n(InputIter first, OutputIter dest, Size count)
{
    while (count > 0)
    {
        *dest = *first;
        ++dest;
        ++first;
    }
    return dest;
}

/*****************************************************************************************/
// move
// 把 [first, last)区间内的元素移动到 [result, result + (last - first))内
/*****************************************************************************************/
// 注意：和 MyTinySTL 中的 move 设计不同
// input_iterator_tag 版本
template <typename InputIter, typename OutputIter>
OutputIter unchecked_move_cat(InputIter first, InputIter last, OutputIter dest, mystl::input_iterator_tag)
{
    while (first != last)
    {
        *dest = *first;         // MyTinySTL : *dest = mystl::move(*first)
        ++dest;
        ++first;
    }
    return dest;
}

// ramdom_access_iterator_tag 版本
template <typename RandomIter, typename OutputIter>
OutputIter unchecked_move_cat(RandomIter first, RandomIter last, OutputIter dest, mystl::random_access_iterator_tag)
{
    for (auto n = last - first; n > 0; --n, ++first, ++dest)
    {
        *dest = *first;         // MyTinySTL : *dest = mystl::move(*first)
    }
    return dest;
}

// 对外接口
template <typename InputIter, typename OutputIter>
OutputIter move(InputIter first, InputIter last, OutputIter dest)
{
    unchecked_move_cat(first, last, dest, mystl::iterator_category(first));
}

/*****************************************************************************************/
// move_backward
// 将 [first, last)区间内的元素移动到 [result - (last - first), result)内
/*****************************************************************************************/
// 有不同
// bidirectional_iterator_tag 版本
template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2 unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 destEnd, mystl::bidirectional_iterator_tag)
{
    while (first != last)
    {
        *--destEnd = mystl::move(*--last);
    }
    return destEnd;
}

// random_access_iterator_tag 版本
template <typename RandomIter1, typename RandomIter2>
RandomIter2 unchecked_move_backward_cat(RandomIter1 first, RandomIter1 last, RandomIter2 destEnd, mystl::random_access_iterator_tag)
{
    for (auto n = last - first; n > 0; --n)
    {
        *--destEnd = mystl::move(*--last);
    }
    return destEnd;
}

// move_backward 对外接口
template <typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2 move_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 destEnd)
{
    unchecked_move_backward_cat(first, last, destEnd, mystl::iterator_category(first));
}

/*****************************************************************************************/
// equal
// 比较第一序列在 [first, last)区间上的元素值是否和第二序列相等
// 比较不同容器类型（例如 vector 和 list）中的元素时、比较不同元素类型时，或是需要比较容器的子范围时，可使用 std::equal。
// 否则，在比较相同容器类型中具有相同类型的元素时，可使用为每个容器提供的非成员运算符 operator==。
/*****************************************************************************************/
template <typename InputIter1, typename InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (mystl::move(*first1) != *mystl::move(*first2))
        {
            return false;
        }
    }
    return true;
}

// 重载版本使用函数对象 comp 代替比较操作
template <typename InputIter1, typename InputIter2, typename BinaryPredicate>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, BinaryPredicate pred)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (pred(*first1, *first2) == false)
        {
            return false;
        }
    }
    return true;
}

/*****************************************************************************************/
// fill_n
// 从 first 位置开始填充 n 个值
/*****************************************************************************************/
template <typename OutputIter, typename Type, typename Size>
OutputIter unchecked_fill_n(OutputIter first, Size count, const Type & value)
{
    for (; n > 0; --n, ++first) 
    {
        *fisrt = value;
    }
    return first;
}

template <typename OutputIter, typename Size, typename Type>
OutputIter fill_n(OutputIter first, Size n, const Type & value)
{
    unchecked_fill_n(first, n, value);
}

/*****************************************************************************************/
// fill
// 为 [first, last)区间内的所有元素填充新值
/*****************************************************************************************/
// forward_iterator_tag 版本
template <typename ForwardIter, typename Type>
void unchicked_fill_cat(ForwardIter first, ForwardIter last, const Type & value, mystl::forward_iterator_tag)
{
    while (first != last)
    {
        *first = value;
        ++first;
    }
}

// random_access_iterator_tag 版本
template <typename RandomIter, typename Type>
void unchecked_fill_cat(RandomIter first, RandomIter last, const Type & value, mystl::random_access_iterator_tag)
{
    for (auto n = last - first; n > 0; --n, ++first)
    {
        *first = value;
    }
}

template <typename ForwardIter, typename Type>
void fill(ForwardIter first, ForwardIter last, const Type & value)
{
    unchecked_fill_cat(first, last, value, mystl::iterator_category(first));
}

/*****************************************************************************************/
// lexicographical_compare
// 以字典序排列对两个序列进行比较，当在某个位置发现第一组不相等元素时，有下列几种情况：
// (1)如果第一序列的元素较小，返回 falst ，否则返回 true
// (2)如果到达 last1 而尚未到达 last2 返回 falst
// (3)如果到达 last2 而尚未到达 last1 返回 true
// (4)如果同时到达 last1 和 last2 返回 false
/*****************************************************************************************/
template <typename InputIter1, typename InputIter2>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
{
    while (first1 != last1 && first2 != last2)
    {
        if (*first1 != *first2)
        {
            if (*first1 > *first2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        ++first1;
        ++first2;
    }
    if (first1 != last1 && first2 == last2)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// 重载版本使用函数对象 comp 代替比较操作
template<class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare pred )
{
    while (first1 != last1 && first2 != last2)
    {
        if (*first1 != *first2)
        {
            if (pred(*first1, *first2))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        ++first1;
        ++first2;
    }
    if (first1 != last1 && first2 == last2)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

/*****************************************************************************************/
// mismatch
// 平行比较两个序列，找到第一处失配的元素，返回一对迭代器，分别指向两个序列中失配的元素
/*****************************************************************************************/
template<class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    while (first1 != last1 && *first1 == *first2)
    {
        ++first1;
        ++first2;
    }
    return mystl::make_pair(first1, first2);    
    // return mystl::pair<InputIter1, InputIter2>(first1, first2)
}

// 重载版本使用函数对象 comp 代替比较操作
template<class InputIterator1, class InputIterator2, class BinaryPredicate> 
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred )
{
    while (first1 != last1 && pred(*first1, *first2))
    {
        ++first1;
        ++first2;
    }
    return mystl::make_pair(first1, first2);    
    // return mystl::pair<InputIter1, InputIter2>(first1, first2)
}


}  // end namespace mystl
#endif //MINIATURE_STL_ALGOBASE_H
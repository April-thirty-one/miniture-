#ifndef MINIATURE_STL_HEAP_ALGO_H
#define MINIATURE_STL_HEAP_ALGO_H

// 这个头文件包含 heap 的四个算法 : push_heap, pop_heap, sort_heap, make_heap

#include "../02_iterators/iterator.h"

namespace mystl
{

/*****************************************************************************************/
// push_heap
// 该函数接受两个迭代器，表示一个 heap 容器的首尾，并且新元素已经插入到底部容器的最尾端，调整 heap
//
// 元素必须先推送回现有堆的末尾，然后使用该算法将此元素添加到现有堆。
// 堆有两个属性：
//     第一个元素始终最大。
//     可以在对数时间内添加或删除元素。
// 堆是实现优先级队列的理想方式
/*****************************************************************************************/
template <typename RandomIter, typename Distance, typename Type>
void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, Type value)
{
    auto parent = (holeIndex - 1) / 2;                          // 得到父节点的 index
    while (holeIndex > topIndex && *(first + parent) < value)   
    {
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

// 若 size = 9, 则 1～8 是已经排序好的堆，最后一个元素是带插入的元素 
template <typename RandomIter, typename Distance>
void push_heap_d(RandomIter first, RandomIter last, Distance *)
{
    mystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1));
}

template <typename RandomIter>
void push_head(RandomIter first, RandomIter last)
{
    mystl::push_heap_d(first, last, distance_type(first));
}

// 重载 二元谓词 版本
template <typename RandomIter, typename Distance, typename Type, typename BinaryPredicate>
void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIdex, Type value, BinaryPredicate pred)
{
    auto parent = (holeIndex - 1) / 2;
    while (holeIndex > topIdex && pred(*(first + parent), value))
    {
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

template <typename RandomIter, typename Distance, typename Type, typename BinaryPredicate>
void push_heap_d(RandomIter first, RandomIter last, Distance *, BinaryPredicate pred)
{
    mystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1), pred);
}

template <typename RandomIter, typename BinaryPredicate>
void push_heap(RandomIter first, RandomIter last, BinaryPredicate pred)
{
    mystl::push_heap_d(first, last, distance_type(first), pred);
}

/*****************************************************************************************/
// pop_heap
// 该函数接受两个迭代器，表示 heap 容器的首尾，将 heap 的根节点取出放到容器尾部，调整 heap
// 
// 移除从堆顶到范围中倒数第二个位置之间的最大元素，然后将剩余元素形成新堆。
/*****************************************************************************************/
template <typename RandomIter, typename Type, typename Distance>
void adjust_heap(RandomIter first, Distance holeIndex, Distance len, Type value)
{
    // 先进行下溯(percolate down)过程
    auto topIndex = holeIndex;
    auto rchild = 2 * holeIndex + 2;
    while (rchild < len)
    {
        if (*(first + rchild) < *(first + rchild - 1))
        {
            --rchild;
        }
        *(first + holeIndex) = *(first + rchild);
        holeIndex = rchild;
        rchild = 2 * (rchild + 1);
    }
    if (rchild == len)
    {
        // 若没有右子结点
        *(first + holeIndex) = *(first + (rchild - 1));
        holeIndex = rchild - 1;
    }
    // 再执行一次上溯(percolate up)过程
    mystl::push_heap_aux(first, holeIndex, topIndex, value);
}

template <typename RandomIter, typename Type, typename Distance>
void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, Type value, Distance *)
{
    // 先将首值调至尾节点，然后调整[first, last - 1)使之重新成为一个 max-heap
    *result = *first;
    mystl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
}

template <typename RandomIter>
void pop_heap(RandomIter first, RandomIter last)
{
    mystl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first));
}

// 重载 二元谓词 版本
template <typename RandomIter, typename Type, typename Distance, typename BinaryPredicate>
void adjust_heap(RandomIter first, Distance holeIndex, Distance len, Type value, BinaryPredicate pred)
{
    // 先进行下溯(percolate down)过程
    auto topIndex = holeIndex;
    auto rchild = 2 * holeIndex + 2;
    while (rchild < len)
    {
        if (pred(*(first + rchild), *(first + rchild - 1)))
        {
            --rchild;
        }
        *(first + holeIndex) = *(first + rchild);
        holeIndex = rchild;
        rchild = 2 * (rchild + 1);
    }
    if (rchild == len)
    {
        // 若没有右子结点
        *(first + holeIndex) = *(first + (rchild - 1));
        holeIndex = rchild - 1;
    }
    // 再执行一次上溯(percolate up)过程
    mystl::push_heap_aux(first, holeIndex, topIndex, value, pred);
}

template <typename RandomIter, typename Type, typename Distance, typename BinaryPredicate>
void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, Type value, Distance *, BinaryPredicate pred)
{
    // 先将首值调至尾节点，然后调整[first, last - 1)使之重新成为一个 max-heap
    *result = *first;
    mystl::adjust_heap(first, static_cast<Distance>(0), last - first, value, pred);
}


template <typename RandomIter, typename BinaryPredicate>
void pop_heap(RandomIter first, RandomIter last, BinaryPredicate pred)
{
    mystl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), mystl::distance_type(first), pred);
}

/*****************************************************************************************/
// sort_heap
// 该函数接受两个迭代器，表示 heap 容器的首尾，不断执行 pop_heap 操作，直到首尾最多相差1
/*****************************************************************************************/
template <typename RandomIter>
void sort_heap(RandomIter first, RandomIter last)
{
    // 每执行一次 pop_heap，最大的元素都被放到尾部，直到容器最多只有一个元素，完成排序
    while (last - first > 1)
    {
        mystl::pop_heap_aux(first, last);
        --last;
    }
}

// 重载 二元谓词 版本
template <typename RandomIter, typename Compare>
void sort_heap(RandomIter first, RandomIter last, Compare pred)
{
    while (last - first > 1)
    {
        mystl::pop_heap(first, last, pred);
        --last;
    }
}

/*****************************************************************************************/
// make_heap
// 该函数接受两个迭代器，表示 heap 容器的首尾，把容器内的数据变为一个 heap
// 
// 将指定范围中的元素转换到第一个元素是最大元素的堆中，其中排序条件可通过二元谓词指定。
/*****************************************************************************************/
template <typename RandomIter, typename Distance>
void make_heap_aux(RandomIter first, RandomIter last, Distance *)
{
    if (last - first < 2)
    {
        return;
    }
    auto len = last - first;
    auto holeIdex = (len - 2) / 2;
    while (true)
    {
        // 重排以 holeIndex 为首的子树
        mystl::adjust_heap(first, holeIdex, len, *(first + holeIdex));
        if (holeIdex == 0)
        {
            return;
        }
        --holeIdex;
    }
}

template <typename RandomIter>
void make_heap(RandomIter first, RandomIter last)
{
    mystl::make_heap_aux(first, last, distance_type(first));
}

// 重载 二元谓词 版本
template <typename RandomIter, typename Distance, typename Compared>
void make_heap_aux(RandomIter first, RandomIter last, Distance*, Compared comp)
{
    if (last - first < 2)
        {
            return;
        }
    auto len = last - first;
    auto holeIndex = (len - 2) / 2;
    while (true)
    {
        // 重排以 holeIndex 为首的子树
        mystl::adjust_heap(first, holeIndex, len, *(first + holeIndex), comp);
        if (holeIndex == 0)
        {
            return;
        }
        holeIndex--;
    }
}

template <typename RandomIter, typename BinaryPredicate>
void make_heap(RandomIter first, RandomIter last, BinaryPredicate pred)
{
    mystl::make_heap_aux(first, last, distance_type(first), pred);
}

}   // end namespace mystl



#endif  // end MINIATURE_STL_HEAP_ALGO_H

//
// Created by yapeng-cheng on 22-12-20.
//

// 这个头文件包含两个函数 construct，destroy
// construct : 负责对象的构造
// destroy   : 负责对象的析构

#ifndef MINIATURE_STL_CONSTRUCT_H
#define MINIATURE_STL_CONSTRUCT_H

#include <new>

#include "type_traits.h"
#include "util.h"
#include "../02_iterators/iterator.h"

namespace mystl
{

//// construct 构造对象
template <typename T>
void construct(T * ptr)
{
    ::new((void *)ptr) T();
}

template <typename T1, typename T2>
void construct(T1 * ptr, const T2 & value)
{
    ::new((void *)ptr) T1(value);
}

template <typename T, typename ... Args>
void construct(T * ptr, Args && ... args)
{
    ::new ((void *)ptr) T(mystl::forward<Args>(args)...);
}



//// destroy 对对象进行析构
template <typename T>
void destroy_one(T *, std::true_type) {}

template <typename T>
void destroy_one(T * pointer, std::false_type)
{
    if (pointer != nullptr)
    {
        pointer -> ~T();
    }
}

template <typename ForwardIterator>
void destroy_cat(ForwardIterator, ForwardIterator, std::true_type) {}

template <typename ForwardIterator>
void destroy_cat(ForwardIterator first, ForwardIterator last, std::false_type)
{
    for (; first != last; ++ first)
    {
        destroy(&*first);
    }
}

template <typename T>
void destroy(T * pointer)
{
    destroy_one(pointer, std::is_trivially_destructible<T> {});
}

template <typename ForwardIterator>
void destroy(ForwardIterator first, ForwardIterator last)
{
    destroy_cat(first, last, std::is_trivially_destructible<typename iterator_traits<ForwardIterator>::value_type> {});
}

}

#endif //MINIATURE_STL_CONSTRUCT_H
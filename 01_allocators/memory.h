//
// Created by yapeng-cheng on 23-1-10.
//

#ifndef MINIATURE_STL_MEMORY_H
#define MINIATURE_STL_MEMORY_H

// 这个头文件负责更高级的动态内存管理
// 包含一些基本函数、空间配置器、未初始化的储存空间管理，以及一个模板类 auto_ptr

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "../03_algorithms/algobase.h"
#include "../01_allocators/allocator.h"
#include "../01_allocators/construct.h"
#include "../01_allocators/uninitalized.h"

namespace mystl 
{

// 获取对象地址
template <typename Type>
constexpr Type * address_of(Type & value) noexcept
{
    return &value;
}

// 获取 / 释放 临时缓冲区
template <typename Type>
pair<Type *, ptrdiff_t> get_buffer_helper(ptrdiff_t len, Type *)
{
    if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(Type)))
    {
        len = INT_MAX / sizeof(Type);
    }
    while (len > 0)
    {
        Type * temp = static_cast<Type *>(malloc(static_cast<size_t>(len) * sizeof(Type)));
        if (temp)
        {
            return pair<Type *, ptrdiff_t>(temp, len);
        }
        len /= 2;
    }
    return pair<Type *, ptrdiff_t>(nullptr, 0);
}

template <typename Type>
pair<Type *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len)
{
    return get_buffer_helper(len, static_cast<Type *>(0));
}

template <typename Type>
pair<Type *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, Type *)
{
    return get_buffer_helper(len, static_cast<Type *>(0));
}

template <typename Type>
void release_remporary_buffer(Type * ptr)
{
    free(ptr);
}


// --------------------------------------------------------------------------------------
// 类模板 : temporary_buffer
// 进行临时缓冲区的申请与释放
template <class ForwardIter, class Type>
class temporary_buffer
{
private:
    ptrdiff_t   original_len;   // 缓冲区申请的大小
    ptrdiff_t   len;            // 缓冲区实际的大小
    Type *      buffer;         // 指向缓冲区的指针

public:
    // 构造、析构函数
    temporary_buffer(ForwardIter first, ForwardIter last);
    ~temporary_buffer()
    {
        mystl::destroy(buffer, buffer + len);
        free(buffer);
    }

public:
    ptrdiff_t size() const noexcept {return len;}
    ptrdiff_t requested_size() const noexcept {return original_len;}
    Type * begin() noexcept {return buffer;}
    Type * end() noexcept {return buffer + len;}

private:
    void allocate_buffer();
    void initialize_buffer(const Type &, std::true_type) {}
    void initialize_buffer(const Type &, std::false_type) {mystl::uninitialized_fill_n(buffer, len, value);}

private:
    temporary_buffer(const temporary_buffer &);
    void operator=(const temporary_buffer &);
};

// 构造函数
template <class ForwardIter, class Type>
temporary_buffer<ForwardIter, Type>::temporary_buffer(ForwardIter first, ForwardIter last)
{
    try
    {
        len = mystl::distance(first, last);
        allocate_buffer();
        if (len > 0)
        {
            initialize_buffer(*first, std::is_trivially_default_constructible<Type>());
        }
    }
    catch(...)
    {
        free(buffer);
        buffer = nullptr;
        len = 0;
    }
}

// allocate_buffer 函数
template <class ForwardIter, class Type>
void temporary_buffer<ForwardIter, Type>::allocate_buffer()
{
    original_len = len;
    if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(Type)))
    {
        len = INT_MAX / sizeof(Type);
    }
    while (len > 0)
    {
        buffer = static_cast<Type *>(malloc(len * sizeof(Type)));
        if (buffer)
        {
            break;
        }
        len /= 2;
    }
}

// --------------------------------------------------------------------------------------
// 模板类: auto_ptr
// 一个具有严格对象所有权的小型智能指针
template <class Type>
class auto_ptr
{
public:
    typedef Type    elem_type;

private:
    elem_type * m_ptr;      // 实际指针

public:
    // 构造、复制、析构函数
    explicit auto_ptr(Type * p = nullptr) : m_ptr(p) {}
    auto_ptr(auto_ptr & rhs) : m_ptr(rhs.m_ptr) {}

    template <typename U>
    auto_ptr(auto_ptr<U> & rhs) : m_ptr(rhs.release()) {}

    auto_ptr & operator=(auto_ptr * rhs)
    {
        if (this != rhs)
        {
            delete m_ptr;
            m_ptr = rhs.release();
        }
        return *this;
    }

    template <typename U>
    auto_ptr & operator=(auto_ptr<U> & rhs)
    {
        if (this->get() != rhs.get())
        {
            delete m_ptr;
            m_ptr = rhs.release();
        }
        return *this;
    }

    ~auto_ptr() {delete m_ptr;}

public:
    // 重载 operator* 和 operator->
    Type & operator*() const {return *m_ptr;}
    Type * operator->() const {return m_ptr;}

    // 获得指针
    Type * get() const {return m_ptr;}

    // 释放指针
    Type * release() 
    {
        Type * temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    // 重置指针
    void reset(Type * p = nullptr)
    {
        if (m_ptr != p)
        {
            delete m_ptr;
            m_ptr = p;
        }
    }
};




}   // end namespace mystl

#endif //MINIATURE_STL_MEMORY_H
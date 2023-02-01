//
// Created by yapeng-cheng on 23-1-9.
//

#ifndef MINIATURE_STL_UTIL_H
#define MINIATURE_STL_UTIL_H

//// 这个文件包含一些通用工具，包括 move, forward, swap 等函数，以及 pair 等

#include <cstddef>

#include "type_traits.h"

namespace mystl
{

// move 将一个左值强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义。
template <typename T>
typename std::remove_reference<T>::type && move(T && arg) noexcept
{
    return static_cast<typename std::remove_reference<T>::type &&>(arg);
}

// forward 将输入的参数原封不动地传递到下一个函数中，这个“原封不动”指的是，如果输入的参数是左值，那么传递给下一个函数的参数的也是左值；如果输入的参数是右值，那么传递给下一个函数的参数的也是右值。
template <typename T>
T && forward(typename std::remove_reference<T>::type & arg) noexcept
{
    return static_cast<T &&>(arg);
}

template <typename T>
T && forward(typename std::remove_reference<T>::type && arg) noexcept
{
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
    return static_cast<T &&>(arg);
}

// swap 交换两个变量或容器的值
template <typename T>
void swap(T & lhs, T & rhs)
{
    auto temp = mystl::move(lhs);
    lhs = mystl::move(rhs);
    rhs = mystl::move(temp);
}

// swap_range 交换两个序列。这个算法需要 3 个正向迭代器作为参数。前两个参数分别是第一个序列的开始和结束迭代器，第三个参数是第二个序列的开始迭代器。显然，这两个序列的长度必须相同。这个算法会返回一个迭代器，它指向第二个序列的最后一个被交换元素的下一个位置。
template <typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator2 swap_range(ForwardIterator1 first1, ForwardIterator2 last1, ForwardIterator2 first2)
{
    for (; first1 != last1; ++ first1, (void) ++ first2)
        mystl::swap(*first1, *first2);
    return first2;
}

template <typename T, size_t N>
void swap(T(&a)[N], T(&b)[N])
{
    mystl::swap_range(a, a+N, b);
}

/*********************************** pair ***********************************/
// 结构体木板 ： pair
// 两个模板参数分别表示两个数据的类型
// 用 first 和 second 来分别取出第一个数据和第二个数据

template <typename Ty1, typename Ty2>
struct pair
{
    typedef Ty1     first_type;
    typedef Ty2     second_type;

    first_type first;       // 保存第一个数据
    second_type  second;    // 保存第二个数据

    // default constructiable
    template <class Other1 = Ty1, class Other2 = Ty2,
            typename = typename std::enable_if<
                    std::is_default_constructible<Other1>::value &&
                    std::is_default_constructible<Other2>::value, void>::type>
    constexpr pair()
            : first(), second()
    {
    }

    // implicit constructiable for this type
    template <class U1 = Ty1, class U2 = Ty2,
            typename std::enable_if<
                    std::is_copy_constructible<U1>::value &&
                    std::is_copy_constructible<U2>::value &&
                    std::is_convertible<const U1&, Ty1>::value &&
                    std::is_convertible<const U2&, Ty2>::value, int>::type = 0>
    constexpr pair(const Ty1& a, const Ty2& b)
            : first(a), second(b)
    {
    }

    // explicit constructible for this type
    template <class U1 = Ty1, class U2 = Ty2,
            typename std::enable_if<
                    std::is_copy_constructible<U1>::value &&
                    std::is_copy_constructible<U2>::value &&
                    (!std::is_convertible<const U1&, Ty1>::value ||
                     !std::is_convertible<const U2&, Ty2>::value), int>::type = 0>
    explicit constexpr pair(const Ty1& a, const Ty2& b)
            : first(a), second(b)
    {
    }

    pair(const pair& rhs) = default;
    pair(pair&& rhs) = default;

    // implicit constructiable for other type
    template <class Other1, class Other2,
            typename std::enable_if<
                    std::is_constructible<Ty1, Other1>::value &&
                    std::is_constructible<Ty2, Other2>::value &&
                    std::is_convertible<Other1&&, Ty1>::value &&
                    std::is_convertible<Other2&&, Ty2>::value, int>::type = 0>
    constexpr pair(Other1&& a, Other2&& b)
            : first(mystl::forward<Other1>(a)),
              second(mystl::forward<Other2>(b))
    {
    }

    // explicit constructiable for other type
    template <class Other1, class Other2,
            typename std::enable_if<
                    std::is_constructible<Ty1, Other1>::value &&
                    std::is_constructible<Ty2, Other2>::value &&
                    (!std::is_convertible<Other1, Ty1>::value ||
                     !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
    explicit constexpr pair(Other1&& a, Other2&& b)
            : first(mystl::forward<Other1>(a)),
              second(mystl::forward<Other2>(b))
    {
    }

    // implicit constructiable for other pair
    template <class Other1, class Other2,
            typename std::enable_if<
                    std::is_constructible<Ty1, const Other1&>::value &&
                    std::is_constructible<Ty2, const Other2&>::value &&
                    std::is_convertible<const Other1&, Ty1>::value &&
                    std::is_convertible<const Other2&, Ty2>::value, int>::type = 0>
    constexpr pair(const pair<Other1, Other2>& other)
            : first(other.first),
              second(other.second)
    {
    }

    // explicit constructiable for other pair
    template <class Other1, class Other2,
            typename std::enable_if<
                    std::is_constructible<Ty1, const Other1&>::value &&
                    std::is_constructible<Ty2, const Other2&>::value &&
                    (!std::is_convertible<const Other1&, Ty1>::value ||
                     !std::is_convertible<const Other2&, Ty2>::value), int>::type = 0>
    explicit constexpr pair(const pair<Other1, Other2>& other)
            : first(other.first),
              second(other.second)
    {
    }

    // implicit constructiable for other pair
    template <class Other1, class Other2,
            typename std::enable_if<
                    std::is_constructible<Ty1, Other1>::value &&
                    std::is_constructible<Ty2, Other2>::value &&
                    std::is_convertible<Other1, Ty1>::value &&
                    std::is_convertible<Other2, Ty2>::value, int>::type = 0>
    constexpr pair(pair<Other1, Other2>&& other)
            : first(mystl::forward<Other1>(other.first)),
              second(mystl::forward<Other2>(other.second))
    {
    }

    // explicit constructiable for other pair
    template <class Other1, class Other2,
            typename std::enable_if<
                    std::is_constructible<Ty1, Other1>::value &&
                    std::is_constructible<Ty2, Other2>::value &&
                    (!std::is_convertible<Other1, Ty1>::value ||
                     !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
    explicit constexpr pair(pair<Other1, Other2>&& other)
            : first(mystl::forward<Other1>(other.first)),
              second(mystl::forward<Other2>(other.second))
    {
    }

    // 重载赋值运算符
    pair & operator=(const pair & rhs)
    {
        if (this != rhs)
        {
            first = rhs.first;
            second = rhs.second;
        }
        return *this;
    }

    pair & operator=(pair && rhs)
    {
        if (this != rhs)
        {
            first = mystl::move(rhs.first);
            second = mystl::move(rhs.second);
        }
        return *this;
    }

    // copy 给其他的 pair
    template <typename Other1, typename Other2>
    pair & operator=(const pair<Other1, Other2> & other)
    {
        first = other.first;
        second = other.second;
        return *this;
    }

    template <typename Other1, typename Other2>
    pair & operator=(pair<Other1, Other2> && other)
    {
        first = mystl::forward<Other1>(other.first);
        second = mystl::forward<Other2>(other.second);
        return *this;
    }

    ~pair() = default;

    void swap(pair & other)
    {
        if (this != other)
        {
            mystl::swap(first, other.first);
            mystl::swap(second, other.second);
        }
    }
};

// 重载比较操作符
template <typename T1, typename T2>
bool operator==(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
bool operator!=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
{
    return !(lhs == rhs);
}

template <typename T1, typename T2>
bool operator<(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
{
    return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template <typename T1, typename T2>
bool operator>(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
{
    return rhs < lhs;
}

template <typename T1, typename T2>
bool operator<=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
{
    return !(rhs < lhs);
}

template <typename T1, typename T2>
bool operator>=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs)
{
    return !(rhs > lhs);
}

// 重载 mystl 的 swap
template <typename T1, typename T2>
void swap(pair<T1, T2> & lhs, pair<T1, T2> & rhs)
{
    lhs.swap(rhs);
}

// 全局函数，让两个数据成为一个 pair
template <typename T1, typename T2>
pair<T1, T2> make_pair(T1 && first, T2 && second)
{
    return pair<T1, T2>(mystl::forward<T1>(first), mystl::forward<T2>(second));
}

} // end namespace mystl

#endif //MINIATURE_STL_UTIL_H
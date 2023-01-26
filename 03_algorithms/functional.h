#ifndef MINIATURE_STL_FUNCTIONAL_H
#define MINIATURE_STL_FUNCTIONAL_H

// 这个头文件包含了 mystl 的函数对象与哈希函数

#include <cstddef>

namespace mystl
{

// 定义一元函数的参数型别和返回值型别
template <class Arg, class Result>
struct unarg_function 
{
    typedef Arg     argument_type;
    typedef Result  result_type;
};

// 定义二元函数的参数型别和返回值型别
template <class Arg1, class Arg2, class Result>
struct binary_function
{
    typedef Arg1    first_argument_type;
    typedef Arg2    second_argument_type;
    typedef Result  result_type; };

// 函数对象 -- 加法
template <typename Type>
struct plus : public binary_function<Type, Type, Type>
{
    Type operator()(const Type & x, const Type & y) const 
    {
        return x + y;
    }
};

// 函数对象 -- 减法
template <typename Type>
struct minus : public binary_function<Type, Type, Type>
{
    Type operator()(const Type & x, const Type & y) const 
    {
        return x - y;
    }
};

// 函数对象：乘法
template <typename Type>
struct multiplies : public binary_function<Type, Type, Type>
{
    Type operator()(const Type & x, const Type & y) const 
    {
        return x * y;
    }
};

// 函数对象：除法
template <typename Type>
struct divides : public binary_function<Type, Type, Type>
{
    Type operator()(const Type & x, const Type & y) const 
    {
        return x / y;
    }
};

// 函数对象：取模
template <typename Type>
struct modulus : public binary_function<Type, Type, Type>
{
    Type operator()(const Type & x, const Type & y) const 
    {
        return x % y;
    }
};

// 函数对象：否定
template <typename Type>
struct negate : public unarg_function<Type, Type>
{
    Type operator()(const Type & x) const 
    {
        return -x;
    }
};

// 加法的证同元素，意思是数值A若与该元素做op运算，会得到A自己。
template <typename Type>
Type identity_element(plus<Type>)
{
    return Type(0);
}

// 乘法的证同元素
template <typename Type>
Type identity_element(multiplies<Type>)
{
    return Type(1);
}

// 函数对象：等于
template <typename Type>
struct equal_to : public binary_function<Type, Type, bool>
{
    bool operator()(const Type & x, const Type & y) const 
    {
        return x == y;
    }
};

// 函数对象：不等于
template <typename Type>
struct not_equal_to : public binary_function<Type, Type, bool>
{
    bool operator()(const Type & x, const Type & y) const 
    {
        return x != y;
    }
};

// 函数对象：大于
template <typename Type>
struct greater : public binary_function<Type, Type, bool>
{
    bool operator()(const Type & x, const Type & y) const 
    {
        return x > y;
    }
};

// 函数对象：小于
template <typename Type>
struct less : public binary_function<Type, Type, bool>
{
  bool operator()(const Type & x, const Type & y) 
  {
    return x < y;
  }
};

// 函数对象：大于等于
template <typename Type>
struct greater_equal : public binary_function<Type, Type, bool>
{
    bool operator()(const Type & x, const Type & y) const 
    {
        return x >= y;
    }
};

// 函数对象：小于等于
template <typename Type>
struct less_equal : public binary_function<Type, Type, bool>
{
    bool operator()(const Type & x, const Type & y) const 
    {
        return x <= y;
    }
};

// 函数对象：逻辑与
template <typename Type>
struct logical_and : public binary_function<Type, Type, bool>
{
    bool operator()(const Type & x, const Type & y) const 
    {
        return x && y;
    }
};

// 函数对象：逻辑或
template <typename Type>
struct logical_or : public binary_function<Type, Type, bool>
{
    bool operator()(const Type & x, const Type & y) const 
    {
        return x || y;
    }
};

// 函数对象：逻辑非
template <typename Type>
struct logical_not : public unarg_function<Type, bool>
{
    bool operator()(const Type & x) const 
    {
        return !x;
    }
};

// 证同函数：不会改变元素，返回本身
template <typename Type>
struct identity : public unarg_function<Type, Type>
{
    const Type & operator()(const Type & x) const 
    {
        return x;
    }
};

// 选择函数：接受一个 pair，返回第一个元素
template <typename Pair>
struct selectfirst : unarg_function<Pair, typename Pair::first_type>
{
    const typename Pair::first_type & operator()(const Pair & x) const 
    {
        return x.first;
    }
};

// 选择函数：接受一个 pair，返回第二个元素
template <typename Pair>
struct selectsecond : unarg_function<Pair, typename Pair::second_type>
{
    const typename Pair::second_type & operator()(const Pair & x) const 
    {
        return x.second;
    }
};

// 投射函数：返回第一参数
template <typename Arg1, typename Arg2>
struct projectfirst : public binary_function<Arg1, Arg2, Arg1>
{
    Arg1 operator()(const Arg1 & x, const Arg2 * y) const 
    {
        return x;
    }
};

// 投射函数：返回第二参数
template <typename Arg1, typename Arg2>
struct projectsecond : public binary_function<Arg1, Arg2, Arg2>
{
    Arg2 operator()(const Arg1 & x, const Arg2 * y) const 
    {
        return y;
    }
};


/*****************************************************************************************/
// 哈希函数对象

// 对于大部分类型，hash function 什么都不做
template <class Key>
struct hash {};

// 针对指针的偏特化版本
template <class Type>
struct hash<Type *>
{
    size_t operator()(Type * p) const noexcept
    {
        return reinterpret_cast<size_t>(p);
    }
};

// 对于整型类型，只是返回原值
#define MYSTL_TRIVIAL_HASH_FCN(Type)         \
template <> struct hash<Type>                \
{                                            \
  size_t operator()(Type val) const noexcept \
  { return static_cast<size_t>(val); }       \
};

MYSTL_TRIVIAL_HASH_FCN(bool)

MYSTL_TRIVIAL_HASH_FCN(char)

MYSTL_TRIVIAL_HASH_FCN(signed char)

MYSTL_TRIVIAL_HASH_FCN(unsigned char)

MYSTL_TRIVIAL_HASH_FCN(wchar_t)

MYSTL_TRIVIAL_HASH_FCN(char16_t)

MYSTL_TRIVIAL_HASH_FCN(char32_t)

MYSTL_TRIVIAL_HASH_FCN(short)

MYSTL_TRIVIAL_HASH_FCN(unsigned short)

MYSTL_TRIVIAL_HASH_FCN(int)

MYSTL_TRIVIAL_HASH_FCN(unsigned int)

MYSTL_TRIVIAL_HASH_FCN(long)

MYSTL_TRIVIAL_HASH_FCN(unsigned long)

MYSTL_TRIVIAL_HASH_FCN(long long)

MYSTL_TRIVIAL_HASH_FCN(unsigned long long)

#undef MYSTL_TRIVIAL_HASH_FCN

// 对于浮点数，逐位哈希
inline size_t bitwise_hash(const unsigned char* first, size_t count)
{
#if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) &&__SIZEOF_POINTER__ == 8)
    const size_t fnv_offset = 14695981039346656037ull;
    const size_t fnv_prime = 1099511628211ull;
#else
    const size_t fnv_offset = 2166136261u;
    const size_t fnv_prime = 16777619u;
#endif
    size_t result = fnv_offset;
    for (size_t i = 0; i < count; ++i)
    {
        result ^= (size_t)first[i];
        result *= fnv_prime;
    }
    return result;
}

template <>
struct hash<float>
{
    size_t operator()(const float& val)
    { 
        return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(float));
    }
};

template <>
struct hash<double>
{
    size_t operator()(const double& val)
    {
        return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(double));
    }
};

template <>
struct hash<long double>
{
    size_t operator()(const long double& val)
    {
        return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(long double));
    }
};



}  // end namespace mystl

#endif

//
// Created by yapeng-cheng on 22-12-20.
//

#ifndef MINIATURE_STL_TYPE_TRAITS_H
#define MINIATURE_STL_TYPE_TRAITS_H

//// 这个头文件用于提取类型信息

#include <type_traits>
namespace mystl
{

template <typename T, T v>
struct integral_constant
{
    static constexpr T value = v;       // constexpr表达式是指值不会改变并且在编译过程就能得到计算结果的表达式。声明为constexpr的变量一定是一个const变量，而且必须用常量表达式初始化
};

template <bool b>
using bool_constant = integral_constant<bool, b>;

typedef bool_constant<true> true_type;
typedef bool_constant<false> false_type;

/**************************************************************************/




}

#endif //MINIATURE_STL_TYPE_TRAITS_H
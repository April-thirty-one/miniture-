#ifndef MINITURE_STL_BASIC_STRING_H_
#define MINITURE_STL_BASIC_STRING_H_

// 这个头文件包含一个模板类 basic_string
// 用于表示字符串类型

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <type_traits>

#include "../02_iterators/iterator.h"
#include "../01_allocators/memory.h"
#include "../03_algorithms/functional.h"

namespace mystl
{

// charr_traits

template <class CharType>
struct char_traits {
    typedef CharType char_type;

    static size_t length(const char_type* str);
    static int compare(const char_type* str1, const char_type* str2, size_t n);
    static char_type* copy(char_type* dst, const char_type* src, size_t n);
    static char_type* move(char_type* dst, const char_type* src, size_t n);
    static char_type* fill(char_type* dst, char_type value, size_t count);
};

// partialized char_traits<char>
template <>
struct char_traits<char> {
    typedef char char_type;

    static size_t length(const char_type* str) noexcept {
        return std::strlen(str);
    }
    
    static int compare(const char_type* str1, const char_type* str2, size_t n) {
        return std::memcmp(str1, str2, n);
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) {
        assert(src + n <= dst || dst + n <= src);
        return static_cast<char_type *>(std::memcpy(dst, src, n));
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) {
        return static_cast<char_type*>(std::memmove(dst, src, n));
    }

    static char_type* fill(char_type* dst, char_type value, size_t n) {
        return static_cast<char_type*>(std::memset(dst, value, n));
    }
};

// partialized char_traits<wchar_t>
template <>
struct char_traits<wchar_t> {
    typedef wchar_t char_type;

    static size_t length(const char_type* str) {
        return std::wcslen(str);
    }

    static int compare(const char_type* str1, const char_type* str2, size_t n) {
        return std::wmemcmp(str1, str2, n);
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) {
        assert(src + n <= dst || dst + n <= src);
        return static_cast<char_type*>(std::wmemcpy(dst, src, n));
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) {
        return static_cast<char_type*>(std::wmemmove(dst, src, n));
    }

    static char_type* fill(char_type* dst, char_type value, size_t count) {
        return static_cast<char_type*>(std::wmemset(dst, value, count));
    }
};

// partialized char_traits<char16_t>
template <>
struct char_traits<char16_t> {
    typedef char16_t char_type;

    static size_t length(const char_type* str) {
        size_t len = 0;
        for (; *str != char_type(0); ++str) {
            ++len;
        }
        return len;
    }

    static int compare(const char_type* str1, const char_type* str2, size_t n) {
        for (; n != 0; --n, ++str1, ++str2) {
            if (*str1 > *str2) {
                return 1;
            }
            else if (*str1 < *str2) {
                return -1;
            } 
        }
        return 0;
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) {
        assert(src + n <= dst || dst + n <= src);
        char_type* result = dst;
        for (; n != 0; --n, ++dst, ++src) {
            *dst = *src;
        }
        return result;
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) {
        char_type* result = dst;
        if (dst < src) {
            for (; n != 0; --n, ++dst, ++src) {
                *dst = *src;
            }
        }
        else if (dst > src) {
            dst += n;
            src += n;
            for (; n != 0; --n) {
                *--dst = *--src;
            }
        }
        return result;
    }

    static char_type* fill(char_type* dst, char_type value, size_t count) {
        char_type* result = dst;
        for (; count != 0; --count) {
            *dst = value;
            ++dst;
        }
        return result;
    }
};

// partialized char_traits<char32_t>
template <>
struct char_traits<char32_t> {
    typedef char32_t char_type;

    static size_t length(const char_type* str) {
        size_t len = 0;
        for (; *str != char_type(0); str++) {
            ++len;
        }
        return len;
    }

    static char_type* copy(char_type* dst, const char_type* src, size_t n) {
        assert(src + n <= dst || dst + n <= src);
        char_type* result = dst;
        for (; n != 0; --n, ++dst, ++src) {
            *dst = *src;
        }
        return result;
    }

    static char_type* move(char_type* dst, const char_type* src, size_t n) {
        char_type * result = dst;
        if (dst < src) {
            for (; n != 0; --n, ++src, ++dst) {
                *dst = *src;
            }
        }
        else if (dst > src) {
            dst += n;
            src += n;
            for (; n != 0; --n) {
                *--dst = *--src;
            }
        }
        return result;
    }

    static char_type* fill(char_type* dst, char_type value, size_t count) {
        char_type* result = dst;
        for (; count > 0; --count, ++dst) {
            *dst = value;
        }
        return result;
    }
};



// 初始化 basic_string 尝试分配的最小 buffer 大小，可能被忽略
const int StringInitSize = 32;

// 模板类 basic_string
// 参数一代表字符类型，参数二代表萃取字符类型的方式，缺省使用 mystl::char_traits
template <class CharType, class CharTraits = mystl::char_traits<CharType>>
class basic_string {
public:
    typedef CharTraits                                  traits_type;
    typedef CharTraits                                  char_traits;

    typedef mystl::allocator<CharType>                  allocator_type;
    typedef mystl::allocator<CharType>                  data_allocator;

    typedef typename allocator_type::value_type         value_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::size_type          size_type;
    typedef typename allocator_type::difference_type    difference_type;

    typedef value_type*                                 iterator;
    typedef const value_type*                           const_iterator;
    typedef mystl::reverse_iterator<iterator>           reverse_iterator;
    typedef mystl::reverse_iterator<const_iterator>     const_reverse_iterator;

    allocator_type get_allocator() {
        return allocator_type();
    }

    static_assert(std::is_pod<CharType>::value, "Character type of basic_string must be a POD");
    static_assert(std::is_same<CharType, typename traits_type::char_type>::value,
                "CharType must be same as traits_type::char_type");

public:
    static constexpr size_type npos = static_cast<size_type>(-1);

private:
    iterator buffer_;   // 存储字符串的起始位置
    size_type size_;    // 大小
    size_type cap_;     // 容量
    
public:
    // 构造、复制、移动、析构函数
    basic_string() { 
        try_init(); 
    }

    basic_string(size_type n, value_type value) : buffer_(nullptr), size_(0), cap_(0) { 
        fill_init(n, value);
    }

    basic_string(const basic_string& other, size_type pos) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(other.buffer_, pos, other.size_ - pos);
    }

    basic_string(const basic_string& other, size_type pos, size_type count) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(other.buffer_, pos, count);
    }

    basic_string(const_pointer str) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(str, 0, char_traits::length(str));
    }

    basic_string(const_pointer str, size_type count) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(str, 0, count);
    }

    template <typename Iter, typename std::enable_if<mystl::is_input_iterator<Iter>::value, int>::type = 0>
    basic_string(Iter first, Iter last) {
        copy_init(first, last, iterator_category(first));
    }

    basic_string(const basic_string& rhs) : buffer_(nullptr), size_(0), cap_(0) {
        init_from(rhs.buffer_, 0, rhs.size_);
    }

    basic_string(basic_string&& rhs) : buffer_(rhs.buffer_), size_(rhs.size_), cap_(rhs.cap_) {
        rhs.buffer_ = nullptr;
        rhs.size_ = 0;
        rhs.cap_ = 0;
    }

    basic_string& operator=(const basic_string& rhs);
    basic_string& operator=(basic_string&& rhs);
    basic_string& operator=(const_pointer str);
    basic_string& operator=(value_type value);

    ~basic_string() { destroy_buffer(); }

public:
    // 迭代器相关操作
    iterator begin() {return buffer_;}
    const_iterator begin() const {return buffer_;}
    iterator end() {return buffer_ + size_;}
    const_iterator end() const {return buffer_ + size_;}

    reverse_iterator rbegin() {return reverse_iterator(end());}
    const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
    reverse_iterator rend() {return reverse_iterator(begin());}
    const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

    const_iterator cbegin() const {return begin();}
    const_iterator cend() const {return end();}
    const_reverse_iterator crbegin() const {return rbegin();}
    const_reverse_iterator crend() const {return rend();}

    // 容量相关的操作
    bool empty() const {return size_ == 0;}

    size_type size() const {return size_;}
    size_type length() const {return size_;}
    size_type capacity() const {return cap_;}
    size_type max_size() const {return static_cast<size_type>(-1);}

    void reserve(size_type n);
    void shrink_to_fit();

    // 访问元素相关操作
};
























template <class CharType>
size_t char_traits<CharType>::length(const char_type* str) {
    size_t result = 0;
    for (; *str != char_type(nullptr); ++str) {
        ++result;
    }
    return result;
}

template <class CharType>
int char_traits<CharType>::compare(const char_type *str1, const char_type *str2, size_t n) {
    for (; n > 0; --n, ++str1, ++str2) {
        if (*str1 > *str2) {
            return 1;
        }
        else if (*str1 < *str2) {
            return -1;
        }
    }
    return 0;
}

template <class CharType>
typename char_traits<CharType>::char_type* char_traits<CharType>::copy(char_type* dst, const char_type* src, size_t n) {
    assert(src + n <= dst || dst + n <= src);
    char_type* result = dst;
    for (; n != 0; --n, ++dst, ++src) {
        *dst = *src;
    }
    return result;
}

template <class CharType>
typename char_traits<CharType>::char_type* char_traits<CharType>::move(char_type* dst, const char_type* src, size_t n) {
    char_type* result = dst;
    if (dst < src) {
        for (; n != 0; --n, ++dst, ++src) {
            *dst = *src;
        }
    }
    else if (dst > src) {
        dst += n;
        src += n;
        for (; n != 0; --n) {
            *--dst = *--src;
        }
    }
    return result;
}

template <class CharType>
typename char_traits<CharType>::char_type* char_traits<CharType>::fill(char_type* dst, char_type value, size_t count) {
    char_type* result = dst;
    for (; count > 0; --count, ++dst) {
        *dst = value;
    }
    return result;
}


}

#endif // MINITURE_STL_BASIC_STRING_H_

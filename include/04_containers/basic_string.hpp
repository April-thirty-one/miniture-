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
#include "../00_utils/exceptdef.h"

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
    reference operator[](size_type n) {
        assert(n <= this->size_);
        if (n == size_) {
            *(buffer_ + n) = value_type();
        }
        return *(buffer_ + n);
    }

    const_reference operator[](size_type n) const {
        assert(n <= size_);
        if (n == size_) {
            *(buffer_ + n) = value_type();
        }
        return *(buffer_ + n);
    }

    reference at(size_type n) {
        THROW_OUT_OF_RANGE_IF(n >= size_, "basic_string<char, Traits>::at()" "subscript out of range");
        return (*this)[n];
    }

    const_reference at(size_type n) const {
        THROW_OUT_OF_RANGE_IF(n >= size_, "basic_string<char, Traits>::at()" "subscript out of range");
        return (*this)[n];
    }

    reference front() {
        MYSTL_DEBUG(!empty());
        return *begin();
    }

    const_reference front() const {
        MYSTL_DEBUG(!empty());
        return *begin();
    }

    reference back() {
        MYSTL_DEBUG(!empty());
        return *(end() - 1);
    }

    const_reference back() const {
        MYSTL_DEBUG(!empty());
        return *(end() - 1);
    }

    const_pointer data() const {
        return to_raw_pointer();
    }

    const_pointer c_str() const {
        return to_raw_pointer();
    }

    // 添加删除相关操作

    // insert
    iterator insert(const_iterator pos, value_type value);
    iterator insert(const_iterator pos, size_type count, value_type value);

    template <class Iter>
    iterator insert(const_iterator pos, Iter first, Iter last);

    // push_back  /  pop_back
    void push_back(value_type value) {
        append(1, value);
    }

    void pop_back() {
        MYSTL_DEBUG(!empty());
        --size_;
    }

    // append
    basic_string& append(size_type count, value_type value);

    basic_string& append(const basic_string& str) {
        return append(str, 0, str, size_);
    }

    basic_string& append(const basic_string& str, size_type pos) {
        return append(str, pos, str, size_ - pos);
    }

    basic_string& append(const basic_string& str, size_type pos, size_type count);

    basic_string& append(const_pointer s) {
        return append(s, char_traits::length(s));
    }

    basic_string& append(const_pointer s, size_type count);

    template <class Iter, typename std::enable_if<mystl::is_input_iterator<Iter>::value, int>::type = 0>
    basic_string& append(Iter first, Iter last) {
        return append_range(first, last);
    }

    // erase  /  clear
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    // resize
    void resize(size_type count) {
        return resize(count, value_type());
    }
    void resize(size_type count, value_type value);

    void clear() {
        size_ = 0;
    }

    // basic_string 相关操作
    
    // compare
    int compare(const basic_string& other) const;
    int compare(size_type pos1, size_type count1, const basic_string& other) const;
    int compare(size_type pos1, size_type count1, const basic_string& other, size_type pos2, size_type count2 = npos) const;
    int compare(const_pointer s) const;
    int compare(size_type pos1, size_type count1, const_pointer s) const;
    int compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const;

    // substr
    basic_string substr(size_type index, size_type count = npos) {
        count = mystl::min(count, size_ - index);
        return basic_string(buffer_ + index, buffer_ + index + count);
    }

    // replace 
    basic_string& replace(size_type pos, size_type count, const basic_string& str) {
        THROW_OUT_OF_RANGE_IF(pos > size_, "basic_string<Char, Traits>::replace's pos out of range");
        return replace_cstr(buffer_ + pos, count, str.buffer_, str.size_);
    }

    basic_string& replace(const_iterator first, const_iterator last, const basic_string& str) {
        MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_cstr(first, static_cast<size_type>(last - first), str.buffer_, str.size_);
    }

    basic_string& replace(size_type pos, size_type count, const_pointer str) {
        THROW_OUT_OF_RANGE_IF(pos > size_, "basic_string<Char, Traits>::replace's pos out of range");
        return replace_cstr(buffer_ + pos, count, str, char_traits::length(str));
    }

    basic_string& replace(const_iterator first, const_iterator last, const_pointer str) {
        MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_cstr(first, static_cast<size_type>(last - first), str, char_traits::length(str));
    }

    basic_string& replace(size_type pos, size_type count, const_pointer str, size_type count2) {
        THROW_OUT_OF_RANGE_IF(pos > size_, "basic_string<Char, Traits>::replace's pos out of range");
        return replace_cstr(buffer_ + pos, count, str, count2);
    }

    basic_string& replace(const_iterator first, const_iterator last, const_pointer str, size_type count) {
        MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_cstr(first, static_cast<size_type>(last - first), str, count);
    }

    basic_string& replace(size_type pos, size_type count, size_type count2, value_type value) {
        THROW_OUT_OF_RANGE_IF(pos > size_, "basic_string<Char, Traits>::replace's pos out of range");
        return replace_fill(buffer_ + pos, count, count2, value);
    }

    basic_string& replace(const_iterator first, const_iterator last, size_type count, value_type value) {
        MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_fill(first, static_cast<size_type>(last - first), count, value);
    }

    basic_string& replace(size_type pos1, size_type count1, const basic_string& str, size_type pos2, size_type count2 = npos) {
        THROW_OUT_OF_RANGE_IF(pos1 > size_ || pos2 > str.size_, "basic_string<Char, Traits>::replace's pos out of range");
        return replace_cstr(buffer_ + pos1, count1, str.buffer_ + pos2, count2);
    }

    template <class Iter, typename std::enable_if<mystl::is_input_iterator<Iter>::value, int>::type = 0>
    basic_string& replace(const_iterator first, const_iterator last, Iter first2, Iter last2) {
        MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
        return replace_copy(first, last, first2, last2);
    }

    // reverse
    void reverse();

    // swap
    void swap(basic_string& rhs);

    // 查找相关操作
    // find
    size_type find(value_type value, size_type pos = 0) const;
    size_type find(const_pointer str, size_type pos = 0) const;
    size_type find(const_pointer str, size_type pos, size_type count) const;
    size_type find(const basic_string& str, size_type pos = 0) const;

    // rfind
    
    size_type rfind(value_type ch, size_type pos = npos)                         const noexcept;
    size_type rfind(const_pointer str, size_type pos = npos)                     const noexcept;
    size_type rfind(const_pointer str, size_type pos, size_type count)           const noexcept;
    size_type rfind(const basic_string& str, size_type pos = npos)               const noexcept;

    // find_first_of
    size_type find_first_of(value_type ch, size_type pos = 0)                    const noexcept;
    size_type find_first_of(const_pointer s, size_type pos = 0)                  const noexcept;
    size_type find_first_of(const_pointer s, size_type pos, size_type count)     const noexcept;
    size_type find_first_of(const basic_string& str, size_type pos = 0)          const noexcept;

    // find_first_not_of
    size_type find_first_not_of(value_type ch, size_type pos = 0)                const noexcept;
    size_type find_first_not_of(const_pointer s, size_type pos = 0)              const noexcept;
    size_type find_first_not_of(const_pointer s, size_type pos, size_type count) const noexcept;
    size_type find_first_not_of(const basic_string& str, size_type pos = 0)      const noexcept;

    // find_last_of
    size_type find_last_of(value_type ch, size_type pos = 0)                     const noexcept;
    size_type find_last_of(const_pointer s, size_type pos = 0)                   const noexcept;
    size_type find_last_of(const_pointer s, size_type pos, size_type count)      const noexcept;
    size_type find_last_of(const basic_string& str, size_type pos = 0)           const noexcept;

    // find_last_not_of
    size_type find_last_not_of(value_type ch, size_type pos = 0)                 const noexcept;
    size_type find_last_not_of(const_pointer s, size_type pos = 0)               const noexcept;
    size_type find_last_not_of(const_pointer s, size_type pos, size_type count)  const noexcept;
    size_type find_last_not_of(const basic_string& str, size_type pos = 0)       const noexcept;

    // count
    size_type count(value_type value, size_type pos = 0) const;

public:
    // 重载 operator+=
    basic_string& operator+=(const basic_string& str) {
        return append(str);
    }

    basic_string& operator+=(value_type value) {
        return append(1, value);
    }

    basic_string& operator+=(const_pointer str) {
        return append(str, str+ char_traits::length(str));
    }

    // 重载 operator>>  / operator<<
    friend std::istream& operator>>(std::istream is, basic_string& str) {
        value_type* buf = new value_type[4096];
        is >> buf;
        basic_string temp(buf);
        str = std::move(temp);
        delete[] buf;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const basic_string& str) {
        for (size_type i = 0; i < str.size_; ++i) {
            os << *(str.buffer_ + i);
        }
        return os;
    }

private:
    // helper functions

    // init  /  destroy
    void try_init();

    void fill_init(size_type n, value_type value);

    template <class Iter>
    void copy_init(Iter first, Iter last, mystl::input_iterator_tag);
    template <class Iter>
    void copy_init(Iter first, Iter last, mystl::forward_iterator_tag);

    void init_from(const_pointer src, size_type pos, size_type n);

    void destroy_buffer();

    // get raw pointer
    const_pointer to_raw_pointer() const;

    // shrink_to_fit
    void reinsert(size_type size);

    // append
    template <class Iter>
    basic_string& append_range(Iter first, Iter last);

    // compare 
    int compare_cstr(const_pointer s1, size_type n1, const_pointer s2, size_type nn2) const;

    // replace
    basic_string& replace_cstr(const_iterator first, size_type count1, const_pointer str, size_type count2);
    basic_string& replace_fill(const_iterator first, size_type count1, size_type count2, value_type value);
    template <class Iter>
    basic_string& replace_copy(const_iterator first, const_iterator last, Iter first2, Iter last2);

    // reallocate
    void reallocate(size_type need);
    iterator reallocate_and_fill(iterator pos, size_type n, value_type value);
    iterator reallocate_and_copy(iterator pos, const_iterator first, const_iterator last);
};

/*****************************************************************************************/

// 复制赋值操作符
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>& basic_string<CharType, CharTraits>::operator=(const basic_string& rhs) {
    if (this != &rhs) {
        basic_string temp(rhs);
        swap(temp);
    }
    return *this;
}

// 移动赋值操作符
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>& basic_string<CharType, CharTraits>::operator=(basic_string&& rhs) {
    destroy_buffer();
    buffer_ = rhs.buffer_;
    size_ = rhs.size_;
    cap_ = rhs.cap;
    rhs.buffer_ = nullptr;
    rhs.size_ = 0;
    rhs.cap_ = 0;
    return *this;
}


// 用一个字符串赋值
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>& basic_string<CharType, CharTraits>::operator=(const_pointer str) {
    const size_type len = char_traits::len(str);
    if (cap_ < len) {
        auto new_buffer = data_allocator::allocator(len + 1);
        data_allocator::deallocate(buffer_);
        buffer_ = new_buffer;
        cap_ = len + 1;
    }
    char_traits::copy(buffer_, str, len);
    size_ = len;
    return *this;
}


// 用一个字符赋值
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>& basic_string<CharType, CharTraits>::operator=(value_type value) {
    if (cap_ < 1) {
        auto new_buffer = data_allocator::allocator(2);
        data_allocator::deallocate(buffer_);
        buffer_ = new_buffer;
        cap_ = 2;
    }
    *buffer_ = value;
    size_ = 1;
    return *this;
}


// 预留储存空间
template <class CharType, class CharTraits> 
void basic_string<CharType, CharTraits>::reserve(size_type n) {
    if (cap_ < n) {
        THROW_LENGTH_ERRPR_IF(n > max_size(), "n can not larger than max_size() in basic_string<CharType, CharTraits>::reserve(n)");
        auto new_buffer = data_allocator::allocator(n);
        buffer_ = new_buffer;
        cap_ = n;
    }
}

// 减少不用的空间
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
shrink_to_fit()
{
    if (size_ != cap_)
    {
        reinsert(size_);
    }
}

// 在 pos 处插入一个元素
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator basic_string<CharType, CharTraits>::insert(const_iterator pos, value_type value) {
    iterator result = const_cast<iterator>(pos);
    if (size_ == cap_) {
        return reallocate_and_fill(result, 1, value);
    }
    char_traits::move(result + 1, result, end() - result);
    ++size_;
    *result = value;
    return result;
}

// 在 pos 处插入 n 个元素
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator basic_string<CharType, CharTraits>::insert(const_iterator pos, size_type count, value_type value) {
    iterator result = const_cast<iterator>(pos);
    if (count == 0) {
        return result;
    }
    if (cap_ - size_ < count) {
        return reallocate_and_fill(result, count, value);
    }
    if (pos == end()) {
        char_traits::fil(end(), value, count);
        size_ += count;
        return result;
    }
    char_traits::move(result + count, result, count);
    char_traits::fill(result, value, count);
    size_  += count;
    return result;
}

// 在 pos 处插入 []
template <class CharType, class CharTraits>
template <class Iter>
typename basic_string<CharType, CharTraits>::iterator
basic_string<CharType, CharTraits>::
insert(const_iterator pos, Iter first, Iter last) {
    iterator r = const_cast<iterator>(pos);
    const size_type len = mystl::distance(first, last);
    if (len == 0)
        return r;
    if (cap_ - size_ < len) {
        return reallocate_and_copy(r, first, last);
    }
    if (pos == end()) {
        mystl::uninitialized_copy(first, last, end());
        size_ += len;
        return r;
    }
    char_traits::move(r + len, r, len);
    mystl::uninitialized_copy(first, last, r);
    size_ += len;
    return r;
}

// 在末尾添加 count 个 ch
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>& basic_string<CharType, CharTraits>::append(size_type count, value_type value) {
    THROW_LENGTH_ERRPR_IF(size_ > max_size() - count, "basic_string<chartype, chartraits>'s size too big");
    if (cap_ - size_ < count) {
        reallocate(count);
    }
    char_traits::fill(buffer_ + size_, value, count);
    size_ += count;
    return *this;
}

// 在末尾添加 [str[pos] str[pos + count]) 一段
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>& basic_string<CharType, CharTraits>::append(const basic_string& str, size_type pos, size_type count) {
    THROW_LENGTH_ERRPR_IF(size_ > max_size() - count, "basic_string<chartypem chartraits>'s size too big");
    if (count == 0) {
        return *this;
    }
    if (cap_ - size_ < count) {
        reallocate(count);
    }
    char_traits::copy(buffer_ + size_, str.buffer + pos, count);
    size_ += count;
    return *this;
}

// 在末尾添加 [s, s+ count) 一段
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>& basic_string<CharType, CharTraits>::append(const_pointer s, size_type count) {
    THROW_LENGTH_ERROR_IF(size_ > max_size() - count, "basic_string<chartype, traits>'s size too big");
    if (cap_ - size_ < count) {
        reallocate(count);
    }
    char_traits::copy(buffer_ + size_, s, count);
    size_ += count;
    return *this;
}

// 删除 pos 处的元素
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator basic_string<CharType, CharTraits>::erase(const_iterator pos) {
    MYSTL_DEBUG(pos != end());
    iterator result = const_cast<iterator>(pos);
    char_traits::move(result, pos + 1, end() - pos - 1);
    --size_;
    return result;
}

// 删除 [first, last) 的元素
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator basic_string<CharType, CharTraits>::erase(const_iterator first, const_iterator last) {
    if (first == begin() && last == end()) {
        clear();
        return end();
    }
    const size_type n = end() - last;
    iterator result = const_cast<iterator>(first);
    char_traits::move(result, last, n);
    size_ -= (last - first);
    return result;
}

// 重置容器大小
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::resize(size_type count, value_type value) {
    if (count < size_) {
        erase(buffer_ + count, buffer_ + size_);
    }
    else {
        append(count - size_, value);
    }
}

// 比较两个 basic_string，小于返回 -1，大于返回 1，等于返回 0
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::compare(const basic_string& other) const {
    return compare_cstr(buffer_, size_, other.buffer_, other.size_);
}

// 从 pos1 下标开始的 count1 个字符跟另一个 basic_string 比较
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::compare(size_type pos1, size_type count1, const basic_string& other) const {
    auto n1 = mystl::min(count1, size_ - pos1);
    return compare_cstr(buffer_ + pos1, n1, other.buffer_, other.size_);
}











}

#endif // MINITURE_STL_BASIC_STRING_H_

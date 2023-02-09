#ifndef MINITURE_STL_DEQUE_HPP_
#define MINITURE_STL_DEQUE_HPP_

// 这个头文件包含了一个模板类 deque
// deque: 双端队列

#include <initializer_list>

#include "../02_iterators/iterator.h"
#include "../01_allocators/memory.h"
#include "../01_allocators/util.h"
#include "../00_utils/exceptdef.h"

namespace mystl {

const int DequeInitSize = 8;

template <typename Type>
struct deque_buf_size {
    static constexpr size_t value = sizeof(Type) < 256 ? 4096 / sizeof(Type) : 16;
};

// deque 的迭代器设计
template <class Type, class Ref, class Ptr>
struct deque_iterator : public iterator<mystl::random_access_iterator_tag, Type> {
    typedef deque_iterator<Type, Type&, Type*>                  iterator;
    typedef deque_iterator<Type, const Type&, const Type*>      const_iterator;
    typedef deque_iterator                                      self;

    typedef Type            value_type;
    typedef Ptr             pointer;
    typedef Ref             reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;
    typedef Type*           value_pointer;
    typedef Type**          map_pointer;

    static const size_type buffer_size = deque_buf_size<Type>::value;

    // 迭代器所含成员数据
    value_pointer cur;    // 指向所在缓冲区的当前元素
    value_pointer first;  // 指向所在缓冲区的头部
    value_pointer last;   // 指向所在缓冲区的尾部
    map_pointer   node;   // 缓冲区所在节点

    // 构造、复制、移动函数
    deque_iterator() : cur(nullptr), first(nullptr), last(nullptr), node(nullptr) {}
    deque_iterator(value_pointer v, map_pointer n) : cur(v), first(*n), last(*n + buffer_size), node(n) {}
    deque_iterator(iterator& rhs) : cur(rhs.cur), first(rhs.first), last(rhs.last), node(rhs.node) {}
    deque_iterator(const_iterator& rhs) : cur(rhs.cur), first(rhs.first), last(rhs.last), node(rhs.node) {}
    deque_iterator(iterator&& rhs) : cur(rhs.cur), first(rhs.first), last(rhs.last), node(rhs.node) {
        rhs.cur = nullptr;
        rhs.first = nullptr;
        rhs.last = nullptr;
        rhs.node = nullptr;
    }

    // 转到另一个缓冲区
    void set_node(map_pointer new_node) {
        node = new_node;
        first = *new_node;
        last = first + buffer_size;
    }

    // 重载运算符
    self&           operator=(const iterator& rhs) {
        if (this != &rhs) {
            cur = rhs.cur;
            first = rhs.first;
            last = rhs.last;
            node = rhs.node;
        }
        return *this;
    }
    reference       operator*() const {return *cur;}
    pointer         operator->() const {return cur;}
    difference_type operator-(const self& rhs) const {
        return static_cast<difference_type>(buffer_size) * (node - rhs.node) + (cur - first) - (rhs.cur - rhs.first);
    }

    self&           operator++() {
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }

    self&           operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self&           operator--() {
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        cur--;
        return cur;
    }

    self&           operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }

    self&           operator+=(difference_type n) {
        const auto offset = n + (cur - first);
        if (offset >= 0 && offset < static_cast<difference_type>(buffer_size)) {
            // 还在当前的缓冲区
            cur += n;
        }
        else {
            // 当前缓冲区已经无法装下 n 个元素了
            const auto node_offset = offset > 0 ? offset / static_cast<difference_type>(buffer_size) : -static_cast<difference_type>((-offset - 1) / buffer_size) - 1;
            set_node(node + node_offset);
            cur = first + (offset - node_offset * static_cast<difference_type>(buffer_size));
        }
        return *this;
    }

    self&           operator+(difference_type n) const {
        self tmp = *this;
        return tmp += n;
    }

    self&           operator-=(difference_type n) {
        return *this += -n;
    }

    self&           operator-=(difference_type n) const {
        self tmp = *this;
        return tmp -= n;
    }

    reference       operator[](difference_type n) const {
        return *(*this + n);
    }

    // 重载比较操作符
    bool operator==(const self& rhs) const {return cur == rhs.cur;}
    bool operator< (const self& rhs) const {
        return node == rhs.node ? (cur < rhs.cur) : (node < rhs.node);
    }
    bool operator!=(const self& rhs) const {return !(*this == rhs);}
    bool operator> (const self& rhs) const {return rhs < *this;}
    bool operator<=(const self& rhs) const {return !(rhs < *this);}
    bool operator>=(const self& rhs) const {return !(rhs > *this);}
};

// 模板类 deque
// 模板参数代表数据类型
template <class Type>
class deque {
public:
    // deque 的型别定义
    typedef mystl::allocator<Type>                      allocator_type;
    typedef mystl::allocator<Type>                      data_allocator;
    typedef mystl::allocator<Type>                      map_allocator;

    typedef typename allocator_type::value_type         value_type;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::size_type          size_type;
    typedef typename allocator_type::difference_type    difference_type;
    typedef pointer*                                    map_pointer;
    typedef const_pointer*                              const_map_pointer;
    
    typedef deque_iterator<Type, Type&, Type*>               iterator;
    typedef deque_iterator<Type, const Type&, const Type*>   const_iterator;
    typedef mystl::reverse_iterator<iterator>                reverse_iterator;
    typedef mystl::reverse_iterator<const_iterator>          const_reverse_iterator;

    allocator_type get_allocator() {return allocator_type();}

    static const size_type buffer_size = deque_buf_size<Type>::value;

private:
    
};

}  // end namespace mystl




#endif // MINITURE_STL_DEQUE_HPP_
#define MINITURE_STL_DEQUE_HPP_end MINITURE_STL_DEQUE_HPP_

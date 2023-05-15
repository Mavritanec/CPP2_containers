#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <initializer_list>
#include <stdexcept>

#include "iterators/vector_iterator.h"

namespace s21 {
template <typename T, class Allocator = std::allocator<T>>
class Vector {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using reference = value_type &;
    using pointer = value_type *;
    using const_reference = const value_type &;
    using iterator = VectorIterator<value_type>;
    using const_iterator = ConstVectorIterator<value_type>;
    using size_type = size_t;

private:
    size_type size_;
    size_type capacity_;
    pointer arr_;
    allocator_type allocator_;

public:
    // FUNCTIONS
    Vector(const allocator_type &Alloc = allocator_type()) noexcept(noexcept(Allocator()))
        : size_(0), capacity_(0), arr_(nullptr), allocator_(Alloc) {}

    Vector(size_type init_size, const value_type &val = value_type(),
           const allocator_type &Alloc = allocator_type())
        : size_(init_size), capacity_(init_size), allocator_(Alloc) {
        arr_ = allocator_.allocate(init_size);
        for (size_type i = 0; i < size_; ++i) {
            allocator_.construct(arr_ + i, val);
        }
    }

    Vector(std::initializer_list<value_type> const &items) : Vector(items.size()) {
        std::copy(items.begin(), items.end(), arr_);
    }

    Vector(const Vector &other) noexcept : Vector(other.size_) {
        std::copy(other.arr_, other.arr_ + other.size_, arr_);
    }

    Vector(Vector &&other) noexcept : size_(other.size_), capacity_(other.capacity_), arr_(other.arr_) {
        other.arr_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~Vector() { remove_vector_(); }

    Vector &operator=(const Vector &other) {
        if (&other != this) {
            remove_vector_();
            arr_ = allocator_.allocate(other.size_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            std::copy(other.arr_, other.arr_ + other.size_, arr_);
        }
        return *this;
    }

    Vector &operator=(Vector &&other) {
        remove_vector_();
        arr_ = other.arr_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.arr_ = nullptr;
        return *this;
    }

    // ELEMENT ACCESS
    reference at(size_type i) {
        if (i >= size_) {
            throw std::out_of_range("Out of range");
        }
        return arr_[i];
    }
    reference operator[](size_type i) { return arr_[i]; }
    reference front() { return arr_[0]; }
    reference back() { return arr_[size_ - 1]; }
    pointer data() noexcept { return arr_; }

    // ITERATORS
    iterator begin() noexcept { return iterator(arr_); }
    const_iterator cbegin() const noexcept { return const_iterator(arr_); }
    iterator end() noexcept { return iterator(arr_ + size_); }
    const_iterator cend() const noexcept { return const_iterator(arr_ + size_); }

    // CAPACITY
    bool empty() const noexcept { return size_ == 0; }
    size_type size() const noexcept { return size_; }
    size_type max_size() const noexcept { return allocator_.max_size(); }

    void reserve(size_type new_size) {
        if (new_size > max_size()) {
            throw std::length_error("vector::reserve");
        } else if (new_size >= size_) {
            T *newarr = allocator_.allocate(new_size);
            for (size_type i = 0; i < size_; ++i) {
                newarr[i] = std::move(arr_[i]);
                allocator_.destroy(arr_ + i);
            }
            allocator_.deallocate(arr_, capacity_);
            arr_ = newarr;
            capacity_ = new_size;
        }
    }
    size_type capacity() const noexcept { return capacity_; }

    void shrink_to_fit() {
        if (size_ != capacity_) reserve(size_);
    }

    // MODIFIERS
    void clear() noexcept {
        for (size_type i = 0; i < size_; ++i) {
            allocator_.destroy(arr_ + i);
        }
        size_ = 0;
    }

    iterator insert(iterator iter, const_reference value) {
        auto it_begin = begin();
        int pos = iter.base() - it_begin.base();
        if ((size_ + 1) > capacity_) {
            reserve(size_ == 0 ? 1 : capacity_ * 2);
        }
        size_++;
        if (iter.base() != nullptr) {
            for (int i = size_ - 1; i >= pos; i--) {
                if (i == 0)
                    arr_[i] = value_type();
                else
                    arr_[i] = arr_[i - 1];
            }
        }
        allocator_.construct(arr_ + pos, value);
        auto tmp = begin();
        tmp += pos;
        return tmp;
    }

    void erase(iterator iter) {
        auto it_begin = begin();
        size_type pos = iter.base() - it_begin.base();
        if (pos >= capacity_) {
            throw std::out_of_range("Out of range");
        }
        for (size_type i = pos; i <= size() - 1; i++) {
            arr_[i] = arr_[i + 1];
        }
        size_--;
        allocator_.destroy(iter.base());
    }

    void push_back(const_reference data) {
        if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        allocator_.construct(arr_ + size_++, data);
    }

    void pop_back() { allocator_.destroy(arr_ + --size_); }

    void swap(Vector<value_type> &other) {
        std::swap(arr_, other.arr_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
    }

    void resize(size_type new_size, const value_type &val = value_type()) {
        while (new_size < size_) {
            pop_back();
        }
        if (new_size > size_) {
            if (size_ <= capacity_) reserve(new_size);
            while (new_size > size_) {
                allocator_.construct(arr_ + size_++, val);
            }
        }
    }

    template <class... Args>
    iterator emplace(const_iterator pos, Args &&...args) {
        iterator iterator(const_cast<pointer>(pos.base()));
        return insert(iterator, value_type(std::forward<Args>(args)...));
    }

    template <class... Args>
    void emplace_back(Args &&...args) {
        push_back(value_type(std::forward<Args>(args)...));
    }

private:
    void remove_vector_() {
        if (arr_) {
            for (size_type i = 0; i < size_; i++) {
                allocator_.destroy(arr_ + i);
            }
            allocator_.deallocate(arr_, capacity_);
        }
        size_ = 0;
        capacity_ = 0;
    }
};

}  // namespace s21

#endif  //  SRC_S21_VECTOR_H_

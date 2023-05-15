#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <stddef.h>

#include <initializer_list>
#include <iostream>
#include <utility>

#include "iterators/tree_iterator.h"
#include "s21_compare.h"
#include "s21_tree_node.h"
#include "s21_vector.h"

constexpr bool left_side = false;
constexpr bool right_side = true;

namespace s21 {
template <typename Key, class Compare = s21::Compare<Key>>
class Set {
public:
    using key_type = Key;
    using reference = Key &;
    using const_reference = const Key &;
    using cmp_type = Compare;
    using iterator = TreeIterator<key_type, cmp_type>;
    using const_iterator = TreeConstIterator<key_type, cmp_type>;
    using size_type = size_t;
    using node_type = TreeNode<Key, cmp_type>;
    using node_pointer = TreeNode<Key, cmp_type> *;

protected:
    cmp_type comp_;
    node_pointer root_;
    node_pointer nill_ = new node_type();
    size_type size_ = 0;
    std::allocator<key_type> alloc_;

public:
    Set() : root_(nullptr) { ; }  // базовый конструктор

    Set(std::initializer_list<key_type> const &items) : Set() {  // конструктор с инициализацией
        for (auto it = items.begin(); it != items.end(); it++) insert(*it);
    }

    Set(const Set &other) : Set() {  // конструктор копирования
        copy_(other.root_, other.nill_);
    }

    Set(Set &&other) : Set() {  // конструктор перемещения
        delete nill_;
        root_ = other.root_;
        size_ = other.size_;
        nill_ = other.nill_;
        other.root_ = nullptr;
        other.nill_ = nullptr;
        other.size_ = 0;
    }

    ~Set() {  // деструктор
        if (size_ != 0) clear();
        if (nill_) delete nill_;
    }

    bool empty() const { return size_ == 0; }
    size_type size() const noexcept { return size_; }
    size_type max_size() const noexcept { return alloc_.max_size(); }
    std::pair<iterator, bool> insert(const key_type &value) {
        return empty() ? setUpFirstNode_(value) : setUpInternalNode_(value);
    }
    bool contains(const key_type &value) const {
        auto pair_res = containsPos_(value);
        return pair_res.second;
    }
    iterator begin() const {
        node_pointer begin_node = root_;
        if (size_ != 0) {
            while (begin_node->left_ != nill_) {
                begin_node = begin_node->left_;
                while (begin_node->right_ != nill_ && comp_.eq(begin_node->right_->key_, begin_node->key_))
                    begin_node = begin_node->right_;
            }
        } else {
            begin_node = nill_;
        }
        return iterator(begin_node);
    }
    const_iterator cbegin() const {
        node_pointer begin_node = root_;
        if (size_ != 0) {
            while (begin_node->left_ != nill_) {
                begin_node = begin_node->left_;
                while (begin_node->right_ != nill_ && comp_.eq(begin_node->right_->key_, begin_node->key_))
                    begin_node = begin_node->right_;
            }
        } else {
            begin_node = nill_;
        }
        return const_iterator(begin_node);
    }
    iterator end() const { return iterator(nill_); }
    const_iterator cend() const { return const_iterator(nill_); }
    void clear() {
        clearData_(this->root_);
        root_ = nullptr;
        size_ = 0;
    }
    void erase(iterator pos) {
        if (pos.base() == nill_) {
            throw std::exception();
        } else {
            deleteAnyTreeNode_(pos);
            delete pos.base();
        }
    }
    void swap(Set &other) {
        node_pointer tmp_root = other.root_;
        node_pointer tmp_nill = other.nill_;
        size_type tmp_size = other.size_;
        other.root_ = this->root_;
        other.nill_ = this->nill_;
        other.size_ = this->size_;
        this->root_ = tmp_root;
        this->nill_ = tmp_nill;
        this->size_ = tmp_size;
    }
    void merge(Set &other) { mergeCycle_(other.root_, other.nill_, other); }
    iterator find(const Key &value) {
        return containsPos_(value).second == true ? containsPos_(value).first : end();
    }
    void operator=(Set &&other) {
        clearData_(root_);
        delete nill_;
        root_ = other.root_;
        size_ = other.size_;
        nill_ = other.nill_;
        other.root_ = nullptr;
        other.nill_ = nullptr;
        other.size_ = 0;
    }
    template <class... Args>
    Vector<std::pair<iterator, bool>> emplace(Args &&...args) {
        Vector<std::pair<iterator, bool>> result;
        result.push_back(insert(key_type(std::forward<Args>(args)...)));
        return result;
    }
    // ========INTERNAL METHODS========
protected:
    std::pair<iterator, bool> setUpFirstNode_(const key_type &value) {
        node_pointer elem = new node_type(value, nullptr, nill_, nill_);
        root_ = elem;
        size_++;
        iterator insert_iter(elem);
        std::pair<iterator, bool> res_pair = {insert_iter, true};
        nill_->parent_ = root_;
        return res_pair;
    }
    std::pair<iterator, bool> setUpInternalNode_(const key_type &value) {
        bool result = true;
        node_pointer new_node;
        if (!this->contains(value)) {
            std::pair<node_pointer, bool> pair_deside = insertDesider_(value);
            // insertDesider_ возвращает ноду - родителя следующей
            // новой ноды, поэтому при создании новой ноды указываем родителя
            new_node = new node_type(value, pair_deside.first, nill_, nill_);
            if (pair_deside.second == right_side)
                pair_deside.first->right_ = new_node;
            else
                pair_deside.first->left_ = new_node;
            size_++;
        } else {
            new_node = containsPos_(value).first.base();
            result = false;
        }
        iterator res_it(new_node);
        std::pair<iterator, bool> result_pair = {res_it, result};
        nill_->parent_ = getMaxFrom_(root_);
        return result_pair;
    }
    std::pair<node_pointer, bool> insertDesider_(const key_type &value) {
        node_pointer target_node = root_;
        bool side = left_side;
        while (target_node->left_ && target_node->right_) {
            if (comp_.ge(value, target_node->key_)) {
                side = right_side;
                if (target_node->right_ == nill_) break;
                target_node = target_node->right_;
            } else {
                side = left_side;
                if (target_node->left_ == nill_) break;
                target_node = target_node->left_;
            }
        }
        std::pair<node_pointer, bool> pair_result = {target_node, side};
        return pair_result;
    }
    bool insertTreeNode_(node_pointer other_node, Set &other) {
        bool result = true;
        if (!this->contains(other_node->key_)) {
            if (root_ != nullptr) {
                std::pair<node_pointer, bool> pair_deside = insertDesider_(other_node->key_);
                iterator it(other_node);
                other.deleteAnyTreeNode_(it);
                if (pair_deside.second == right_side)
                    pair_deside.first->right_ = other_node;
                else
                    pair_deside.first->left_ = other_node;
                other_node->left_ = nill_;
                other_node->right_ = nill_;
                other_node->parent_ = pair_deside.first;
            } else {
                iterator it(other_node);
                other.deleteAnyTreeNode_(it);
                root_ = other_node;
                root_->left_ = nill_;
                root_->right_ = nill_;
            }
            size_++;
            nill_->parent_ = getMaxFrom_(root_);
        } else {
            result = false;
        }
        return result;
    }
    void clearData_(node_pointer node) {
        if (node != nill_ && node != nullptr) {
            if (node->left_ != nill_) clearData_(node->left_);
            if (node->right_ != nill_) clearData_(node->right_);
            delete node;
        }
    }
    std::pair<iterator, bool> containsPos_(const key_type &value) const {
        bool result = false;
        node_pointer node = root_;
        while (node && node != nill_) {
            if (comp_.lt(value, node->key_)) {
                node = node->left_;
            } else if (comp_.gt(value, node->key_)) {
                node = node->right_;
            } else if (comp_.eq(value, node->key_)) {
                result = true;
                break;
            }
        }
        auto res_iter(node);
        std::pair<iterator, bool> contain_res = {res_iter, result};
        return contain_res;
    }
    void copy_(node_pointer node, node_pointer nill) {
        if (node != nullptr && node != nill) {
            if (node->left_ != nill) copy_(node->left_, nill);
            if (node->right_ != nill) copy_(node->right_, nill);
            insert(node->key_);
        }
    }
    void deleteAnyTreeNode_(iterator &pos) {
        if (pos.base()->left_ == nill_ &&
            pos.base()->right_ == nill_) {  // if TreeNode does not have any child
            // delete empty TreeNode method
            deleteChildlessTreeNode_(pos);
        } else if (pos.base()->left_ != nill_ &&
                   pos.base()->right_ == nill_) {  // if TreeNode has only left child
            // delete leftonly TreeNode method
            deleteOneChildTreeNode_(pos, left_side);  // side = left_side
        } else if (pos.base()->right_ != nill_ &&
                   pos.base()->left_ == nill_) {  // if TreeNode has only right child
            // delete rightonly TreeNode method
            deleteOneChildTreeNode_(pos, right_side);
        } else {  // if TreeNode has both children
            // delete both TreeNode method
            deleteBothChildrenTreeNode_(pos);
        }
        size_--;
        nill_->parent_ = getMaxFrom_(root_);
    }
    void deleteChildlessTreeNode_(iterator &pos) {
        if (pos.base() != root_) {
            if (comp_.eq(pos.base()->parent_->right_->key_, pos.base()->key_))
                pos.base()->parent_->right_ = nill_;
            else
                pos.base()->parent_->left_ = nill_;
        }
    }
    void deleteOneChildTreeNode_(iterator &pos, bool side) {
        if (pos.base() != root_) {
            if (comp_.eq(pos.base()->parent_->right_->key_, pos.base()->key_))
                pos.base()->parent_->right_ = side == left_side ? pos.base()->left_ : pos.base()->right_;
            else
                pos.base()->parent_->left_ = side == left_side ? pos.base()->left_ : pos.base()->right_;
        } else {
            root_ = side == left_side ? root_->left_ : root_->right_;
            root_->parent_ = nullptr;
        }
    }
    void deleteBothChildrenTreeNode_(iterator &pos) {
        node_pointer min_right_node = getMinFrom_(pos.base()->right_);
        Key value = min_right_node->key_;
        erase(min_right_node);
        size_++;
        node_pointer new_node = new node_type(value, pos.base() == root_ ? nullptr : pos.base()->parent_,
                                              pos.base()->left_, pos.base()->right_);
        if (pos.base()->parent_->left_ == pos.base())
            pos.base()->parent_->left_ = new_node;
        else
            pos.base()->parent_->right_ = new_node;
    }
    node_pointer getMinFrom_(node_pointer start) {
        node_pointer begin_node = start;
        while (begin_node->left_ != nill_) {
            begin_node = begin_node->left_;
            while (begin_node->right_ != nill_ && comp_.ge(begin_node->key_, begin_node->right_->key_))
                begin_node = begin_node->right_;
        }
        return begin_node;
    }
    node_pointer getMaxFrom_(node_pointer start) {
        node_pointer begin_node = start;
        while (begin_node->right_ != nill_) {
            begin_node = begin_node->right_;
            while (begin_node->left_ != nill_ && comp_.le(begin_node->key_, begin_node->left_->key_))
                begin_node = begin_node->left_;
        }
        return begin_node;
    }
    void mergeCycle_(node_pointer current_node, node_pointer nill, Set &other) {
        if (current_node != nill && current_node != nullptr) {
            if (current_node->left_ != nill) mergeCycle_(current_node->left_, nill, other);
            if (current_node->right_ != nill) mergeCycle_(current_node->right_, nill, other);
            insertTreeNode_(current_node, other);
        }
    }
};  // class Set
}  // namespace s21
#endif  // SRC_S21_SET_H_
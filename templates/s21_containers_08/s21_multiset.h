#ifndef SRC_S21_MULTIISET_H_
#define SRC_S21_MULTIISET_H_

#include <stddef.h>

#include <initializer_list>
#include <utility>

#include "s21_compare.h"
#include "s21_set.h"

namespace s21 {
template <class Key, class Compare = Compare<Key>>
class Multiset : public Set<Key, Compare> {
protected:
    std::allocator<Set<Key, Compare>> alloc_;

public:
    using cmp_type = Compare;
    using key_type = Key;
    using value_type = key_type;
    using reference = value_type &;
    using const_reference = const value_type &;
    using node_type = TreeNode<Key, cmp_type>;
    using node_pointer = typename Set<value_type, cmp_type>::node_pointer;
    using iterator = TreeIterator<value_type, cmp_type>;
    using size_type = size_t;
public:
    Multiset() : Set<key_type, cmp_type>() { ; }
    Multiset(std::initializer_list<key_type> const &items) : Set<key_type, cmp_type>() {
        for (auto it = items.begin(); it != items.end(); it++) insert(*it);
    }
    Multiset(const Multiset &other) : Set<key_type, cmp_type>() {
        for (auto it = other.begin(); it != other.end(); it++) insert(*it);
    }
    Multiset(Multiset &&other) : Set<key_type, cmp_type>() {
        delete this->nill_;
        this->root_ = other.root_;
        this->size_ = other.size_;
        this->nill_ = other.nill_;
        other.root_ = nullptr;
        other.nill_ = nullptr;
        other.size_ = 0;
    }
    ~Multiset() { ; }
    size_type max_size() { return alloc_.max_size(); }
    void operator=(Multiset &&other) {
        Set<value_type, cmp_type>::clearData_(this->root_);
        delete this->nill_;
        this->root_ = other.root_;
        this->size_ = other.size_;
        this->nill_ = other.nill_;
        other.root_ = nullptr;
        other.nill_ = nullptr;
        other.size_ = 0;
    }
    iterator insert(const value_type &value) {
        return this->empty() ? Set<value_type, cmp_type>::setUpFirstNode_(value).first
                             : setUpInternalNode_(value);
    }
    void merge(Multiset &other) { mergeCycle_(other.root_, other.nill_, other); }
    size_type count(const value_type &key) {
        size_type result = 0;
        for (auto it = this->find(key); this->comp_.eq(*it, key) && it != this->end(); it++) result++;
        return result;
    }
    std::pair<iterator, iterator> equal_range(const value_type &key) {
        auto it_begin = this->find(key);
        auto it_end = it_begin;
        for (; this->comp_.eq(*it_end, key) && it_end != this->end(); it_end++) {
            ;
        }
        std::pair<iterator, iterator> res_pair = {it_begin, it_end};
        return res_pair;
    }
    iterator lower_bound(const value_type &key) {
        auto result_it = this->begin();
        for (; this->comp_.lt(*result_it, key) && result_it != this->end(); result_it++) {
            ;
        }
        return result_it;
    }
    iterator upper_bound(const value_type &key) {
        auto result_it = this->begin();
        for (; this->comp_.le(*result_it, key) && result_it != this->end(); result_it++) {
            if (result_it == this->end()) break;
        }
        return result_it;
    }

protected:
    iterator setUpInternalNode_(const key_type &value) {
        node_pointer new_node;
        std::pair<node_pointer, bool> pair_deside = this->insertDesider_(value);
        new_node = new node_type(value, pair_deside.first, this->nill_, this->nill_);
        if (pair_deside.second == right_side)
            pair_deside.first->right_ = new_node;
        else
            pair_deside.first->left_ = new_node;
        this->size_++;
        iterator res_it(new_node);
        return res_it;
    }
    void mergeCycle_(node_pointer current_node, node_pointer nill, Multiset &other) {
        if (current_node != nullptr && current_node != nill) {
            if (current_node->left_ != nill) mergeCycle_(current_node->left_, nill, other);
            if (current_node->right_ != nill) mergeCycle_(current_node->right_, nill, other);
            insertTreeNode_(current_node, other);
        }
    }
    bool insertTreeNode_(node_pointer other_node, Multiset &other) {
        bool result = true;
        if (this->root_ != nullptr) {
            std::pair<node_pointer, bool> pair_deside = this->insertDesider_(other_node->key_);  // 4 left
            iterator it(other_node);
            other.deleteAnyTreeNode_(it);
            if (pair_deside.second == right_side)
                pair_deside.first->right_ = other_node;
            else
                pair_deside.first->left_ = other_node;
            other_node->left_ = this->nill_;
            other_node->right_ = this->nill_;
            other_node->parent_ = pair_deside.first;
        } else {
            iterator it(other_node);
            other.deleteAnyTreeNode_(it);
            this->root_ = other_node;
            this->root_->left_ = this->nill_;
            this->root_->right_ = this->nill_;
        }
        this->size_++;
        this->nill_->parent_ = this->getMaxFrom_(this->root_);
        return result;
    }
};  // class Multiset
}  // namespace s21
#endif  // SRC_S21_MULTIISET_H_
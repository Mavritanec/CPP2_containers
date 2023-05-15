#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_
#include <stddef.h>

#include <utility>

#include "s21_pair_compare.h"
#include "s21_set.h"

namespace s21 {
template <class Key, class T, class Compare = PairCompare<Key, T>>
class Map : public Set<std::pair<Key, T>, PairCompare<Key, T>> {
public:
    using mapped_type = T;
    using key_type = Key;
    using value_type = std::pair<key_type, mapped_type>;
    using cmp_type = Compare;
    using iterator = TreeIterator<value_type, cmp_type>;
    using node_type = TreeNode<Key, cmp_type>;
    using node_pointer = typename Set<value_type, cmp_type>::node_pointer;

public:
    // базовый конструктор
    Map() : Set<value_type, cmp_type>() { ; }
    // конструктор с инициализацией
    Map(std::initializer_list<value_type> const &items) : Set<value_type, cmp_type>(items) { ; }
    // конструктор копирования
    Map(const Map &other) : Set<value_type, cmp_type>(other) { ; }
    // конструктор перемещения
    Map(Map &&other) : Set<value_type, cmp_type>() {
        delete this->nill_;
        this->root_ = other.root_;
        this->size_ = other.size_;
        this->nill_ = other.nill_;
        other.root_ = nullptr;
        other.nill_ = nullptr;
        other.size_ = 0;
    }
    void operator=(Map &&other) {
        Set<value_type, cmp_type>::clearData_(this->root_);
        delete this->nill_;
        this->root_ = other.root_;
        this->size_ = other.size_;
        this->nill_ = other.nill_;
        other.root_ = nullptr;
        other.nill_ = nullptr;
        other.size_ = 0;
    }
    // деструктор
    ~Map() { ; }
    // доступ к элементу по ключу
    mapped_type &at(const key_type &key) {
        auto result = containsRef_(key);
        if (result.second == false) throw std::out_of_range("There is no pair with such key");
        return result.first;
    }
    // доступ к элементу по ключу (без исключений)
    mapped_type &operator[](const key_type &key) {
        try {
            return at(key);
        } catch (...) {
            Set<value_type, cmp_type>::insert({key, mapped_type()});
            return at(key);
        }
    }
    // вставка по паре
    std::pair<iterator, bool> insert(const value_type &value) {
        return Set<value_type, cmp_type>::insert({value.first, value.second});
    }
    // вставка по ключу и значению
    std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj) {
        return Set<value_type, cmp_type>::insert({key, obj});
    }
    // вставка или присваивание по ключу и значению
    std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
        auto pair = Set<value_type, cmp_type>::insert({key, obj});
        if (pair.second == false) at(key) = obj;
        return pair;
    }
    template <class... Args>
    Vector<std::pair<iterator, bool>> emplace(Args &&...args) {
        Vector<std::pair<iterator, bool>> result;
        result.push_back(insert(std::forward<Args>(args)...));
        return result;
    }
    // проверяет что в контейнере содержится пара с таким ключом
    bool contains(const Key &key) { return containsRef_(key).second; }

protected:
    std::pair<mapped_type &, bool> containsRef_(const key_type &key) {
        value_type pair_for_find = {key, mapped_type()};
        bool result = false;
        node_pointer node = this->root_;
        while (node && node != this->nill_) {
            if (Set<value_type, cmp_type>::comp_.lt(pair_for_find, node->key_)) {
                node = node->left_;
            } else if (Set<value_type, cmp_type>::comp_.gt(pair_for_find, node->key_)) {
                node = node->right_;
            } else if (Set<value_type, cmp_type>::comp_.eq(pair_for_find, node->key_)) {
                result = true;
                break;
            }
        }
        std::pair<mapped_type &, bool> pair_res = {node->key_.second, result};
        return pair_res;
    }
};  // class Map
}  // namespace s21
#endif  // SRC_S21_MAP_H_
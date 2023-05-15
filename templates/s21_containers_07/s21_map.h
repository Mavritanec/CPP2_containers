#ifndef S21_MAP_H_
#define S21_MAP_H_

#include "s21_set.h"

namespace s21 {
template <typename Key, typename T>
class map : public s21::set<std::pair<Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<Key, T>;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename set<value_type>::SetIterator;
  using const_iterator = typename set<value_type>::SetConstIterator;
  using Node = typename set<std::pair<Key, T>>::Node;

  map();
  explicit map(std::initializer_list<value_type> const &items);
  map(const map &ms);
  map(map &&ms);

  map operator=(map &&ms);
  map operator=(const map &ms);
  mapped_type &operator[](const key_type &&key);

  mapped_type &at(const Key &key);
  iterator find(const key_type &key);
  bool contains(const key_type &key);

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key,
                                             const mapped_type &obj);

  void merge(map &other);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args) {
    std::initializer_list<value_type> items{args...};
    std::pair<iterator, bool> result;
    for (auto it = items.begin(); it != items.end(); ++it) {
      result = insert(it->first, it->second);
    }
    return result;
  }

 protected:
  key_type get_key(value_type value) { return value.first; }
  virtual bool isLess(std::pair<Key, T> value1,
                      std::pair<Key, T> value2) override;
  virtual bool isInsert(std::pair<Key, T> value1,
                        std::pair<Key, T> value2) override;
};

}  // namespace s21
#include "s21_map.tpp"

#endif  // S21_MAP_H_
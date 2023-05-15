#include "s21_map.h"
namespace s21 {
template <class key_type, class mapped_type, class Compare>
typename map<key_type, mapped_type, Compare>::mapped_type &
map<key_type, mapped_type, Compare>::at(const key_type &key) {
  iterator tmp = this->begin();
  if (tmp.get_data() == tmp.get_nil()) {
    throw std::out_of_range("Camone man");
  }
  for (; tmp != this->end(); ++tmp) {
    if (tmp->first == key) return tmp->second;
  }
  return tmp->second;
}

template <class key_type, class mapped_type, class Compare>
typename map<key_type, mapped_type, Compare>::mapped_type &
map<key_type, mapped_type, Compare>::operator[](const key_type &key) {
  iterator tmp = this->begin();
  for (; tmp != end(); ++tmp)
    if (tmp->first == key) return tmp->second;
  return tmp->second;
}

template <class key_type, class mapped_type, class Compare>
std::pair<typename map<key_type, mapped_type, Compare>::iterator, bool>
map<key_type, mapped_type, Compare>::insert(const value_type &value) {
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i->first == value.first) {
      return (std::make_pair(this->c.end(), false));
    }
  }
  auto pair_set = c.insert(value);
  iterator iter(pair_set.first);
  return std::make_pair(iter, pair_set.second);
}

template <class key_type, class mapped_type, class Compare>
std::pair<typename map<key_type, mapped_type, Compare>::iterator, bool>
map<key_type, mapped_type, Compare>::insert(const key_type &key,
                                            const mapped_type &obj) {
  return this->insert({key, obj});
}

template <class key_type, class mapped_type, class Compare>
std::pair<typename map<key_type, mapped_type, Compare>::iterator, bool>
map<key_type, mapped_type, Compare>::insert_or_assign(const key_type &key,
                                                      const mapped_type &obj) {
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i->first == key) {
      i->second = obj;
    }
  }
  auto pair_set = c.insert(std::make_pair(key, obj));
  iterator iter(pair_set.first);
  return std::make_pair(iter, pair_set.second);
}

template <class key_type, class mapped_type, class Compare>
void map<key_type, mapped_type, Compare>::merge(map &other) {
  iterator iter = other.begin();
  while (iter != other.end()) {
    if (this->insert(*iter).second) {
      other.erase(iter);
    }
    iter++;
  }
}

template <class key_type, class mapped_type, class Compare>
bool map<key_type, mapped_type, Compare>::contains(const key_type &key) {
  for (const_iterator i = this->begin(); i != this->end(); ++i) {
    if (i->first == key) return true;
  }
  return false;
}

}  // namespace s21
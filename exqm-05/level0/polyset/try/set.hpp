#pragma once

#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

class set 
{
private:
    searchable_bag& _bag;
public:
  set() = delete;
  set(const set &) = delete;
  set  &operator=(const set &) = delete;
  set(searchable_bag& bag);
  ~set();

  void insert(int nbr);
  void insert(int *array, int size);
  void print() const;
  void clear();
  bool has(int nbr) const;
  const searchable_bag& get_bag();
};
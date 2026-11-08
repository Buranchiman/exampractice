#pragma once

#include "tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

class set
{
 private:
	searchable_bag &bag;
 public:
	set() = delete;
	set(searchable_bag &search_bag);
	set(const set &other) = delete;
	set &operator=(const set &other) = delete;
	~set();

	searchable_bag& get_bag() const;
	bool has(int target) const;
  	void insert(int nbr);
  	void insert(int *array, int size);
  	void print() const;
  	void clear();
};

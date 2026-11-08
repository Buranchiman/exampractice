#include "set.hpp"

set::set(searchable_bag &search_bag) : bag(search_bag){}

bool set::has(int target) const
{
	return (bag.has(target));
}

void set::insert(int nbr)
{
	if (!bag.has(nbr))
		bag.insert(nbr);
}

void set::insert(int *array, int size)
{
	for (int i = 0; i < size; i++)
		bag.insert(array[i]);
}
void set::print() const
{
	bag.print();
}
void set::clear()
{
	bag.clear();
}

set::~set(){}

searchable_bag& set::get_bag() const
{
	return (bag);
}

#include "set.hpp"

set::set(searchable_bag& bag) : _bag(bag) {}

void set::insert(int nbr)
{
    if (!_bag.has(nbr))
        _bag.insert(nbr);
}

void set::insert(int *array, int size)
{
    for (int i =0; i< size; i++)
        insert(array[i]); 
}
void set::print() const
{
    _bag.print();
}

void set::clear()
{
    _bag.clear();
}
bool set::has(int nbr) const
{
    return(_bag.has(nbr));
}

const searchable_bag& set::get_bag()
{
    return (_bag);
}

set::~set() {}
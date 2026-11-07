#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other) : tree_bag(other) {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag &other) 
{
    if (this != &other)
        tree_bag::operator=(other);
    return (*this);
}

searchable_tree_bag::~searchable_tree_bag() {}

bool searchable_tree_bag::search(node *node, int nbr) const
{
    if (!node)
        return (false);
    if (node->value == nbr)
        return (true);
    if (search(node->l, nbr) == true)
        return (true);
    if (search(node->r, nbr) == true)
        return (true);
    return (false);
}

bool searchable_tree_bag::has(int nbr) const
{
    
    return (search(tree, nbr));
}
#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{
}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other) : tree_bag(other)
{
}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag &other)
{
	if (this != &other)
		tree_bag::operator=(other);
	return *this;
}
searchable_tree_bag::~searchable_tree_bag(){}

bool searchable_tree_bag::search(node *node, const int value) const
{
	if (!node)
		return (false);
	if (node->value == value)
		return (true);
	if (node->l && search(node->l, value) == true)
		return (true);
	if (node->r && search(node->r, value) == true)
		return (true);
	return (false);
}

bool searchable_tree_bag::has(int target) const
{
	return (search(tree, target));
}

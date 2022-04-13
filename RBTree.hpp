
#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "reverse_iterator.h"
#include "tree_iterator.hpp"
#include "utility.hpp"

template<class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> >
class RBTree
{
	typedef Value 													value_type;
	typedef Compare 												value_compare;
	typedef Alloc													allocator_type;
	typedef typename Alloc::template rebind<Node<Value> >::other 	node_allocator;
	typedef	typename node_allocator::pointer						node_pointer;
	typedef typename allocator_type::reference 						reference;
	typedef typename allocator_type::const_reference 				const_reference;
	typedef typename allocator_type::pointer 						pointer;
	typedef typename allocator_type::const_pointer 					const_pointer;
	typedef std::ptrdiff_t											difference_type;
	typedef std::size_t												size_type;
	typedef TreeIter<Value>											iterator;
	typedef TreeIter<const Value>									const_iterator;
	typedef	ft::reverse_iterator<iterator> 							reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator> 					const_reverse_iterator;

private:
	allocator_type				_val_alloc;
	node_allocator				_node_alloc;
	value_compare 				_compare;
	node_pointer				_nil;
	node_pointer				_header;
	node_pointer				_root;
	size_type					_size;

	node_pointer tree_min(node_pointer n) const
	{
		while (n->left != NULL && !n->left->is_nil)
			n = n->left;
		return n;
	}

	node_pointer tree_max(node_pointer n) const
	{
		while (!n->right->is_nil)
			n = n->right;
		return n;
	}

	void rotate_right (node_pointer node) const
	{
		node_pointer tmp = node->left;
		node->left = tmp->right;
		if (!is_nil(tmp->right))
			tmp->right->parent = node;
		tmp->parent = node->parent;
		if (node->parent == NULL)
			_root = tmp;
		else if (node == node->parent->left)
			node->parent->left = tmp;
		else
			node->parent->right = tmp;
		tmp->right = node;
		node->parent = tmp;
	}

	void rotate_left (node_pointer node) const
	{
		node_pointer tmp = node->right;
		node->right = tmp->left;
		if (!is_nil(tmp->left))
			tmp->left->parent = node;
		tmp->parent = node->parent;
		if (node->parent == NULL)
			_root = tmp;
		else if (node == node->parent->left)
			node->parent->left = tmp;
		node->parent->right = tmp;
		tmp->left = node;
		node->parent = tmp;
	}

	node_pointer _insert(node_pointer new_node)
	{
		if (_root == _header)
			_root = new_node;
		else
			_insert_to_node(_root, new_node);
		return new_node;
	}
	node_pointer	_insert_to_node(node_pointer root, node_pointer new_node)
	{
		if (_compare(*new_node->value, *root->value))
		{
			if (!is_nil(root->left))
				return (_insert_to_node(root->left, new_node));
			root->left = new_node;
		} else
		{
			if (!is_nil(root->right))
				return (_insert_to_node(root->right, new_node));
			root->right = new_node;
		}
		new_node->parent = root;
		return (new_node);
	}

	node_pointer _insert_into_tree
};

#endif

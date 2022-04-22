
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
		}
		else
		{
			if (!is_nil(root->right))
				return (_insert_to_node(root->right, new_node));
			root->right = new_node;
		}
		new_node->parent = root;
		return (new_node);
	}

	node_pointer _insert_into_tree(node_pointer new_node, node_pointer where)
	{
		if (_root == _header)
			_root = new_node;
		else
			_insert_to_node(where, new_node);
		return (new_node);
	}

	void _insert_fixup(node_pointer node)
	{
		if (node != _root && node->parent != _root){
			while (node != _root && !node->parent->is_black){
				if (node->parent == node->parent->parent->left){
					node_pointer uncle = node->parent->parent->right;
					if (!uncle->is_black){
						node->parent->is_black = true;
						uncle->is_black = true;
						node->parent->parent->is_black = false;
						node = node->parent->parent;
					}
					else {
						if (node == node->parent->right){
							node = node->parent;
							_rotate_left(node);
						}
						node->parent->is_black = true;
						node->parent->parent->is_black = false;
						_rotate_right(node->parent->parent);
					}
				}
				else{
					node_pointer uncle = node->parent->parent->left;
					if (!uncle->is_black){
						node->parent->is_black = true;
						uncle->is_black = true;
						node->parent->parent->is_black = false;
						node = node->parent->parent;
					}
					else{
						if (node == node->parent->left){
							node = node->parent;
							_rotate_right(node);
						}
						node->parent->is_black = true;
						node->parent->parent->is_black = false;
						_rotate_left(node->parent->parent);
					}
				}
			}
		}
		_root->is_black = true;
	}

	bool is_nil(node_pointer node) const
	{
		return node == _nil || node == _header;
	}

	void clear_node(node_pointer node)
	{
		if (node && !is_nil(node))
		{
			clear_node(node->right);
			clear_node(node->left);
			_val_alloc.destroy(node->value, 1);
			_val_alloc.deallocate(node->value, 1);
			_node_alloc.deallocate(node, 1);
		}
	}

	void	init_nil_head()
	{
		_nil = _node_alloc.allocate(1);
		_node_alloc.construct(_nil, Node<Value>());
		_nil->is_black = true;
		_nil->is_nil = true;
		_header = _node_alloc.allocate(1);
		_node_alloc.construct(_header, Node<Value>());
		_header->value = _val_alloc.allocate(1);
		_val_alloc.construct(_header->value, Value());
		_header->is_black = true;
	}

	void transplant(node_pointer where, node_pointer what)
	{
		if (where == _root)
			_root = what;
		else if (where == where->parent->left)
			where->parent->left = what;
		else
			where->parent->right = what;
		what->parent = where->parent;
	}

	void free_node(node_pointer node)
	{
		_val_alloc.destroy(node->value);
		_val_alloc.deallocate(node->value, 1);
		_node_alloc.deallocate(node, 1);
	}

public:
	iterator end()
	{
		return (iterator(_header));
	}

	const_iterator end() const
	{
		return const_iterator(_header);
	}

	iterator begin()
	{
		(iterator(_size == 0 ? _header : iterator(tree_min(_root))));
	}

	const_iterator begin() const
	{
		return(const_iterator(_size == 0 ? _header : const_iterator(tree_min(_root))));
	}

	reverse_iterator rbegin()
	{
		return (reverse_iterator(end()));
	}

	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(end()));
	}

	reverse_iterator rend()
	{
		return (reverse_iterator(begin()));
	}

	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(begin()));
	}

	pointer create_value(const value_type &value)
	{
		pointer new_val = _val_alloc.allocate(1);
		_val_alloc.construct(new_val, value);
		return (new_val);
	}

	node_pointer copy_node(node_pointer other)
	{
		node_pointer new_node = _node_alloc.allocate(1);
		_node_alloc.construct(new_node, Node<Value>());
		new_node->is_black = other->is_black;
		new_node->is_nil = other->is_nil;
		if (other->value){
			new_node->value = _val_alloc.allocate(1);
			_val_alloc.construct(new_node->value, *other->value);
		}
		return (new_node);
	}


};

#endif

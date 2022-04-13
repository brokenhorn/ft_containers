
#include "utility.hpp"
#ifndef TREE_ITERATOR_HPP
#define ITERATOR_HPP

template<class Value>
struct Node
{
public:
	bool 	is_nil;
	bool 	is_black;
	Value 	*value;
	Node 	*right;
	Node 	*left;
	Node 	*parent;

	explicit Node(Value val = 0): value(val), parent(0), left(0), right(0), is_black(false), is_nil(false){}

	Node(Node const &src)
	{
		this->is_black = src.is_black;
		this->value = src.value;
		this->parent = src.parent;
		this->is_nil = src.is_nil;
		this->right = src.right;
		this->left = src.left;
	}

	Node &operator=(Node const &src)
	{
		this->is_black = src.is_black;
		this->value = src.value;
		this->parent = src.parent;
		this->is_nil = src.is_nil;
		this->right = src.right;
		this->left = src.left;
		return (*this);
	}

	virtual ~Node(){}
};

template <typename T>
class TreeIter
{
public:
	typedef std::bidirectional_iterator_tag 					iterator_category;
	typedef typename ft::iterator_traits<T*>::value_type 		value_type;
	typedef typename ft::iterator_traits<T*>::reference 		reference;
	typedef typename ft::iterator_traits<T*>::difference_type 	difference_type;
	typedef typename ft::iterator_traits<T*>::pointer 			pointer;
	typedef Node<typename ft::remove_const<value_type>::type >* node_pointer;

private:
	node_pointer _node;

public:
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

	TreeIter(){};
	TreeIter(void *node): _node(static_cast<node_pointer>(node)) {}
	TreeIter(const TreeIter<typename ft::remove_const<value_type>::type> & src)
	{
		*this = src;
	}
	//operators
	TreeIter& operator=(const TreeIter<typename ft::remove_const<value_type>::type>& other) {
		this->_node = other.node();
		return *this;
	}
	reference operator*() const
	{
		return *(_node->value);
	}
	pointer operator->() const
	{
		return _node->value;
	}
	TreeIter operator++()
	{
		if (_node->right && !_node->right->is_nil) {
			_node = tree_min(_node->right);
		}
		else
		{
			node_pointer tmp = _node->parent;
			while (tmp != NULL && _node == tmp->right)
			{
				_node = tmp;
				tmp = tmp->parent;
			}
			_node = tmp;
		}
		return *this;
	}
	TreeIter operator++(int)
	{
		TreeIter<value_type> temp = *this;
		if (_node->right && !_node->right->is_nil) {
			_node = tree_min(_node->right);
		}
		else
		{
			node_pointer tmp = _node->parent;
			while (tmp != NULL && _node == tmp->right)
			{
				_node = tmp;
				tmp = tmp->parent;
			}
			_node = tmp;
		}
		return temp;
	}
	TreeIter& operator--()
	{
		if (_node->left && !_node->left->is_nil) {
			_node = tree_max(_node->left);
		}
		else
		{
			node_pointer tmp = _node->parent;
			while (tmp != NULL && _node == tmp->left)
			{
				_node = tmp;
				tmp = tmp->parent;
			}
			_node = tmp;
		}
		return *this;
	}
	TreeIter operator--(int)
	{
		TreeIter<value_type> temp = *this;
		if (_node->left && !_node->left->is_nil) {
			_node = tree_max(_node->left);
		}
		else
		{
			node_pointer tmp = _node->parent;
			while (tmp != NULL && _node == tmp->left)
			{
				_node = tmp;
				tmp = tmp->parent;
			}
			_node = tmp;
		}
		return temp;
	}
	node_pointer node() const
	{
		return _node;
	}

};

template<typename A, typename B>
bool operator==(const TreeIter<A> & lhs, const TreeIter<B> & rhs)
{
	return (lhs.node() == rhs.node());
}

template<typename A, typename B>
bool operator!=(const TreeIter<A> & lhs, const TreeIter<B> & rhs)
{
	return (lhs.node() != rhs.node());
}

#endif
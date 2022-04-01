#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "memory"
#include "stdexcept"
#include "utility.hpp"

namespace ft
{

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{

		template<typename L>
		class RandomAccessIterator
		{
		public:
			typedef typename iterator_traits<L*>::difference_type		difference_type;
			typedef typename iterator_traits<L*>::value_type			value_type;
			typedef typename iterator_traits<L*>::pointer				pointer;
			typedef typename iterator_traits<L*>::reference				reference;
			typedef typename iterator_traits<L*>::iterator_category		iterator_category;

		private:
			pointer _ptr;

		public:
			RandomAccessIterator(): _ptr(){}
			RandomAccessIterator(pointer p): _ptr(p){}
			virtual ~RandomAccessIterator(){}
			RandomAccessIterator(const RandomAccessIterator<typename remove_const<value_type>::type> &src) : _ptr(&(*src)){}
			RandomAccessIterator<value_type> & operator=(RandomAccessIterator<typename remove_const<value_type>::type> &src)
			{
				_ptr = &(*src);
				return (*this);
			}

			//math operators
			RandomAccessIterator & operator++()
			{
				_ptr++; //???!
				return (*this);
			}
			RandomAccessIterator  operator++(int)
			{
				RandomAccessIterator tmp(*this);
				_ptr++;
				return (tmp);
			}
			RandomAccessIterator operator+(const difference_type & b) const
			{
				return _ptr + b;
			}
			RandomAccessIterator & operator+=(const difference_type & b)
			{
				_ptr += b;
				return (*this);
			}
			RandomAccessIterator & operator--()
			{
				_ptr--;
				return (*this);
			}
			RandomAccessIterator  operator--(int)
			{
				RandomAccessIterator tmp(*this);
				_ptr++;
				return (tmp);
			}
			RandomAccessIterator operator-(const difference_type & b) const
			{
				return _ptr - b;
			}
			RandomAccessIterator & operator-=(const difference_type & b)
			{
				_ptr -= b;
				return (*this);
			}
			reference operator*() const
			{
				return (*_ptr);
			}
			reference operator->() const
			{
				return (_ptr);
			}
			reference operator[](difference_type n) const
			{
				return *(_ptr + n);
			}
		}; // EndOfRAIterator

		//RAIterator comparison op
	public: //TRY CHANGE ::TEMPLATE
		template<typename A, typename B>
		friend bool operator==(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs){
			return &(*lhs) == &(*rhs);
		}
		template<typename A, typename B>
		friend bool operator!=(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) != &(*rhs);
		}
		template<typename A, typename B>
		friend bool operator>(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) > &(*rhs);
		}
		template<typename A, typename B>
		friend bool operator<(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) < &(*rhs);
		}
		template<typename A, typename B>
		friend bool operator<=(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) <= &(*rhs);
		}
		template<typename A, typename B>
		friend bool operator>=(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs) {
			return &(*lhs) >= &(*rhs);
		}
		template<typename A, typename B>
		friend typename vector::template RandomAccessIterator<A>::difference_type operator-(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs){
			return &(*lhs) - &(*rhs);
		}
		template<typename A, typename B>
		friend typename vector::template RandomAccessIterator<A>::difference_type operator+(const vector::template RandomAccessIterator<A> & lhs, const vector::template RandomAccessIterator<B> & rhs){
			return &(*lhs) + &(*rhs);
		}
		template<typename L>
		friend vector::template RandomAccessIterator<L> operator +(const typename vector::template RandomAccessIterator<L>::difference_type & a, const vector::template RandomAccessIterator<L> & iter){
			return	(iter + a);
		}
		template<typename L>
		friend vector::template RandomAccessIterator<L> operator -(const typename vector::template RandomAccessIterator<L>::difference_type & a, const vector::template RandomAccessIterator<L> & iter){
			return	(iter - a);
		}

	public:
		typedef T											value_type;
		typedef Alloc 										allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef  std::size_t 								size_type;
		typedef  RandomAccessIterator<value_type>			iterator;
		typedef RandomAccessIterator<const value_type>		const_iterator;
		//reverse



	private:
		pointer _first;
		size_type _size, _capacity;
		allocator_type _alloc;

	public:
		explicit vector (const allocator_type& alloc = allocator_type()): _first(0), _size(0), _capacity(0), _alloc(alloc) {};
		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()): _size(n), _capacity(n), _alloc(alloc)
		{
			_first = _alloc.allocate(n);
			for(int i = 0; i < n; i++)
				_alloc.construct(_first + i, val);
		};

//		template <class InputIterator>
//		vector (InputIterator first, InputIterator last,
//				const allocator_type& alloc = allocator_type());

		~vector()
		{
			for(int i = 0; i < _size; i++)
				_alloc.destroy(_first + i);
			if (_capacity)
				_alloc.deallocate(_first, _capacity);
		}


		vector &operator=(const vector &x)
		{
			if (*this == x)
				return (*this);
			for(int i = 0; i < _size; i++)
				_alloc.destroy(_first + i);
			_size = x._size;
			if (_capacity != x._capacity)
			{
				if (_capacity != 0)
					_alloc.deallocate(_first,  _capacity);
				_capacity = x._capacity;
				_first = _alloc.allocate(_capacity);
			}
			for(int i = 0; i < _size; i++)
				_alloc.construct(_first + i, *(x._first + i)); // МБ x[i]
			return (*this);
		}

		vector (const vector& x): _size(0), _capacity(0)
		{
			*this = x;
		}
		//CAPACITY
		size_type size() const
		{
			return _size;
		}
		size_type max_size() const
		{
			return _alloc.max_size();
		}
		void resize (size_type n, value_type val = value_type())
		{
			if (n <= _capacity)
			{
				if (_size > n)
				{
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_first + i);
				}
				else if (_size < n)
				{
					for (size_type i = _size; i < n; i++)
						_alloc.construct(_first + i, val);
				}
				_size = n;
			}
			else
			{
				pointer tmp_first =_alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
				{
					try
					{
						if (i < _size)
							_alloc.construct(tmp_first + i, *(_first + i)); // mb x[i]??
						else
							_alloc.construct(tmp_first + i, val);
					}
					catch (std::exception &e)
					{
						size_type tmp_size = 0;
						while (tmp_first + i != NULL && i < _size)
						{
							_alloc.destroy(tmp_first + i);
							i++;
						}
						_alloc.deallocate(tmp_first, n);
						throw;
					}
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_first + i);
				_alloc.deallocate(_first, _capacity);
				_first = tmp_first;
				_capacity = n;
				_size = n;
			}
		}
		size_type capacity() const
		{
			return _capacity;
		}
		bool empty() const
		{
			return (_size == 0);
		}
		void reserve (size_type n)
		{
			if (n > _capacity)
			{
				pointer tmp_first = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					try
					{
						_alloc.construct(tmp_first + i, *(_first + i));
					}
					catch (std::exception &e)
					{
						size_type tmp_size = 0;
						while (tmp_first + i != NULL && i < _size)
						{
							_alloc.destroy(tmp_first + i);
							i++;
						}
						_alloc.deallocate(tmp_first, n);
						throw;
					}
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_first + i);
				_alloc.deallocate(_first, _capacity);
				_first = tmp_first;
				_capacity = n;
			}
		}
		//Element access
		reference operator[] (size_type n)
		{
			return *(_first + n);
		}
		const_reference operator[] (size_type n) const
		{
			return *(_first + n);
		}
		reference at (size_type n)
		{
			if (n > _size)
				throw std::out_of_range("vector at out of range");
			return *(_first + n);
		}
		const_reference at (size_type n) const
		{
			if (n > _size)
				throw std::out_of_range("vector at out of range");
			return *(_first + n);
		}
		reference front()
		{
			return *(_first);
		}
		const_reference front() const
		{
			return *(_first);
		}
		reference back()
		{
			return *(_first + _size - 1);
		}
		const_reference back() const
		{
			return *(_first + _size - 1);
		}
		//Modifiers
//		template <class InputIterator>
//		void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val)
		{
			clear();
			if (n > _capacity)
			{
				_alloc.deallocate(_first, _capacity);
				_first = _alloc.allocate(n);
				_capacity = n;
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_first + i, val);
			_size = n;
		}
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_first + i);
			_size = 0;
		}
		void push_back (const value_type& val)
		{
			if (_size + 1 > _capacity)
				reserve(_size + 1);
			_alloc.construct(_first + _size, val);
			_size++;
		}
		void pop_back()
		{
			_alloc.destroy(_first + _size - 1);
			_size--;
		}
		void swap (vector& x)
		{
			std::swap(_first, x._first);
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(_alloc, x._alloc);
		}
		//Allocator
		allocator_type get_allocator() const
		{

			return _alloc;
		}

	};
};

#endif

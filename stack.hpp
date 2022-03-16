

#ifndef STACK_HPP
#define STACK_HPP

#include "vector" // ЗАМЕНИТЬ

namespace ft
{
	template<class T, class C = std::vector<T> >
			class stack
			{

			public:
				typedef C container_type;
				typedef typename C::value_type value_type;
				typedef typename C::size_type size_type;

			protected:
				container_type _container;

			public:
				explicit stack(const C& Cont = container_type()): _container(Cont){}
				stack(): container_type(){}
				stack(const stack &other): _container(other.container_type){}

				stack &operator=(const stack &other)
				{
					_container = other._container;
					return *this;
				}

				bool empty() const {return _container.empty();}
				size_type size() const {return _container.size();}
				value_type& top()  {return _container.back();}
				const value_type& top() const {return _container.back();}
				void push(const value_type& val){_container.push_back(val);}
				void pop(){_container.pop_back();}

				template <class A, class Container>
				bool friend operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs == rhs;}

				template <class A, class Container>
				bool friend operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs != rhs;}

				template <class A, class Container>
				bool friend operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs < rhs;}

				template <class A, class Container>
				bool friend operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs <= rhs;}

				template <class A, class Container>
				bool friend operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs > rhs;}

				template <class A, class Container>
				bool friend operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs >= rhs;}
			};
};

#endif

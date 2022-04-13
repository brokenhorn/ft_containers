
#ifndef UTILITY_HPP
#define UTILITY_HPP
#include "string"

namespace ft
{
	template <bool cond, class Type = void>
	struct enable_if;

	template<class T> struct remove_const { typedef T type; };

	template<class T> struct remove_const <const T> { typedef T type; };

	template <class Type>
	struct enable_if<true, Type>
	{
		typedef Type type;
	};

	template <bool B, class T, class F>
	struct conditional
	{
		typedef F type;
	};

	template <class T, class F>
	struct conditional<true, T, F>
	{
		typedef T type;
	};


	template <class Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type 		difference_type;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category 	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
	public:
		typedef typename						std::ptrdiff_t difference_type;
		typedef T								value_type;
		typedef T* 								pointer;
		typedef T& 								reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
	public:
		typedef typename  						std::ptrdiff_t difference_type;
		typedef  T 								value_type;
		typedef const T& 						pointer;
		typedef const T& 						reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template< class T, T v >
	struct integral_constant
	{
		typedef T value_type;
		typedef integral_constant type;
		static const bool value = v;
		operator value_type() const { return value; }
	};

	template< class T > struct is_integral : public ft::integral_constant<T, false>{};

	template<> 			struct is_integral<bool> 				: public ft::integral_constant<bool, true>{};
	template<> 			struct is_integral<char>				: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<char16_t>			: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<short>				: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<int>					: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<long>				: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
	template<> 			struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};


	//default (1)
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
	//custom (2) MAYBE WRONG
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2,
								  Compare comp)
	{
		while (first1!=last1)
		{
			if (comp(*first1, *first2)) return true;
			else if (!comp(*first1, *first2)) return false;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class T1, class T2> struct pair
	{
	public:
		typedef T1 first_type;
		typedef T2 second_type;
		first_type first;
		second_type second;


		pair(): first(), second(){};
		template <class U, class V> pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}
		pair(const pair & pr) : first(pr.first), second(pr.second) {}
		pair (const first_type& a, const second_type& b): first(a), second(b){};
		pair& operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};
	//pair logical op
	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first ||
			   (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}
}
#endif

#include "vector.hpp"
#include "vector"
#include "iostream"

int main (void)
{
	ft::vector<int> Myv(5, 12);
	std::vector<int> V(5, 12);

	Myv.push_back(15);
	V.push_back(15);

	ft::vector<int>::iterator iter1;
	std::cout << "My vector" << std::endl;
	for (iter1 = Myv.begin(); iter1 != Myv.end(); ++iter1)
	{
		std::cout << *iter1 << "  ";
	}

	std::cout << std::endl;

	std::vector<int>::iterator iter2;
	std::cout << "STL vector" << std::endl;
	for (iter2 = V.begin(); iter2 != V.end(); ++iter2)
	{
		std::cout << *iter2 << "  ";
	}

	std::cout << std::endl;
	return 1;
}
//create main for test ft::stack

#include "ft_vector.hpp"
#include <vector>
#include <iostream>

int			main()
{
	ft::vector<int>		ft_vector;
	ft::vector<int>		std_vector;


	ft_vector.push_back(1);
	ft_vector.push_back(2);
	ft_vector.push_back(3);
	ft_vector.push_back(4);
	ft_vector.push_back(5);
	ft_vector.push_back(6);
	ft_vector.push_back(7);
	ft_vector.push_back(8);
	ft_vector.push_back(9);
	ft_vector.push_back(10);
	ft_vector.push_back(11);

	std_vector.push_back(1);
	std_vector.push_back(2);
	std_vector.push_back(3);
	std_vector.push_back(4);
	std_vector.push_back(5);
	std_vector.push_back(6);
	std_vector.push_back(7);
	std_vector.push_back(8);
	std_vector.push_back(9);
	std_vector.push_back(10);
	std_vector.push_back(11);

	std::cout << "ft_vector size : " << ft_vector.size() << std::endl;
	std::cout << "std_vector size : " << std_vector.size() << std::endl;

	ft_vector.pop_back();
	std_vector.pop_back();

	std::cout << "ft_vector size : " << ft_vector.size() << std::endl;
	std::cout << "std_vector size : " << std_vector.size() << std::endl;

	if (std_vector.empty() == ft_vector.empty())
        std::cout << "GOOD" << std::endl;
    else
	{
        std::cout << "BAD" << std::endl;
	}
	return (0);
}
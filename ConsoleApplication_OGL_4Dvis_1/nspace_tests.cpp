#include "stdafx.h"


#include <iostream>

#include <nmath/util/Array.h>

#include <nspace/tests.h>


class test_index_ref
{
public:
	void set_i(unsigned int i)
	{
		_M_i = i;
	}
	unsigned int get_i()
	{
		return _M_i;
	}
private:
	unsigned int _M_i;
};

void nspace::tests::test_array()
{
	auto arr = std::make_shared<nmath::util::Array<double>>();

	auto d0 = arr->push_back(0);

	auto tir = std::make_shared<test_index_ref>();

	auto d1 = arr->push_back_index_ref(0, std::bind(&test_index_ref::set_i, tir, std::placeholders::_1), std::bind(&test_index_ref::get_i, tir));

	std::cout << "array size " << arr->size() << std::endl;

}



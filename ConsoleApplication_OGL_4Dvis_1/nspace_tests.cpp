#include "stdafx.h"

<<<<<<< HEAD
<<<<<<< HEAD
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
	auto arr = std::make_shared<nspace::util::Array<double>>();

	auto d0 = arr->push_back(0);

	auto tir = std::make_shared<test_index_ref>();

	auto d1 = arr->push_back_index_ref(0, std::bind(&test_index_ref::set_i, tir, std::placeholders::_1), std::bind(&test_index_ref::get_i, tir));

	std::cout << "array size " << arr->size() << std::endl;
=======
=======
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

#include <nspace/tests.h>
#include <nspace/util/Array.h>

void nspace::tests::test_array()
{
	nspace::util::Array<double> arr;

	auto d0 = arr.push_back(0);


<<<<<<< HEAD
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
=======
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
}



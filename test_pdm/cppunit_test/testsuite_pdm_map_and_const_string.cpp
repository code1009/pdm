/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

//===========================================================================
#include"../stdafx.h"
#include"../../pdm/pdm/pdm.h"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef unsigned short int second_t;
typedef pdm_const_string_t first_t;



//===========================================================================
static void dump_pdm_map_and_const_string_element (pdm_map_t* map, pdm_size_t index, pdm_pointer_t pointer)
{
	first_t*  first_pointer;
	second_t* second_pointer;


	if (PDM_NULL_POINTER!=pointer)
	{
		first_pointer  = (first_t* )pdm_map_first(map, pointer);
		second_pointer = (second_t*)pdm_map_second(map, pointer);

		printf ("[%d] %s = %d \r\n", index, 
			pdm_const_string_c_str(first_pointer),
			*second_pointer
			);
	}
	else
	{
		printf ("[%d] NULL \r\n", index);
	}
}

static void dump_pdm_map_and_const_string (pdm_map_t* map)
{
	pdm_size_t count;
	pdm_size_t i;
	
	pdm_pointer_t pointer;


	count = pdm_map_count(map);
	printf ("map-count = %d \r\n", count);
	for (i=0u; i<count; i++)
	{
		pointer = pdm_map_at(map, i);

		dump_pdm_map_and_const_string_element(map, i, pointer);
	}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class testsuite_pdm_map_and_const_string : public CppUnit::TestFixture
{
private:
	pdm_size_t  _buffer_size;
	pdm_byte_t* _buffer_pointer;
	pdm_core_t* _sut_core;
	pdm_map_t*  _sut_map;

	pdm_const_string_t _const_string[6];

public:
	testsuite_pdm_map_and_const_string();
	virtual ~testsuite_pdm_map_and_const_string();

public:
	virtual void setUp();
	virtual void tearDown();

private:
	CPPUNIT_TEST_SUITE(testsuite_pdm_map_and_const_string);
	CPPUNIT_TEST(test_insert);
	CPPUNIT_TEST(test_erase);
	CPPUNIT_TEST(test_set);
	CPPUNIT_TEST(test_get);
	CPPUNIT_TEST(test_find);
	CPPUNIT_TEST(test_first_erase);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_insert(void);
	void test_erase(void);
	void test_set(void);
	void test_get(void);
	void test_find(void);
	void test_first_erase(void);

public:
	void fill_map (pdm_map_t& map);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CPPUNIT_TEST_SUITE_REGISTRATION(testsuite_pdm_map_and_const_string);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
testsuite_pdm_map_and_const_string::testsuite_pdm_map_and_const_string():
	_buffer_size   (0),
	_buffer_pointer(PDM_NULL_POINTER),
	_sut_core      (PDM_NULL_POINTER),
	_sut_map       (PDM_NULL_POINTER)
{
}

testsuite_pdm_map_and_const_string::~testsuite_pdm_map_and_const_string()
{
}

//===========================================================================
void testsuite_pdm_map_and_const_string::setUp()
{
	printf("\r\n");

	pdm_size_t element_max_count = 5;
	pdm_size_t element_size      = 1024;


	_buffer_size    = element_size*element_max_count;
	_buffer_pointer = new pdm_byte_t[_buffer_size];

	_sut_core = new pdm_core_t;
	_sut_map  = new pdm_map_t;

	if (PDM_NULL_POINTER==_buffer_pointer) {CPPUNIT_ASSERT(0);}
	if (PDM_NULL_POINTER==_sut_core)       {CPPUNIT_ASSERT(0);}
	if (PDM_NULL_POINTER==_sut_map)        {CPPUNIT_ASSERT(0);}


	pdm_core_t& core = *_sut_core;
	pdm_map_t&  map  = *_sut_map;


	core.memory.size    = _buffer_size;
	core.memory.pointer = (pdm_byte_t*)_buffer_pointer;

	if (PDM_FALSE==pdm_core_create (&core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}

	if (PDM_FALSE==pdm_map_create(&map, element_max_count, sizeof(first_t), sizeof(second_t), pdm_equal_const_string, pdm_less_const_string, &core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}

	
	pdm_bool_t result;


	result = pdm_const_string_create(&_const_string[0], "0:zero", -1, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	result = pdm_const_string_create(&_const_string[1], "1:one", -1, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	result = pdm_const_string_create(&_const_string[2], "2:two", -1, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	result = pdm_const_string_create(&_const_string[3], "3:three", -1, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	result = pdm_const_string_create(&_const_string[4], "4:four", -1, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	result = pdm_const_string_create(&_const_string[5], "5:five", -1, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

}

void testsuite_pdm_map_and_const_string::tearDown()
{
	pdm_core_t& core = *_sut_core;
	pdm_map_t&  map  = *_sut_map;


	if (_sut_map)
	{
		pdm_map_destroy(&map);
	}
	if (_sut_core)
	{
		pdm_core_destroy(&core);
	}

	if (_buffer_pointer) { delete[] _buffer_pointer; }
	if (_sut_core)       { delete _sut_core;         }
	if (_sut_map)        { delete _sut_map;          }

	_buffer_size    = 0u;
	_buffer_pointer = PDM_NULL_POINTER;

	_sut_core = PDM_NULL_POINTER;
	_sut_map  = PDM_NULL_POINTER;
}

//===========================================================================
void testsuite_pdm_map_and_const_string::fill_map (pdm_map_t& map)
{
	pdm_core_t& core = *_sut_core;

	first_t* first_pointer;
	second_t second;

	pdm_bool_t result;



	//-----------------------------------------------------------------------
	first_pointer = &_const_string[0];
	second = 0u;

	result = pdm_map_insert(&map, first_pointer, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	//-----------------------------------------------------------------------
	first_pointer = &_const_string[3];
	second = 3u;

	result = pdm_map_insert(&map, first_pointer, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	//-----------------------------------------------------------------------
	first_pointer = &_const_string[2];
	second = 2u;

	result = pdm_map_insert(&map, first_pointer, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	//-----------------------------------------------------------------------
	first_pointer = &_const_string[1];
	second = 1u;

	result = pdm_map_insert(&map, first_pointer, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	//-----------------------------------------------------------------------
	CPPUNIT_ASSERT(4u==pdm_map_count(&map));
}

//===========================================================================
void testsuite_pdm_map_and_const_string::test_insert(void)
{
	pdm_map_t& map = *_sut_map;

	first_t* first_pointer;
	second_t second;

	pdm_bool_t result;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first_pointer = &_const_string[1];
	second = 999u;

	result = pdm_map_insert(&map, first_pointer, &second);
	CPPUNIT_ASSERT(PDM_FALSE==result);


	first_pointer = &_const_string[4];
	second = 4u;

	result = pdm_map_insert(&map, first_pointer, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	CPPUNIT_ASSERT(5u==pdm_map_count(&map));


	dump_pdm_map_and_const_string(&map);
}

void testsuite_pdm_map_and_const_string::test_erase(void)
{
	pdm_map_t& map = *_sut_map;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	printf ("pdm_map_erase(3)\r\n");
	dump_pdm_map_and_const_string(&map);
	pdm_map_erase(&map, 3);
	CPPUNIT_ASSERT(3u==pdm_map_count(&map));
	dump_pdm_map_and_const_string(&map);
	printf ("\r\n");

	printf ("pdm_map_erase(0)\r\n");
	dump_pdm_map_and_const_string(&map);
	pdm_map_erase(&map, 0);
	CPPUNIT_ASSERT(2u==pdm_map_count(&map));
	dump_pdm_map_and_const_string(&map);
	printf ("\r\n");

	printf ("pdm_map_erase(1)\r\n");
	dump_pdm_map_and_const_string(&map);
	pdm_map_erase(&map, 1);
	CPPUNIT_ASSERT(1u==pdm_map_count(&map));
	dump_pdm_map_and_const_string(&map);
}

void testsuite_pdm_map_and_const_string::test_set(void)
{
	pdm_map_t& map = *_sut_map;

	first_t* first_pointer;
	second_t second;

	pdm_bool_t result;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first_pointer = &_const_string[1];
	second = 999u;
	result = pdm_map_set(&map, first_pointer, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	dump_pdm_map_and_const_string(&map);
}

void testsuite_pdm_map_and_const_string::test_get(void)
{
	pdm_map_t& map = *_sut_map;

	first_t* first_pointer;
	second_t second;

	pdm_bool_t result;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first_pointer = &_const_string[1];
	second = 0u;
	result = pdm_map_get(&map, first_pointer, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	CPPUNIT_ASSERT(second == 1u);
}

void testsuite_pdm_map_and_const_string::test_find(void)
{
	pdm_map_t& map = *_sut_map;

	pdm_pointer_t pointer;
	first_t* first_pointer;



	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first_pointer = &_const_string[4];
	pointer = pdm_map_find(&map, first_pointer);
	CPPUNIT_ASSERT(PDM_NULL_POINTER==pointer);


	first_pointer = &_const_string[1];
	pointer = pdm_map_find(&map, first_pointer);
	CPPUNIT_ASSERT(PDM_NULL_POINTER!=pointer);


//	first_t*  first_pointer;
	second_t* second_pointer;


	first_pointer  = (first_t* )pdm_map_first(&map, pointer);
	second_pointer = (second_t*)pdm_map_second(&map, pointer);

	CPPUNIT_ASSERT(0==pdm_const_string_compare(first_pointer, &_const_string[1]));

	CPPUNIT_ASSERT(*second_pointer == 1u);
}

void testsuite_pdm_map_and_const_string::test_first_erase(void)
{
	pdm_map_t& map = *_sut_map;

	first_t*  first_pointer;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first_pointer = &_const_string[4];
	pdm_map_first_erase(&map, first_pointer);
	CPPUNIT_ASSERT(pdm_map_count(&map)==4);


	first_pointer = &_const_string[1];
	pdm_map_first_erase(&map, first_pointer);
	CPPUNIT_ASSERT(pdm_map_count(&map)==3);


	pdm_size_t count;
	pdm_size_t i;
	
	pdm_pointer_t pointer;

//	first_t*  first_pointer;
	second_t* second_pointer;


	count = pdm_map_count(&map);
	for (i=0u; i<count; i++)
	{
		pointer = pdm_map_at(&map, i);

		if (PDM_NULL_POINTER!=pointer)
		{
			first_pointer  = (first_t* )pdm_map_first (&map, pointer);
			second_pointer = (second_t*)pdm_map_second(&map, pointer);

			CPPUNIT_ASSERT(0!=pdm_const_string_compare(first_pointer, &_const_string[1]));
		}
		else
		{
			CPPUNIT_ASSERT(0);
		}
	}

	dump_pdm_map_and_const_string(&map);
}





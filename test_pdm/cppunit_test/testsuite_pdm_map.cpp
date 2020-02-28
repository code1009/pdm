/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

//===========================================================================
#include"../stdafx.h"
#include"../../pdm/pdm/pdm.h"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
typedef struct _second_t
{
	unsigned short int value1;
	unsigned short int value2;
	unsigned short int value3;
} second_t;

typedef struct _first_t
{
	unsigned short int value1;
} first_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static pdm_bool_t element_first_equal (pdm_pointer_t left, pdm_pointer_t right)
{
	first_t* ap;
	first_t* bp;


	ap = (first_t*)left;
	bp = (first_t*)right;


	if (ap->value1 == bp->value1)
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}

static pdm_bool_t element_first_less (pdm_pointer_t left, pdm_pointer_t right)
{
	first_t* ap;
	first_t* bp;


	ap = (first_t*)left;
	bp = (first_t*)right;


	if (ap->value1 < bp->value1)
	{
		return PDM_TRUE;
	}

	return PDM_FALSE;
}

//===========================================================================
static void dump_pdm_map_element (pdm_map_t* map, pdm_size_t index, pdm_pointer_t pointer)
{
	first_t*  first_pointer;
	second_t* second_pointer;


	if (PDM_NULL_POINTER!=pointer)
	{
		first_pointer  = (first_t* )pdm_map_first(map, pointer);
		second_pointer = (second_t*)pdm_map_second(map, pointer);

		printf ("[%d] %d = %d \r\n", index, 
			first_pointer->value1,
			second_pointer->value1
			);
	}
	else
	{
		printf ("[%d] NULL \r\n", index);
	}
}

static void dump_pdm_map (pdm_map_t* map)
{
	pdm_size_t count;
	pdm_size_t i;
	
	pdm_pointer_t pointer;


	count = pdm_map_count(map);
	printf ("map-count = %d \r\n", count);
	for (i=0u; i<count; i++)
	{
		pointer = pdm_map_at(map, i);

		dump_pdm_map_element(map, i, pointer);
	}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class testsuite_pdm_map : public CppUnit::TestFixture
{
private:
	pdm_size_t  _buffer_size;
	pdm_byte_t* _buffer_pointer;
	pdm_core_t* _sut_core;
	pdm_map_t*  _sut_map;

public:
	testsuite_pdm_map();
	virtual ~testsuite_pdm_map();

public:
	virtual void setUp();
	virtual void tearDown();

private:
	CPPUNIT_TEST_SUITE(testsuite_pdm_map);
	CPPUNIT_TEST(test_insert);
	CPPUNIT_TEST(test_erase);
	CPPUNIT_TEST(test_set);
	CPPUNIT_TEST(test_get);
	CPPUNIT_TEST(test_find);
	CPPUNIT_TEST(test_erase_by_first);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_insert(void);
	void test_erase(void);
	void test_set(void);
	void test_get(void);
	void test_find(void);
	void test_erase_by_first(void);

public:
	void fill_map (pdm_map_t& map);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CPPUNIT_TEST_SUITE_REGISTRATION(testsuite_pdm_map);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
testsuite_pdm_map::testsuite_pdm_map():
	_buffer_size   (0),
	_buffer_pointer(PDM_NULL_POINTER),
	_sut_core      (PDM_NULL_POINTER),
	_sut_map       (PDM_NULL_POINTER)
{
}

testsuite_pdm_map::~testsuite_pdm_map()
{
}

//===========================================================================
void testsuite_pdm_map::setUp()
{
	printf("\r\n");

	pdm_size_t element_max_count = 5;
	pdm_size_t element_size      = (4+8);


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

	if (PDM_FALSE==pdm_map_create(&map, element_max_count, sizeof(first_t), sizeof(second_t), element_first_equal, element_first_less, &core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}
}

void testsuite_pdm_map::tearDown()
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
void testsuite_pdm_map::fill_map (pdm_map_t& map)
{
	first_t  first;
	second_t second;

	pdm_bool_t result;


	first .value1 = 0;
	second.value1 = 0;
	second.value2 = 0;
	second.value3 = 0;


	//-----------------------------------------------------------------------
	first .value1 = 50;
	second.value1 = 51;
	result = pdm_map_insert(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	first .value1 = 20;
	second.value1 = 21;
	result = pdm_map_insert(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	first .value1 = 40;
	second.value1 = 41;
	result = pdm_map_insert(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	first .value1 = 30;
	second.value1 = 31;
	result = pdm_map_insert(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	CPPUNIT_ASSERT(4u==pdm_map_count(&map));
}

//===========================================================================
void testsuite_pdm_map::test_insert(void)
{
	pdm_map_t& map = *_sut_map;

	first_t  first;
	second_t second;

	pdm_bool_t result;


	first .value1 = 0;
	second.value1 = 0;
	second.value2 = 0;
	second.value3 = 0;


	//-----------------------------------------------------------------------
	first .value1 = 50;
	second.value1 = 51;
	result = pdm_map_insert(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	first .value1 = 20;
	second.value1 = 21;
	result = pdm_map_insert(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	first .value1 = 40;
	second.value1 = 41;
	result = pdm_map_insert(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	first .value1 = 40;
	second.value1 = 41;
	result = pdm_map_insert(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_FALSE==result);


	CPPUNIT_ASSERT(3u==pdm_map_count(&map));


	dump_pdm_map(&map);
}

void testsuite_pdm_map::test_erase(void)
{
	pdm_map_t& map = *_sut_map;

	first_t  first;
	second_t second;


	first .value1 = 0;
	second.value1 = 0;
	second.value2 = 0;
	second.value3 = 0;


	//-----------------------------------------------------------------------
	fill_map(map);

	printf ("pdm_map_erase(3)\r\n");
	dump_pdm_map(&map);
	pdm_map_erase(&map, 3);
	CPPUNIT_ASSERT(3u==pdm_map_count(&map));
	dump_pdm_map(&map);
	printf ("\r\n");

	printf ("pdm_map_erase(0)\r\n");
	dump_pdm_map(&map);
	pdm_map_erase(&map, 0);
	CPPUNIT_ASSERT(2u==pdm_map_count(&map));
	dump_pdm_map(&map);
	printf ("\r\n");

	printf ("pdm_map_erase(1)\r\n");
	dump_pdm_map(&map);
	pdm_map_erase(&map, 1);
	CPPUNIT_ASSERT(1u==pdm_map_count(&map));
	dump_pdm_map(&map);
}

void testsuite_pdm_map::test_set(void)
{
	pdm_map_t& map = *_sut_map;

	first_t  first;
	second_t second;

	pdm_bool_t result;


	first .value1 = 0;
	second.value1 = 0;
	second.value2 = 0;
	second.value3 = 0;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first .value1 = 10;
	second.value1 = 11;
	result = pdm_map_set(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	first .value1 = 10;
	second.value1 = 999;
	result = pdm_map_set(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	CPPUNIT_ASSERT(PDM_TRUE==pdm_map_full(&map));


	first .value1 = 999;
	second.value1 = 999;
	result = pdm_map_set(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_FALSE==result);


	dump_pdm_map(&map);
}

void testsuite_pdm_map::test_get(void)
{
	pdm_map_t& map = *_sut_map;

	first_t  first;
	second_t second;

	pdm_bool_t result;


	first .value1 = 999;
	second.value1 = 999;
	second.value2 = 999;
	second.value3 = 999;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first .value1 = 999;
	result = pdm_map_get(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_FALSE==result);


	//-----------------------------------------------------------------------
	first .value1 = 40;
	result = pdm_map_get(&map, &first, &second);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	CPPUNIT_ASSERT(second.value1 == 41u);
	CPPUNIT_ASSERT(second.value2 == 0u);
	CPPUNIT_ASSERT(second.value3 == 0u);
}

void testsuite_pdm_map::test_find(void)
{
	pdm_map_t& map = *_sut_map;

	pdm_pointer_t pointer;
	first_t  first;
	second_t second;


	first .value1 = 999;
	second.value1 = 999;
	second.value2 = 999;
	second.value3 = 999;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first .value1 = 999;
	pointer = pdm_map_find(&map, &first);
	CPPUNIT_ASSERT(PDM_NULL_POINTER==pointer);


	first .value1 = 40;
	pointer = pdm_map_find(&map, &first);
	CPPUNIT_ASSERT(PDM_NULL_POINTER!=pointer);


	first_t*  first_pointer;
	second_t* second_pointer;


	first_pointer  = (first_t* )pdm_map_first(&map, pointer);
	second_pointer = (second_t*)pdm_map_second(&map, pointer);

	CPPUNIT_ASSERT(second_pointer->value1 == 41u);
	CPPUNIT_ASSERT(second_pointer->value2 == 0u);
	CPPUNIT_ASSERT(second_pointer->value3 == 0u);
}

void testsuite_pdm_map::test_erase_by_first(void)
{
	pdm_map_t& map = *_sut_map;

	first_t  first;
	second_t second;


	first .value1 = 999;
	second.value1 = 999;
	second.value2 = 999;
	second.value3 = 999;


	//-----------------------------------------------------------------------
	fill_map(map);


	//-----------------------------------------------------------------------
	first .value1 = 999;
	pdm_map_erase_by_first(&map, &first);
	CPPUNIT_ASSERT(pdm_map_count(&map)==4);


	first .value1 = 20;
	pdm_map_erase_by_first(&map, &first);
	CPPUNIT_ASSERT(pdm_map_count(&map)==3);


	pdm_size_t count;
	pdm_size_t i;
	
	pdm_pointer_t pointer;

	first_t*  first_pointer;
	second_t* second_pointer;


	count = pdm_map_count(&map);
	for (i=0u; i<count; i++)
	{
		pointer = pdm_map_at(&map, i);

		if (PDM_NULL_POINTER!=pointer)
		{
			first_pointer  = (first_t* )pdm_map_first (&map, pointer);
			second_pointer = (second_t*)pdm_map_second(&map, pointer);

			CPPUNIT_ASSERT(first_pointer->value1!=20);
		}
		else
		{
			CPPUNIT_ASSERT(0);
		}
	}
}





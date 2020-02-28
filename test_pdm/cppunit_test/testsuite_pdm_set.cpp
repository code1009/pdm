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
typedef int element_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static void dump_pdm_set_element (pdm_set_t* set, pdm_size_t index, pdm_pointer_t pointer)
{
	element_t* element;


	if (PDM_NULL_POINTER!=pointer)
	{
		element = (element_t*)pointer;

		printf ("[%d] = %d \r\n", index, *element);
	}
	else
	{
		printf ("[%d] NULL \r\n", index);
	}
}

static void dump_pdm_set (pdm_set_t* set)
{
	pdm_size_t count;
	pdm_size_t i;
	
	pdm_pointer_t pointer;


	count = pdm_set_count(set);
	printf ("set-count = %d \r\n", count);
	for (i=0u; i<count; i++)
	{
		pointer = pdm_set_at(set, i);

		dump_pdm_set_element(set, i, pointer);
	}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class testsuite_pdm_set : public CppUnit::TestFixture
{
private:
	pdm_size_t  _buffer_size;
	pdm_byte_t* _buffer_pointer;
	pdm_core_t* _sut_core;
	pdm_set_t*  _sut_set;

public:
	testsuite_pdm_set();
	virtual ~testsuite_pdm_set();

public:
	virtual void setUp();
	virtual void tearDown();

private:
	CPPUNIT_TEST_SUITE(testsuite_pdm_set);
	CPPUNIT_TEST(test_erase);
	CPPUNIT_TEST(test_insert);
	CPPUNIT_TEST(test_find);
	CPPUNIT_TEST(test_erase_by_element);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_erase(void);
	void test_insert(void);
	void test_find(void);
	void test_erase_by_element(void);

public:
	void fill_set (pdm_set_t& set);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CPPUNIT_TEST_SUITE_REGISTRATION(testsuite_pdm_set);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
testsuite_pdm_set::testsuite_pdm_set():
	_buffer_size   (0),
	_buffer_pointer(PDM_NULL_POINTER),
	_sut_core      (PDM_NULL_POINTER),
	_sut_set       (PDM_NULL_POINTER)
{
}

testsuite_pdm_set::~testsuite_pdm_set()
{
}

//===========================================================================
void testsuite_pdm_set::setUp()
{
	printf("\r\n");

	pdm_size_t element_max_count = 5;
	pdm_size_t element_size      = sizeof(element_t);


	_buffer_size    = element_size*element_max_count;
	_buffer_pointer = new pdm_byte_t[_buffer_size];

	_sut_core = new pdm_core_t;
	_sut_set  = new pdm_set_t;

	if (PDM_NULL_POINTER==_buffer_pointer) {CPPUNIT_ASSERT(0);}
	if (PDM_NULL_POINTER==_sut_core)       {CPPUNIT_ASSERT(0);}
	if (PDM_NULL_POINTER==_sut_set)        {CPPUNIT_ASSERT(0);}


	pdm_core_t& core = *_sut_core;
	pdm_set_t&  set  = *_sut_set;


	core.memory.size    = _buffer_size;
	core.memory.pointer = (pdm_byte_t*)_buffer_pointer;

	if (PDM_FALSE==pdm_core_create (&core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}

	if (PDM_FALSE==pdm_set_create(&set, element_max_count, element_size, pdm_equal_int, pdm_less_int, &core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}
}

void testsuite_pdm_set::tearDown()
{
	pdm_core_t& core = *_sut_core;
	pdm_set_t&  set  = *_sut_set;


	if (_sut_set)
	{
		pdm_set_destroy(&set);
	}
	if (_sut_core)
	{
		pdm_core_destroy(&core);
	}

	if (_buffer_pointer) { delete[] _buffer_pointer; }
	if (_sut_core)       { delete _sut_core;         }
	if (_sut_set)        { delete _sut_set;          }

	_buffer_size    = 0u;
	_buffer_pointer = PDM_NULL_POINTER;

	_sut_core = PDM_NULL_POINTER;
	_sut_set  = PDM_NULL_POINTER;
}

//===========================================================================
void testsuite_pdm_set::fill_set (pdm_set_t& set)
{
	//-----------------------------------------------------------------------
	element_t element;


	//-----------------------------------------------------------------------
	element = 0;


	//-----------------------------------------------------------------------
	element = 40;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_set_insert (&set, &element));


	element = 30;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_set_insert (&set, &element));


	element = 40;
	CPPUNIT_ASSERT(PDM_FALSE==pdm_set_insert (&set, &element));


	element = 10;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_set_insert (&set, &element));


	element = 20;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_set_insert (&set, &element));

	
	CPPUNIT_ASSERT(4u==pdm_set_count(&set));
}

//===========================================================================
void testsuite_pdm_set::test_insert(void)
{
	//-----------------------------------------------------------------------
	pdm_set_t& set = *_sut_set;

	element_t element;


	//-----------------------------------------------------------------------
	element = 0;


	//-----------------------------------------------------------------------
	fill_set(set);


	//-----------------------------------------------------------------------
	element = 50;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_set_insert(&set, &element));


	element = 60;
	CPPUNIT_ASSERT(PDM_FALSE==pdm_set_insert(&set, &element));


	CPPUNIT_ASSERT(5u==pdm_set_count(&set));


	CPPUNIT_ASSERT( 10==*((element_t*)pdm_set_at(&set, 0u)) );
	CPPUNIT_ASSERT( 20==*((element_t*)pdm_set_at(&set, 1u)) );
	CPPUNIT_ASSERT( 30==*((element_t*)pdm_set_at(&set, 2u)) );
	CPPUNIT_ASSERT( 40==*((element_t*)pdm_set_at(&set, 3u)) );
	CPPUNIT_ASSERT( 50==*((element_t*)pdm_set_at(&set, 4u)) );
}

void testsuite_pdm_set::test_erase(void)
{
	//-----------------------------------------------------------------------
	pdm_set_t& set = *_sut_set;

	element_t* element_pointer;


	//-----------------------------------------------------------------------
	fill_set(set);


	//-----------------------------------------------------------------------
	dump_pdm_set(&set);


	//-----------------------------------------------------------------------
	pdm_set_erase(&set, 1u);


	element_pointer = (element_t*)pdm_set_at(&set, 1u);
	CPPUNIT_ASSERT(*element_pointer == 30);


	//-----------------------------------------------------------------------
	dump_pdm_set(&set);
}

void testsuite_pdm_set::test_find(void)
{
	//-----------------------------------------------------------------------
	pdm_set_t& set = *_sut_set;

	element_t element;

	pdm_pointer_t pointer;


	//-----------------------------------------------------------------------
	element = 0;


	//-----------------------------------------------------------------------
	fill_set(set);


	//-----------------------------------------------------------------------
	element = 30;
	pointer = pdm_set_find(&set, &element);

	CPPUNIT_ASSERT(pointer != PDM_NULL_POINTER);
	CPPUNIT_ASSERT(pointer == pdm_set_at(&set, 2));
}

void testsuite_pdm_set::test_erase_by_element(void)
{
	//-----------------------------------------------------------------------
	pdm_set_t& set = *_sut_set;

	element_t element;;

	element_t* element_pointer;

	pdm_size_t count;
	pdm_size_t i;
	

	//-----------------------------------------------------------------------
	element = 0;


	//-----------------------------------------------------------------------
	fill_set(set);


	//-----------------------------------------------------------------------
	element = 40;
	pdm_set_erase_by_element(&set, &element);
	CPPUNIT_ASSERT(3u==pdm_set_count(&set));


	element = 20;
	pdm_set_erase_by_element(&set, &element);
	CPPUNIT_ASSERT(2u==pdm_set_count(&set));


	count = pdm_set_count(&set);
	for (i=0u; i<count; i++)
	{
		element_pointer = (element_t*)pdm_set_at(&set, i);

		if (PDM_NULL_POINTER!=element_pointer)
		{
			CPPUNIT_ASSERT(*element_pointer!=20);
			CPPUNIT_ASSERT(*element_pointer!=40);
		}
		else
		{
			CPPUNIT_ASSERT(0);
		}
	}
}



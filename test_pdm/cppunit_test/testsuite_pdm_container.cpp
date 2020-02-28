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
typedef struct _element_t
{
	unsigned short int value1;
	unsigned short int value2;
	unsigned short int value3;
} element_t;



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static void dump_pdm_container_element (pdm_container_t* container, pdm_size_t index, pdm_pointer_t pointer)
{
	element_t* element_pointer;


	if (PDM_NULL_POINTER!=pointer)
	{
		element_pointer = (element_t*)pointer;

		printf ("[%d] = %d %d %d \r\n", index, 
			element_pointer->value1,
			element_pointer->value2,
			element_pointer->value3
			);
	}
	else
	{
		printf ("[%d] NULL \r\n", index);
	}
}

static void dump_pdm_container (pdm_container_t* container)
{
	pdm_size_t count;
	pdm_size_t i;
	
	pdm_pointer_t pointer;


	count = pdm_container_count(container);
	printf ("container-count = %d \r\n", count);
	for (i=0u; i<count; i++)
	{
		pointer = pdm_container_at(container, i);

		dump_pdm_container_element(container, i, pointer);
	}
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class testsuite_pdm_container : public CppUnit::TestFixture
{
private:
	pdm_size_t       _buffer_size;
	pdm_byte_t*      _buffer_pointer;
	pdm_core_t*      _sut_core;
	pdm_container_t* _sut_container;

public:
	testsuite_pdm_container();
	virtual ~testsuite_pdm_container();

public:
	virtual void setUp();
	virtual void tearDown();

private:
	CPPUNIT_TEST_SUITE(testsuite_pdm_container);
	CPPUNIT_TEST(test_erase);
	CPPUNIT_TEST(test_insert);
	CPPUNIT_TEST(test_set);
	CPPUNIT_TEST(test_get);
	CPPUNIT_TEST(test_push_back);
	CPPUNIT_TEST(test_pop_back);
	CPPUNIT_TEST(test_push_front);
	CPPUNIT_TEST(test_pop_front);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_erase(void);
	void test_insert(void);
	void test_set(void);
	void test_get(void);
	void test_push_back(void);
	void test_pop_back(void);
	void test_push_front(void);
	void test_pop_front(void);

public:
	void fill_container (pdm_container_t& container);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CPPUNIT_TEST_SUITE_REGISTRATION(testsuite_pdm_container);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
testsuite_pdm_container::testsuite_pdm_container():
	_buffer_size   (0),
	_buffer_pointer(PDM_NULL_POINTER),
	_sut_core      (PDM_NULL_POINTER),
	_sut_container (PDM_NULL_POINTER)
{
}

testsuite_pdm_container::~testsuite_pdm_container()
{
}

//===========================================================================
void testsuite_pdm_container::setUp()
{
	//-----------------------------------------------------------------------
	printf("\r\n");


	//-----------------------------------------------------------------------
	pdm_size_t element_max_count = 5;
	pdm_size_t element_size      = sizeof(element_t);


	_buffer_size    = element_size*element_max_count+2u; // 6*5+2 = 32
	_buffer_pointer = new pdm_byte_t[_buffer_size];

	_sut_core      = new pdm_core_t;
	_sut_container = new pdm_container_t;

	if (PDM_NULL_POINTER==_buffer_pointer) {CPPUNIT_ASSERT(0);}
	if (PDM_NULL_POINTER==_sut_core)       {CPPUNIT_ASSERT(0);}
	if (PDM_NULL_POINTER==_sut_container)  {CPPUNIT_ASSERT(0);}


	//-----------------------------------------------------------------------
	pdm_core_t&      core      = *_sut_core;
	pdm_container_t& container = *_sut_container;


	core.memory.size    = _buffer_size;
	core.memory.pointer = (pdm_byte_t*)_buffer_pointer;

	if (PDM_FALSE==pdm_core_create (&core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}


	container.core = &core; // Áß¿ä
	container.element_max_count = element_max_count;
	container.element_size      = element_size;
	if (PDM_FALSE==pdm_container_create(&container))
	{
		CPPUNIT_ASSERT(0);
		return;
	}
}

void testsuite_pdm_container::tearDown()
{
	//-----------------------------------------------------------------------
	pdm_core_t&      core      = *_sut_core;
	pdm_container_t& container = *_sut_container;


	if (_sut_container)
	{
		pdm_container_destroy(&container);
	}
	if (_sut_core)
	{
		pdm_core_destroy(&core);
	}


	//-----------------------------------------------------------------------
	if (_buffer_pointer) { delete[] _buffer_pointer; }
	if (_sut_core)       { delete _sut_core;         }
	if (_sut_container)  { delete _sut_container;    }

	_buffer_size    = 0u;
	_buffer_pointer = PDM_NULL_POINTER;

	_sut_core       = PDM_NULL_POINTER;
	_sut_container  = PDM_NULL_POINTER;
}

//===========================================================================
void testsuite_pdm_container::fill_container (pdm_container_t& container)
{
	//-----------------------------------------------------------------------
	element_t element;


	//-----------------------------------------------------------------------
	element.value1 = 0;
	element.value2 = 0;
	element.value3 = 0;


	//-----------------------------------------------------------------------
	element.value1 = 10;
	element.value2 = 11;
	element.value3 = 12;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_push_back(&container, &element));


	element.value1 = 20;
	element.value2 = 21;
	element.value3 = 22;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_push_back(&container, &element));


	element.value1 = 30;
	element.value2 = 31;
	element.value3 = 32;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_push_back(&container, &element));


	element.value1 = 40;
	element.value2 = 41;
	element.value3 = 42;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_push_back(&container, &element));


	CPPUNIT_ASSERT(4u==pdm_container_count(&container));
}

//===========================================================================
void testsuite_pdm_container::test_erase(void)
{
	//-----------------------------------------------------------------------
	pdm_container_t& container = *_sut_container;

	element_t* element_pointer;


	//-----------------------------------------------------------------------
	fill_container(container);


	//-----------------------------------------------------------------------
	pdm_container_erase(&container, 1u);


	element_pointer = (element_t*)pdm_container_at(&container, 1u);
	CPPUNIT_ASSERT(element_pointer->value1 == 30);
	CPPUNIT_ASSERT(element_pointer->value2 == 31);
	CPPUNIT_ASSERT(element_pointer->value3 == 32);
}

void testsuite_pdm_container::test_insert(void)
{
	//-----------------------------------------------------------------------
	pdm_container_t& container = *_sut_container;

	element_t element;

	element_t* element_pointer;


	//-----------------------------------------------------------------------
	element.value1 = 0;
	element.value2 = 0;
	element.value3 = 0;


	//-----------------------------------------------------------------------
	fill_container(container);


	//-----------------------------------------------------------------------
	element.value1 = 999;
	element.value2 = 991;
	element.value3 = 992;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_insert(&container, 1u, &element));


	element.value1 = 899;
	element.value2 = 891;
	element.value3 = 892;
	CPPUNIT_ASSERT(PDM_FALSE==pdm_container_insert(&container, 1u, &element));


	CPPUNIT_ASSERT(5u==pdm_container_count(&container));


	element_pointer = (element_t*)pdm_container_at(&container, 1u);
	CPPUNIT_ASSERT(element_pointer->value1 == 999);
	CPPUNIT_ASSERT(element_pointer->value2 == 991);
	CPPUNIT_ASSERT(element_pointer->value3 == 992);
}

void testsuite_pdm_container::test_set(void)
{
	//-----------------------------------------------------------------------
	pdm_container_t&  container = *_sut_container;

	element_t element;

	element_t* element_pointer;


	//-----------------------------------------------------------------------
	element.value1 = 0;
	element.value2 = 0;
	element.value3 = 0;


	//-----------------------------------------------------------------------
	fill_container(container);


	//-----------------------------------------------------------------------
	element.value1 = 999;
	element.value2 = 998;
	element.value3 = 997;
	pdm_container_set(&container, 1, &element);

	element_pointer = (element_t*)pdm_container_at(&container, 1u);
	CPPUNIT_ASSERT(element_pointer->value1 == 999);
	CPPUNIT_ASSERT(element_pointer->value2 == 998);
	CPPUNIT_ASSERT(element_pointer->value3 == 997);
}

void testsuite_pdm_container::test_get(void)
{
	//-----------------------------------------------------------------------
	pdm_container_t&  container = *_sut_container;

	element_t element;


	//-----------------------------------------------------------------------
	element.value1 = 0;
	element.value2 = 0;
	element.value3 = 0;


	//-----------------------------------------------------------------------
	fill_container(container);


	//-----------------------------------------------------------------------
	CPPUNIT_ASSERT(PDM_TRUE == pdm_container_get(&container, 3, &element));

	CPPUNIT_ASSERT(element.value1 == 40);
	CPPUNIT_ASSERT(element.value2 == 41);
	CPPUNIT_ASSERT(element.value3 == 42);
}

//===========================================================================
void testsuite_pdm_container::test_push_back(void)
{
	//-----------------------------------------------------------------------
	pdm_container_t& container = *_sut_container;

	element_t element;


	//-----------------------------------------------------------------------
	element.value1 = 0;
	element.value2 = 0;
	element.value3 = 0;


	//-----------------------------------------------------------------------
	fill_container(container);


	//-----------------------------------------------------------------------
	element.value1 = 50;
	element.value2 = 51;
	element.value3 = 52;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_push_back(&container, &element));


	element.value1 = 60;
	element.value2 = 61;
	element.value3 = 62;
	CPPUNIT_ASSERT(PDM_FALSE==pdm_container_push_back(&container, &element));


	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_full(&container));
}

void testsuite_pdm_container::test_pop_back(void)
{
	//-----------------------------------------------------------------------
	pdm_container_t&  container = *_sut_container;


	//-----------------------------------------------------------------------
	fill_container(container);


	//-----------------------------------------------------------------------
	pdm_container_pop_back(&container);


	CPPUNIT_ASSERT(3u==pdm_container_count(&container));
}

void testsuite_pdm_container::test_push_front(void)
{
	//-----------------------------------------------------------------------
	pdm_container_t& container = *_sut_container;

	element_t element;

	element_t* element_pointer;


	//-----------------------------------------------------------------------
	element.value1 = 0;
	element.value2 = 0;
	element.value3 = 0;


	//-----------------------------------------------------------------------
	fill_container(container);


	//-----------------------------------------------------------------------
	element.value1 = 999;
	element.value2 = 991;
	element.value3 = 992;
	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_push_front(&container, &element));

	
	CPPUNIT_ASSERT(PDM_TRUE==pdm_container_full(&container));


	element.value1 = 899;
	element.value2 = 891;
	element.value3 = 892;
	CPPUNIT_ASSERT(PDM_FALSE==pdm_container_push_front(&container, &element));


	element_pointer = (element_t*)pdm_container_at(&container, 0u);
	CPPUNIT_ASSERT(element_pointer->value1 == 999);
	CPPUNIT_ASSERT(element_pointer->value2 == 991);
	CPPUNIT_ASSERT(element_pointer->value3 == 992);
}

void testsuite_pdm_container::test_pop_front(void)
{
	//-----------------------------------------------------------------------
	pdm_container_t& container = *_sut_container;

	element_t* element_pointer;


	//-----------------------------------------------------------------------
	fill_container(container);


	//-----------------------------------------------------------------------
	pdm_container_pop_front(&container);

	element_pointer = (element_t*)pdm_container_at(&container, 0u);
	CPPUNIT_ASSERT(element_pointer->value1 == 20);
	CPPUNIT_ASSERT(element_pointer->value2 == 21);
	CPPUNIT_ASSERT(element_pointer->value3 == 22);


	pdm_container_pop_front(&container);

	element_pointer = (element_t*)pdm_container_at(&container, 0u);
	CPPUNIT_ASSERT(element_pointer->value1 == 30);
	CPPUNIT_ASSERT(element_pointer->value2 == 31);
	CPPUNIT_ASSERT(element_pointer->value3 == 32);
}




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
static void dump_pdm_const_string (pdm_const_string_t* const_string)
{
	printf ("const_string(%d) = {%s} \r\n",
		pdm_const_string_length(const_string),
		pdm_const_string_c_str(const_string)
		);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class testsuite_pdm_const_string : public CppUnit::TestFixture
{
private:
	pdm_size_t  _buffer_size;
	pdm_byte_t* _buffer_pointer;
	pdm_core_t* _sut_core;

public:
	testsuite_pdm_const_string();
	virtual ~testsuite_pdm_const_string();

public:
	virtual void setUp();
	virtual void tearDown();

private:
	CPPUNIT_TEST_SUITE(testsuite_pdm_const_string);
	CPPUNIT_TEST(test_length);
	CPPUNIT_TEST(test_c_str);
	CPPUNIT_TEST(test_empty);
	CPPUNIT_TEST(test_compare);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_length  (void);
	void test_c_str   (void);
	void test_empty   (void);
	void test_compare (void);
};



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CPPUNIT_TEST_SUITE_REGISTRATION(testsuite_pdm_const_string);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
testsuite_pdm_const_string::testsuite_pdm_const_string():
	_buffer_size   (0),
	_buffer_pointer(PDM_NULL_POINTER),
	_sut_core      (PDM_NULL_POINTER)
{
}

testsuite_pdm_const_string::~testsuite_pdm_const_string()
{
}

//===========================================================================
void testsuite_pdm_const_string::setUp()
{
	printf("\r\n");

	pdm_size_t element_max_count = 8;
	pdm_size_t element_size      = sizeof(pdm_char_t);


	_buffer_size    = element_size*element_max_count;
	_buffer_pointer = new pdm_byte_t[_buffer_size];

	_sut_core = new pdm_core_t;

	if (PDM_NULL_POINTER==_buffer_pointer) {CPPUNIT_ASSERT(0);}
	if (PDM_NULL_POINTER==_sut_core)       {CPPUNIT_ASSERT(0);}


	pdm_core_t& core = *_sut_core;


	core.memory.size    = _buffer_size;
	core.memory.pointer = (pdm_byte_t*)_buffer_pointer;

	if (PDM_FALSE==pdm_core_create (&core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}
}

void testsuite_pdm_const_string::tearDown()
{
	pdm_core_t& core = *_sut_core;


	if (_sut_core)
	{
		pdm_core_destroy(&core);
	}

	if (_buffer_pointer) { delete[] _buffer_pointer; }
	if (_sut_core)       { delete _sut_core;         }

	_buffer_size    = 0u;
	_buffer_pointer = PDM_NULL_POINTER;

	_sut_core = PDM_NULL_POINTER;
}

//===========================================================================
void testsuite_pdm_const_string::test_length (void)
{
	pdm_core_t& core = *_sut_core;
	
	pdm_bool_t result;


	pdm_const_string_t const_string;

	
	result = pdm_const_string_create(&const_string, "ABCD", -1, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	CPPUNIT_ASSERT(4u==pdm_const_string_length(&const_string));

	dump_pdm_const_string(&const_string);
}

void testsuite_pdm_const_string::test_c_str (void)
{
	pdm_core_t& core = *_sut_core;
	
	pdm_bool_t result;


	pdm_const_string_t const_string;

	
	result = pdm_const_string_create(&const_string, "ABCDEF", 4, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	CPPUNIT_ASSERT(4u==pdm_const_string_length(&const_string));

	CPPUNIT_ASSERT(0==strcmp(pdm_const_string_c_str(&const_string), "ABCD"));

	dump_pdm_const_string(&const_string);
}

void testsuite_pdm_const_string::test_empty (void)
{
	pdm_core_t& core = *_sut_core;
	
	pdm_bool_t result;


	pdm_const_string_t const_string;

	
	result = pdm_const_string_create(&const_string, "ABCDEF", 0, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	CPPUNIT_ASSERT(0u==pdm_const_string_length(&const_string));

	CPPUNIT_ASSERT(PDM_TRUE==pdm_const_string_empty(&const_string));

	dump_pdm_const_string(&const_string);
}

void testsuite_pdm_const_string::test_compare (void)
{
	pdm_core_t& core = *_sut_core;
	
	pdm_bool_t result;


	pdm_const_string_t const_string;

	
	result = pdm_const_string_create(&const_string, "ABCDEF", 3, &core);
	CPPUNIT_ASSERT(PDM_TRUE==result);

	CPPUNIT_ASSERT(3u==pdm_const_string_length(&const_string));

	CPPUNIT_ASSERT(PDM_FALSE==pdm_const_string_empty(&const_string));




	pdm_byte_t buffer[8];
	pdm_core_t n_core;
	pdm_const_string_t n_const_string;

	n_core.memory.size    = sizeof(buffer);
	n_core.memory.pointer = (pdm_byte_t*)buffer;

	//-----------------------------------------------------------------------
	if (PDM_FALSE==pdm_core_create (&n_core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}

	result = pdm_const_string_create(&n_const_string, "ABCDEF", 3, &n_core);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	CPPUNIT_ASSERT(0==pdm_const_string_compare(&const_string, &n_const_string));


	//-----------------------------------------------------------------------
	if (PDM_FALSE==pdm_core_create (&n_core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}

	result = pdm_const_string_create(&n_const_string, "ABCDEF", 2, &n_core);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	CPPUNIT_ASSERT(0<pdm_const_string_compare(&const_string, &n_const_string));


	//-----------------------------------------------------------------------
	if (PDM_FALSE==pdm_core_create (&n_core))
	{
		CPPUNIT_ASSERT(0);
		return;
	}

	result = pdm_const_string_create(&n_const_string, "ABCDEF", 4, &n_core);
	CPPUNIT_ASSERT(PDM_TRUE==result);


	CPPUNIT_ASSERT(0>pdm_const_string_compare(&const_string, &n_const_string));}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

//===========================================================================
#include"../stdafx.h"
#include"../../pdm/pdm/pdm.h"

//===========================================================================
#include "testsuite_pdm.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CPPUNIT_TEST_SUITE_REGISTRATION(testsuite_pdm);



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
testsuite_pdm::testsuite_pdm():
	_sut(0)
{
}

testsuite_pdm::~testsuite_pdm()
{
}

//===========================================================================
void testsuite_pdm::setUp()
{
	printf("\r\n");

//	printf("testsuite_pdm::setUp()\r\n");
	_sut = new(std::nothrow) pdm_core_t;

	CPPUNIT_ASSERT(0!=_sut);
}

void testsuite_pdm::tearDown()
{
//	printf("testsuite_pdm::tearDown()\r\n");
	delete _sut;
}

//===========================================================================
void testsuite_pdm::test_1(void)
{
//	printf ("testsuite_pdm::test_1()\r\n");
//	_sut->method();

	CPPUNIT_ASSERT(1);
}

void testsuite_pdm::test_2(void)
{
//	printf ("testsuite_pdm::test_2()\r\n");
//	_sut->method();

	CPPUNIT_ASSERT(1);
}



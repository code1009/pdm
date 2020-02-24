#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class testsuite_pdm : public CppUnit::TestFixture
{
private:
	pdm_core_t* _sut; // System Under Test

public:
	testsuite_pdm();
	virtual ~testsuite_pdm();

public:
	virtual void setUp();
	virtual void tearDown();

private:
	CPPUNIT_TEST_SUITE(testsuite_pdm);
//	CPPUNIT_TEST(test_1);
//	CPPUNIT_TEST(test_2);
	CPPUNIT_TEST_SUITE_END();

public:
	void test_1(void);
	void test_2(void);
};



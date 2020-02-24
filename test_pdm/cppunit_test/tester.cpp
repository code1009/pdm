/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <stdio.h>

//===========================================================================
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/XmlOutputter.h>

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>


//===========================================================================
#include "tester.hpp"



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// include= D:\Development\SDK\cppunit\cppunit-1.13.2\include
// lib    = D:/Development/SDK/cppunit/cppunit-1.13.2/src/cppunit/Debug/
#pragma comment(lib, "D:/Development/SDK/cppunit/cppunit-1.13.2/src/cppunit/Debug/cppunitd.lib")



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
tester::tester()
{
}

tester::~tester()
{
}

//===========================================================================
#if 0

int tester::run(void)
{
    CppUnit::TextUi::TestRunner runner;

    CppUnit::Test*      suite;
	CppUnit::Outputter* outputter;

	bool wasSucessful;

    
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();


    suite = registry.makeTest();

    runner.addTest( suite );

	outputter = new CppUnit::CompilerOutputter( &runner.result(),  CppUnit::stdCOut() );
    runner.setOutputter( outputter );


    // Run the test.
    wasSucessful = runner.run();

    // Return error code 1 if the one of test failed.

    return wasSucessful ? 0 : 1;
}

#else

int tester::run(void)
{
	CppUnit::TestResult testresult;


	CppUnit::TestResultCollector collectedresults;

	testresult.addListener(&collectedresults);


	// register listener for per-test progress output
	CppUnit::BriefTestProgressListener progress;

	testresult.addListener(&progress);


	// insert test-suite at test-runner by registry
	CppUnit::TestRunner testrunner;

	testrunner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(testresult);


	// output results in compiler-format
	CppUnit::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
	
	std::string locationFormat = "%f:%l";

	compileroutputter.setLocationFormat(locationFormat );
	compileroutputter.write();


	// Output XML for Jenkins CPPunit plugin
	std::ofstream xmlFileOut("cppunit-report.xml");

	CppUnit::XmlOutputter xmlOut(&collectedresults, xmlFileOut, std::string("UTF-8"));
	xmlOut.setStyleSheet("cppunit-report.xsl");
	xmlOut.write();


	// return 0 if tests were successful
	return collectedresults.wasSuccessful() ? 0 : 1;
}

#endif



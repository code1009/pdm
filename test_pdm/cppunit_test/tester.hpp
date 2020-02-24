#pragma once



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class tester
{
public:
	tester();
	virtual ~tester();

public:
	void run (void);

public:
	int run_and_report_console (void);
	int test_and_report_xml    (void);
};



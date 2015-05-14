// CPP_CLR_Console_App01.cpp : main project file.

#include "stdafx.h"
#include <comutil.h> // _bstr_t
#include <time.h> // time_t
#include <atlstr.h> // CString
#include "CPP_CLR_Console_App01.h" // CString GetCurrentTime_ToString()
#include <OleAuto.h> // VariantTimeToSystemTime
#include <ATLComTime.h> // COleDateTime Class
#include <math.h> // ceil
#include "Common.h" // IncMe
using namespace System;

int main(array<System::String ^> ^args)
{
	// Time Delta tesing
	//TimeDelta();

	// VARIANT and DATE
	//TestVariant();

	// Test ceil
	//bool intFunction = true;
	//TestCeil(intFunction);
	//intFunction = false;
	//TestCeil(intFunction);

	// Test External function
	int oldVal = 1;
	int newVal = IncMe(oldVal);

	Console::WriteLine("Press Enter to exit...");
	Console::ReadLine();
    return 0;
}

void TestVariant()
{
	Console::WriteLine("TestVariant - Starts");

	// Setup
	_variant_t vStartTime;
	_variant_t vEndTime;
	_variant_t vDurationTime;
	vStartTime = 2.0;
	vEndTime = 3.11;
	vStartTime.vt = VT_DATE;
	vEndTime.vt = VT_DATE;
	vDurationTime.vt = VT_DATE;
	vDurationTime = (double)vEndTime - (double)vStartTime;

	// Start Time
	_variant_t vStartTimeStr;
	vStartTimeStr = VT_DATEToVT_BSTR(vStartTime);
	printf("StartTime: ");
	printf((_bstr_t)vStartTimeStr);
	printf("\n");

	// End Time
	//char sEndTime [50];
	_variant_t vEndTimeStr;
	vEndTimeStr = VT_DATEToVT_BSTR(vEndTime);
	printf("EndTime: ");
	printf((_bstr_t)vEndTimeStr);
	printf("\n");

	// Duration Time
	_variant_t vDurationTimeStr = GetDurationTime(vStartTime, vEndTime);
	printf("DurationTime: ");
	printf((_bstr_t)vDurationTimeStr);
	printf("\n");

	//double delta = vDurationTime.dblVal * 24;
	//int hours = (int)delta;
	//int minutes = (int)((delta - hours) * 60);

	//char sDurationTime [50];
	//sprintf(sDurationTime, "%02d:%02d", hours, minutes);

	//printf("DurationTime: ");
	//printf(sDurationTime);
	//printf("\n");

	Console::WriteLine("TestVariant - Ends");
}

_variant_t GetDurationTime(_variant_t vStartTime, _variant_t vEndTime)
{
	_variant_t vRetVal;

	if ((vStartTime.vt == VT_DATE) || (vStartTime.vt == VT_R8)
		&& (vEndTime.vt == VT_DATE) || (vEndTime.vt == VT_R8))
    {
		double delta = ((double)vEndTime - (double)vStartTime) * 24;
		int hours = (int)delta;
		int minutes = (int)((delta - hours) * 60);
		char sDurationTime [50];
		sprintf(sDurationTime, "%02d:%02d", hours, minutes);
		vRetVal = sDurationTime;
	}	

	return vRetVal;
}

_variant_t VT_DATEToVT_BSTR(_variant_t vDateVal)
{
	_variant_t vDateStr;
	char sDateStr [50];
	if ((vDateVal.vt == VT_DATE) || (vDateVal.vt == VT_R8))
    {
            COleDateTime tmpDateTime = vDateVal;

            sprintf(sDateStr, "%02d/%02d/%04d %02d:%02d", 
                            tmpDateTime.GetMonth(), 
                            tmpDateTime.GetDay(), 
                            tmpDateTime.GetYear(),
                            tmpDateTime.GetHour(),
                            tmpDateTime.GetMinute());
    }
    else
    {
            strcpy(sDateStr, "00/00/0000 00:00");
    }

	vDateStr = sDateStr;
	return vDateStr;
}

void TimeDelta()
{
	CString sCnfgXml;
	CString sStartingTime = GetCurrentTime_ToString();
	BSTR temp = sStartingTime.AllocSysString();
	//sCnfgXml.Format(JOB_STARTING_TIME, temp);
	//sCnfgXml.Format("<JobStartingTime>%S</JobStartingTime>", (_bstr_t)temp);
	_tprintf(_T("%s"), sCnfgXml);
}

// returns date/time formatted according to user locale settings
CString GetCurrentTime_ToString()
{
	char buff[20];
	time_t tNow = time(NULL);
	strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&tNow));	
	CString sNow(buff);
	return sNow;
}

void TestCeil(bool intFunction)
{
	if (intFunction)
	{
		printf ( "Testing internal ceil function:\n");
		printf ( "ceil of 2.3 is %.1f\n", myceil(2.3) );
		printf ( "ceil of 3.8 is %.1f\n", myceil(3.8) );
		printf ( "ceil of -2.3 is %.1f\n", myceil(-2.3) );
		printf ( "ceil of -3.8 is %.1f\n", myceil(-3.8) );
		printf ( "ceil of 0.0 is %.1f\n", myceil(0.0) );
		printf ( "ceil of 0.01 is %.1f\n", myceil(0.01) );
	}
	else
	{
		printf ( "Testing extrenal ceil function:\n");
		printf ( "ceil of 2.3 is %.1f\n", ceil(2.3) );
		printf ( "ceil of 3.8 is %.1f\n", ceil(3.8) );
		printf ( "ceil of -2.3 is %.1f\n", ceil(-2.3) );
		printf ( "ceil of -3.8 is %.1f\n", ceil(-3.8) );
		printf ( "ceil of 0.0 is %.1f\n", ceil(0.0) );
		printf ( "ceil of 0.01 is %.1f\n", ceil(0.01) );
	}
}

double myceil(double value)
{
	double fraction = value - (int)value;
	if (fraction > 0)
	{
		return (int)value + 1.0;
	}
	else if (fraction < 0)
	{
		return (int)value - 0.0;
	}
	else
	{
		return value;
	}
}

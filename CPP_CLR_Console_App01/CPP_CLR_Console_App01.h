// CPP_CLR_Console_App01.h : Header for CPP_CLR_Console_App01.cpp
#define JOB_STARTING_TIME "<JobStartingTime>%S</JobStartingTime>"
_variant_t GetDurationTime(_variant_t vStartTime, _variant_t vEndTime);
_variant_t VT_DATEToVT_BSTR(_variant_t vDateVal);
void TestVariant();
void TimeDelta();
CString GetCurrentTime_ToString();
void TestCeil(bool intFunction);
double myceil(double value);
#include "pch.h"
#include "framework.h"
#include "age_calculator.h"
#include <commctrl.h>
class age
{

public:
	HWND Date, Calculate, Result, Heading;
	void InitializeComponent(HWND hWnd, HINSTANCE hInst)
	{
		int ypos = 10;
		int nwidth = 83;
		Heading = CreateWindowEx(WS_EX_TRANSPARENT, L"STATIC", L"Age Calculator: Set BirthDate && click on calculate button", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,    10, ypos , (nwidth * 3) + 1.02, 35, hWnd, NULL, hInst, NULL);
		Date = CreateWindowEx(0, DATETIMEPICK_CLASS, TEXT("DateTime"), WS_BORDER | WS_CHILD | WS_VISIBLE,                                                                     10, ypos + 40 , (nwidth * 3) + 1.02, 30, hWnd, NULL, hInst, NULL);
		Calculate = CreateWindow(L"button", L"Calculate", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,                                                                           10, ypos + 75, (nwidth * 3) + 1.02, 30, hWnd, (HMENU)IDC_CALCULATE_BUTTON, hInst, NULL);
		Result = CreateWindowEx(WS_EX_TRANSPARENT, L"STATIC", L"Result: Year:0 Month:0 Day:0", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,                                  10, ypos + 110, (nwidth * 3) + 1.02, 20, hWnd, NULL, hInst, NULL);
	}
	int ConvertMonthToDays(int Month)
	{
		int Days = 0;
		for (int i = 1; i < 1 + Month; i++)
		{
			if (i == 2) { Days += 28; }
			else if (i == 4 || i == 6 || i == 9 || i == 11) { Days += 30; }
			else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) { Days += 31; }
		}
		return Days;
	}

	void CalculateButton_Click(HWND hWnd)
	{
		SYSTEMTIME BirthDate{}, CurrentDate{};
		GetSystemTime(&CurrentDate);
		DateTime_GetSystemtime(Date, &BirthDate);

		double CurrentDays = ((CurrentDate.wYear * 365) + ConvertMonthToDays(CurrentDate.wMonth) + CurrentDate.wDay);
		double BirthDays = ((BirthDate.wYear * 365) + ConvertMonthToDays(BirthDate.wMonth) + BirthDate.wDay);
		int  Year = ((CurrentDays - BirthDays) / 365);
		int Month = (CurrentDate.wMonth < BirthDate.wMonth) ? 12 - BirthDate.wMonth + CurrentDate.wMonth : BirthDate.wMonth - CurrentDate.wMonth;
		int Day = ((CurrentDate.wDay - BirthDate.wDay) == 0) ? 0 : 31 - BirthDate.wDay + CurrentDate.wDay;

		TCHAR buf[100]{};
		wsprintf(buf, L"Result: Year:%d Month:%d Day:%d", Year, Month, Day);
		SetWindowText(Result, buf);
	}





};

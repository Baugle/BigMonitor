#pragma once
#include<Windows.h>
namespace Display
{
	void StartHardwareThread();
	void display();
	void MakeWindowTopMost(HWND);
	void CancelWindowTopMost(HWND);
}
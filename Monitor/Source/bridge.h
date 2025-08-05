#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	__declspec(dllexport) void InitHardwareMonitor();

	// CPU
	__declspec(dllexport) float GetCpuPower();
	__declspec(dllexport) float GetCpuClock();
	__declspec(dllexport) float GetCpuVoltage();
	__declspec(dllexport) float GetCpuLoad();
	__declspec(dllexport) float GetCpuTemperature();

	// GPU
	__declspec(dllexport) float GetGpuTemperature();
	__declspec(dllexport) float GetGpuLoad();
	__declspec(dllexport) float GetGpuPower();
	__declspec(dllexport) float GetGpuClock();
	__declspec(dllexport) float GetGpuFanSpeed();

	
	// Storage
	__declspec(dllexport) float GetDriveTemperature();
	__declspec(dllexport) float GetDriveUsed();
	__declspec(dllexport) float GetDriveReadRate();
	__declspec(dllexport) float GetDriveWriteRate();

	// Network
	__declspec(dllexport) float GetNetworkDownload();
	__declspec(dllexport) float GetNetworkUpload();
	__declspec(dllexport) float GetNetworkLoad();

#ifdef __cplusplus
}
#endif

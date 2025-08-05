#pragma once
#include <mutex>

struct HardwareStatus
{
    float cpuLoad = 0, cpuClock = 0, cpuTemp = 0, cpuVoltage = 0, cpuPower = 0;
    float gpuTemp = 0, gpuLoad = 0, gpuClock = 0, gpuPower = 0;
    float driveUsed = 0, driveTemp = 0,  driveReadRate = 0, driveWriteRate = 0;

    
};

extern HardwareStatus g_hwStatusBack;  // ��̨д���߳�ʹ��
extern HardwareStatus g_hwStatusFront; // ���̶߳�ȡ��
extern std::mutex g_hwMutex;

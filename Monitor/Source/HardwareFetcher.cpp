#include "HardwareStatus.h"
#include "bridge.h"
#include <thread>
#include <chrono>

void HardwareUpdateThread()
{
    while (true)
    {
        // 1. ���������������ʱ�����У���������
        HardwareStatus temp;
        temp.cpuLoad = GetCpuLoad();
        temp.cpuClock = GetCpuClock();
        temp.cpuTemp = GetCpuTemperature();
        temp.cpuVoltage = GetCpuVoltage();
        temp.cpuPower = GetCpuPower();
        temp.gpuLoad = GetGpuLoad();
        temp.gpuTemp = GetGpuTemperature();
        temp.gpuClock = GetGpuClock();
        temp.gpuPower = GetGpuPower();
        temp.driveUsed = GetDriveUsed();
        temp.driveTemp = GetDriveTemperature();
        temp.driveReadRate = GetDriveReadRate();
        temp.driveWriteRate = GetDriveWriteRate();


        // 2. �����л�������������ʱ�伫�̣�
        {
            std::lock_guard lock(g_hwMutex);
            g_hwStatusBack = temp;
        }

        // 3. ˢ�¼�����ɵ��� 1 �룩
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


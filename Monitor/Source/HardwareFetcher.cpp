#include "HardwareStatus.h"
#include "bridge.h"
#include <thread>
#include <chrono>

void HardwareUpdateThread()
{
    while (true)
    {
        // 1. 调用慢函数，填到临时变量中（不持锁）
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


        // 2. 快速切换缓冲区（加锁时间极短）
        {
            std::lock_guard lock(g_hwMutex);
            g_hwStatusBack = temp;
        }

        // 3. 刷新间隔（可调成 1 秒）
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}


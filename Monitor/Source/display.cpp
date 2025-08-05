#include"display.h"

#include <imgui.h>

#include <thread>
#include "HardwareStatus.h"
#include "HardwareFetcher.h"
#include "bridge.h"

extern bool showCpuUsage;
extern bool showCpuTemp;
extern bool showCpuClock;
extern bool showCpuVoltage;
extern bool showCpuPower;
extern bool showGpuUsage;
extern bool showGpuTemp;
extern bool showGpuClock;
extern bool showGpuPower;
extern bool showDriveUsed;
extern bool showDriveTemp;
extern bool showDriveReadRate;
extern bool showDriveWriteRate;
HardwareStatus snapshot;



namespace Display
{
        
    

    void StartHardwareThread()
    {
        std::thread th(HardwareUpdateThread);
        th.detach();
    }

    void display()
    {
        ImGui::Begin("System Monitor");

        std::lock_guard lock(g_hwMutex);
        snapshot = g_hwStatusBack;

        if (showCpuUsage)
            ImGui::Text("CPU Usage: %.1f%%", snapshot.cpuLoad);
        if (showCpuTemp)
            ImGui::Text("CPU Temperature: %.1f*C", snapshot.cpuTemp);
        if (showCpuClock)
            ImGui::Text("CPU Clock: %.1fGHz", snapshot.cpuClock);
        if (showCpuVoltage)
            ImGui::Text("CPU Voltage: %.1fV", snapshot.cpuVoltage);
        if (showCpuPower)
            ImGui::Text("CPU Power: %.1fW", snapshot.cpuPower);
        if (showGpuUsage)
            ImGui::Text("GPU Usage: %.1f%%", snapshot.gpuLoad);
        if (showGpuTemp)
            ImGui::Text("GPU Usage: %.1f*C", snapshot.gpuTemp);
        if (showGpuClock)
            ImGui::Text("GPU Clock: %.1fGHz", snapshot.gpuClock);
        if (showGpuPower)
            ImGui::Text("GPU Power: %.1fW", snapshot.gpuPower);
        if (showDriveUsed)
            ImGui::Text("Drive Used: %.1f%%", snapshot.driveUsed);
        if (showDriveTemp)
            ImGui::Text("Drive Temperature: %.1f*C", snapshot.driveTemp);
        if (showDriveReadRate)
            ImGui::Text("Drive Read Rate: %.1f", snapshot.driveReadRate);
        if (showDriveWriteRate)
            ImGui::Text("Drive Write Rate: %.1f", snapshot.driveWriteRate);
        
        ImGui::End();
    }

    void MakeWindowTopMost(HWND hwnd)
    {
        if (!IsWindow(hwnd)) return;

        SetWindowPos(hwnd, HWND_TOPMOST,
            0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }

    void CancelWindowTopMost(HWND hwnd)
    {
        if (!IsWindow(hwnd)) return;

        SetWindowPos(hwnd, HWND_NOTOPMOST,
            0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }

}


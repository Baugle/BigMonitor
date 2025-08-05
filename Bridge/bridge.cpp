#pragma managed
#using <System.dll>
#using "LibreHardwareMonitorLib.dll"

#include "Bridge.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace LibreHardwareMonitor::Hardware;
using namespace msclr::interop;

ref class MonitorManager
{
private:
    static Computer^ computer = nullptr;

public:
    static void Init()
    {
        if (computer == nullptr)
        {
            computer = gcnew Computer();
            computer->IsCpuEnabled = true;
            computer->IsGpuEnabled = true;
            //computer->IsMemoryEnabled = true;
            computer->IsMotherboardEnabled = true;
            computer->IsStorageEnabled = true;
            computer->IsNetworkEnabled = true;
            computer->Open();
        }
    }

    static float GetSensorValue(HardwareType type, SensorType sensorType, String^ nameMatch)
    {
        Init();

        for each (IHardware ^ hardware in computer->Hardware)
        {
            if (hardware->HardwareType == type)
            {
                hardware->Update();
                for each (ISensor ^ sensor in hardware->Sensors)
                {
                    if (sensor->SensorType == sensorType && sensor->Name->Contains(nameMatch))
                    {
                        return sensor->Value.HasValue ? sensor->Value.Value : -1.0f;
                    }
                }

                for each (IHardware ^ sub in hardware->SubHardware)
                {
                    sub->Update();
                    for each (ISensor ^ sensor in sub->Sensors)
                    {
                        if (sensor->SensorType == sensorType && sensor->Name->Contains(nameMatch))
                        {
                            return sensor->Value.HasValue ? sensor->Value.Value : -1.0f;
                        }
                    }
                }
            }
        }
        return -1.0f;
    }
};

extern "C" __declspec(dllexport) void InitHardwareMonitor()
{
    MonitorManager::Init();
}

// ===== CPU =====
extern "C" __declspec(dllexport) float GetCpuPower() { return MonitorManager::GetSensorValue(HardwareType::Cpu, SensorType::Power, "Package"); }
extern "C" __declspec(dllexport) float GetCpuClock() { return MonitorManager::GetSensorValue(HardwareType::Cpu, SensorType::Clock, "Core"); }
extern "C" __declspec(dllexport) float GetCpuVoltage() { return MonitorManager::GetSensorValue(HardwareType::Cpu, SensorType::Voltage, "Core"); }
extern "C" __declspec(dllexport) float GetCpuLoad() { return MonitorManager::GetSensorValue(HardwareType::Cpu, SensorType::Load, "Total"); }
extern "C" __declspec(dllexport) float GetCpuTemperature() { return MonitorManager::GetSensorValue(HardwareType::Cpu, SensorType::Temperature, "Package"); }

// ===== GPU (NVIDIA д╛хо) =====
extern "C" __declspec(dllexport) float GetGpuTemperature() { return MonitorManager::GetSensorValue(HardwareType::GpuNvidia, SensorType::Temperature, "GPU"); }
extern "C" __declspec(dllexport) float GetGpuLoad() { return MonitorManager::GetSensorValue(HardwareType::GpuNvidia, SensorType::Load, "Core"); }
extern "C" __declspec(dllexport) float GetGpuPower() { return MonitorManager::GetSensorValue(HardwareType::GpuNvidia, SensorType::Power, "GPU"); }
extern "C" __declspec(dllexport) float GetGpuClock() { return MonitorManager::GetSensorValue(HardwareType::GpuNvidia, SensorType::Clock, "Core"); }
extern "C" __declspec(dllexport) float GetGpuFanSpeed() { return MonitorManager::GetSensorValue(HardwareType::GpuNvidia, SensorType::Fan, "Fan"); }

// ===== Storage =====
extern "C" __declspec(dllexport) float GetDriveTemperature() { return MonitorManager::GetSensorValue(HardwareType::Storage, SensorType::Temperature, "Temperature"); }
extern "C" __declspec(dllexport) float GetDriveUsed() { return MonitorManager::GetSensorValue(HardwareType::Storage, SensorType::Load, "Used"); }
extern "C" __declspec(dllexport) float GetDriveReadRate() { return MonitorManager::GetSensorValue(HardwareType::Storage, SensorType::Throughput, "Read"); }
extern "C" __declspec(dllexport) float GetDriveWriteRate() { return MonitorManager::GetSensorValue(HardwareType::Storage, SensorType::Throughput, "Write"); }

// ===== Network =====
extern "C" __declspec(dllexport) float GetNetworkDownload() { return MonitorManager::GetSensorValue(HardwareType::Network, SensorType::Throughput, "Download"); }
extern "C" __declspec(dllexport) float GetNetworkUpload() { return MonitorManager::GetSensorValue(HardwareType::Network, SensorType::Throughput, "Upload"); }
extern "C" __declspec(dllexport) float GetNetworkLoad() { return MonitorManager::GetSensorValue(HardwareType::Network, SensorType::Load, "Total"); }

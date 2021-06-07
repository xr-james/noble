#pragma once

#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Foundation.Collections.h"
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>

using winrt::Windows::Devices::Bluetooth::GenericAttributeProfile::GattCharacteristicProperties;

std::string ws2s(const wchar_t* wstr);
std::string formatBluetoothAddress(unsigned long long BluetoothAddress);
std::string formatBluetoothUuid(unsigned long long BluetoothAddress);
std::string toStr(winrt::guid uuid);
std::vector<std::string> toPropertyArray(GattCharacteristicProperties& properties);

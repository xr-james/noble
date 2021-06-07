//
//  notify_map.cc
//  noble-winrt-native
//
//  Created by Georg Vienna on 07.09.18.
//

#include "notify_map.h"
#include "winrt/base.h"
namespace winrt::impl
{
    template <typename Async>
    auto wait_for(Async const& async, Windows::Foundation::TimeSpan const& timeout);
}

bool Key::operator==(const Key& other) const
{
    return (uuid == other.uuid && serviceUuid == other.serviceUuid &&
            characteristicUuid == other.characteristicUuid);
}

void NotifyMap::Add(std::string uuid, GattCharacteristic characteristic, winrt::event_token token)
{
    Key key = { uuid, characteristic.Service().Uuid(), characteristic.Uuid() };
    mNotifyMap.insert(std::make_pair(key, token));
    mCharacteristicMap.insert(std::make_pair(key, characteristic));
}

bool NotifyMap::IsSubscribed(std::string uuid, GattCharacteristic characteristic)
{
    try
    {
      Key key = { uuid, characteristic.Service().Uuid(), characteristic.Uuid() };
      return mNotifyMap.find(key) != mNotifyMap.end();
    }
    catch (...)
    {
      return false;
    }
}

void NotifyMap::Unsubscribe(std::string uuid, GattCharacteristic characteristic)
{
    Key key = { uuid, characteristic.Service().Uuid(), characteristic.Uuid() };
    const auto& it = mNotifyMap.find(key);
    if (it == mNotifyMap.end())
    {
        return;
    }
    auto& token = it->second;
    characteristic.ValueChanged(token);
    mNotifyMap.erase(key);
    mCharacteristicMap.erase(key);
}

void NotifyMap::Remove(std::string uuid)
{
    for (auto it = mNotifyMap.begin(); it != mNotifyMap.end();)
    {
        auto& key = it->first;
        if (key.uuid == uuid)
        {
            it = mNotifyMap.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (auto it = mCharacteristicMap.begin(); it != mCharacteristicMap.end();)
    {
        auto& key = it->first;
        if (key.uuid == uuid)
        {
            it = mCharacteristicMap.erase(it);
        }
        else
        {
            it++;
        }
    }
}

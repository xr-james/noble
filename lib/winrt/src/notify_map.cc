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
    return (uuid == other.uuid && characteristic.Service().Uuid() == other.characteristic.Service().Uuid() &&
            characteristic.Uuid() == other.characteristic.Uuid());
}

void NotifyMap::Add(std::string uuid, GattCharacteristic characteristic, winrt::event_token token)
{
    Key key = { uuid, characteristic };
    mNotifyMap.insert(std::make_pair(key, token));
}

bool NotifyMap::IsSubscribed(std::string uuid, GattCharacteristic characteristic)
{
    try
    {
      Key key = { uuid, characteristic};
      return mNotifyMap.find(key) != mNotifyMap.end();
    }
    catch (...)
    {
      return false;
    }
}

void NotifyMap::Unsubscribe(std::string uuid, GattCharacteristic characteristic)
{
    Key key = { uuid, characteristic };
    const auto& it = mNotifyMap.find(key);
    if (it == mNotifyMap.end())
    {
        return;
    }
    auto& token = it->second;
    characteristic.ValueChanged(token);
    mNotifyMap.erase(key);
}

void NotifyMap::Remove(std::string uuid)
{
    for (auto it = mNotifyMap.begin(); it != mNotifyMap.end();)
    {
        auto& key = it->first;
        if (key.uuid == uuid)
        {
            auto& token = it->second;
            key.characteristic.ValueChanged(token);
            // key.characteristic.WriteClientCharacteristicConfigurationDescriptorWithResultAsync(GattClientCharacteristicConfigurationDescriptorValue::None);
            it = mNotifyMap.erase(it);
        }
        else
        {
            it++;
        }
    }
}

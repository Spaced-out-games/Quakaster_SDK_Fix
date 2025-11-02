#include "KModuleBase.h"


namespace qk::kernel
{
    KModuleBase::KModuleBase(std::string name, SSID id)
    {
        m_Name = std::move(name);
        m_ProcessID = id;
        m_StartTime = std::chrono::steady_clock::now();
    }

    std::chrono::milliseconds KModuleBase::uptime() const
    {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - m_StartTime);
    }
}
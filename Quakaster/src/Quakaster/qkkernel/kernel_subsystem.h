#pragma once
#include "../Core.h"
#include <chrono>


namespace qk::kernel
{


    struct QK_API Kernel;

    /// <summary>
    /// Maintains process information and automates the mounting process.
    /// </summary>
    class QK_API Subsystem {
    public:
        Subsystem(int pid);
        virtual ~Subsystem();


        /// <summary>
        /// Mounts this subsystem to the provided kernel
        /// </summary>
        /// <param name="kernel">The kernel you're mounting to</param>
        /// <returns>true on success</returns>
        virtual bool mount(Kernel& kernel) = 0;

        /// <summary>
        /// Custom behavior. Might be as simple as clearing the command registry,
        /// </summary>
        virtual void shutdown();

        // Current task / state reporting. Might make it return an enum
        virtual std::string current_task() const;

        // process ID
        int pid = 0;

        // whether or not the  is running
        bool running = true;

        // the time that the subsystem started
        std::chrono::steady_clock::time_point start_time;

        // how long the process has been open. 
        std::chrono::steady_clock::duration uptime() const;

        
    };
}
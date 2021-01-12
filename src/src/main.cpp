#include <iostream>
#include <chrono>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/bin_to_hex.h"
#include "spdlog/sinks/msvc_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

int main()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    //console_sink->set_level(spdlog::level::warn);
    //console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("multisink.txt", true);
    //file_sink->set_level(spdlog::level::trace);
    auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();

    spdlog::logger logger("multi_sink", { console_sink, file_sink, msvc_sink });
    logger.set_level(spdlog::level::trace);
    logger.set_pattern("%^ %Y-%m-%d %H:%M:%S.%e [%L] [%t] - [%@,%!] %v %$");
    logger.flush_on(spdlog::level::warn);
    spdlog::flush_every(std::chrono::seconds(3));

    while(1)
    {
        logger.trace("this should level is trace,this should level is trace");
        logger.debug("this should level is debug,this should level is debug");
        logger.info("this should level is info,this should level is info");
        logger.warn("this should level is warn,this should level is warn");
        logger.error("this should level is error,this should level is error");
        logger.critical("this should level is critical,this should level is critical");
        std::cout << __FILE__ <<" "<< __FUNCTION__ <<" "<< __LINE__;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}

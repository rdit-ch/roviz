
#include "core/logger.h"

namespace roviz
{

std::shared_ptr<spdlog::logger> logger;

void initLogger(void)
{
    std::vector<spdlog::sink_ptr> sinks;

    auto log_stdout = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    log_stdout->set_level(spdlog::level::warn);
    sinks.push_back(log_stdout);

    // TODO Make that dynamic
    auto log_file = std::make_shared<spdlog::sinks::simple_file_sink_mt>("/tmp/roviz.log");
    log_file->set_level(spdlog::level::info);
    sinks.push_back(log_file);

    logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
    spdlog::register_logger(logger);
}

}

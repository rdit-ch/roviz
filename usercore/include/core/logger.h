#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include "spdlog/spdlog.h"
#include "core/export_handling.h"

namespace roviz
{
    extern std::shared_ptr<spdlog::logger> logger;

    void ROVIZ_EXPORT initLogger(void);
}

#endif // LOGGER_H

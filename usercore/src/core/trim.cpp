
#include "core/trim.h"
#include "core/logger.h"

namespace roviz
{

Trim::Trim(TrimImpl *impl)
    : impl(impl)
{
    logger->error_if(impl == nullptr, "Trying to construct a Trim without an implementation");
}

double Trim::value() const
{
    return impl->value();
}

}

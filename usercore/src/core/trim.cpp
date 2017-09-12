
#include "core/trim.h"

Trim::Trim(TrimImpl *impl)
    : impl(impl)
{
}

double Trim::value() const
{
    return impl->value();
}


#include "core/trim.h"

namespace roviz
{

Trim::Trim(TrimImpl *impl)
    : impl(impl)
{
}

double Trim::value() const
{
    return impl->value();
}

}


#include "core/trim.h"

Trim::Trim(RovizItem *item, std::string name, double min, double max, int steps, bool logarithmic, std::function<void (double)> notifier_func)
    : TrimBase(item, name, min, max, steps, logarithmic, notifier_func)
{
}

Trim::Trim(Trim &&trim)
    : TrimBase(std::move(trim))
{
}

Trim &Trim::operator=(Trim &&trim)
{
    TrimBase::operator=(std::move(trim));
    return *this;
}

double Trim::value() const
{
    return TrimBase::value();
}

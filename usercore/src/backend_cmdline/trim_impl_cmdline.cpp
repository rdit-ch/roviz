
#include "backend_cmdline/trim_impl_cmdline.h"

namespace roviz
{

double TrimImplCmdline::value()
{
    return this->val;
}

void TrimImplCmdline::setValue(double val)
{
    this->val = val;
}

}

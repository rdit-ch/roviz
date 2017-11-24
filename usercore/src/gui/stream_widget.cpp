
#include "gui/stream_widget.h"

namespace roviz
{

StreamWidget::StreamWidget(OutputPrivate *out)
{
    this->out = out;
}

OutputPrivate *StreamWidget::output()
{
    return this->out;
}

}


#include "gui/stream_widget.h"

StreamWidget::StreamWidget(OutputPrivate *out)
{
    this->out = out;
}

OutputPrivate *StreamWidget::output()
{
    return this->out;
}

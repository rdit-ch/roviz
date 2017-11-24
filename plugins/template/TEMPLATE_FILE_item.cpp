
#include "TEMPLATE_FILE_item.h"

TEMPLATE_CLASSItem::TEMPLATE_CLASSItem()
    : roviz::Item("TEMPLATE_CLASS")
{
    ROVIZ_INIT_ITEM(TEMPLATE_CLASS);

    this->input = this->addInput<roviz::Image>("Input");
    this->output = this->addOutput<roviz::Image>("Output");
}

TEMPLATE_CLASSItem::~TEMPLATE_CLASSItem()
{
    this->stop();
}

void TEMPLATE_CLASSItem::thread()
{
    while(this->input.waitForInput())
    {
    }
}

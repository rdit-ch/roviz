
#include "TEMPLATE_FILE_item.h"

TEMPLATE_CLASSItem::TEMPLATE_CLASSItem()
    : PortableItem("TEMPLATE_CLASS")
{
    PORTABLE_INIT(TEMPLATE_CLASS);

    this->input = this->addImageInput("Input");
    this->output = this->addImageOutput("Output");
}

TEMPLATE_CLASSItem::~TEMPLATE_CLASSItem()
{
    this->stop();
}

void TEMPLATE_CLASSItem::thread()
{
    while(this->waitForImage(this->input))
    {
    }
}


#include "backend_dev/trim_dev_base_p.h"

#include <QVariant>
#include <QSlider>
#include "helper/settings_scope.h"
#include "core/roviz_item.h"

void TrimDevBasePrivate::load()
{
    // TODO SettingsScope() becomes invalid during destruction but still emits
    // the parentScopeChanged() signal. This should be fixed in the
    // itemframework. Maybe it is in the newest version?
    if(this->loaded)
        return;

    QVariant var = this->item->settingsScope()->value("Trim/" + QString::fromStdString(this->name));
    if(var.isValid())
        this->main_slider->setValue(var.toInt());
    else
        this->main_slider->setValue(0);
    this->loaded = true;
}

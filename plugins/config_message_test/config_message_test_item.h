#ifndef CONFIGMESSAGETEST_ITEM_H
#define CONFIGMESSAGETEST_ITEM_H

#include "core/roviz_item.h"
#include "streams/message_m.h"
#include "config/config.h"

class ConfigMessageTestItem : public roviz::Item
{
#if ROVIZ_BACKEND == ROVIZ_BACKEND_Dev
    Q_OBJECT
#endif

public:
    ROVIZ_INVOKABLE ConfigMessageTestItem();
    ~ConfigMessageTestItem();

protected:
    void thread(void) override;

private:
    roviz::Output<roviz::Message> output;

    roviz::Config<int> conf_int;
    roviz::Config<double> conf_double;
    roviz::Config<std::string> conf_string;
    roviz::Config<std::vector<std::string> > conf_list;
    roviz::Config<bool> conf_bool;
    roviz::Config<roviz::FilePath> conf_path_any, conf_path_dir, conf_path_ex, conf_path_mult;

    std::vector<std::string> list_values;

    static std::string listToString(const std::vector<std::string> &list);
};

#endif // CONFIGMESSAGETEST_ITEM_H

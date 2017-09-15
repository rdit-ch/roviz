#ifndef CONFIGMESSAGETEST_ITEM_H
#define CONFIGMESSAGETEST_ITEM_H

#include "core/roviz_item.h"
#include "streams/message_m.h"
#include "config/config.h"

class ConfigMessageTestItem : public RovizItem
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
    Output<Message> output;

    Config<int> conf_int;
    Config<double> conf_double;
    Config<std::string> conf_string;
    Config<std::vector<std::string> > conf_list;
    Config<bool> conf_bool;
    Config<FilePath> conf_path_any, conf_path_dir, conf_path_ex, conf_path_mult;

    std::vector<std::string> list_values;

    static std::string listToString(const std::vector<std::string> &list);
};

#endif // CONFIGMESSAGETEST_ITEM_H

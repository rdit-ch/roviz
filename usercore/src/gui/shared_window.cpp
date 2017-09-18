
#include "gui/shared_window.h"

#include <QObject>
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QSize>
#include <QRect>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTabBar>
#include <QToolButton>
#include <QCloseEvent>
#include "helper/settings_scope.h"
#include "backend_dev/roviz_item_base_dev.h"
#include "gui/dock_widget_signaling.h"

QMap<SettingsScope*, SharedWindow*> SharedWindow::inst;

SharedWindow::SharedWindow(QWidget *parent)
    : QMainWindow(parent),
      ico_start(QIcon(":/usercore/res/start.png")),
      ico_restart(QIcon(":/usercore/res/restart.png")),
      ico_pause(QIcon(":/usercore/res/pause.png")),
      ico_unpause(QIcon(":/usercore/res/unpause.png")),
      ico_stop(QIcon(":/usercore/res/stop.png")),
      ico_new_tab(QIcon(":/usercore/res/new_tab.png"))
{
    this->running = false;
    this->paused = false;
    this->initialized = false;

    this->btn_start = new QToolButton();
    this->btn_pause = new QToolButton();
    this->btn_stop = new QToolButton();
    this->tab = new QTabBar();
    this->btn_new_tab = new QToolButton();
    this->main_window = new QMainWindow();
    QHBoxLayout *btn_layout = new QHBoxLayout();
    QHBoxLayout *tab_layout = new QHBoxLayout();
    QVBoxLayout *main_layout = new QVBoxLayout();
    QWidget *central = new QWidget();

    this->btn_start->setIcon(this->ico_start);
    this->btn_pause->setIcon(this->ico_pause);
    this->btn_stop->setIcon(this->ico_stop);
    this->btn_start->setIconSize(QSize(50, 50));
    this->btn_pause->setIconSize(QSize(50, 50));
    this->btn_stop->setIconSize(QSize(50, 50));
    this->btn_start->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->btn_pause->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->btn_stop->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->btn_start->setFixedSize(50, 50);
    this->btn_pause->setFixedSize(50, 50);
    this->btn_stop->setFixedSize(50, 50);
    this->btn_start->setAutoRaise(true);
    this->btn_pause->setAutoRaise(true);
    this->btn_stop->setAutoRaise(true);
    btn_layout->addWidget(this->btn_start);
    btn_layout->addWidget(this->btn_pause);
    btn_layout->addWidget(this->btn_stop);
    btn_layout->setAlignment(Qt::AlignLeft);

    this->btn_new_tab->setIcon(this->ico_new_tab);
    this->btn_new_tab->setIconSize(QSize(20, 20));
    this->btn_new_tab->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->btn_new_tab->setAutoRaise(true);
    this->tab->setMovable(true);
    this->tab->setChangeCurrentOnDrag(true);
    this->tab->setTabsClosable(true);
    this->main_window->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->main_window->setDockOptions(QMainWindow::AnimatedDocks |
                                      QMainWindow::AllowTabbedDocks |
                                      QMainWindow::AllowNestedDocks);
    this->main_window->setStyleSheet("QMainWindow::separator {background-color: gray; width: 5px; height: 5px}");
    tab_layout->addWidget(this->tab);
    tab_layout->addWidget(this->btn_new_tab);
    tab_layout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    main_layout->addLayout(btn_layout);
    main_layout->addLayout(tab_layout);
    main_layout->addWidget(this->main_window);
    central->setLayout(main_layout);
    this->setCentralWidget(central);

    connect(this->btn_start, &QPushButton::clicked,
            this, &SharedWindow::start);
    connect(this->btn_pause, &QPushButton::clicked,
            this, &SharedWindow::pause);
    connect(this->btn_stop, &QPushButton::clicked,
            this, &SharedWindow::stop);
    connect(this->btn_new_tab, &QPushButton::clicked,
            this, &SharedWindow::addTab);
    connect(this->tab, &QTabBar::currentChanged,
            this, &SharedWindow::changeToTab);
    connect(this->tab, &QTabBar::tabCloseRequested,
            this, &SharedWindow::tabClosed);
    connect(this->tab, &QTabBar::tabMoved,
            this, &SharedWindow::tabMoved);
    connect(this->tab, &QTabBar::tabBarDoubleClicked,
            this, &SharedWindow::tabStartRename);

    // That's probably the only place that gets called only once in the
    // beginning  without adding a new class/function.
    qRegisterMetaType<StreamObject>();
}

bool SharedWindow::allChildrenClosed()
{
    for(auto child : this->dock_items)
        if(child->isVisible())
            return false;

    return true;
}

void SharedWindow::destroy()
{
    delete this;
}

void SharedWindow::start()
{
    if(this->running)
    {
        for(RovizItemBaseDev *item : this->parents)
            item->stop();

        for(RovizItemBaseDev *item : this->parents)
            item->start();

        this->btn_pause->setIcon(this->ico_pause);
        this->paused = false;
    }
    else
    {
        for(RovizItemBaseDev *item : this->parents)
            item->start();

        this->btn_start->setIcon(this->ico_restart);
        this->btn_pause->setEnabled(true);
        this->running = true;
    }
}

void SharedWindow::pause()
{
    if(this->paused)
    {
        for(RovizItemBaseDev *item : this->parents)
            item->unpause();

        this->btn_pause->setIcon(this->ico_pause);
        this->paused = false;
    }
    else
    {
        for(RovizItemBaseDev *item : this->parents)
            item->pause();

        this->btn_pause->setIcon(this->ico_unpause);
        this->paused = true;
    }
}

void SharedWindow::stop()
{
    for(RovizItemBaseDev *item : this->parents)
        item->stop();

    this->running = false;
    this->btn_start->setIcon(this->ico_start);
    this->paused = false;
    this->btn_pause->setIcon(this->ico_pause);
    this->btn_pause->setEnabled(false);
}

void SharedWindow::addTab()
{
    this->states.append(QByteArray());
    this->tab->setCurrentIndex(this->tab->addTab(QString("Tab #") + QString::number(this->tab->count() + 1)));
}

void SharedWindow::changeToTab(int index)
{
    if(index == this->active_tab || this->active_tab == -1)
        return;

    this->states[this->active_tab] = this->main_window->saveState();
    for(QWidget *w : this->dock_items)
            w->hide();

    this->main_window->restoreState(this->states[index]);
    this->tab->setCurrentIndex(index);
    this->active_tab = index;
    // Otherwise, the seperator is still visible when changing to a blank tab
    this->main_window->repaint();
}

void SharedWindow::tabClosed(int index)
{
    if(this->tab->count() == 1)
    {
        this->states[0] = QByteArray();
        for(QWidget *w : this->dock_items)
                w->hide();
        this->close();
    }
    else
    {
        this->states.remove(index);
        // Invalidate the active tab, because we don't want the changeToTab function to be executed
        this->active_tab = -1;
        this->tab->removeTab(index);
        this->main_window->restoreState(this->states[this->tab->currentIndex()]);
        this->active_tab = this->tab->currentIndex();
    }
}

void SharedWindow::tabMoved(int to, int from)
{
    std::swap(this->states[from], this->states[to]);
    this->active_tab = to;
}

void SharedWindow::tabStartRename(int index)
{
    this->rename_edit = new QLineEdit(this->tab);
    this->rename_edit->show();
    QRect rect = this->tab->tabRect(index);
    int left_margin = 6, top_margin = 3;
    this->rename_edit->move(rect.left() + left_margin, rect.top() + top_margin);
    this->rename_edit->resize(rect.width() - 2 * left_margin, rect.height() - 2 * top_margin);
    this->rename_edit->setText(this->tab->tabText(index));
    this->rename_edit->selectAll();
    this->rename_edit->setFocus();
    this->rename_index = index;
    connect(this->rename_edit, &QLineEdit::editingFinished,
            this, &SharedWindow::tabFinishRename);
}

void SharedWindow::tabFinishRename()
{
    this->tab->setTabText(this->rename_index, this->rename_edit->text());
    this->rename_edit->deleteLater();
}

void SharedWindow::itemClosed()
{
    if(this->allChildrenClosed())
    {
        if(this->tab->count() > 1)
            this->tab->removeTab(this->tab->currentIndex());
        else
            this->close();
    }
}

void SharedWindow::load()
{
    if(!this->initialized)
    {
        QStringList state_list = this->project_settings->value("roviz/SharedWindow/States").toStringList();
        for(QString var : state_list)
        {
            QByteArray ba;
            ba.append(var);
            this->states.append(QByteArray::fromBase64(ba));
        }
        QStringList tab_names = this->project_settings->value("roviz/SharedWindow/Tabs").toStringList();
        this->active_tab = this->project_settings->value("roviz/SharedWindow/ActiveTab").toInt();
        for(QString t : tab_names)
            this->tab->addTab(t);
        this->tab->setCurrentIndex(this->active_tab);
        if(this->tab->count() == 0)
        {
            this->states.append(this->main_window->saveState());
            this->tab->addTab("Tab #1");
        }
        // Size is not valid until the first tab is present
        this->btn_new_tab->setFixedSize(this->tab->tabRect(0).height(), this->tab->tabRect(0).height());
        this->main_window->restoreState(this->states[this->active_tab]);
        this->initialized = true;
    }
    this->show();
}

void SharedWindow::addItem(RovizItemBaseDev* item)
{
    if(!this->parents.contains(item))
    {
        DockWidgetSignaling *dock = new DockWidgetSignaling(item->name(), this->main_window);
        dock->setWidget(item->widget());
        // Needed for saving/restoring the layout
        dock->setObjectName(item->name());
        this->main_window->addDockWidget(Qt::TopDockWidgetArea, dock);
        this->dock_items.append(dock);
        this->parents.append(item);
        item->widget()->hide();
        dock->hide();
        connect(dock, &DockWidgetSignaling::closed,
                this, &SharedWindow::itemClosed);
        if(this->running)
            item->start();
    }
}

void SharedWindow::removeItem(RovizItemBaseDev *item)
{
    this->parents.removeOne(item);
    QDockWidget *d = qobject_cast<QDockWidget*>(item->widget()->parentWidget());
    this->dock_items.removeOne(d);
    d->deleteLater();
    item->widget()->deleteLater();
}

SharedWindow *SharedWindow::instance(SettingsScope *proj)
{
    if(proj == nullptr)
        return nullptr;

    // Get instance for the current project
    SharedWindow *sw = SharedWindow::inst.value(proj, nullptr);

    if(sw == nullptr)
    {
        // Create instance if it doesn't exist already
        sw = new SharedWindow(nullptr);

        // We have to ensure proper deletion of every SharedWindow. We can't
        // make it static because it would be destructed after QApplication,
        // and that leads to SEGFAULTs for QObjects. Instead, we want to delete
        // it as soon as the project is closed. We can't make it it's parent
        // directly, because a QObject is not allowed to be the parent of a
        // QWidget. Instead, we wait for the destroyed() signal and destroy it
        // then.
        connect(proj, &QObject::destroyed,
                sw, &SharedWindow::destroy);

        SharedWindow::inst.insert(proj, sw);
        sw->project_settings = proj;
    }

    return sw;
}

void SharedWindow::closeEvent(QCloseEvent *)
{
    QStringList tab_names;

    for(int i = 0; i < this->tab->count(); i++)
        tab_names.append(this->tab->tabText(i));

    QStringList state_list;
    for(QByteArray state : this->states)
        state_list.append(state.toBase64());

//    this->project_settings->setValue("roviz/SharedWindow/Tabs", tab_names);
//    this->project_settings->setValue("roviz/SharedWindow/ActiveTab", this->active_tab);
//    this->project_settings->setValue("roviz/SharedWindow/States", state_list);

    // We don't want to close the window to preserve it's state for when it's
    // opened the next time.
    this->hide();
}

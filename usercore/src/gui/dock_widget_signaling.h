#ifndef DOCKWIDGETSIGNALING_H
#define DOCKWIDGETSIGNALING_H

#include <QDockWidget>
#include <QString>

class QWidget;
class QCloseEvent;
class QShowEvent;

namespace roviz
{

/**
 * @brief QDockWidget that emits signals
 *
 * This is a normal QDockWidget, but it emits signals when closed/shown.
 *
 * \sa SharedWindow
 */
class DockWidgetSignaling : public QDockWidget
{
    Q_OBJECT

public:
    DockWidgetSignaling(QString title, QWidget *parent);
    ~DockWidgetSignaling() = default;

    /**
     * @brief Close event
     * @param event The close event
     *
     * See QDockWidget::closeEvent
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief Show event
     * @param event Show event
     *
     * See QDockWidget::showEvent
     */
    void showEvent(QShowEvent *event) override;

signals:
    /**
     * @brief The widget was closed
     */
    void closed(void);

    /**
     * @brief The widget is shown
     */
    void shown(void);
};

}

#endif // DOCKWIDGETSIGNALING_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSharedPointer>
#include <unordered_map>
#include <unordered_set>

namespace Ui
{
class MainWindow;
}

class Communicator;
class BookieWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionMatch_Book_toggled(bool checked);
    void OnCommunicatorLogin(bool success);

    void on_actionPinnacle_toggled(bool arg1);

private:
    Ui::MainWindow* ui;
    std::unordered_map<QObject*, BookieWidget *> m_activeBookies;
    void AddOrDeleteBookieWidget(QObject *sender, Communicator *communicator, bool togled);
};

#endif // MAINWINDOW_H

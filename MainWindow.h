#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <functional>
#include <QSharedPointer>
#include <unordered_map>
#include <unordered_set>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionMatch_Book_toggled(bool checked);

private:
    Ui::MainWindow* ui;
    std::unordered_map<QObject*, std::function<void()>> m_freeBookieCallbacks;
};

#endif // MAINWINDOW_H

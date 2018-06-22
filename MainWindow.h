#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QMap>
#include <functional>
#include <QJsonObject>

namespace Ui
{
class MainWindow;
}

class JsonModel;
class QNetworkAccessManager;
class QNetworkReply;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_loginBtn_clicked();
    void on_request_complete(QNetworkReply *);

    void on_eventBtn_clicked();

    void on_sportsBtn_clicked();

private:
    Ui::MainWindow* ui;
    JsonModel* jsonModel = nullptr;
    QNetworkAccessManager *restClient = nullptr;
    QUrl apiUrl;
    QString sessionToken;
    QJsonObject eventsResponse;
    QMap<QNetworkReply*, std::function<void()>> onRequestOk;
    int currentOffset = 0, perPage = 20;
};

#endif // MAINWINDOW_H

#ifndef BOOKIEWIDGET_H
#define BOOKIEWIDGET_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class BookieWidget;
}

class Communicator;
class JsonModel;

class BookieWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookieWidget(QWidget *parent = nullptr, Communicator *communicator = nullptr);
    ~BookieWidget();

private:
    Ui::BookieWidget *ui;
    Communicator *m_communicator = nullptr;
    JsonModel* m_jsonModel = nullptr;
    bool m_loggedIn = false;

Q_SIGNALS:
    void Login(const QString &userName, const QString &password);
    void CollectData();

public slots:
    void OnLoginButtonClicked();
    void OnCollectDataButtonClicked();
    void OnDataReady(QJsonObject);
    void OnLoginCompleted(bool success);
};

#endif // BOOKIEWIDGET_H

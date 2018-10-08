#ifndef BOOKIEWIDGET_H
#define BOOKIEWIDGET_H

#include <QWidget>
#include <QJsonDocument>

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

Q_SIGNALS:
    void Login(const QString &userName, const QString &password);

public slots:
    void OnLoginButtonClicked();
    void OnDataReady(QJsonDocument);
};

#endif // BOOKIEWIDGET_H

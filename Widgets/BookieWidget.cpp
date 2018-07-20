#include "BookieWidget.h"
#include "ui_BookieWidget.h"
#include "Communicators/Communicator.h"
#include "JsonModel.h"
#include <QJsonDocument>

BookieWidget::BookieWidget(QWidget *parent, Communicator *communicator) :
    QWidget(parent),
    ui(new Ui::BookieWidget), m_communicator(communicator), m_jsonModel(new JsonModel(this))
{
    ui->setupUi(this);
    ui->treeView->setModel(m_jsonModel);

    connect(ui->loginBtn, &QPushButton::clicked, this, &BookieWidget::OnLoginButtonClicked);

    if(m_communicator)
    {
        connect(this, &BookieWidget::Login, m_communicator, &Communicator::OnLoginButtonClicked);

        connect(m_communicator, &Communicator::DataReady, this, &BookieWidget::OnDataReady);
    }
}

BookieWidget::~BookieWidget()
{
    delete ui;
}

void BookieWidget::OnLoginButtonClicked()
{
    auto userName = ui->usrEdit->text(), password = ui->pwdEdit->text();
    if(!userName.isEmpty() && !password.isEmpty())
    {
        emit Login(userName, password);
    }
}

void BookieWidget::OnDataReady(QJsonObject object)
{
    if(!object.isEmpty())
    {
        m_jsonModel->parse(QJsonDocument(object));
    }
}

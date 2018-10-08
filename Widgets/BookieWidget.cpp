#include "BookieWidget.h"
#include "ui_BookieWidget.h"
#include "Communicators/Communicator.h"
#include "JsonModel.h"
#include <QJsonDocument>

BookieWidget::BookieWidget(QWidget *parent, Communicator *communicator) :
    QWidget(parent),
    ui(new Ui::BookieWidget)
{
    ui->setupUi(this);
    m_jsonModel = new JsonModel(this);
    m_communicator = communicator;

    if(m_communicator)
    {
        ui->groupBox->setTitle(communicator->ApiPath());
        m_communicator->setParent(this);
        connect(this, &BookieWidget::Login, m_communicator, &Communicator::OnLoginButtonClicked);
        connect(m_communicator, &Communicator::DataReady, this, &BookieWidget::OnDataReady);
    }

    ui->treeView->setModel(m_jsonModel);

    connect(ui->loginBtn, &QPushButton::clicked, this, &BookieWidget::OnLoginButtonClicked);
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

void BookieWidget::OnDataReady(QJsonDocument object)
{
    m_jsonModel->parse(object);
}

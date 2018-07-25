#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Communicators/MatchbookCommunicator.h"
#include "Widgets/BookieWidget.h"
#include "OdbData/Models/OdbBookie.hxx"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionMatch_Book_toggled(bool checked)
{
    AddOrDeleteBookieWidget(sender(), new MatchbookCommunicator(), checked);
}

void MainWindow::OnCommunicatorLogin(bool success)
{
    if(success)
        ui->collectDataBtn->setEnabled(true);
}

void MainWindow::AddOrDeleteBookieWidget(QObject *sender, Communicator *communicator, bool togled)
{
    if(togled)
    {
        connect(communicator, &Communicator::LoginComplete, this, &MainWindow::OnCommunicatorLogin);
        connect(ui->collectDataBtn, &QPushButton::clicked, communicator, &Communicator::OnCollectDataButtonClicked);

        auto bookieWidget = new BookieWidget(this, communicator);

        connect(bookieWidget, &BookieWidget::destroyed, [this](){
            if(!m_activeBookies.size())
                ui->collectDataBtn->setEnabled(false);
        });

        ui->BookiesBox->layout()->addWidget(bookieWidget);
        m_activeBookies.emplace(sender, bookieWidget);
    }
    else
    {
        auto deleter = m_activeBookies.find(sender);
        if(deleter != m_activeBookies.end())
        {
            ui->BookiesBox->layout()->removeWidget(deleter->second);
            m_activeBookies.erase(deleter);
            deleter->second->deleteLater();
        }
    }
}

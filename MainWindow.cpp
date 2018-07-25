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
    if(checked)
    {
        auto bookieWidget = new BookieWidget(ui->BookiesBox, new MatchbookCommunicator());
        connect(ui->collectDataBtn, &QPushButton::clicked, bookieWidget, &BookieWidget::OnCollectDataButtonClicked);
        ui->BookiesBox->layout()->addWidget(bookieWidget);
        m_freeBookieCallbacks.emplace(sender(), [bookieWidget, this](){
            ui->BookiesBox->layout()->removeWidget(bookieWidget);
            disconnect(ui->collectDataBtn, &QPushButton::clicked, bookieWidget, &BookieWidget::OnCollectDataButtonClicked);
            bookieWidget->deleteLater();
        });
    }
    else
    {
        m_freeBookieCallbacks[sender()]();
    }
}

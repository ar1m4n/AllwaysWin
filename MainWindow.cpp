#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Communicators/MatchbookCommunicator.h"
#include "Widgets/BookieWidget.h"

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
        auto bookieWidget = new BookieWidget(this, new MatchbookCommunicator());
        ui->centralWidget->layout()->addWidget(bookieWidget);
    }
    else
    {
        for(int i = 0; i < ui->centralWidget->layout()->count(); ++i)
        {
            auto bookieWidget = ui->centralWidget->layout()->itemAt(i)->widget();
            auto commuicator = std::find_if(bookieWidget->children().begin(), bookieWidget->children().end(),
                [](const QObject* child) {
                    return dynamic_cast<const MatchbookCommunicator*>(child);
                }
            );

            if(commuicator != bookieWidget->children().end())
            {
                ui->centralWidget->layout()->removeWidget(bookieWidget);
                bookieWidget->deleteLater();
                return;
            }
        }
    }
}

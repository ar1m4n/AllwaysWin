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

void MainWindow::on_actionAdd_New_Bookie_triggered()
{
    ui->centralWidget->layout()->addWidget(new BookieWidget(this, new MatchbookCommunicator(this)));
}

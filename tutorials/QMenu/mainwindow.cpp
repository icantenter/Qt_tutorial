#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help")); //by this statement the menubar will show a menubar called "Help"
    auto action1 = new QAction(tr("action1"), this);
    auto action2 = new QAction(tr("action2"), this);

    helpMenu->addAction(action1);
    helpMenu->addSeparator();       //add separator between action1 and action2
    helpMenu->addAction(action2);

    menuBar()->addSeparator();
    QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


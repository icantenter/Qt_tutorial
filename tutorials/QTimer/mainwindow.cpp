#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{

	ui->setupUi(this);
	this->timer = new QTimer(this);
    //this->timer->setInterval(1000 * 3);
    this->timer->setInterval(1000 * 60 * 30);

	connect(this->timer, &QTimer::timeout, this, &MainWindow::WorkTimeOut);
    this->timer->start();

}

void MainWindow::WorkTimeOut()
{
	BreakHint();

}

void MainWindow::BreakHint()
{
		QMessageBox::information(NULL,
			"休息提示", "你已经工作了30分钟\n请注意休息");
}

MainWindow::~MainWindow()
{
	delete ui;
}


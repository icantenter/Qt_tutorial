#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_buttons();
    init_time();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::file_append_routine()
{
    QFile *file_append = new QFile(QDir::currentPath() + "/" + this->current_date.toString()); //此路径下没有就会自己创建一个

    if (file_append->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        /*QDataStream append_stream(file_append);

        append_stream << this->current_task->text()
                      << this->task_begin << QTime::currentTime();*/
        Pd::ROUTINE append_routine{this->current_task->text(), this->task_begin, QTime::currentTime()};
        file_append->write((char *)&append_routine, sizeof(Pd::ROUTINE));
        file_append->close();
    }

    if (file_append->open(QFile::ReadOnly | QFile::Text))
    {
        Pd::ROUTINE display_routine;
        QString display_string;

        while (!file_append->atEnd())
        {
             file_append->read((char *)&display_routine, sizeof(Pd::ROUTINE));

             display_string += "任务" + display_routine.task_name.toUtf8() + ":  \n";
             display_string += "起始时间: "+ display_routine.task_begin.toString() + "\n";
             display_string += "结束时间: "+ display_routine.task_end.toString() + "\n";
        }

        /*QDataStream display_stream(file_append);
        QString display_string, temp_string;
        QTime temp_time;

        while (!display_stream.atEnd())
        {
            display_stream >> temp_string;
            temp_string.prepend("任务");
            temp_string += ":  \n";
            display_string += temp_string.toUtf8();

            display_stream >> temp_time;
            display_string += "起始时间: "+ temp_time.toString() + "\n";

            display_stream >> temp_time;
            display_string += "结束时间: "+ temp_time.toString() + "\n";
        }*/

        ui->textBrowser->setHtml(display_string);
        file_append->close();
    }
}

void MainWindow::on_task_buttons_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender()); //获取发射信号的对象
    //file_append_routine();
    this->current_task->setText(button->text());
    this->task_begin = QTime::currentTime();

}

/*
void MainWindow::on_jump_buttons_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());


}

void MainWindow::jump_page(int page)
{

}
*/
void MainWindow::update_date()
{
    this->current_date = QDate::currentDate();
}
/*
void MainWindow::save_routine()
{
    Pd::ROUTINE routine;

    routine.task_name = this->current_task->text();
    routine.task_begin = this->task_begin;
    routine.task_end = QTime
}*/

void MainWindow::onTimeOut()
{
    QString display_time;
    int duration;

    if (QDate::currentDate() > this->current_date)
    {
        update_date();
    }
    QTime current_time = QTime::currentTime();
    duration = current_time.hour() * 360 + current_time.minute() * 60 + current_time.second() - this->task_begin.hour() * 360 - this->task_begin.minute() * 60 - this->task_begin.second();
    for (int i = 0; i < 3; i++)
    {
        display_time.prepend(QString::number(duration % 60));
        if (i != 2)
        {
            display_time.prepend(":");
        }
        duration /= 60;
    }
    ui->lcdNumber->display(display_time);
}

void MainWindow::init_time()
{
    this->current_date = QDate::currentDate();
    this->task_begin = QTime::currentTime();
    this->timer = new QTimer(this);
    this->timer->setInterval(1000);

    connect(this->timer, &QTimer::timeout, this, &MainWindow::onTimeOut);
    this->timer->start();
}

void MainWindow::init_buttons()
{
    QPushButton *temp;
    this->current_task = ui->current_task;
    QObjectList list = children();

    foreach (QObject *obj, list)
    {
        if (obj->metaObject()->className() == QStringLiteral("QWidget"))
        {
            QObjectList list2 = obj->children();
            foreach (QObject *obj1, list2)
            {
                if (obj1->inherits("QPushButton"))
                {
                    temp = qobject_cast<QPushButton *>(obj1);
                    switch (temp->property("tag").toInt())
                    {
                    case Pd::TaskTag:
                        connect(temp, &QPushButton::clicked, this, &MainWindow::on_task_buttons_clicked);
                        break;

                    case Pd::JumpTag:
                        //connect(temp, &QPushButton::clicked, this, &MainWindow::on_jump_buttons_clicked);
                        break;
                    }
                }
            }
        }
    }
}

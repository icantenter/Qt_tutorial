#include "textfinder.h"
#include "ui_textfinder.h"

textfinder::textfinder(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::textfinder)
{
    ui->setupUi(this);
    loadTextFile();
    loadCompleter();
}

textfinder::~textfinder()
{
    delete ui;
}

void textfinder::on_findButton_clicked()
{
    QString searchString = ui->input->text();
    QString substrings;

    for (int i = 0; i < this->list.length(); i++)
    {
        if (this->list[i].contains(searchString))
            substrings.append(this->list[i]);
    }
    if (substrings.length() == 0)
    {
        substrings.append("not find");
    }
    ui->textEdit->setPlainText(substrings);

}

void textfinder::loadTextFile()
{
    //QStringList files = QFileDialog::getOpenFileNames(this, windowTitle());
    // QTextStream in(&inputFile);
    QString temp;
    QFile inputFile(":/input.txt");
    inputFile.open(QIODevice::ReadOnly);

    temp = inputFile.readLine(); //读取一行放到字符串里
    while (!temp.isNull())       //字符串有内容
    {
        this->list.append(temp); //循环读取下行
        temp = inputFile.readLine();
    }
    inputFile.close();

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}

void textfinder::loadCompleter()
{
    QCompleter *completer = new QCompleter(this->list, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->input->setCompleter(completer);
}

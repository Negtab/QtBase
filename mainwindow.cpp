#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QSqlRecord"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C://Users/Asus/Documents/Qt/dbtest1.5.sqlite");
    db.open();
    QSqlQuery query(db);

    if (query.exec("SELECT * FROM test"))
    {
        QString message;

        QSqlRecord record = query.record();
        while (query.next())
        {
            for (int i = 0; i < record.count(); i++)
            {
                message += record.fieldName(i) + ": " + query.value(i).toString() + "\n";
            }
            message += "\n";
        }

        QMessageBox::information(nullptr, "Данные таблицы", message);


    }
    else
    {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось выполнить запрос к БД");
    }
    db.close();
}


void MainWindow::on_pushButton_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C://Users/Asus/Documents/Qt/dbtest1.5.sqlite");
    db.open();
    QSqlQuery query(db);
    QString message;
    query.exec("SELECT * FROM test");
    QString text = ui->textEdit->toPlainText();
    while(query.next())
    {
        QString nameF = query.value(1).toString();
        if(nameF == text)
        {
            QString indexF = query.value(0).toString();
            message = nameF +" " + indexF;
            break;
        }
        else
        {
            message = "Не найден";
        }
    }
    QMessageBox::information(nullptr, "Искомый человек", message);


    db.close();
}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C://Users/Asus/Documents/Qt/dbtest1.5.sqlite");
    db.open();
    QSqlQuery query(db);
    QString textName = ui->textEdit->toPlainText();
    QString textId = ui->textEdit_2->toPlainText();
    query.prepare("INSERT INTO test (test_id, name) values(:id, :name)");
    query.bindValue(":id", textId);
    query.bindValue(":name", textName);
    query.exec();
    db.close();
}


void MainWindow::on_pushButton_4_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C://Users/Asus/Documents/Qt/dbtest1.5.sqlite");
    db.open();
    QSqlQuery query(db);
    QString text = ui->textEdit->toPlainText();

    query.prepare("DELETE FROM test WHERE name = :name");
    query.bindValue(":name", text);
    query.exec();

    db.close();

}


void MainWindow::on_pushButton_5_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C://Users/Asus/Documents/Qt/dbtest1.5.sqlite");
    db.open();
    QSqlQuery query(db);
    QString textId = ui->textEdit->toPlainText();
    QString textNewName = ui->textEdit_2->toPlainText();

    query.prepare("UPDATE test SET name = :name WHERE test_id = :id");
    query.bindValue(":name", textNewName);
    query.bindValue(":id", textId);
    query.exec();

    db.close();
}


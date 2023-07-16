#include "form1.h"
#include "ui_form1.h"
#include "QSqlRecord"
#include "QMessageBox"

form1::form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::form1)
{
    ui->setupUi(this);
}

form1::~form1()
{
    delete ui;
}

void form1::on_pushButtonShow_clicked()
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


#include "form.h"
#include "form1.h"
#include "ui_form.h"
#include "mainwindow.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}



void Form::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C://Users/Asus/Documents/Qt/dbtest1.5.sqlite");
    db.open();
    QSqlQuery query(db);


    QString textName = ui->textEdit->toPlainText();
    QString textId = ui->textEdit_2->toPlainText();

    query.exec("SELECT * FROM test");

    bool isExist = false;
    bool isAdmin = false;

    QString adminOrUser = ui->comboBox->currentText();
    if(adminOrUser.compare("admin") == 0)
    {
        isAdmin = true;
    }
    else
    {
        isAdmin = false;
    }

    while(query.next())
    {
        QString nameF = query.value(1).toString();
        QString textIdF = query.value(0).toString();
        bool isAdminF = query.value(2).toBool();
        if(nameF == textName && isAdminF == isAdmin && textIdF == textId)
        {
            isExist = true;
            break;
        }
        else
        {
            isExist = false;
            break;
        }
    }


    if(isExist == true && isAdmin == true)
    {
        MainWindow *window = new MainWindow();
        window->show();
    }
    if(isExist == true && isAdmin == false)
    {
        form1 *window = new form1();
        window->show();
    }
    if(isExist == false)
    {
        query.prepare("INSERT INTO test (test_id, name, root) values(:id, :name, :root)");
        query.bindValue(":id", textId);
        query.bindValue(":name", textName);
        query.bindValue(":root", isAdmin);
        query.exec();
        if(isAdmin == true)
        {
            MainWindow *window = new MainWindow();
            window->show();
        }
        else
        {
            form1 *window = new form1();
            window->show();
        }
    }


    db.close();
}




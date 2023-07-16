#ifndef FORM1_H
#define FORM1_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class form1;
}

class form1 : public QWidget
{
    Q_OBJECT

public:
    explicit form1(QWidget *parent = nullptr);
    ~form1();

private slots:
    void on_pushButtonShow_clicked();

private:
    Ui::form1 *ui;
};

#endif // FORM1_H

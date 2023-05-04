#ifndef FUNCTIONMAIN_H
#define FUNCTIONMAIN_H

#include "DatabaseManager.h"
#include "DeviceRegister.h"

#include <QDialog>

namespace Ui {
class FunctionMain;
}

class FunctionMain : public QDialog
{
    Q_OBJECT

public:
    FunctionMain(QWidget *parent, QString username, QString password);
    ~FunctionMain();

private slots:
    void on_Display_2_clicked();

    void on_Display_clicked();

    void on_Display_4_clicked();

    void on_Display_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();
private:
    Ui::FunctionMain *ui;
    QString user;
    QString pass;
};

#endif // FUNCTIONMAIN_H

#include "LoginQt.h"
//#include "ui_mainwindow.h"
#include "Login.h"
#include "ui_LoginQt.h"
/**
*@brief GUI for loggin into the system
*@author Xu Wang 250 748 901, Henry Chen 251 166 178, Artur Krupa, 251190423
**/

/**
*@brief Constructor for Mainwindow object
*@param *parent
*@author Xu Wang 250 748 901
*@return nothing 
**/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}
/**
*@brief Destructor for MainWindow object
*@author Xu Wang 250 748 901
*@return nothing
*@param nothing
**/
MainWindow::~MainWindow()
{
    delete ui;
}

/**
*@brief This function allows the user to see the main screen if their login credentials are valid, or they can try to login again if their credentials are invalid
*@author Xu Wang 250 748 901, Henry Chen 251 166 178, Artur Krupa, 251190423
*@return nothing
*@param nothing
**/
void MainWindow::on_pushButton_clicked()
{

    QString username,password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();

    DatabaseManager* manager = DatabaseManager::instance();
    manager->createTable("Device");
    manager->createTable("Attends");


if (Login::instance()->AuthenticateUser(username.toStdString(),password.toStdString())){ 
        this->hide();
        mFunctionmain = new FunctionMain(this, username, password);
        mFunctionmain->show();
    }
else { 
    ui->label_3->setText("Invalid Credentials Entered");
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
}

}


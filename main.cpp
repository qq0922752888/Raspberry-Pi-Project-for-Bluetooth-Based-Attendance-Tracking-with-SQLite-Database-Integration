#include "LoginQt.h"

#include <QApplication>
/**
*@brief calls the system GUI's
*@author Xu Wang 250 748 901
**/

/**
*@brief Starts up the GUI's
*@param argc, argv - Number of command line arguements and the arguements in a vector
*@author Xu Wang 250 748 901
*@returns nothing
**/
int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <QTableWidget>
#include <QLinkedList>
#include "Schedule.h"

Schedule schedule;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.load("input.txt");

    QTableWidget* teacherTable = w.centralWidget()->findChild<QTableWidget*>(QString("teacherTableWidget"));
    QStringList list;
    list << "TeacherID" << "Name" << "Second Name" << "Last Name";
    teacherTable->setHorizontalHeaderLabels(list);
    teacherTable->setColumnCount(4);


    w.show();
    return a.exec();
}

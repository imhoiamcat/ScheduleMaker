#include "mainwindow.h"
#include <QApplication>
#include <QTableWidget>
#include <QLinkedList>
#include <QDesktopWidget>
#include <QStyle>
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

    w.setGeometry(QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            a.desktop()->availableGeometry().size(),
            a.desktop()->availableGeometry()
    ));
    w.show();
    return a.exec();
}

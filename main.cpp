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
    QTableWidget* teacherTable = w.centralWidget()->findChild<QTableWidget*>(
            QString("teacherTableWidget"));

    w.setGeometry(QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            a.desktop()->availableGeometry().size(),
            a.desktop()->availableGeometry()
    ));
    w.show();
    return a.exec();
}

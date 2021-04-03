#include <QTableView>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pushButton_clicked() {

    QTableWidget *table = this->centralWidget()->findChild<QTableWidget *>(QString("teacherTableWidget"));

    int row = schedule.teacherCount();
    schedule.addTeacher("Ivan");

    table->setRowCount(schedule.teacherCount());

    QTableWidgetItem *item = new QTableWidgetItem(
            QString(to_string(schedule.getTeacher(row).getID()).c_str()));
    table->setItem(row, 0, item);

    item = new QTableWidgetItem(
            QString(schedule.getTeacher(row).getFirstName().c_str()));
    table->setItem(row, 1, item);

    item = new QTableWidgetItem(
            QString(schedule.getTeacher(row).getSecondName().c_str()));
    table->setItem(row, 2, item);

    item = new QTableWidgetItem(
            QString(schedule.getTeacher(row).getLastName().c_str()));
    table->setItem(row, 3, item);
}



void MainWindow::on_pushButton_2_clicked()
{
    QTableWidget *table = this->centralWidget()->findChild<QTableWidget *>(QString("teacherTableWidget"));
    int row = schedule.teacherCount() - 1;
    if (row >= 0) {
        schedule.removeLastTeacher();
        table->removeRow(row);
    }
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{

}

// Make schedule
void MainWindow::on_pushButton_7_clicked()
{
    schedule.make();

}

void MainWindow::load(const string& input_name) {
    schedule.load(input_name);
    QTableWidget *table = this->centralWidget()->findChild<QTableWidget *>(QString("teacherTableWidget"));

    int count = schedule.teacherCount();
    table->setRowCount(count);

    for (int row = 0; row < count; row++) {
        QTableWidgetItem *item = new QTableWidgetItem(
                QString(to_string(schedule.getTeacher(row).getID()).c_str()));
        table->setItem(row, 0, item);

        item = new QTableWidgetItem(
                QString(schedule.getTeacher(row).getFirstName().c_str()));
        table->setItem(row, 1, item);

        item = new QTableWidgetItem(
                QString(schedule.getTeacher(row).getSecondName().c_str()));
        table->setItem(row, 2, item);

        item = new QTableWidgetItem(
                QString(schedule.getTeacher(row).getLastName().c_str()));
        table->setItem(row, 3, item);
    }

    table = this->centralWidget()->findChild<QTableWidget *>(QString("gradeTableWidget"));

    table->setRowCount(schedule.getProgram().size());
    int row = 0;
    for (pair<string, vector<pair<Lesson, int>>> i: schedule.getProgram()) {
        QTableWidgetItem *item = new QTableWidgetItem(
                QString(to_string(row).c_str()));

        table->setItem(row, 0, item);

        item = new QTableWidgetItem(QString(i.first.c_str()));
        table->setItem(row++, 1, item);
    }

}

void MainWindow::on_teacherTableWidget_cellClicked(int row, int column)
{
    QTableWidget *table = this->centralWidget()->findChild<QTableWidget *>(QString("teacherTimeTableWidget"));

    for (int k = 0; k < 6; k++) {
        for (int j = 0; j < 8; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(
                    QString(to_string(schedule.getTeacher(row).getTime()[k][j]).c_str()));
            table->setItem(k, j, item);
        }
    }
}

void MainWindow::on_gradeTableWidget_cellClicked(int row, int column)
{
    QTableWidget *gradeTable = this->centralWidget()->findChild<QTableWidget *>(QString("gradeTableWidget"));
    QTableWidget *table = this->centralWidget()->findChild<QTableWidget *>(QString("gradeDetailsTableWidget"));

    auto item  = gradeTable->item(row, 1);


    string grade = item->text().toStdString();

    auto details = schedule.getProgram().at(grade);
    table->setRowCount(details.size());
    for (int i = 0; i < details.size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(
                QString(details[i].first.getSubj().c_str()));
        table->setItem(i, 0, item);

        item = new QTableWidgetItem(
                QString(schedule.getTeacher(details[i].first.getTeacher()).getName().c_str()));
        table->setItem(i, 1, item);

        item = new QTableWidgetItem(
                QString(to_string(details[i].second).c_str()));
        table->setItem(i, 2, item);
    }
}

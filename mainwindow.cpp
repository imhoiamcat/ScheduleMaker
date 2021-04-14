#include <QTableView>
#include <QFileDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ScheduleJSONConverter.h"
#include "ScheduleXMLConverter.h"
#include "ScheduleXLSXConverter.h"

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

    table->setRowCount(schedule.teacherCount());

    QTableWidgetItem *item = new QTableWidgetItem(
            QString(to_string(schedule.getTeacher(row).getID()).c_str()));
    table->setItem(row, 0, item);

    item = new QTableWidgetItem(
            QString(schedule.getTeacher(row).getName().c_str()));
    table->setItem(row, 1, item);
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
                QString(schedule.getTeacher(row).getName().c_str()));
        table->setItem(row, 1, item);
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

    table = this->centralWidget()->findChild<QTableWidget *>(QString("scheduleTableWidget"));

    table->setRowCount(schedule.getProgram().size());
    row = 0;
    for (pair<string, vector<pair<Lesson, int>>> i: schedule.getProgram()) {

        QTableWidgetItem* item = new QTableWidgetItem(QString(i.first.c_str()));
        table->setItem(row++, 0, item);
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
                QString(details[i].first.getTeacher() >= 0 ?
                schedule.getTeacher(details[i].first.getTeacher()).getName().c_str() : ""));
        table->setItem(i, 1, item);

        item = new QTableWidgetItem(
                QString(to_string(details[i].second).c_str()));
        table->setItem(i, 2, item);
    }
}

void MainWindow::on_generateButton_clicked()
{
    schedule.make();
}

void MainWindow::on_scheduleTableWidget_cellClicked(int row, int column)
{
    if (schedule.getSchedule().empty()) return;

    QTableWidget *scheduleTable = this->centralWidget()->findChild<QTableWidget *>(QString("scheduleTableWidget"));
    auto item  = scheduleTable->item(row, 0);

    const string grade = item->text().toStdString();

    QTableWidget *dayTable[] = {
            this->centralWidget()->findChild<QTableWidget *>(QString("monSchedTableWidget")),
            this->centralWidget()->findChild<QTableWidget *>(QString("tueSchedTableWidget")),
            this->centralWidget()->findChild<QTableWidget *>(QString("wedSchedTableWidget")),
            this->centralWidget()->findChild<QTableWidget *>(QString("thuSchedTableWidget")),
            this->centralWidget()->findChild<QTableWidget *>(QString("friSchedTableWidget")),
            this->centralWidget()->findChild<QTableWidget *>(QString("satSchedTableWidget")),
    };

    vector<vector<Lesson>> s = schedule.getSchedule().at(grade);
    for (int i = 0; i < 6; i++) {
        dayTable[i]->setRowCount(8);
        for (int j = 0; j < 8; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(QString(to_string(j).c_str()));
            dayTable[i]->setItem(j, 0, item);
            if (s[i][j].getTeacher() != -1) {
                QTableWidgetItem *item = new QTableWidgetItem(QString(s[i][j].getSubj().c_str()));
                dayTable[i]->setItem(j, 1, item);

                item = new QTableWidgetItem(QString(schedule.getTeacher(s[i][j].getTeacher()).getName().c_str()));
                dayTable[i]->setItem(j, 2, item);
            } else {
                QTableWidgetItem *item = new QTableWidgetItem(QString(""));
                dayTable[i]->setItem(j, 1, item);

                item = new QTableWidgetItem(QString(""));
                dayTable[i]->setItem(j, 2, item);
            }
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    std::string file_name = QFileDialog::getOpenFileName(this,
        tr("Open Schedule"), ".", tr("Schedule Files (*.txt)")).toStdString();

    load(file_name);
}

void MainWindow::on_actionSave_triggered()
{
    schedule.save("out.txt");
}

void MainWindow::on_actionJSON_triggered()
{
  std::string file_name = QFileDialog::getSaveFileName(this,
                                                       tr("Save Schedule"), ".", tr("JSON Files (*.json)")).toStdString();
  schedule.save(file_name, ScheduleJSONConverter());
}

void MainWindow::on_actionXML_triggered()
{
  std::string file_name = QFileDialog::getSaveFileName(this,
                                                       tr("Save Schedule"), ".", tr("XML Files (*.xml)")).toStdString();
  schedule.save(file_name, ScheduleXMLConverter());
}

void MainWindow::on_actionXLSX_triggered()
{
  std::string file_name = QFileDialog::getSaveFileName(this,
                                                       tr("Save Schedule"), ".", tr("Excel Files (*.xlsx)")).toStdString();
  schedule.save(file_name, ScheduleXLSXConverter());
}

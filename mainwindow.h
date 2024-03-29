#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Teacher.h"
#include "Schedule.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void load(const string& input_name);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_teacherTableWidget_cellClicked(int row, int column);

    void on_gradeTableWidget_cellClicked(int row, int column);

    void on_generateButton_clicked();

    void on_scheduleTableWidget_cellClicked(int row, int column);

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionJSON_triggered();

    void on_actionXML_triggered();

    void on_actionXLSX_triggered();

 private:
  Ui::MainWindow *ui;
  Schedule schedule;
};

#endif // MAINWINDOW_H

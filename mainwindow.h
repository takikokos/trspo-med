#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class VaccineTable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_authButton_clicked();

    void on_openFileButton_clicked();

    void on_exitButton_clicked();

    void on_covidCheckBox_stateChanged(int arg1);
    void on_flgCheckBox_stateChanged(int arg1);
    void on_tuberCheckBox_stateChanged(int arg1);
    void on_diftCheckBox_stateChanged(int arg1);
    void on_corCheckBox_stateChanged(int arg1);

    void on_addNewRowButton_clicked();

    void on_deleteButton_clicked();

    void on_saveAllButton_clicked();

    void on_saveReportButton_clicked();

    void on_searchByNameButton_clicked();

    void on_searchByGroupButton_clicked();

    void on_resetSearchButton_clicked();

private:
    Ui::MainWindow *ui;
    VaccineTable *vaccines = nullptr;
    QStringListModel *applied_filters = nullptr;

    QString curFileName;
};
#endif // MAINWINDOW_H

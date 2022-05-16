#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QDate>

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

    void on_findOutdatedButton_clicked();

    void on_allCheckedButton_clicked();

    void on_allEmptyButton_clicked();

    void on_findUpToDateButton_clicked();

private:
    Ui::MainWindow *ui;
    VaccineTable *vaccines = nullptr;
    QStringListModel *applied_filters = nullptr;

    QString curFileName;
};

class FilterDateProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    FilterDateProxyModel(QObject *parent = 0) : QSortFilterProxyModel(parent) {};

    int dateCol() const { return filterCol; }
    void setDateCol(int col) {filterCol = col; };
    void setOutdated(bool val) {outdated = val; };

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override
    {
        QString date_s = sourceModel()->data(sourceModel()->index(sourceRow, filterCol)).toString();

        if (date_s.length() == 0){ // means no end date
            return !this->outdated;
        }

        QDate date = QDate::fromString(date_s, "dd.MM.yyyy");
        Q_ASSERT(date.isValid());

        if (date > QDate::currentDate()){
            return !this->outdated;
        }
        return this->outdated;
    }

private:
    bool outdated; // true if we want to show only outdated, false to show up-to-date
    int filterCol;
};

#endif // MAINWINDOW_H

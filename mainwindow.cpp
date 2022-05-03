#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "vaccinetable.h"
#include "authdlg.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vaccines = new VaccineTable(this);
    applied_filters = new QStringListModel(this);
//    ui->tableView->setModel(vaccines);
//    ui->tableView->resizeColumnsToContents();

    ui->openFileButton->setEnabled(false);
    ui->saveAllButton->setEnabled(false);
    ui->exitButton->setEnabled(false);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->covidCheckBox->setEnabled(false);
    ui->flgCheckBox->setEnabled(false);
    ui->tuberCheckBox->setEnabled(false);
    ui->diftCheckBox->setEnabled(false);
    ui->corCheckBox->setEnabled(false);

    ui->addNewRowButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);

    ui->searchByGroupButton->setEnabled(false);
    ui->searchByGroupEdit->setEnabled(false);

    ui->searchByNameButton->setEnabled(false);
    ui->searchByNameEdit->setEnabled(false);

    ui->resetSearchButton->setEnabled(false);

    ui->saveReportButton->setEnabled(false);

    ui->findOutdatedButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authButton_clicked()
{
    AuthDlg authDlg(this);

    if (authDlg.exec() != QDialog::Accepted)
        return;

    ui->authButton->setEnabled(false);
    ui->exitButton->setEnabled(true);

    QString user = authDlg.getUser();
    if (user == "admin")
    {
        ui->openFileButton->setEnabled(true);
    }
}

void MainWindow::on_openFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Открыть таблицу"), QCoreApplication::applicationDirPath(), tr("Table Data (*.csv)")
    );
    QFile file(fileName);

    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug() << "File not exists";
    } else {
        curFileName = fileName;

        vaccines->clear();

        ui->covidCheckBox->setEnabled(true);
        ui->flgCheckBox->setEnabled(true);
        ui->tuberCheckBox->setEnabled(true);
        ui->diftCheckBox->setEnabled(true);
        ui->corCheckBox->setEnabled(true);

        ui->covidCheckBox->setChecked(true);
        ui->flgCheckBox->setChecked(true);
        ui->tuberCheckBox->setChecked(true);
        ui->diftCheckBox->setChecked(true);
        ui->corCheckBox->setChecked(true);

        ui->addNewRowButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->saveAllButton->setEnabled(true);

        ui->searchByGroupButton->setEnabled(true);
        ui->searchByGroupEdit->setEnabled(true);

        ui->searchByNameButton->setEnabled(true);
        ui->searchByNameEdit->setEnabled(true);

        ui->resetSearchButton->setEnabled(true);

        ui->saveReportButton->setEnabled(true);

        ui->findOutdatedButton->setEnabled(true);

        ui->tableView->setModel(vaccines);
        ui->appliedFiltersView->setModel(applied_filters);
        ui->tableView->resizeColumnsToContents();

        QTextStream in(&file);
        in.readLine(); // skip header
        vaccines->loadFromText(in);
        ui->tableView->resizeColumnsToContents();
        applied_filters->removeRows(0, applied_filters->rowCount());
        file.close();
    }
}

void MainWindow::on_exitButton_clicked()
{
    ui->authButton->setEnabled(true);
    ui->exitButton->setEnabled(false);
    ui->openFileButton->setEnabled(false);

    ui->covidCheckBox->setEnabled(false);
    ui->flgCheckBox->setEnabled(false);
    ui->tuberCheckBox->setEnabled(false);
    ui->diftCheckBox->setEnabled(false);
    ui->corCheckBox->setEnabled(false);

    ui->addNewRowButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->saveAllButton->setEnabled(false);

    ui->searchByGroupButton->setEnabled(false);
    ui->searchByGroupEdit->setEnabled(false);

    ui->searchByNameButton->setEnabled(false);
    ui->searchByNameEdit->setEnabled(false);

    ui->resetSearchButton->setEnabled(false);

    ui->saveReportButton->setEnabled(false);

    ui->findOutdatedButton->setEnabled(false);

    vaccines->clear();
    applied_filters->removeRows(0, applied_filters->rowCount());
}


void MainWindow::on_covidCheckBox_stateChanged(int arg1)
{
    if (!arg1)
    {
        ui->tableView->hideColumn(2);
        ui->tableView->hideColumn(3);
        ui->tableView->hideColumn(4);
    }
    else
    {
        ui->tableView->showColumn(2);
        ui->tableView->showColumn(3);
        ui->tableView->showColumn(4);
    }
}

void MainWindow::on_flgCheckBox_stateChanged(int arg1)
{
    if (!arg1)
    {
        ui->tableView->hideColumn(5);
        ui->tableView->hideColumn(6);
        ui->tableView->hideColumn(7);
    }
    else
    {
        ui->tableView->showColumn(5);
        ui->tableView->showColumn(6);
        ui->tableView->showColumn(7);
    }
}

void MainWindow::on_tuberCheckBox_stateChanged(int arg1)
{
    if (!arg1)
    {
        ui->tableView->hideColumn(8);
        ui->tableView->hideColumn(9);
        ui->tableView->hideColumn(10);
    }
    else
    {
        ui->tableView->showColumn(8);
        ui->tableView->showColumn(9);
        ui->tableView->showColumn(10);
    }
}

void MainWindow::on_diftCheckBox_stateChanged(int arg1)
{
    if (!arg1)
    {
        ui->tableView->hideColumn(11);
        ui->tableView->hideColumn(12);
        ui->tableView->hideColumn(13);
    }
    else
    {
        ui->tableView->showColumn(11);
        ui->tableView->showColumn(12);
        ui->tableView->showColumn(13);
    }
}

void MainWindow::on_corCheckBox_stateChanged(int arg1)
{
    if (!arg1)
    {
        ui->tableView->hideColumn(14);
        ui->tableView->hideColumn(15);
        ui->tableView->hideColumn(16);
    }
    else
    {
        ui->tableView->showColumn(14);
        ui->tableView->showColumn(15);
        ui->tableView->showColumn(16);
    }
}


void MainWindow::on_addNewRowButton_clicked()
{
    ui->tableView->model()->insertRow( ui->tableView->model()->rowCount() );
}


void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    std::sort(selection.begin(), selection.end(), qGreater<QModelIndex>());

    // Multiple rows can be selected
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        ui->tableView->model()->removeRow( index.row());
    }
}


void MainWindow::on_saveAllButton_clicked()
{
    QFile f(curFileName);
    if ( !f.open(QIODevice::WriteOnly | QIODevice::Text) ) {
        qDebug() << "File not exists";
    } else {
        QTextStream out(&f);
        vaccines->saveToText(out);
        f.close();
        QMessageBox msg;
        msg.setWindowTitle("Сохранено");
        msg.setText("База данных " + curFileName + " успешно обновлена");
        msg.exec();
    }
}


void MainWindow::on_saveReportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Создать отчет"), QCoreApplication::applicationDirPath(), tr("Table Data (*.csv)")
    );
    QFile f(fileName);

    if ( !f.open(QIODevice::WriteOnly | QIODevice::Text) ) {
        qDebug() << "Can't open file";
    } else {
        QTextStream out(&f);
        auto model = ui->tableView->model(); // use currently displayed data for report

        int cols_count = model->columnCount();

        for (int i = 0; i < cols_count; i++ ) {
            if (ui->tableView->isColumnHidden(i)) continue;
            out << vaccines->getHeader().at(i);
            if (i + 1 != cols_count) out << ";";
        }

        out << "\n";

        for(int i = 0; i < model->rowCount(); i++)
        {
            if (ui->tableView->isRowHidden(i)) continue;
            QString s;

            for (int j = 0; j < cols_count; j++)
            {
                if (ui->tableView->isColumnHidden(j)) continue;
                auto index = model->index(i, j);
                s += model->data(index).toString() + ";";
            }
            s.remove(s.size()-1, 1);
            out << s << "\n";

        }

        f.close();
        QMessageBox msg;
        msg.setWindowTitle("Отчет");
        msg.setText("Отчет создан успешно в " + fileName);
        msg.exec();
    }
}

void MainWindow::on_searchByNameButton_clicked()
{
    QString query = ui->searchByNameEdit->text();
    if (query.trimmed().length() == 0) return;
    auto model = ui->tableView->model();
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(model);

    proxy->setFilterKeyColumn(0);
    proxy->setFilterRegExp(QRegExp("*" + query + "*", Qt::CaseInsensitive, QRegExp::Wildcard));

    ui->tableView->setModel(proxy);
    ui->searchByNameEdit->setText("");

    applied_filters->insertRow(0);
    applied_filters->setData(applied_filters->index(0), query);
}

void MainWindow::on_searchByGroupButton_clicked()
{
    QString query = ui->searchByGroupEdit->text();
    if (query.trimmed().length() == 0) return;
    auto model = ui->tableView->model();

    QSortFilterProxyModel *proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(model);

    proxy->setFilterKeyColumn(1);
    proxy->setFilterRegExp(QRegExp("*" + query + "*", Qt::CaseInsensitive, QRegExp::Wildcard));

    ui->tableView->setModel(proxy);
    ui->searchByGroupEdit->setText("");

    applied_filters->insertRow(0);
    applied_filters->setData(applied_filters->index(0), query);
}

void MainWindow::on_resetSearchButton_clicked()
{
    ui->tableView->setModel(vaccines);
    applied_filters->removeRows(0, applied_filters->rowCount());
    for (int i = 0; i < ui->tableView->model()->rowCount() ; i++ ) {
        ui->tableView->showRow(i);
    }
}

void MainWindow::on_findOutdatedButton_clicked()
{
    int selected_vacs =
            int(ui->corCheckBox->isChecked()) +
            int(ui->covidCheckBox->isChecked()) +
            int(ui->diftCheckBox->isChecked()) +
            int(ui->flgCheckBox->isChecked()) +
            int(ui->tuberCheckBox->isChecked());
     if (selected_vacs != 1){
         QMessageBox msg;
         msg.setWindowTitle("Внимание");
         msg.setText("Эту функцию можно использовать только когда выбрана 1 вакцина из всех");
         msg.exec();
         return;
     }

     int vac_date_col = -1;
     QString log_msg;

     if (ui->corCheckBox->isChecked()) { vac_date_col = 15; log_msg = "Просроченные по Кори"; }
     if (ui->covidCheckBox->isChecked()) { vac_date_col = 3; log_msg = "Просроченные по Ковиду"; }
     if (ui->diftCheckBox->isChecked()) { vac_date_col = 12; log_msg = "Просроченные по Дифтерии"; }
     if (ui->flgCheckBox->isChecked()) { vac_date_col = 6; log_msg = "Просроченные по ФЛГ"; }
     if (ui->tuberCheckBox->isChecked()) { vac_date_col = 9; log_msg = "Просроченные по Туберкулезу"; }

     FilterDateProxyModel *proxy = new FilterDateProxyModel;
     proxy->setSourceModel(ui->tableView->model());

     proxy->setDateCol(vac_date_col);

     ui->tableView->setModel(proxy);

     applied_filters->insertRow(0);
     applied_filters->setData(applied_filters->index(0), log_msg);
}

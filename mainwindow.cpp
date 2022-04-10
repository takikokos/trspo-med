#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "vaccinetable.h"
#include "authdlg.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vaccines = new VaccineTable(this);
//    ui->tableView->setModel(vaccines);
//    ui->tableView->resizeColumnsToContents();

    ui->openFileButton->setEnabled(false);
    ui->exitButton->setEnabled(false);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
        vaccines->clear();

        ui->tableView->setModel(vaccines);
        ui->tableView->resizeColumnsToContents();

        QTextStream in(&file);
        in.readLine(); // skip header
        vaccines->load_from_text(in);
        ui->tableView->resizeColumnsToContents();
        file.close();
    }
}

void MainWindow::on_exitButton_clicked()
{
    ui->authButton->setEnabled(true);
    ui->exitButton->setEnabled(false);
    ui->openFileButton->setEnabled(false);

    vaccines->clear();
}


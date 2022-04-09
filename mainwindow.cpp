#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vaccines = new VaccineTable(this);
    ui->tableView->setModel(vaccines);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open table"), QCoreApplication::applicationDirPath(), tr("Table Data (*.csv)")
    );
    QFile file(fileName);

    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug() << "File not exists";
    } else {
        QTextStream in(&file);
        in.readLine(); // skip header
        vaccines->load_from_text(in);
        ui->tableView->resizeColumnsToContents();
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete vaccines;
}


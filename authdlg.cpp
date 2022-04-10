#include "authdlg.h"
#include "ui_authdlg.h"

#include <QMessageBox>

AuthDlg::AuthDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDlg)
{
    ui->setupUi(this);

    passwords["admin"] = "password";
}

AuthDlg::~AuthDlg()
{
    delete ui;
}

void AuthDlg::done(int r)
{
    if(QDialog::Accepted == r)  // ok was pressed
        {
            QString login = ui->loginEdit->text();
            QString pass = ui->passwordEdit->text();

            if(passwords.contains(login))   // validate the data somehow
            {
                if(passwords[login] == pass)
                {
                    QDialog::done(r);
                    return;
                }
                else
                {
                    QMessageBox msg;
                    msg.setText("Неверный логин или пароль");
                    msg.setWindowTitle("Ошибка!");
                    msg.exec();
                    return;
                }
            }
            else
            {
                //statusBar->setText("Invalid data in text edit...try again...");
                QMessageBox msg;
                msg.setText("Неверный логин или пароль");
                msg.setWindowTitle("Ошибка!");
                msg.exec();
                return;
            }
        }
        else    // cancel, close or exc was pressed
        {
            QDialog::done(r);
            return;
    }
}

QString AuthDlg::getUser() const
{
    return ui->loginEdit->text();
}

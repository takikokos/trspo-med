#ifndef AUTHDLG_H
#define AUTHDLG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class AuthDlg;
}

class AuthDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDlg(QWidget *parent = nullptr);
    ~AuthDlg();

    virtual void done(int r);

    QString getUser() const;

private:
    Ui::AuthDlg *ui;

    QMap<QString, QString> passwords;
};

#endif // AUTHDLG_H

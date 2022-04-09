#ifndef VACCINETABLE_H
#define VACCINETABLE_H

#include <QStandardItemModel>
#include <QTextStream>

class VaccineTable : public QStandardItemModel
{
public:
    VaccineTable(QObject *parent = nullptr);

    void load_from_text(QTextStream &input_data, QString sep = ";");

    static const int column_count = 7;

private:

    const QStringList header = {
        "ФИО", "Группа", "Прививка ковид (дата)", "ФЛГ (дата)",
        "Прививка против туберкулеза", "Прививка против дифтерии", "Прививка против кори"
    };

};

#endif // VACCINETABLE_H

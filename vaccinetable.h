#ifndef VACCINETABLE_H
#define VACCINETABLE_H

#include <QStandardItemModel>
#include <QTextStream>

class VaccineTable : public QStandardItemModel
{
public:
    VaccineTable(QObject *parent = nullptr);

    void loadFromText(QTextStream &input_data, QString sep = ";");
    void saveToText(QTextStream &input_data, QString sep = ";");\

    QStringList getHeader() const;

    static const int column_count = 17;

private:

    const QStringList header = {
        "ФИО","Группа",
        "COVID (дата постановки)","COVID (дата окончания)","COVID (доп. информация)",
        "ФЛГ (дата постановки)","ФЛГ (дата окончания)","ФЛГ (доп. информация)",
        "Туберкулез (дата постановки)","Туберкулез (дата окончания)","Туберкулез (доп. информация)",
        "Дифтерия (дата постановки)","Дифтерия (дата окончания)","Дифтерия (доп. информация)",
        "Корь (дата постановки)","Корь (дата окончания)","Корь (доп. информация)"
    };

};

#endif // VACCINETABLE_H

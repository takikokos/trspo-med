#include "vaccinetable.h"

VaccineTable::VaccineTable(QObject *parent) :
    QStandardItemModel(parent)
{
    this->setHorizontalHeaderLabels(this->header);
    this->setColumnCount(this->column_count);
}

void VaccineTable::load_from_text(QTextStream &input_data, QString sep)
{
    while (!input_data.atEnd())
    {
        QString line = input_data.readLine();

        QList<QStandardItem *> record;

        for (QString item : line.split(sep)) {
            if (item.length() > 0)
                record.append(new QStandardItem(item));
        }

        if (record.length() > 0) {
            Q_ASSERT(record.length() == this->column_count); // what happens if we append smaller row? o_O
            this->insertRow(this->rowCount(), record);
        }
    }
}

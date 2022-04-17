#include "vaccinetable.h"

#include <QDebug>

VaccineTable::VaccineTable(QObject *parent) :
    QStandardItemModel(parent)
{
    //this->setHorizontalHeaderLabels(this->header);
    this->setColumnCount(this->column_count);

}

void VaccineTable::loadFromText(QTextStream &input_data, QString sep)
{
    this->setHorizontalHeaderLabels(this->header);
    while (!input_data.atEnd())
    {
        QString line = input_data.readLine();

        QList<QStandardItem *> record;

        for (QString item : line.split(sep)) {
            //if (item.length() > 0)
                record.append(new QStandardItem(item));
        }

        if (record.length() > 0) {
            //Q_ASSERT(record.length() == this->column_count); // what happens if we append smaller row? o_O
            this->insertRow(this->rowCount(), record);
        }
    }
}

void VaccineTable::saveToText(QTextStream &input_data, QString sep)
{
    for(int i = 0; i < this->rowCount(); i++)
    {
        QString s;
        for (int j = 0; j < this->columnCount(); j++)
        {
            s += this->item(i, j)->text() + sep;
        }
        s.remove(s.size()-1, 1);
        input_data << s << "\n";
    }
}

QStringList VaccineTable::getHeader() const
{
    return header;
}

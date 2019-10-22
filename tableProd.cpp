#include "tableProd.h"

//! [0]

TableModelP::TableModelP(QList<Product>& Dish,QObject *parent)
    : QAbstractTableModel(parent), Dishes(&Dish)
{
}

//! [0]

//! [1]
int TableModelP::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Dishes->size();
}

int TableModelP::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}
//! [1]

//! [2]
QVariant TableModelP::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= Dishes->size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &Dish = Dishes->at(index.row());

        if (index.column() == 0)
            return Dish.name;
        else if (index.column() == 1)
            return Dish.description;
    }
    return QVariant();
}
//! [2]

//! [3]
QVariant TableModelP::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Название");

            case 1:
                return tr("Количество");

            default:
                return QVariant();
        }
    }
    return QVariant();
}
//! [3]

//! [4]
bool TableModelP::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        Dishes->insert(position, { QString(), int() });

    endInsertRows();
    return true;
}
//! [4]

//! [5]
bool TableModelP::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        Dishes->removeAt(position);

    endRemoveRows();
    return true;
}
//! [5]
Product TableModelP::getProd(int i)const{
    auto Dish = Dishes->at(i);
    return Dish;
}
//! [6]
bool TableModelP::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto Dish = Dishes->value(row);

        if (index.column() == 0)
            Dish.name = value.toString();
        else if (index.column() == 1)
            Dish.description = value.toInt();
        else
            return false;

        Dishes->replace(row, Dish);
        emit dataChanged(index, index, {role});

        return true;
    }

    return false;
}
//! [6]

//! [7]
Qt::ItemFlags TableModelP::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]

//! [8]
QList<Product>* TableModelP::getContacts()
{
    return Dishes;
}
//! [8]

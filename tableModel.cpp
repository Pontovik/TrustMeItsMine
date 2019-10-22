#include "tableModel.h"

//! [0]

TableModel::TableModel(QList<Dish>* Dish, QObject *parent)
    : QAbstractTableModel(parent)
    , Dishes(Dish)
{

}
//! [0]

//! [1]
int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Dishes->size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}
//! [1]

//! [2]
QVariant TableModel::data(const QModelIndex &index, int role) const
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
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Имя");

            case 1:
                return tr("Описание");
            default:
                return QVariant();
        }
    }
    return QVariant();
}
//! [3]

//! [4]
bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        Dishes->insert(position, { QString(), QString() });

    endInsertRows();
    return true;
}
//! [4]
Dish& TableModel::getSelectedDish(int position){
    Dish*temp = &Dishes->at(position);
     return *temp;
}
//! [5]
bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        Dishes->removeAt(position);

    endRemoveRows();
    return true;
}
//! [5]

//! [6]
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto Dish = Dishes->value(row);

        if (index.column() == 0)
            Dish.name = value.toString();
        else if (index.column() == 1)
            Dish.description = value.toString();
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
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]

//! [8]
QList<Dish>* TableModel::getContacts()
{
    return Dishes;
}
//! [8]

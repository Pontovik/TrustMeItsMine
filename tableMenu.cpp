#include "tableMenu.h"

//! [0]

TableMenu::TableMenu(QList<Dish>* Dish, QObject *parent)
    : QAbstractTableModel(parent)
    , Dishes(Dish)
{

}
//! [0]

//! [1]
int TableMenu::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Dishes->size();
}

int TableMenu::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}
//! [1]

//! [2]
QVariant TableMenu::data(const QModelIndex &index, int role) const
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
        else if(index.column() == 2)
            return Dish.price;
    }
    return QVariant();
}
//! [2]

//! [3]
QVariant TableMenu::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Имя");

            case 1:
                return tr("Описание");
        case 2:
            return tr("Цена");
            default:
                return QVariant();
        }
    }
    return QVariant();
}
//! [3]

//! [4]
bool TableMenu::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        Dishes->insert(position, { QString(), QString() });

    endInsertRows();
    return true;
}
bool TableMenu::insertRows(Dish&t, int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        Dishes->insert(position, t);

    endInsertRows();
    return true;
}
//! [4]
Dish& TableMenu::getSelectedDish(int position){
    Dish*temp = &Dishes->at(position);
     return *temp;
}
//! [5]
bool TableMenu::removeRows(int position, int rows, const QModelIndex &index)
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
bool TableMenu::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto Dish = Dishes->value(row);

        if (index.column() == 0)
            Dish.name = value.toString();
        else if (index.column() == 1)
            Dish.description = value.toString();
        else if (index.column() == 2)
            Dish.price = value.toInt();
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
Qt::ItemFlags TableMenu::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]

//! [8]
QList<Dish>* TableMenu::getContacts()
{
    return Dishes;
}
//! [8]

/****************************************************************************
**
** Copyright (C) 2010-2018 B.D. Mihai.
**
** This file is part of JSON Viewer.
**
** JSON Viewer is free software: you can redistribute it and/or modify it
** under the terms of the GNU Lesser Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** JSON Viewer is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
** or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser Public License for
** more details.
**
** You should have received a copy of the GNU Lesser Public License along
** with JSON Viewer.  If not, see http://www.gnu.org/licenses/.
**
****************************************************************************/

#include "JsonModel.h"
#include "QJsonDocument"
#include <QDebug>
#include <QString>

JsonModel::JsonModel(QObject* parent) : QAbstractItemModel(parent), JsonItem(nullptr)
{
}

JsonModel::~JsonModel()
{
}

int JsonModel::columnCount(const QModelIndex&) const
{
    return 2;
}

QVariant JsonModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    JsonItem* item = static_cast<JsonItem*>(index.internalPointer());

    switch (role)
    {
    case Qt::DisplayRole:
    {
        if (index.column() == 0)
            return item->name();
        else
            return item->value();
    }
    default:
        return QVariant();
    }
}

Qt::ItemFlags JsonModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant JsonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
            return tr("Name");
        else
            return tr("Value");
    }

    return QVariant();
}

QModelIndex JsonModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    const JsonItem* parentItem;

    if (!parent.isValid())
        parentItem = this;
    else
        parentItem = static_cast<JsonItem*>(parent.internalPointer());

    JsonItem* childItem = parentItem->at(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex JsonModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    JsonItem* childItem = static_cast<JsonItem*>(index.internalPointer());
    JsonItem* parentItem = childItem->parent();

    if (parentItem == this)
        return QModelIndex();

    return createIndex(parentItem->indexOf(childItem), 0, parentItem);
}

int JsonModel::rowCount(const QModelIndex& parent) const
{
    const JsonItem* parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = this;
    else
        parentItem = static_cast<JsonItem*>(parent.internalPointer());

    return parentItem->count();
}

QVariantMap JsonModel::parse(const QByteArray& text)
{
    QJsonParseError error;
    auto json = QJsonDocument::fromJson(text, &error);
    if(error.error == QJsonParseError::NoError)
    {
        return parse(json);
    }
    else
    {
        qDebug() << error.errorString();
    }

    return QVariantMap();
}

QVariantMap JsonModel::parse(const QJsonDocument &json)
{
    beginResetModel();
    qDeleteAll(*this);
    clear();
    QVariantMap result = json.toVariant().toMap();
    parse(&result, this);
    endResetModel();
    return result;
}

void JsonModel::parse(const QVariantMap* map, JsonItem* parent)
{
    QList<QString> keyList = map->keys();

    foreach (QString key, keyList)
    {
        QVariant value = map->value(key);

        switch (value.type())
        {
        case QVariant::Map:
        {
            QVariantMap childMap = value.toMap();
            JsonItem* item = new JsonItem(parent);

            item->setName(key);
            item->setType(JsonItem::ComplexType);
            parse(&childMap, item);
            break;
        }
        case QVariant::List:
        {
            QVariantList childList = value.toList();
            JsonItem* item = new JsonItem(parent);

            item->setName(key);
            item->setType(JsonItem::ArrayType);
            parse(&childList, item);
            break;
        }
        default:
        {
            JsonItem* item = new JsonItem(parent);

            item->setName(key);
            item->setValue(value.toString());
            item->setType(JsonItem::ValueType);
        }
        }
    }
}

void JsonModel::parse(const QVariantList* list, JsonItem* parent)
{
    for (int i = 0; i < list->count(); i++)
    {
        QVariant value = list->at(i);

        switch (value.type())
        {
        case QVariant::Map:
        {
            QVariantMap childMap = value.toMap();
            JsonItem* item = new JsonItem(parent);

            item->setName(QString("[%1]").arg(i));
            item->setType(JsonItem::ComplexType);
            parse(&childMap, item);
            break;
        }
        case QVariant::List:
        {
            QVariantList childList = value.toList();
            JsonItem* item = new JsonItem(parent);

            item->setName(QString("[%1]").arg(i));
            item->setType(JsonItem::ArrayType);
            parse(&childList, item);
            break;
        }
        default:
        {
            JsonItem* item = new JsonItem(parent);

            item->setName(QString("[%1]").arg(i));
            item->setValue(value.toString());
            item->setType(JsonItem::ValueType);
        }
        }
    }
}
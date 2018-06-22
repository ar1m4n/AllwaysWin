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

#ifndef JSONITEM_H
#define JSONITEM_H

#include <QList>
#include <QString>
#include <QVariant>

class JsonItem : public QList<JsonItem*>
{
public:
    enum ItemType
    {
        ValueType,
        ArrayType,
        ComplexType
    };

public:
    JsonItem(JsonItem* itemParent);
    virtual ~JsonItem();

    const QString &name() const;
    const QString &value() const;
    JsonItem *parent() const;
    const ItemType &type() const;

    void setName(const QString& itemName);
    void setValue(const QString& itemValue);
    void setType(const ItemType& itemType);

protected:
    JsonItem* itemParent;
    QString itemName;
    QString itemValue;
    ItemType itemType;
};

#endif // JSONITEM_H

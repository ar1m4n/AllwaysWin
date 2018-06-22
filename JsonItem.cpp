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

#include "JsonItem.h"

JsonItem::JsonItem(JsonItem* parent)
{
    this->itemParent = parent;
    itemName = "";
    itemValue = "";

    if (itemParent != 0)
        itemParent->append(this);
}

JsonItem::~JsonItem()
{
    qDeleteAll(*this);
}

const QString &JsonItem::name() const
{
    return itemName;
}

const QString &JsonItem::value() const
{
    return itemValue;
}

JsonItem *JsonItem::parent() const
{
    return itemParent;
}

const JsonItem::ItemType &JsonItem::type() const
{
    return itemType;
}

void JsonItem::setName(const QString &itemName)
{
    this->itemName = itemName;
}

void JsonItem::setValue(const QString &itemValue)
{
    this->itemValue = itemValue;
}

void JsonItem::setType(const JsonItem::ItemType &itemType)
{
    this->itemType = itemType;
}

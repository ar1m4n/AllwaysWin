#pragma once

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>

enum class OdbPriceType
{
    Back, Lay
};

class OdbRunner;

#pragma db object
class OdbPrice
{
public:
    OdbPrice(double odds, double availableAmount, OdbPriceType priceType = OdbPriceType::Back);

    unsigned long Id() const;

    OdbPriceType PriceType() const;

    double Odds() const;

    double AvailableAmount() const;

    QLazySharedPointer<OdbRunner> &Runner();

private:
    friend class odb::access;
    OdbPrice() = default;

    #pragma db id auto
    unsigned long m_id;

    #pragma db default(OdbPriceType::Back)
    OdbPriceType m_priceType;

    #pragma db default(0)
    double m_odds;

    #pragma db default(0)
    double m_availableAmount;

    #pragma db not_null
    QLazySharedPointer<OdbRunner> m_runner;
};

#ifdef ODB_COMPILER
#include "OdbData/Models/OdbRunner.txx"
#endif

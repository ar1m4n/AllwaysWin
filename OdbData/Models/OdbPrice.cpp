#include "OdbPrice.txx"

OdbPrice::OdbPrice(double odds, double availableAmount, OdbPriceType priceType)
    :m_priceType(priceType), m_odds(odds), m_availableAmount(availableAmount)
{

}

unsigned long OdbPrice::Id() const
{
    return m_id;
}

OdbPriceType OdbPrice::PriceType() const
{
    return m_priceType;
}

double OdbPrice::Odds() const
{
    if(PriceType() == OdbPriceType::Lay)
        return 1 + 1 / (m_odds - 1);

    return m_odds;
}

double OdbPrice::AvailableAmount() const
{
    return m_availableAmount;
}

QLazySharedPointer<OdbRunner> &OdbPrice::Runner()
{
    return m_runner;
}

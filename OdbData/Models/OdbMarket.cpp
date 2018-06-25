#include "OdbMarket-odb.hxx"

OdbMarket::OdbMarket(const QString &name)
    :m_name(name)
{

}

unsigned long OdbMarket::Id() const
{
    return m_id;
}

const QString &OdbMarket::Name() const
{
    return m_name;
}

const QLazySharedPointer<OdbSport> &OdbMarket::Sport() const
{
    return m_sport;
}

const QOdbList<QLazySharedPointer<OdbMarket> > &OdbMarket::SameAs() const
{
    return m_sameAs;
}

void OdbMarket::UpdateSame(odb::callback_event e, odb::database &) const
{
    if(e == odb::callback_event::pre_update || e == odb::callback_event::pre_persist)
    {
        if(m_sameAs._impl().state() == odb::vector_impl::state_changed)
        {
            QList<OdbMarket*> inserted, modified;
            size_t idx = 0;
            for(auto it = m_sameAs.begin(); it != m_sameAs.end(); ++it, ++idx)
            {
                auto elState = it.list()->_impl().state(idx);
                if(it->isNull() && !it->loaded())
                    it->load();

                if(elState == odb::vector_impl::state_inserted)
                {
                    inserted.push_back(it->data());
                }
                else if(elState != odb::vector_impl::state_erased)
                {
                    modified.push_back(it.modify().data());
                }
            }

            for(auto it = inserted.begin(); it != inserted.end();)
            {
                QLazySharedPointer<OdbMarket> ptr(*it);
                for(auto other : modified)
                {
                    other->m_sameAs.push_back(ptr);
                }

                for(auto nextIt = ++it; nextIt != inserted.end(); ++nextIt)
                {
                    (*nextIt)->m_sameAs.push_back(ptr);
                }
            }
        }
    }
}

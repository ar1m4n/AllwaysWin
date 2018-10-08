#include "OdbBookieEntity.txx"

OdbBookieEntity::OdbBookieEntity(const QString &idInBookie)
    :m_idInBookie(idInBookie)
{

}

const QString &OdbBookieEntity::IdInBookie() const
{
    return m_idInBookie;
}

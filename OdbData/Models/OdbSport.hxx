#ifndef ODBSPORT_HXX
#define ODBSPORT_HXX

#include <QtCore/QString>
#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>

#pragma db object
class OdbSport
{
public:
    unsigned long Id() const {
        return m_id;
    }

private:
    friend class odb::access;
    OdbSport () = default;

    #pragma db id auto
    unsigned long m_id;
};

#endif //ODBSPORT_HXX

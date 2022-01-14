#ifndef MAPEARDADOS_H
#define MAPEARDADOS_H
#include<QString>

namespace dnn{
class MapearDados
{
public:
    virtual QString desmaterializar()const = 0;
    virtual void materializar(QString str) = 0;
};
}
#endif // MAPEARDADOS_H

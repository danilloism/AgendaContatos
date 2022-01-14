#ifndef CRUD_H
#define CRUD_H
#include<contato.h>
#include<list>
namespace dnn{//inicio
class CRUD
{
public:
    virtual void incluir(Contato &objeto) const = 0;
    virtual std::list<Contato>* listagem()const = 0;
    virtual void excluir(int id) const = 0;
    virtual void editar(Contato &objeto) const = 0;
};
}//fim
#endif // CRUD_H

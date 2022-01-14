#ifndef CONTATODAO_H
#define CONTATODAO_H
#include<QString>
#include<crud.h>
#include<fstream>
#include<map>
namespace dnn{
class ContatoDAO: public CRUD
{
private:
    QString nomeDoArquivoNoDisco;
public:
    ContatoDAO(QString nomeDoArquivoNoDisco);
    //Sobrescrevendo
    void incluir(Contato &objeto) const;
    std::list<Contato>* listagem() const;
    void excluir(int id) const;
    void editar(Contato &objeto) const;
};
}
#endif // CONTATODAO_H

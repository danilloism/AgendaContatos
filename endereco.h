#ifndef ENDERECO_H
#define ENDERECO_H
#include<QString>
#include<mapeardados.h>
#include<QStringList>

namespace dnn{
class Endereco: public MapearDados
{
private:
    QString logradouro;
    int numero;
public:
    Endereco();
    Endereco(QString logradouro, int numero);
    void setLogradouro(QString logradouro){this->logradouro = logradouro;}
    void setNumero(int numero){this->numero = numero;}
    QString getLogradouro()const{return logradouro;}
    int getNumero()const{return numero;}

    //Sobrescrevendo
    QString desmaterializar()const;
    void materializar(QString str);
};
}
#endif // ENDERECO_H

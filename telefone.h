#ifndef TELEFONE_H
#define TELEFONE_H
#include<mapeardados.h>
#include<QStringList>

namespace dnn{
class Telefone: public MapearDados
{
private:
    int id;
    int ddi;
    int ddd;
    long numero;
public:
    Telefone():id(0),ddi(0),ddd(0),numero(0){}
    Telefone(int id, int ddi, int ddd, long numero);
    int getID()const{return id;}
    int getDDI()const{return ddi;}
    int getDDD()const{return ddd;}
    int getNumero()const{return numero;}
    void setID(int id){this->id = id;}
    void setDDI(int ddi){this->ddi = ddi;}
    void setDDD(int ddd){this->ddd = ddd;}
    void setNumero(long numero){this->numero = numero;}
    QString getTelefone()const;

    //Sobrescrevendo
    QString desmaterializar()const;
    void materializar(QString str);
};
}
#endif // TELEFONE_H

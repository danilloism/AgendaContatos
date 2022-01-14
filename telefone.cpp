#include "telefone.h"
namespace dnn{
Telefone::Telefone(int id, int ddi, int ddd, long numero):
    id(id),
    ddi(ddi),
    ddd(ddd),
    numero(numero)
{
}
QString Telefone::getTelefone()const{
    QString saida;
    saida += "+" + QString::number(this->ddi);
    saida += "(" + QString::number(this->getDDD())+")";
    saida += QString::number(this->numero);
    return saida;
}
//Sobrescrevendo
QString Telefone::desmaterializar()const{
    QString saida;
    saida += QString::number(this->id) + ";";
    saida += QString::number(this->ddi) + ";";
    saida += QString::number(this->ddd) + ";";
    saida += QString::number(this->numero);
    return saida;
}
void Telefone::materializar(QString str){
    QStringList dados = str.split(";");
    id = dados[0].toInt();
    ddi = dados[1].toInt();
    ddd = dados[2].toInt();
    numero = dados[3].toInt();
}
}

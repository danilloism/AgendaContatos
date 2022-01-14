#include "endereco.h"
namespace dnn{
Endereco::Endereco():
    logradouro(""),
    numero(0)
{
}
Endereco::Endereco(QString logradouro, int numero):
    logradouro(logradouro),
    numero(numero)
{
}
//Sobrescrevendo
QString Endereco::desmaterializar()const{
    QString saida;
    saida += this->logradouro + ";";
    saida += QString::number(this->numero);
    return saida;
}
void Endereco::materializar(QString str){
    QStringList dados = str.split(";");
    logradouro = dados[0];
    numero = dados[1].toInt();
}

}

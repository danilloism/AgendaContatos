#include "contato.h"
namespace dnn{
Contato::Contato():
    id(0),
    nome(""),
    enderecoResidencial()
{
}
Contato::Contato(int id, QString nome, Endereco enderecoResidencial):
    id(id),
    nome(nome),
    enderecoResidencial(enderecoResidencial)
{
}
void Contato::limparContato(){
    id = 0;
    nome.clear();
    enderecoResidencial.setLogradouro("");
    enderecoResidencial.setNumero(0);
    telefones.clear();
}
//std::vector<QString>* Contato::getEmail()const{
//    std::vector<QString> *aux = new std::vector<QString>();
//    for(int pos=0; pos<email.size(); pos++){
//        aux->push_back(email.at(pos));
//    }
//    return aux;
//}
//std::vector<Telefone>* Contato::getTelefone()const{
//    std::vector<Telefone> *aux = new std::vector<Telefone>();
//    for(int pos=0; pos<telefones.size(); pos++){
//        aux->push_back(telefones.at(pos));
//    }
//    return aux;
//}
//Sobrescrevendo
QString Contato::desmaterializar()const{
    QString saida = QString::number(this->id);
    saida += ";";
    saida += this->nome + ";";
    saida += this->getEnderecoResidencial().desmaterializar();
    return saida;
}
void Contato::materializar(QString str){
    QStringList dados = str.split(";");
    id = dados[0].toInt();
    nome = dados[1];
    enderecoResidencial.setLogradouro(dados[2]);
    enderecoResidencial.setNumero(dados[3].toInt());
}

}

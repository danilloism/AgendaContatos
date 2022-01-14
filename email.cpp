#include "email.h"

namespace dnn {

Email::Email(int id, QString email):
    id(id),
    email(email)
{

}

QString Email::desmaterializar() const
{
    QString saida;
    saida += QString::number(this->id) + ";";
    saida += this->email;
    return saida;
}

void Email::materializar(QString str)
{
    QStringList dados = str.split(";");
    id = dados[0].toInt();
    email = dados[1];
}


}


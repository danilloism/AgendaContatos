#ifndef EMAIL_H
#define EMAIL_H
#include<mapeardados.h>
#include<QStringList>

namespace dnn {

class Email : public MapearDados
{
private:
    int id;
    QString email;

public:
    Email():id(0),email(""){}
    Email(int id, QString email);
    int getID()const{return id;}
    QString getEmail()const{return email;}
    void setID(int id){this->id = id;}
    void setEmail(QString email){this->email = email;}

    //Sobrescrevendo
    QString desmaterializar()const;
    void materializar(QString str);
};

}


#endif // EMAIL_H

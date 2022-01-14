#include "geradorid.h"
namespace dnn{
GeradorID::GeradorID():
    id(1)
{
    std::fstream arquivoID;
    arquivoID.open("./ArquivoDeID.txt",std::ios::in);
    if(!arquivoID.is_open()){
        std::ofstream arquivo;
        arquivo.open("./ArquivoDeID.txt");
        arquivo<<1;
        arquivo.close();
        arquivoID.open("./ArquivoDeID.txt",std::ios::in);
    }
    arquivoID>>id;
    arquivoID.close();
}

GeradorID::~GeradorID(){
    std::fstream arquivoID;
    arquivoID.open("./ArquivoDeID.txt",std::ios::out);
    arquivoID<<id;
    arquivoID.close();
}



}

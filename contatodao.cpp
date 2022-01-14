#include "contatodao.h"
namespace dnn{
ContatoDAO::ContatoDAO(QString nomeDoArquivoNoDisco):
    nomeDoArquivoNoDisco(nomeDoArquivoNoDisco)
{
}
//Sobrescrevendo
void ContatoDAO::incluir(Contato &objeto) const{
    std::ofstream arquivoAgenda;
    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str(),
                                   std::ios::out|std::ios::app);
    if(!arquivoAgenda.is_open()){
        throw QString("Arquivo de Agenda nao foi aberto - Metodo incluir");
    }
    arquivoAgenda<<objeto.desmaterializar().toStdString()+"\n";
    arquivoAgenda.close();
    // incluindo dados dos telefone
    std::ofstream arquivoTelefones;
    arquivoTelefones.open( "./TelefonesDosContatos.txt",
                        std::ios::out|std::ios::app);
    if(!arquivoTelefones.is_open()){
        throw QString("Arquivo de Telefones nao foi aberto - Metodo incluir");
    }
    std::vector<Telefone> fones;
    fones = objeto.getTelefone();
    for(int pos =0; pos < fones.size() ; pos++ ){
        dnn::Telefone aux = fones.at(pos);
        aux.setID(objeto.getId());
        arquivoTelefones<<aux.desmaterializar().toStdString() + "\n";
    }
    arquivoTelefones.close();


    //incluindo dados dos emails
    std::ofstream arquivoEmail;
    arquivoEmail.open( "./EmailDosContatos.txt",
                        std::ios::out|std::ios::app);
    if(!arquivoEmail.is_open()){
        throw QString("Arquivo de Email nao foi aberto - Metodo incluir");
    }
    std::vector<Email> email;
    email = objeto.getEmail();
    for(int pos =0; pos < email.size() ; pos++ ){
        dnn::Email aux = email.at(pos);
        aux.setID(objeto.getId());
        arquivoEmail<<aux.desmaterializar().toStdString() + "\n";
    }
    arquivoEmail.close();

}
std::list<Contato>* ContatoDAO::listagem()const{
    //Criando uma Lista com os dados dos contatos
    //Dados armazenados no arquivo de Contatos
    std::list<dnn::Contato> *listaContatos = 0;
    listaContatos = new std::list<dnn::Contato>();
    std::ifstream arquivoAgenda;
    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str());
    if(!arquivoAgenda.is_open()){
        throw QString("Arquivo de Agenda nao foi aberto");
    }
    std::string linha;
    std::getline(arquivoAgenda,linha);
    while(!arquivoAgenda.eof()){
        dnn::Contato objeto;
        objeto.materializar(QString::fromStdString(linha));
        listaContatos->push_back(objeto);
        std::getline(arquivoAgenda,linha);
    }
    arquivoAgenda.close();
    // Finalizando o processo de criar a lista de contatos

    //Criando uma lista com todos os telefones armazenados
    //No arquivo de telefones
    std::list<dnn::Telefone> *listaTelefones = 0;
    listaTelefones = new std::list<dnn::Telefone>();
    std::ifstream arquivoTelefones;
    arquivoTelefones.open("./TelefonesDosContatos.txt");
    if(!arquivoTelefones.is_open()){
        throw QString("Arquivo de Agenda nao foi aberto");
    }
    std::string linhaTelefone;
    std::getline(arquivoTelefones,linhaTelefone);
    while(!arquivoTelefones.eof()){
        dnn::Telefone fone;
        fone.materializar(QString::fromStdString(linhaTelefone));
        listaTelefones->push_back(fone);
        std::getline(arquivoTelefones,linhaTelefone);
    }
    arquivoTelefones.close();


    //Criando uma lista com todos os email armazenados
    //No arquivo de telefones
    std::map<int, dnn::Email> *arvoreEmail = 0;
    arvoreEmail = new std::map<int, dnn::Email>();
    int chaveArvore = 0;
    std::ifstream arquivoEmail;
    arquivoEmail.open("./EmailDosContatos.txt");
    if(!arquivoEmail.is_open()){
        throw QString("Arquivo de Email nao foi aberto");
    }
    std::string linhaEmail;
    std::getline(arquivoEmail,linhaEmail);
    while(!arquivoEmail.eof()){
        dnn::Email email;
        email.materializar(QString::fromStdString(linhaEmail));
        //arvoreEmail[chaveArvore] = email;
        arvoreEmail->insert(std::pair<int, dnn::Email>(chaveArvore,email));
        chaveArvore++;
        std::getline(arquivoEmail,linhaEmail);
    }
    arquivoEmail.close();

    std::list<dnn::Contato> *listaContatosFinal = 0;
    listaContatosFinal = new std::list<dnn::Contato>();

    std::list<dnn::Contato>::iterator iListaContatos;
    for(iListaContatos = listaContatos->begin();iListaContatos!=listaContatos->end();iListaContatos++){
        dnn::Contato objContato = *iListaContatos;
        std::list<dnn::Telefone>::iterator iListaTelefones;
        //std::map<int, dnn::Email>::iterator iArvoreEmail;
        int idContato = (*iListaContatos).getId();

        for(iListaTelefones = listaTelefones->begin();iListaTelefones!=listaTelefones->end();iListaTelefones++){
            if(idContato == (*iListaTelefones).getID() ){
                objContato.setTelefone((*iListaTelefones));
            }
        }

        /*for(iArvoreEmail = arvoreEmail->begin();iArvoreEmail!=arvoreEmail->end();iArvoreEmail++){
            if(idContato == (*iArvoreEmail).getID() ){
                objContato.setEmail((*iArvoreEmail));
            }
        }*/

        //não conseguir fazer com o iterator
        for(int i=0;i<arvoreEmail->size();i++){
            if(idContato == arvoreEmail->at(i).getID() ){
                objContato.setEmail(arvoreEmail->at(i));
            }
        }

        listaContatosFinal->push_back(objContato);
    }
    return listaContatosFinal;
}

void ContatoDAO::excluir(int id) const
{
    std::list<dnn::Contato> *lista = this->listagem();
    std::list<dnn::Contato>::iterator iListaContatos;

    std::ofstream arquivoAgenda;
    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str(),std::ios::out);
    if(!arquivoAgenda.is_open()){
        throw QString("Arquivo de Agenda nao foi aberto - Metodo excluir");
    }
    arquivoAgenda.close();

    std::ofstream arquivoTelefones;
    arquivoTelefones.open("./TelefonesDosContatos.txt",std::ios::out);
    if(!arquivoTelefones.is_open()){
        throw QString("Arquivo de Telefones nao foi aberto - Metodo excluir");
    }
    arquivoTelefones.close();

    std::ofstream arquivoEmail;
    arquivoEmail.open("./EmailDosContatos.txt",std::ios::out);
    if(!arquivoEmail.is_open()){
        throw QString("Arquivo de Email nao foi aberto - Metodo excluir");
    }
    arquivoEmail.close();


    for(iListaContatos = lista->begin();iListaContatos!=lista->end();iListaContatos++){
        int idContato = (*iListaContatos).getId();
        dnn::Contato objContato = *iListaContatos;
        if(idContato != id){
            this->incluir(objContato);
        }
    }
}

void ContatoDAO::editar(Contato &objeto) const
{
    std::list<dnn::Contato> *lista = this->listagem();
    std::list<dnn::Contato>::iterator iListaContatos;

    std::ofstream arquivoAgenda;
    arquivoAgenda.open(nomeDoArquivoNoDisco.toStdString().c_str(),std::ios::out);
    if(!arquivoAgenda.is_open()){
        throw QString("Arquivo de Agenda nao foi aberto - Metodo excluir");
    }
    arquivoAgenda.close();

    std::ofstream arquivoTelefones;
    arquivoTelefones.open("./TelefonesDosContatos.txt",std::ios::out);
    if(!arquivoTelefones.is_open()){
        throw QString("Arquivo de Telefones nao foi aberto - Metodo excluir");
    }
    arquivoTelefones.close();

    std::ofstream arquivoEmail;
    arquivoEmail.open("./EmailDosContatos.txt",std::ios::out);
    if(!arquivoEmail.is_open()){
        throw QString("Arquivo de Email nao foi aberto - Metodo excluir");
    }
    arquivoEmail.close();


    QString nome = objeto.getNome();
    QString logradouro = objeto.getEnderecoResidencial().getLogradouro();
    int numero = objeto.getEnderecoResidencial().getNumero();
    dnn::Endereco end(logradouro,numero);
    int id = objeto.getId();
    std::vector<dnn::Email> email = objeto.getEmail();
    std::vector<dnn::Telefone> telefones = objeto.getTelefone();

    for(iListaContatos = lista->begin();iListaContatos!=lista->end();iListaContatos++){
        dnn::Contato objContato = *iListaContatos;
        if(objContato.getId() == id){

            objContato.limparContato();
            objContato.setEnderecoResidencial(end);
            objContato.setNome(nome);
            for(int i=0;i<email.size();i++) objContato.setEmail(email[i]);
            for(int i=0;i<telefones.size();i++) objContato.setTelefone(telefones[i]);
            objContato.setId(id);
            this->incluir(objContato);

        }else{
            this->incluir(objContato);
        }
    }
}


}

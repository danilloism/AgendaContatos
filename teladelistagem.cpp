#include "teladelistagem.h"
#include "ui_teladelistagem.h"

TelaDeListagem::TelaDeListagem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaDeListagem),
    nomeDoArquivoDeContatos("Contatos.txt")
{
    ui->setupUi(this);
}

TelaDeListagem::~TelaDeListagem()
{
    delete ui;
}

void TelaDeListagem::on_pushButtonVoltar_clicked()
{
    this->close();
}

void TelaDeListagem::on_pushButtonListar_clicked()
{
    ui->tableWidgetListagem->clear();
    ui->tableWidgetListagem->setRowCount(0);
    std::list<dnn::Contato>* lista = 0;

    try {
        dnn::ContatoDAO agendaDeContatos(nomeDoArquivoDeContatos);
        lista = agendaDeContatos.listagem();

        std::list<dnn::Contato>::iterator iterLista;
        for(iterLista = lista->begin();iterLista!=lista->end();iterLista++){
            dnn::Contato objeto = *iterLista;
            //teste
            ui->tableWidgetListagem->setAlternatingRowColors(true);
            //ui->tableWidgetListagem->resizeColumnsToContents();
            QString id = QString::number(objeto.getId());
            QString nome = objeto.getNome();
            QString logradouro = objeto.getEnderecoResidencial().getLogradouro();
            QString numero = QString::number(objeto.getEnderecoResidencial().getNumero());
            //QString telefone = "123";
            QTableWidgetItem *item1 = new QTableWidgetItem(id);
            QTableWidgetItem *item2 = new QTableWidgetItem(nome);
            QTableWidgetItem *item3 = new QTableWidgetItem(logradouro);
            QTableWidgetItem *item4 = new QTableWidgetItem(numero);
            int linha = ui->tableWidgetListagem->rowCount();
            ui->tableWidgetListagem->insertRow(linha);
            //ui->tableWidgetListagem->
            ui->tableWidgetListagem->setItem(linha,0,item1);
            ui->tableWidgetListagem->setItem(linha,1,item2);
            ui->tableWidgetListagem->setItem(linha,2,item3);
            ui->tableWidgetListagem->setItem(linha,3,item4);

            std::vector<dnn::Telefone> telefones;
            telefones = objeto.getTelefone();
            std::vector<dnn::Email> email;
            email = objeto.getEmail();
            QString telefone2 = telefones.at(0).getTelefone();
            QTableWidgetItem *item5 = new QTableWidgetItem(telefone2);
            ui->tableWidgetListagem->setItem(linha,4,item5);
            QString email2 = email.at(0).getEmail();
            QTableWidgetItem *item6 = new QTableWidgetItem(email2);
            ui->tableWidgetListagem->setItem(linha,5,item6);

            int maiorVetor = (telefones.size()>email.size()) ? telefones.size() : email.size();

            for(int i=1;i<maiorVetor;i++){
                linha = ui->tableWidgetListagem->rowCount();
                ui->tableWidgetListagem->insertRow(linha);
                if(telefones.size()>i){
                    telefone2 = telefones.at(i).getTelefone();
                    QTableWidgetItem *item7 = new QTableWidgetItem(telefone2);
                    ui->tableWidgetListagem->setItem(linha,4,item7);
                }
                if(email.size()>i){
                    email2 = email.at(i).getEmail();
                    QTableWidgetItem *item8 = new QTableWidgetItem(email2);
                    ui->tableWidgetListagem->setItem(linha,5,item8);
                }
            }

        }

    } catch (QString &e) {
        QMessageBox::warning(this,"ERRO",e);
    }

    if(lista) delete lista;
}

void TelaDeListagem::on_pushButtonExcluir_clicked()
{
    int id = QInputDialog::getInt(this,"Leitura", "Digite o ID do contato a ser excluido:");

    try {
        dnn::ContatoDAO agendaDeContatos(nomeDoArquivoDeContatos);
        agendaDeContatos.excluir(id);

        this->on_pushButtonListar_clicked();

    } catch (QString &e) {
        QMessageBox::warning(this,"ERRO",e);
    }

}

void TelaDeListagem::on_pushButtonEditar_clicked()
{
    telaDeEdicao telaEdicao;
    telaEdicao.setModal(true);
    telaEdicao.exec();
    this->on_pushButtonListar_clicked();
}

#include "teladeedicao.h"
#include "ui_teladeedicao.h"

telaDeEdicao::telaDeEdicao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::telaDeEdicao)
{
    ui->setupUi(this);
    this->idContato = QInputDialog::getInt(this,"Leitura", "Digite o ID do contato a ser editado:");
    ui->lineEditID->setText(QString::number(idContato));

    dnn::ContatoDAO agenda("Contatos.txt");
    std::list<dnn::Contato> *lista = agenda.listagem();
    std::list<dnn::Contato>::iterator iListaContatos = lista->begin();
    int aux = 0;

    for(iListaContatos = lista->begin();iListaContatos!=lista->end(), aux==0;iListaContatos++){
        dnn::Contato objContato = *iListaContatos;
        if(objContato.getId() == this->idContato){
            aux = 1;

            ui->lineEditNome->setText(objContato.getNome());
            ui->lineEditLogradouro->setText(objContato.getEnderecoResidencial().getLogradouro());
            ui->lineEditNumero->setText(QString::number(objContato.getEnderecoResidencial().getNumero()));

            for(int i=0; i<objContato.getEmail().size(); i++){
                QString email = objContato.getEmail()[i].getEmail();
                dnn::Email objEmail(contato.getId(), email);
                contato.setEmail(objEmail);

                int linha = ui->listWidgetEmail->count();
                ui->listWidgetEmail->insertItem(linha, email);
            }

            for(int i=0; i<objContato.getTelefone().size(); i++){
                QString ddd_str = QString::number(objContato.getTelefone()[i].getDDD());
                QString ddi_str = QString::number(objContato.getTelefone()[i].getDDI());
                QString numero_str = QString::number(objContato.getTelefone()[i].getNumero());

                int ddd = ddd_str.toInt();
                int ddi = ddi_str.toInt();
                int numero = numero_str.toInt();
                dnn::Telefone fone(contato.getId(), ddi, ddd, numero);
                contato.setTelefone(fone);

                QTableWidgetItem *item1 = new QTableWidgetItem(ddi_str);
                QTableWidgetItem *item2 = new QTableWidgetItem(ddd_str);
                QTableWidgetItem *item3 = new QTableWidgetItem(numero_str);

                int linha = ui->tableWidgetListaTelefone->rowCount();
                ui->tableWidgetListaTelefone->insertRow(linha);
                ui->tableWidgetListaTelefone->setItem(linha, 0, item1);
                ui->tableWidgetListaTelefone->setItem(linha, 1, item2);
                ui->tableWidgetListaTelefone->setItem(linha, 2, item3);
            }
        }
    }

    if(aux==0){
        this->close();
    }
}

telaDeEdicao::~telaDeEdicao()
{
    delete ui;
}

void telaDeEdicao::on_pushButtonEditar_clicked()
{
    try {
        if(contato.getEmail().size()==0) throw QString("Email obrigatório!");
        if(contato.getTelefone().size()==0) throw QString("Telefone obrigatório!");

        QString nome = ui->lineEditNome->text();
        QString logradouro = ui->lineEditLogradouro->text();
        int num = ui->lineEditNumero->text().toInt();
        dnn::Endereco end(logradouro,num);
        //dnn::Contato pessoa(geraID.getID(),nome,end);
        if(nome=="") throw QString("Nome obrigatório!");
        if(logradouro=="") throw QString("Logradouro obrigatório!");
        if(num==0) throw QString("Número obrigatório!");

        contato.setId(this->idContato);
        contato.setNome(nome);
        contato.setEnderecoResidencial(end);


        dnn::ContatoDAO agendaContatos("Contatos.txt");
        agendaContatos.editar(contato);
        contato.limparContato();
        this->close();
    } catch (QString &erro) {
        QMessageBox::warning(this,"ERRO",erro);
    }
}

void telaDeEdicao::on_pushButton_incluirMais_clicked()
{
    QString ddd_str = ui->lineEditDDD->text();
    QString ddi_str = ui->lineEditDDI->text();
    QString numero_str = ui->lineEditNumeroTel->text();

    int ddd = ddd_str.toInt();
    int ddi = ddi_str.toInt();
    int numero = numero_str.toInt();
    dnn::Telefone fone(contato.getId(), ddi, ddd, numero);
    contato.setTelefone(fone);

    QTableWidgetItem *item1 = new QTableWidgetItem(ddi_str);
    QTableWidgetItem *item2 = new QTableWidgetItem(ddd_str);
    QTableWidgetItem *item3 = new QTableWidgetItem(numero_str);

    int linha = ui->tableWidgetListaTelefone->rowCount();
    ui->tableWidgetListaTelefone->insertRow(linha);
    ui->tableWidgetListaTelefone->setItem(linha, 0, item1);
    ui->tableWidgetListaTelefone->setItem(linha, 1, item2);
    ui->tableWidgetListaTelefone->setItem(linha, 2, item3);

    ui->lineEditDDD->clear();
    ui->lineEditDDI->clear();
    ui->lineEditNumeroTel->clear();
}

void telaDeEdicao::on_pushButton_incluirMaisEmail_clicked()
{
    QString email = ui->lineEditEmail->text();
    dnn::Email objEmail(contato.getId(),email);
    contato.setEmail(objEmail);
    int linha = ui->listWidgetEmail->count();
    ui->listWidgetEmail->insertItem(linha, email);

    ui->lineEditEmail->clear();
}

void telaDeEdicao::on_pushButtonCancelar_clicked()
{
    this->close();
}

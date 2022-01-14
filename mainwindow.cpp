#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::limparTela() const
{
    ui->lineEditNome->clear();
    ui->lineEditNumero->clear();
    ui->lineEditLogradouro->clear();
    ui->tableWidgetListaTelefone->clear();
    ui->tableWidgetListaTelefone->setRowCount(0);
    ui->listWidgetEmail->clear();
}

void MainWindow::on_pushButtonIncluir_clicked()
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

        contato.setId(geraID.getID());
        contato.setNome(nome);
        contato.setEnderecoResidencial(end);


        dnn::ContatoDAO agendaContatos("Contatos.txt");
        agendaContatos.incluir(contato);
        this->limparTela();
        contato.limparContato();
    } catch (QString &erro) {
        QMessageBox::warning(this,"ERRO",erro);
    }

    //dnn::ContatoDAO agendaContatos("Contatos.txt");
    //agendaContatos.incluir(testeC1);

}

void MainWindow::on_pushButtonListagem_clicked()
{
    TelaDeListagem telaLista;
    telaLista.setModal(true);
    telaLista.exec();
}

void MainWindow::on_pushButton_incluirMais_clicked()
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

void MainWindow::on_pushButton_incluirMaisEmail_clicked()
{
    QString email = ui->lineEditEmail->text();
    dnn::Email objEmail(contato.getId(),email);
    contato.setEmail(objEmail);
    int linha = ui->listWidgetEmail->count();
    ui->listWidgetEmail->insertItem(linha, email);

    ui->lineEditEmail->clear();
}

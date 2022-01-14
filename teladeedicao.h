#ifndef TELADEEDICAO_H
#define TELADEEDICAO_H

#include <QDialog>
#include<QInputDialog>
#include<contatodao.h>
#include<QMessageBox>

namespace Ui {
class telaDeEdicao;
}

class telaDeEdicao : public QDialog
{
    Q_OBJECT

public:
    explicit telaDeEdicao(QWidget *parent = 0);
    ~telaDeEdicao();

private slots:
    void on_pushButtonEditar_clicked();

    void on_pushButton_incluirMais_clicked();

    void on_pushButton_incluirMaisEmail_clicked();

    void on_pushButtonCancelar_clicked();

private:
    Ui::telaDeEdicao *ui;
    int idContato;
    dnn::Contato contato;
};

#endif // TELADEEDICAO_H

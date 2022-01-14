#ifndef TELADELISTAGEM_H
#define TELADELISTAGEM_H

#include <QDialog>
#include<contatodao.h>
#include<QMessageBox>
#include<QInputDialog>
#include<teladeedicao.h>

namespace Ui {
class TelaDeListagem;
}

class TelaDeListagem : public QDialog
{
    Q_OBJECT

public:
    explicit TelaDeListagem(QWidget *parent = 0);
    ~TelaDeListagem();

private slots:
    void on_pushButtonVoltar_clicked();

    void on_pushButtonListar_clicked();

    void on_pushButtonExcluir_clicked();

    void on_pushButtonEditar_clicked();

private:
    Ui::TelaDeListagem *ui;
    const QString nomeDoArquivoDeContatos;
};

#endif // TELADELISTAGEM_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<endereco.h>
#include<QMessageBox>
#include<contato.h>
#include<contatodao.h>
#include<geradorid.h>
#include<teladelistagem.h>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void limparTela()const;

private slots:
    void on_pushButtonIncluir_clicked();

    void on_pushButtonListagem_clicked();

    void on_pushButton_incluirMais_clicked();

    void on_pushButton_incluirMaisEmail_clicked();

private:
    Ui::MainWindow *ui;
    dnn::GeradorID geraID;
    dnn::Contato contato;
};

#endif // MAINWINDOW_H

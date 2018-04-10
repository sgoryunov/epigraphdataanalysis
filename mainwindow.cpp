#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(Browse()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(Browse_2()));
    m_lineEditRawDir = ui->lineEdit;
    m_lineEditProcDir = ui->lineEdit_2;

    CreateMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateMenu()
{
    m_pAnalysTypeMnu = menuBar()->addMenu("Analyses type");
    m_pAnalysTypeMnu->addAction("&Classic analyses",this,SLOT(ClassAnParamWnd()));
    m_pAnalysTypeMnu->addAction("&Reverse TOF analyses",this,SLOT(RevTofAnParamWnd()));

    menuBar()->show();
    

}

void MainWindow::ClassAnParamWnd()
{

}

void MainWindow::RevTofAnParamWnd()
{

}

// закроем окно понажатию кнопки
void MainWindow::on_pushButton_4_clicked()
{
   this->close();
}
// обработаем файлы по нажатию кнопки
void MainWindow::on_pushButton_3_clicked()
{

}
// выберем директорию
#include <QFileDialog>
#include <QDir>

void MainWindow::Browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                  tr("Find Files"), QDir::currentPath());

       if (!directory.isEmpty())
       {
           m_lineEditRawDir->setText(directory);
           if(m_lineEditProcDir->text().isEmpty())
                m_lineEditProcDir->setText(directory);
       }

}

void MainWindow::Browse_2()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                  tr("Find Files"), QDir::currentPath());

       if (!directory.isEmpty())
           m_lineEditProcDir->setText(directory);

}

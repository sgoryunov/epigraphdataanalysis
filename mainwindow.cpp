#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qepigraphdataprocessor.h"

#include <QThread>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(Browse()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(Browse_2()));
    m_lineEditRawDir = ui->lineEdit;
    m_lineEditProcDir = ui->lineEdit_2;
    m_btnProcess = ui->pushButton_3;

    CreateMenu();
}

MainWindow::~MainWindow()
{
    stopThreads();
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
    // запустим поток для обработки данных
    if(m_btnProcess->text() != "Stop")
    {
       if(!m_lineEditRawDir->text().isEmpty())
       {
           m_btnProcess->setText("Stop");
           addThread();
       }
    }else
    {
        stopThreads();
        m_btnProcess->setText("Process files");
    }


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
           m_lineEditRawDir->setText(directory.append("/"));
           if(m_lineEditProcDir->text().isEmpty())
           {
                m_lineEditProcDir->setText(directory);
           }
       }

}

void MainWindow::Browse_2()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                                  tr("Find Files"), QDir::currentPath());

       if (!directory.isEmpty())
           m_lineEditProcDir->setText(directory.append("/"));

}

void MainWindow::setProcessStatus(int num)
{
    ui->progressBar->setValue(num);
 return;
}


void MainWindow::addThread()
{
    ui->progressBar->setMaximum(
                GetNumOfRawFilesInDir(m_lineEditRawDir->text()));

    m_DataProcessor = new QEpigraphDataProcessor(m_lineEditRawDir->text(),m_lineEditProcDir->text());
    QThread* thread = new QThread ;
    m_DataProcessor->moveToThread(thread);

    /*  Теперь внимательно следите за руками.  Раз: */
        connect(thread, SIGNAL(started()), m_DataProcessor, SLOT(process()));
    /* … и при запуске потока будет вызван метод process(), который создаст построитель отчетов, который будет работать в новом потоке

    Два: */
        connect(m_DataProcessor, SIGNAL(finished()), thread, SLOT(quit()));
    /* … и при завершении работы построителя отчетов, обертка построителя передаст потоку сигнал finished() , вызвав срабатывание слота quit()

    Три:
    */
       // connect(this, SIGNAL(stopAll()), m_DataProcessor, SLOT(stop()));
    /* … и Session может отправить сигнал о срочном завершении работы обертке построителя, а она уже остановит построитель и направит сигнал finished() потоку

    Четыре: */
        connect(m_DataProcessor, SIGNAL(finished()),m_DataProcessor, SLOT(deleteLater()));
    /* … и обертка пометит себя для удаления при окончании построения отчета

    Пять: */
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    /* … и поток пометит себя для удаления, по окончании построения отчета. Удаление будет произведено только после полной остановки потока.


    И наконец :
    */
        connect(m_DataProcessor,SIGNAL(NumProcessedFiles(int)),this,SLOT(setProcessStatus(int)));

        thread->start();

    /* Запускаем поток, он запускает RBWorker::process(), который создает ReportBuilder и запускает  построение отчета */

        return ;

}

void MainWindow::stopThreads(){
    //emit stopAll();
    m_DataProcessor->stop();
}

int MainWindow::GetNumOfRawFilesInDir(QString dir)
{
    QDir qDir(dir);
    qDir.setNameFilters(QStringList()<<"*.dat");
    QStringList fileList = qDir.entryList();
    return fileList.length();
}



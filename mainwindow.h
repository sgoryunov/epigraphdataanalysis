#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QLineEdit>
#include <QPushButton>

#include "qepigraphdataprocessor.h"


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
    Ui::MainWindow *ui;

    QMenu *m_pAnalysTypeMnu;
    QLineEdit *m_lineEditRawDir;
    QLineEdit *m_lineEditProcDir;
    QPushButton *m_btnProcess;
    QEpigraphDataProcessor* m_DataProcessor;

    void CreateMenu();

    void addThread();
    void stopThreads();
    int GetNumOfRawFilesInDir(QString);

public slots:


private slots:
    void ClassAnParamWnd();
    void RevTofAnParamWnd();
    void Browse();
    void Browse_2();
    void DataProcessingFinished();
    
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

    void setProcessStatus(int);

signals:
    void stopAll();
    
};

#endif // MAINWINDOW_H

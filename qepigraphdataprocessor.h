#ifndef QEPIGRAPHDATAPROCESSOR_H
#define QEPIGRAPHDATAPROCESSOR_H

#include <QObject>
#include <QString>


class QEpigraphDataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit QEpigraphDataProcessor(QObject *parent);
    QEpigraphDataProcessor( QString , QString);


    int GetNumberOfRawFiles(QString);

public slots:
    void process(); 	/*  создает и запускает обработчика файлов */
    void stop();    	/*  останавливает обработсика файлов */
    void ProcessedOneRawFile();

signals:
    void finished(); 	/* сигнал о завершении  работы обработчика файлов */
    void NumProcessedFiles(int);


private:
    QString m_DirWithRawData;
    QString m_DirWithProcData;
    int m_NumOfProcessedFiles;
};

#endif // QEPIGRAPHDATAPROCESSOR_H

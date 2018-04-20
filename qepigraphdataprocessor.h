#ifndef QEPIGRAPHDATAPROCESSOR_H
#define QEPIGRAPHDATAPROCESSOR_H

#include <QObject>
#include <QString>

#include "../QEpigDataFourierAnalysisLib/cprocessrawepigraphdata.h"


class QEpigraphDataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit QEpigraphDataProcessor(QObject *parent);
    QEpigraphDataProcessor( QString , QString);

    void stop();    	/*  останавливает обработсика файлов */
    int GetNumberOfRawFiles(QString);

public slots:
    void process(); 	/*  создает и запускает обработчика файлов */
   // void stop();    	/*  останавливает обработсика файлов */
    void ProcessedOneRawFile();

signals:
    void finished(); 	/* сигнал о завершении  работы обработчика файлов */
    void NumProcessedFiles(int);
    void StopDataProcessor();//


private:
    QString m_DirWithRawData;
    QString m_DirWithProcData;
    int m_NumOfProcessedFiles;
    CProcessRawEpigraphData* m_DataProcessor;
};

#endif // QEPIGRAPHDATAPROCESSOR_H

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
    QEpigraphDataProcessor( QStringList & , QString);// (list of raw files, processed dir path)

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
    void ProcessedFileName(QString);
    void scrollDown();

private:
    QString m_DirWithProcData;
    int m_NumOfProcessedFiles;
    CProcessRawEpigraphData* m_DataProcessor;
    QStringList m_RawFileList;
    bool m_isStopProcess;

};

#endif // QEPIGRAPHDATAPROCESSOR_H

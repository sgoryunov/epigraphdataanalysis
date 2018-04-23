#include "qepigraphdataprocessor.h"
#include "../QEpigDataFourierAnalysisLib/qepigdatafourieranalysislib.h"


QEpigraphDataProcessor::QEpigraphDataProcessor(QObject *parent) : QObject(parent){}

QEpigraphDataProcessor::QEpigraphDataProcessor( QString str1, QString str2)
{
    m_DirWithRawData = str1;
    m_DirWithProcData = str2;
    m_NumOfProcessedFiles = 0;
    m_DataProcessor = NULL;
}

void QEpigraphDataProcessor::ProcessedOneRawFile()
{
     emit  NumProcessedFiles( ++m_NumOfProcessedFiles);
}
void QEpigraphDataProcessor::process()
{
    m_DataProcessor = new CProcessRawEpigraphData(this);
    if(m_DataProcessor != NULL)
    {
        connect(m_DataProcessor,SIGNAL(ProcessedFile()),this,SLOT(ProcessedOneRawFile()));
        connect(this,SIGNAL(StopDataProcessor()),m_DataProcessor,SLOT(Stop()));
        //start process files in directory
        wchar_t buf[256] = {0};
        wchar_t buf2[256] = {0};
        m_DirWithRawData.toWCharArray(buf);
        m_DirWithProcData.toWCharArray(buf2);
        m_DataProcessor->SetDirectoryForProcessedFiles(buf2);
        m_DataProcessor->ProcessDirectory(buf);

        m_DataProcessor->deleteLater();
    }

    emit finished();

    return ;

}

void QEpigraphDataProcessor::stop()
{
    if(m_DataProcessor != NULL)m_DataProcessor->Stop();
}

int QEpigraphDataProcessor::GetNumberOfRawFiles(QString str)
{


}

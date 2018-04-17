#include "qepigraphdataprocessor.h"
#include "../QEpigDataFourierAnalysisLib/qepigdatafourieranalysislib.h"
#include "../QEpigDataFourierAnalysisLib/cprocessrawepigraphdata.h"

QEpigraphDataProcessor::QEpigraphDataProcessor(QObject *parent) : QObject(parent){}

QEpigraphDataProcessor::QEpigraphDataProcessor( QString str1, QString str2)
{
    m_DirWithRawData = str1;
    m_DirWithProcData = str2;
    m_NumOfProcessedFiles = 0;
}

void QEpigraphDataProcessor::ProcessedOneRawFile()
{
     emit  NumProcessedFiles( ++m_NumOfProcessedFiles);
}
void QEpigraphDataProcessor::process()
{
    CProcessRawEpigraphData dataProcessor(this);
    connect(&dataProcessor,SIGNAL(ProcessedFile()),this,SLOT(ProcessedOneRawFile()));
    connect(this,SIGNAL(StopDataProcessor()),&dataProcessor,SLOT(Stop()));
    //start process files in directory
    wchar_t buf[256] = {0};
    wchar_t buf2[256] = {0};
    m_DirWithRawData.toWCharArray(buf);
    m_DirWithProcData.toWCharArray(buf2);
    dataProcessor.SetDirectoryForProcessedFiles(buf2);
    dataProcessor.ProcessDirectory(buf);

    emit finished();
    return ;

}

void QEpigraphDataProcessor::stop()
{
    emit StopDataProcessor();
}

int QEpigraphDataProcessor::GetNumberOfRawFiles(QString str)
{


}

#include "qepigraphdataprocessor.h"
#include "../QEpigDataFourierAnalysisLib/qepigdatafourieranalysislib.h"


QEpigraphDataProcessor::QEpigraphDataProcessor(QObject *parent) : QObject(parent){}

QEpigraphDataProcessor::QEpigraphDataProcessor( QStringList& lst, QString str)
{
    m_RawFileList = lst;
    m_DirWithProcData = str;
    m_NumOfProcessedFiles = 0;
    m_DataProcessor = NULL;
    m_isStopProcess = false;
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
        m_DirWithProcData.toWCharArray(buf2);
        m_DataProcessor->SetDirectoryForProcessedFiles(buf2);
        //m_DataProcessor->ProcessDirectory(buf);
        int error(0);
        int i(0);
        foreach (QString str, m_RawFileList) {
          if(m_isStopProcess) break;
          wmemset (buf,L'\0',256);
          str.toWCharArray(buf);
          //qDebug()<<QString::fromWCharArray(buf,256);
          m_DataProcessor->ProcessFile(buf);
          emit  NumProcessedFiles( ++m_NumOfProcessedFiles);
          if(!error)
          {
              i++;
              emit  ProcessedFileName(str+" -->OK!");

          }
          else
          {
              if(error == 46)
              {
                  i++;

                  emit  ProcessedFileName(str + " --> No pulse in DET channel");
              }
              else
              {
                 emit  ProcessedFileName(str + " --> BAD! Format error!");
              }
          }
         }
        emit  ProcessedFileName(QString("Processed %1 files from %2 !").arg(QString::number(i),QString::number(m_RawFileList.length())));
        emit scrollDown();
        m_DataProcessor->deleteLater();
    }

    emit finished();

    return ;

}

void QEpigraphDataProcessor::stop()
{
    if(m_DataProcessor != NULL)m_DataProcessor->Stop();
    m_isStopProcess = true;
}

int QEpigraphDataProcessor::GetNumberOfRawFiles(QString str)
{


}

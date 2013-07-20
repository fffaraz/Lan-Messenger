#ifndef VOICEIO_H
#define VOICEIO_H

#include <QObject>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QDebug>
#include <QIODevice>

class VoiceIO : public QObject
{
    Q_OBJECT
public:
    explicit VoiceIO(QObject *parent = 0);
    void setEnabled(bool val);

private:
    QIODevice *devInput;
    QIODevice *devOutput;
    bool isEnabled;
    
signals:
    void readVoice(QByteArray data);

public slots:
    void writeVoice(QByteArray data);

private slots:
    void devInput_readyRead();
    
};

#endif // VOICEIO_H

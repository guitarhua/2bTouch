#include "serialhandler.h"

SerialHandler::SerialHandler(QThread *thr, QObject *parent) : QObject(parent) {
    thread = thr;
    //this->moveToThread(thread);

    settings = new QSettings("2B Technologies", "2B Touch");
    gettingSettings = false;

    configSerialPort();
    currentConnectionType = SerialHandler::Inactive;
}

void SerialHandler::writeSync(QString *dat) {
    if(dat == QString("v")) {
        updateSettings();
    } else {
        dataList<<dat;
        if(currentConnectionType == SerialHandler::Synchronously) {
            qDebug()<<"Data operation already in process, adding to queue";
        } else {
            qDebug()<<"Writing Sync";
            currentConnectionType = SerialHandler::Synchronously;
            data = dat;
            syncIndex = 0;
            serialPort->write(QString('<').toLocal8Bit().constData());
            //serialPort->write(QString("<").toLatin1().toStdString().c_str(), 1);
        }
    }
}

void SerialHandler::writeAsync(QString *dat) {
    currentConnectionType = SerialHandler::Asynchronously;
    data = dat;
    serialPort->write(dat->toLocal8Bit().constData(), dat->length());
    currentConnectionType = (SerialHandler::Finished);
}

void SerialHandler::writeChar(char c) {
    if(c == 'v') {
        updateSettings();
        return;
    }
    const char *d = &c;
    serialPort->write(d);
}

void SerialHandler::configSerialPort() {
    serialPort = new QSerialPort();

    reader = new XmlDeviceReader(":/deviceConfig.xml");
    reader->read();

    device = reader->getADevice(1);
    portName = device.getCom_port();
    baudRate = device.getBaud_rate();

    qDebug()<<"Port Name: "<<portName;
    qDebug()<<"Baud Rate: "<<baudRate;

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);

    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug()<<"Setup Serial Port successfully";
        connect(serialPort, SIGNAL(readyRead()), this, SLOT(dataReady()));
    }else{
        qDebug()<<"Error setting up serial port";
    }

}

void SerialHandler::dataReady() {
    if(serialPort->canReadLine()) {
        QByteArray retData = serialPort->readAll();
        //qDebug()<<"Received new line from serial: "<<retData;
        //serialPort->flush();
        QString *retDataStr = new QString(retData);
        retDataStr->remove('\r');
        QList<QString> list = retDataStr->split('\n');
        for(int i = 0; i < list.length(); i++) {
            QString line = QString(list.at(i));

            if((line.length() == 0) || (line == "\r")) {
               //qDebug()<<"Empty Line";
                /*qDebug()<<"Empty Line";
                qDebug()<<"Empty Line";
                qDebug()<<"Empty Line";
                qDebug()<<"Empty Line";
                qDebug()<<"Empty Line";
                qDebug()<<"Empty Line";
                qDebug()<<"Empty Line";*/
            } else {
                if(line.length() < 20) {
                    qDebug()<<"Received new line from serial: "<<line;
                }
                if((line == "Settings") || (line == "\rSettings")) {
                   //qDebug()<<"Waiting For Settings";
                    gettingSettings = true;
                } else if((gettingSettings) && (line.length() > 1)) {
                    qDebug()<<"Getting Settings";

                    gettingSettings = false;
                    QStringList settingsList = retDataStr->split(",");
                    qDebug()<<settingsList;
                    if(settingsList.length() == 6) {
                        settings->setValue("Raw Settings String", line);
                        settings->setValue("Zero", settingsList.at(0));
                        settings->setValue("Avg", settingsList.at(1));
                        settings->setValue("VOut", settingsList.at(2));
                        settings->setValue("Rel1On", settingsList.at(3));
                        settings->setValue("Rel1Off", settingsList.at(4));
                        settings->setValue("Slope", settingsList.at(5));
                    } else {
                        qDebug()<<"Incomplete Settings List";
                    }
                } else if(currentConnectionType == SerialHandler::Synchronously) {
                    //qDebug()<<"Sync Data";
                    handleSyncData(QString(line));
                } else {
                    emit dataAvailable(line);
                }
            }
        }
    }
}

void SerialHandler::handleSyncData(QString retData) {
    if((retData == "n") || (retData == "Starting string")) {
        if(syncIndex < (data->size())) {
            serialPort->write(QString(data->at(syncIndex)).toLocal8Bit().constData(), 1);
            syncIndex++;
        } else {
            serialPort->write(QString(">").toLocal8Bit().constData(), 1);
            currentConnectionType = SerialHandler::Finished;
            qDebug()<<"Finished Sync Write";
            checkQueue();
        }
    } else {
        emit dataAvailable(retData);
    }
}

void SerialHandler::checkQueue() {
    qDebug()<<dataList;
    int index = dataList.indexOf(data);
    qDebug()<<index;
    if((index+1) != dataList.size()) {
        currentConnectionType = SerialHandler::Synchronously;
        data = dataList.at(index+1);
        syncIndex = 0;
        serialPort->write(QString("<").toLocal8Bit().constData(), 1);
    }
}

void SerialHandler::updateSettings() {
    int test = settings->value("InitSettings", -1).toInt();
    if (test == -1) {
        qDebug()<<"Getting Settings From Device";
        writeAsync(new QString("v"));
        settings->setValue("InitSettings", 1);
    } else {
        writeSync(new QString("c:" + settings->value("Zero").toString()));
        writeSync(new QString("a:" + settings->value("Avg").toString()));
        writeSync(new QString("v:" + settings->value("VOut").toString()));
        writeSync(new QString("l:" + settings->value("Rel1On").toString()));
        writeSync(new QString("h:" + settings->value("Rel1Off").toString()));
        writeSync(new QString("s:" + settings->value("Slope").toString()));
    }

}

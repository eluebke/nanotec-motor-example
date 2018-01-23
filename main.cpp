#include <QCoreApplication>
#include <QSerialPort>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSerialPort serial;
    QByteArray answer;

    int comPortNo = 4;
    bool brakeMotor = true;

    // configure the comport / connection
    // all nanotec motors need a baud rate of 115200

    QString portName = "COM" + QString(QString::number(comPortNo));
    serial.setPortName(portName);
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    bool openedSuccessfully = serial.open(QIODevice::ReadWrite);

    if (openedSuccessfully) {

        // set target speed to 1000 Hz

        serial.write("#1o1000\r");
        serial.waitForReadyRead(30);
        answer = serial.readAll();
        qDebug() << answer;

        // start motor

        serial.write("#1A\r");
        serial.waitForReadyRead(30);
        answer = serial.readAll();
        qDebug() << answer;

        // wait five seconds
        QThread::sleep(5);

        // brake or halt motor depending on variable assignment

        if (brakeMotor) {
            serial.write("#1S1\r");
        } else {
            serial.write("#1S0\r");
        }

        serial.waitForReadyRead(30);
        answer = serial.readAll();
        qDebug() << answer;

        QThread::sleep(1);
        
        // all done, close the connection

        serial.close();
    }

    return a.exec();
}

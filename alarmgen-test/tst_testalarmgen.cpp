#include <QString>
#include <QtTest>

#include "alarmgenerator.h"

class TestAlarmgen : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void setDisconnectedLineFound();
    void setDisconnectedLineLost1();
    void setDisconnectedLineLost2();
    void setConnectedLineFound();
    void setConnectedLineLost1();
    void setConnectedLineLost2();
    void cleanupTestCase();

private:
    AlarmGenerator alarmgen;

    bool connected;
    bool disconnected;
    QVarLengthArray<bool> lineFound;
    QVarLengthArray<bool> lineLost1;
    QVarLengthArray<bool> lineLost2;
};

void TestAlarmgen::initTestCase()
{
    this->connected = true;
    this->disconnected = false;

    QVarLengthArray<bool> temp(21);

    for(quint8 i=0;i<21;i++)
        temp.replace(i,true);
    this->lineLost1 = temp;

    for(quint8 i=0;i<21;i++)
        temp.replace(i,false);
    this->lineLost2 = temp;

    for(quint8 i=9;i<12;i++)
        temp.replace(i,true);
    this->lineFound = temp;
}

void TestAlarmgen::cleanupTestCase()
{
    // nothing
}

void TestAlarmgen::setConnectedLineLost1()
{
    this->alarmgen.setConnectionState(this->connected);
    this->alarmgen.setLineState(this->lineLost1);
    this->alarmgen.updateColor();
    QVERIFY(this->alarmgen.getColor() == ALARM_RED);
}

void TestAlarmgen::setConnectedLineLost2()
{
    this->alarmgen.setConnectionState(this->connected);
    this->alarmgen.setLineState(this->lineLost2);
    this->alarmgen.updateColor();
    QVERIFY(this->alarmgen.getColor() == ALARM_RED);
}

void TestAlarmgen::setConnectedLineFound()
{
    this->alarmgen.setConnectionState(this->connected);
    this->alarmgen.setLineState(this->lineFound);
    this->alarmgen.updateColor();
    QVERIFY(this->alarmgen.getColor() == ALARM_GREEN);
}

void TestAlarmgen::setDisconnectedLineLost1()
{
    this->alarmgen.setConnectionState(this->disconnected);
    this->alarmgen.setLineState(this->lineLost1);
    this->alarmgen.updateColor();
    QVERIFY(this->alarmgen.getColor() == ALARM_YELLOW);
}

void TestAlarmgen::setDisconnectedLineLost2()
{
    this->alarmgen.setConnectionState(this->disconnected);
    this->alarmgen.setLineState(this->lineLost2);
    this->alarmgen.updateColor();
    QVERIFY(this->alarmgen.getColor() == ALARM_YELLOW);
}

void TestAlarmgen::setDisconnectedLineFound()
{
    this->alarmgen.setConnectionState(this->disconnected);
    this->alarmgen.setLineState(this->lineFound);
    this->alarmgen.updateColor();
    QVERIFY(this->alarmgen.getColor() == ALARM_YELLOW);
}


QTEST_APPLESS_MAIN(TestAlarmgen)

#include "tst_testalarmgen.moc"

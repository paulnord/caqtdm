/*
 *  This file is part of the caQtDM Framework, developed at the Paul Scherrer Institut,
 *  Villigen, Switzerland
 *
 *  The caQtDM Framework is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The caQtDM Framework is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the caQtDM Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright (c) 2010 - 2020
 *
 *  Author:
 *    Helge Brands
 *  Contact details:
 *    helge.brands@psi.ch
 */
#ifndef MODBUS_CHANNELDATA_H
#define MODBUS_CHANNELDATA_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QModbusTcpClient>
#include <QDateTime>
class modbus_channeldata : public QObject
{
    Q_OBJECT
public:
    modbus_channeldata();
    modbus_channeldata(int index,QModbusDataUnit* readUnit);


    QModbusDataUnit::RegisterType getModbus_type() const;
    void setModbus_type(const QModbusDataUnit::RegisterType &value);
    int getModbus_addr() const;
    void setModbus_addr(int value);
    int getModbus_count() const;
    void setModbus_count(int value);
    QModbusDataUnit *getReadUnit() const;
    void addIndex(int pvindex);
    void delIndex(int pvindex);

    int getIndex() const;
    QList<int> getIndexes(){return index;}

    void trigger_request();
    void trigger_process();
    void process_timestamp(char* timestamp);

    bool getWill_be_written();
    void setWill_be_written();
    void resetWill_be_written();

    int getCycleTime() const;
    void setCycleTime(int value);

    int getStation() const;
    void setStation(int value);

    QString getRcalc() const;
    void setRcalc(const QString &value);

    QString getWcalc() const;
    void setWcalc(const QString &value);

    bool getValid_calc() const;

    void setInvalid_calc();

private:
    QMutex mutex;
    bool will_be_written;
    int CycleTime;
    int Station;
    QModbusDataUnit* readUnit;
    QList<int> index;
    QDateTime generation_time;
    QDateTime request_time;
    QDateTime process_time;
    QString rcalc;
    QString wcalc;
    bool valid_calc;

};

#endif // MODBUS_CHANNELDATA_H

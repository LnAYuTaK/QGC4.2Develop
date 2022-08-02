#ifndef DATAMANAGER_H
#define DATAMANAGER_H

//QT Head
#include <QObject>
#include <QDateTime>
#include <QMap>
#include <QVector>
#include <QByteArray>
#include <QString>
//QGC Head
#include "QGCMAVLink.h"
#include "QGCApplication.h"
#include "Vehicle.h"
#define   PACKHEAD  "EB90"

//植保机DataFact
class  VehicleDataFactPack:public QObject
{
    Q_OBJECT
public:
      explicit VehicleDataFactPack(QObject *parent = nullptr);
      //对外接口获取数据的接口
      QVector <QByteArray> * Pack         () {return &vehiclePack;}

      Q_INVOKABLE bool     flightState    () {return _flightState;}
      Q_INVOKABLE QString  flightTime     () {return _flightTime;}
      Q_INVOKABLE uint8_t  sprayState     () {return _sprayStat;}
      Q_INVOKABLE int      id             () {return _id;}
      Q_INVOKABLE uint8_t  flowRate       () {return _flowRate;}
      Q_INVOKABLE double   workArea       () {return _workArea;}
      Q_INVOKABLE double   lot            () {return _lot;}
      Q_INVOKABLE double   lat            () {return _lat;}
      Q_INVOKABLE double   flightTailTude () {return _flightTailTude;}
      Q_INVOKABLE double   groundSpeed    () {return _groundSpeed;}
      Q_INVOKABLE QString  flightMode     () {return _flightMode;}
      //飞行模式类型// 还有别的类型后续添加
      const QStringList FlightModeType {
              "PreFlight",
              "Stabilize",
              "Guided",
              "Auto",
              "Test",
              "Altitude Hold",
              "RTL",
              "Loiter"
      };
//处理从Vehcile接收的数据
public slots:
  void _vehicleTakeOff();

  void _vehicleLand();

  void _vehicleFlightTime(QString time);

  void _vehicleSprayState(bool isOpen);

  void _vehicleid(int id);

  void _vehicleFlowRate(uint8_t flowRate);

  void _vehicleWorkArea(double workArea);

  void _vehicleLongitude(double lot);

  void _vehicleLatitude(double lat);

  void _vehicleFlighTaltiTude(double flightTaltiTude);

  void _vehicleGroundFlightSpeed(double groundSpeed);

  void _vehicleDataSendTime();

  void _vehicleLevelGaugeStatus(bool gaugetype);

  void _vehicleFlightMode(QString flightmodetype);

private:
      static bool      _flightState;
      static QString   _flightTime;
      static uint8_t   _sprayStat;
      static int       _id ;
      static uint8_t   _flowRate;
      static double    _workArea;
      static double    _lot;
      static double    _lat;
      static double    _flightTailTude;
      static double    _groundSpeed;
      static bool      _gaugetype;
      static QString   _flightMode;
      //是否更新飞行架次flag
      static bool      _upDataFlightFlag;
      //帧头
      const  QByteArray  packHead = QString(PACKHEAD).toLatin1();
      //版本和固件号通过暂时获取通过HySetting获取
      const QString    _softWareVersion;
      const QString    _fireWareVersion;

//Tools
   QVector <qint64> splitDouble(double data,qint16 digit);

//发送到后台的数据包 每条消息位数固定（如有丢位可直接舍弃），字段在消息中位置固定，十六进制字符串
   QVector <QByteArray> vehiclePack;
};
//初始化静态变量

//数据管理类
class DataManager : public QGCTool
{
    Q_OBJECT

//
public:
     DataManager(QGCApplication* app, QGCToolbox* toolbox);
     // Override from QGCTool
     virtual void setToolbox(QGCToolbox* toolbox)final;
private:
    VehicleDataFactPack* createDataFact(Vehicle* vehicle);
    //
    void dataFactAdd(Vehicle* vehicle);
    //
    void dataFactRemove(Vehicle* vehicle);
    //Key&Value
    //Vehicle ID  ---  VehicleDataFactPack pointer
    QMap<int,VehicleDataFactPack *> *dataFactMap=nullptr;

protected:
    QGCApplication* _app;
    QGCToolbox*     _toolbox;
signals:

};

#endif // DATAMANAGER_H

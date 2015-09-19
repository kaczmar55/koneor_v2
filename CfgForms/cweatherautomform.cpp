#include "cweatherautomform.h"
#include "ui_cweatherautomform.h"

CWeatherAutomForm::CWeatherAutomForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CWeatherAutomForm)
{
    ui->setupUi(this);
    ui->blowSensorRegNoLbl->setHidden(true);
    ui->blowSensorRegNo->setHidden(true);
}

CWeatherAutomForm::~CWeatherAutomForm()
{
    delete ui;
}

bool CWeatherAutomForm::setCfg(void *cfg_struct)
{
    weather_autom_cfg_t* weather_autom_cfg = (weather_autom_cfg_t*)cfg_struct;
    uint8_t type;

    type = weather_autom_cfg->t_cold.type;
    ui->sensorColdTypeCmb->setCurrentIndex(type);
    ui->sensorColdAddr->setValue(weather_autom_cfg->t_cold.addr[type]);
    ui->sensorColdRegNo->setValue(weather_autom_cfg->t_cold.reg_no[type]);

    type = weather_autom_cfg->t_hot.type;
    if(type == 2)
        type = 1;
    ui->sensorHotTypeCmb->setCurrentIndex(type);
    ui->sensorHotAddr->setValue(weather_autom_cfg->t_hot.addr[type]);
    ui->sensorHotRegNo->setValue(weather_autom_cfg->t_hot.reg_no[type]);

    type = weather_autom_cfg->snow_blow_sensor.type;
    ui->blowSensTypeCmb->setCurrentIndex(type);
    ui->blowSensorAddr->setValue(weather_autom_cfg->snow_blow_sensor.addr[type]);
    ui->blowSensorRegNo->setValue(weather_autom_cfg->snow_blow_sensor.reg_no[type]);
    ui->blowSensorBitNo->setValue(weather_autom_cfg->snow_blow_sensor.bit_no[type]);

    if(weather_autom_cfg->sensor_pwr_ctrl.active == 0)
        ui->sensorPwrCtrlChk->setChecked(false);
    else
        ui->sensorPwrCtrlChk->setChecked(true);
    ui->sensorPwrCtrlIOMod->setValue(weather_autom_cfg->sensor_pwr_ctrl.module_id);
    ui->sensorPwrCtrlBitNo->setValue(weather_autom_cfg->sensor_pwr_ctrl.bit_no);

    ui->referenceCirNo->setValue(weather_autom_cfg->referenceCircuitNo);

    return true;
}

bool CWeatherAutomForm::getCfg(void *cfg_struct)
{
    weather_autom_cfg_t* weather_autom_cfg = (weather_autom_cfg_t*)cfg_struct;
    uint8_t type;

    memset(weather_autom_cfg, 0, sizeof(weather_autom_cfg_t));

    type = ui->sensorColdTypeCmb->currentIndex();
    weather_autom_cfg->t_cold.type = type;
    weather_autom_cfg->t_cold.addr[type] = ui->sensorColdAddr->value();
    weather_autom_cfg->t_cold.reg_no[type] = ui->sensorColdRegNo->value();

    type = ui->sensorHotTypeCmb->currentIndex();
    if(type == 1)
        type = 2;
    weather_autom_cfg->t_hot.type = type;
    weather_autom_cfg->t_hot.addr[type] = ui->sensorHotAddr->value();
    weather_autom_cfg->t_hot.reg_no[type] = ui->sensorHotRegNo->value();

    type = ui->blowSensTypeCmb->currentIndex();
    weather_autom_cfg->snow_blow_sensor.type = type;
    weather_autom_cfg->snow_blow_sensor.addr[type] = ui->blowSensorAddr->value();
    weather_autom_cfg->snow_blow_sensor.reg_no[type] = ui->blowSensorRegNo->value();
    weather_autom_cfg->snow_blow_sensor.bit_no[type] = ui->blowSensorBitNo->value();

    weather_autom_cfg->sensor_pwr_ctrl.active = ui->sensorPwrCtrlChk->isChecked();
    weather_autom_cfg->sensor_pwr_ctrl.module_id = ui->sensorPwrCtrlIOMod->value();
    weather_autom_cfg->sensor_pwr_ctrl.bit_no = ui->sensorPwrCtrlBitNo->value();

    weather_autom_cfg->referenceCircuitNo = ui->referenceCirNo->value();

    switch(weather_autom_cfg->snow_blow_sensor.type)
    {
    case 0:     //io
        if(checkIoMod(weather_autom_cfg->snow_blow_sensor.addr[weather_autom_cfg->snow_blow_sensor.type], 0, "Czujnik śniegu nawianego") == 1)
            return false;
        break;
    case 1:     //can
        break;
    case 2:     //modbus
        break;
    }

    switch(weather_autom_cfg->t_hot.type)
    {
    case 0:     //TH
        if(checkIoMod(weather_autom_cfg->t_hot.addr[weather_autom_cfg->t_hot.type], 2, "Czujnik temperatury szyny grzanej") == 1)
            return false;
        break;
    case 1:     //CAN
        break;
    case 2:     //Modbus
        break;
    }

    switch(weather_autom_cfg->t_cold.type)
    {
    case 0:     //TH
        if(checkIoMod(weather_autom_cfg->t_cold.addr[weather_autom_cfg->t_cold.type], 2, "Czujnik temperatury szyny zimnej") == 1)
            return false;
        break;
    case 1:     //CAN
        break;
    case 2:     //Modbus
        break;
    }

    if(weather_autom_cfg->sensor_pwr_ctrl.active != 0)
    {
        if(checkIoMod(weather_autom_cfg->sensor_pwr_ctrl.module_id, 2, "Potwierdzenie zasilania czujników") == 1)
            return false;
    }

    return true;
}

void CWeatherAutomForm::on_sensorColdTypeCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:     //TH
        ui->sensorColdAddrLbl->setText("Nr modułu TH");
        ui->sensorColdAddr->setMinimum(1);
        ui->sensorColdAddr->setMaximum(IO_MODULE_COUNT);
        ui->sensorColdRegNoLbl->setText("Nr kanału TH");
        ui->sensorColdRegNo->setMinimum(1);
        ui->sensorColdRegNo->setMaximum(4);
        break;
    case 1:     //CAN
        ui->sensorColdAddrLbl->setText("Adres CAN");
        ui->sensorColdAddr->setMinimum(1);
        ui->sensorColdAddr->setMaximum(255);
        ui->sensorColdRegNoLbl->setText("Nr meldunku");
        ui->sensorColdRegNo->setMinimum(0);
        ui->sensorColdRegNo->setMaximum(127);
        break;
    case 2:     //Modbus
        ui->sensorColdAddrLbl->setText("Adres Modbus");
        ui->sensorColdAddr->setMinimum(1);
        ui->sensorColdAddr->setMaximum(255);
        ui->sensorColdRegNoLbl->setText("Nr rejestru");
        ui->sensorColdRegNo->setMinimum(0);
        ui->sensorColdRegNo->setMaximum(65535);
        break;
    }
}

void CWeatherAutomForm::on_sensorHotTypeCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:     //TH
        ui->sensorHotAddrLbl->setText("Nr modułu TH");
        ui->sensorHotAddr->setMinimum(1);
        ui->sensorHotAddr->setMaximum(IO_MODULE_COUNT);
        ui->sensorHotRegNoLbl->setText("Nr kanału TH");
        ui->sensorHotRegNo->setMinimum(1);
        ui->sensorHotRegNo->setMaximum(4);
        break;
    case 1:     //Modbus
        ui->sensorHotAddrLbl->setText("Adres Modbus");
        ui->sensorHotAddr->setMinimum(1);
        ui->sensorHotAddr->setMaximum(255);
        ui->sensorHotRegNoLbl->setText("Nr rejestru");
        ui->sensorHotRegNo->setMinimum(0);
        ui->sensorHotRegNo->setMaximum(65535);
        break;
    }
}

void CWeatherAutomForm::on_blowSensTypeCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:     //IO
        ui->blowSensorAddrLbl->setText("Nr modułu IO");
        ui->blowSensorAddr->setMinimum(1);
        ui->blowSensorAddr->setMaximum(IO_MODULE_COUNT);
        ui->blowSensorBitNoLbl->setText("Nr wejścia");
        ui->blowSensorBitNo->setMinimum(1);
        ui->blowSensorBitNo->setMaximum(20);
        ui->blowSensorRegNoLbl->setVisible(false);
        ui->blowSensorRegNo->setVisible(false);
        break;
    case 1:     //CAN
        ui->blowSensorAddrLbl->setText("Adres CAN");
        ui->blowSensorAddr->setMinimum(1);
        ui->blowSensorAddr->setMaximum(255);
        ui->blowSensorBitNoLbl->setText("Nr bitu");
        ui->blowSensorBitNo->setMinimum(1);
        ui->blowSensorBitNo->setMaximum(16);
        ui->blowSensorRegNoLbl->setVisible(true);
        ui->blowSensorRegNoLbl->setText("Nr meldunku");
        ui->blowSensorRegNo->setMinimum(0);
        ui->blowSensorRegNo->setMaximum(127);
        ui->blowSensorRegNo->setVisible(true);
        break;
    case 2:     //Modbus
        ui->blowSensorAddrLbl->setText("Adres Modbus");
        ui->blowSensorAddr->setMinimum(1);
        ui->blowSensorAddr->setMaximum(255);
        ui->blowSensorBitNoLbl->setText("Nr bitu");
        ui->blowSensorBitNo->setMinimum(1);
        ui->blowSensorBitNo->setMaximum(16);
        ui->blowSensorRegNoLbl->setVisible(true);
        ui->blowSensorRegNoLbl->setText("Nr rejestru");
        ui->blowSensorRegNo->setMinimum(0);
        ui->blowSensorRegNo->setMaximum(65535);
        ui->blowSensorRegNo->setVisible(true);
        break;
    }
}

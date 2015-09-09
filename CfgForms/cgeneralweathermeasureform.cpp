#include "cgeneralweathermeasureform.h"
#include "ui_cgeneralweathermeasureform.h"

CGeneralWeatherMeasureForm::CGeneralWeatherMeasureForm(QWidget *parent) :
    CMyForm(parent),
    ui(new Ui::CGeneralWeatherMeasureForm)
{
    ui->setupUi(this);
}

CGeneralWeatherMeasureForm::~CGeneralWeatherMeasureForm()
{
    delete ui;
}

bool CGeneralWeatherMeasureForm::setCfg(void *cfg_struct)
{
    general_weather_measure_cfg_t *general_weather_measure_cfg = (general_weather_measure_cfg_t*)cfg_struct;

    ui->generalTempSensorTypeCmb->setCurrentIndex(general_weather_measure_cfg->temperature_sensor.type);
    ui->generalTempSensorAddr->setValue(general_weather_measure_cfg->temperature_sensor.addr);
    ui->generalTempSensorRegNo->setValue(general_weather_measure_cfg->temperature_sensor.reg_no);

    ui->generalFallSensorTypeCmb->setCurrentIndex(general_weather_measure_cfg->snow_fall_sensor.type);
    ui->generalFallSensorAddr->setValue(general_weather_measure_cfg->snow_fall_sensor.addr);
    ui->generalFallSensorBitNo->setValue(general_weather_measure_cfg->snow_fall_sensor.bit_no);
    ui->generalFallSensorRegNo->setValue(general_weather_measure_cfg->snow_fall_sensor.reg_no);

    if(general_weather_measure_cfg->sensor_pwr_ctrl.active != 0)
        ui->sensorPwrCtrlChk->setChecked(true);
    else
        ui->sensorPwrCtrlChk->setChecked(false);
    ui->sensorPwrCtrlIOMod->setValue(general_weather_measure_cfg->sensor_pwr_ctrl.module_id);
    ui->sensorPwrCtrlBitNo->setValue(general_weather_measure_cfg->sensor_pwr_ctrl.bit_no);

    return true;
}

bool CGeneralWeatherMeasureForm::getCfg(void *cfg_struct)
{
    general_weather_measure_cfg_t *general_weather_measure_cfg = (general_weather_measure_cfg_t*)cfg_struct;

    bool ret = true;
    uint8_t addr = ui->generalTempSensorAddr->value();
    uint16_t reg_no = ui->generalTempSensorRegNo->value();
    uint8_t bit_no;

    memset(general_weather_measure_cfg, 0, sizeof(general_weather_measure_cfg_t));
    general_weather_measure_cfg->temperature_sensor.type = ui->generalTempSensorTypeCmb->currentIndex();
    general_weather_measure_cfg->temperature_sensor.addr = addr;
    general_weather_measure_cfg->temperature_sensor.reg_no = reg_no;

    switch(general_weather_measure_cfg->temperature_sensor.type)
    {
    case 0:     //TH
        if(checkIoMod(addr, 2, "Ogólne pomiary pogody - czujnik temperatury otoczenia") == 1)
            return false;
        break;
    case 1:     //CAN
        break;
    case 2:     //Modbus
        break;
    }

    general_weather_measure_cfg->snow_fall_sensor.type = ui->generalFallSensorTypeCmb->currentIndex();
    addr = ui->generalFallSensorAddr->value();
    reg_no = ui->generalFallSensorRegNo->value();
    bit_no = ui->generalFallSensorBitNo->value();

    switch(general_weather_measure_cfg->snow_fall_sensor.type)
    {
    case 0:     //io
        if(checkIoMod(addr, 0, "Ogólne pomiary pogody - czujnik opadu") == 1)
            return false;
        break;
    case 1:     //can
        break;
    case 2:     //modbus
        break;
    }
    general_weather_measure_cfg->snow_fall_sensor.addr = addr;
    general_weather_measure_cfg->snow_fall_sensor.reg_no = reg_no;
    general_weather_measure_cfg->snow_fall_sensor.bit_no = bit_no;

    if(ui->sensorPwrCtrlChk->isChecked())
        general_weather_measure_cfg->sensor_pwr_ctrl.active = 1;
    else
        general_weather_measure_cfg->sensor_pwr_ctrl.active = 0;
    addr = ui->sensorPwrCtrlIOMod->value();
    bit_no = ui->sensorPwrCtrlBitNo->value();
    if((general_weather_measure_cfg->sensor_pwr_ctrl.active == 1) &&
            (checkIoMod(addr, 0, "Ogólne pomiary pogody - potwierdzenie zasilania czujników") == 1))
        return false;
    general_weather_measure_cfg->sensor_pwr_ctrl.module_id = addr;
    general_weather_measure_cfg->sensor_pwr_ctrl.bit_no = bit_no;

    return ret;
}

void CGeneralWeatherMeasureForm::on_generalTempSensorTypeCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:     //TH
        ui->generalTempSensorAddrLbl->setText("Nr modułu TH");
        ui->generalTempSensorAddr->setMinimum(1);
        ui->generalTempSensorAddr->setMaximum(IO_MODULE_COUNT);
        ui->generalTempSensorRegNoLbl->setText("Nr kanału TH");
        ui->generalTempSensorRegNo->setMinimum(1);
        ui->generalTempSensorRegNo->setMaximum(4);
        break;
    case 1:     //CAN
        ui->generalTempSensorAddrLbl->setText("Adres CAN");
        ui->generalTempSensorAddr->setMinimum(1);
        ui->generalTempSensorAddr->setMaximum(255);
        ui->generalTempSensorRegNoLbl->setText("Nr meldunku");
        ui->generalTempSensorRegNo->setMinimum(0);
        ui->generalTempSensorRegNo->setMaximum(127);
        break;
    case 2:     //Modbus
        ui->generalTempSensorAddrLbl->setText("Adres Modbus");
        ui->generalTempSensorAddr->setMinimum(1);
        ui->generalTempSensorAddr->setMaximum(255);
        ui->generalTempSensorRegNoLbl->setText("Nr rejestru");
        ui->generalTempSensorRegNo->setMinimum(0);
        ui->generalTempSensorRegNo->setMaximum(65535);
        break;
    }
}

void CGeneralWeatherMeasureForm::on_generalFallSensorTypeCmb_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:     //IO
        ui->generalFallSensorAddrLbl->setText("Nr modułu IO");
        ui->generalFallSensorAddr->setMinimum(1);
        ui->generalFallSensorAddr->setMaximum(IO_MODULE_COUNT);
        ui->generalFallSensorBitNoLbl->setText("Nr wejścia");
        ui->generalFallSensorBitNo->setMinimum(1);
        ui->generalFallSensorBitNo->setMaximum(20);
        ui->generalFallSensorRegNoLbl->setVisible(false);
        ui->generalFallSensorRegNo->setVisible(false);
        break;
    case 1:     //CAN
        ui->generalFallSensorAddrLbl->setText("Adres CAN");
        ui->generalFallSensorAddr->setMinimum(1);
        ui->generalFallSensorAddr->setMaximum(255);
        ui->generalFallSensorBitNoLbl->setText("Nr bitu");
        ui->generalFallSensorBitNo->setMinimum(1);
        ui->generalFallSensorBitNo->setMaximum(16);
        ui->generalFallSensorRegNoLbl->setVisible(true);
        ui->generalFallSensorRegNoLbl->setText("Nr meldunku");
        ui->generalFallSensorRegNo->setMinimum(0);
        ui->generalFallSensorRegNo->setMaximum(127);
        ui->generalFallSensorRegNo->setVisible(true);
        break;
    case 2:     //Modbus
        ui->generalFallSensorAddrLbl->setText("Adres Modbus");
        ui->generalFallSensorAddr->setMinimum(1);
        ui->generalFallSensorAddr->setMaximum(255);
        ui->generalFallSensorBitNoLbl->setText("Nr bitu");
        ui->generalFallSensorBitNo->setMinimum(1);
        ui->generalFallSensorBitNo->setMaximum(16);
        ui->generalFallSensorRegNoLbl->setVisible(true);
        ui->generalFallSensorRegNoLbl->setText("Nr rejestru");
        ui->generalFallSensorRegNo->setMinimum(0);
        ui->generalFallSensorRegNo->setMaximum(65535);
        ui->generalFallSensorRegNo->setVisible(true);
        break;
    }
}

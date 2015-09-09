#ifndef CGENERALWEATHERMEASUREFORM_H
#define CGENERALWEATHERMEASUREFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CGeneralWeatherMeasureForm;
}

class CGeneralWeatherMeasureForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CGeneralWeatherMeasureForm(QWidget *parent = 0);
    ~CGeneralWeatherMeasureForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private slots:
    void on_generalTempSensorTypeCmb_currentIndexChanged(int index);

    void on_generalFallSensorTypeCmb_currentIndexChanged(int index);

private:
    Ui::CGeneralWeatherMeasureForm *ui;
};

#endif // CGENERALWEATHERMEASUREFORM_H

#ifndef CWEATHERAUTOMFORM_H
#define CWEATHERAUTOMFORM_H

#include "cmyform.h"
#include "eor_cfg.hpp"

namespace Ui {
class CWeatherAutomForm;
}

class CWeatherAutomForm : public CMyForm
{
    Q_OBJECT

public:
    explicit CWeatherAutomForm(QWidget *parent = 0);
    ~CWeatherAutomForm();

    bool getCfg(void* cfg_struct);
    bool setCfg(void* cfg_struct);

private slots:
    void on_sensorColdTypeCmb_currentIndexChanged(int index);

    void on_sensorHotTypeCmb_currentIndexChanged(int index);

    void on_blowSensTypeCmb_currentIndexChanged(int index);

private:
    Ui::CWeatherAutomForm *ui;
};

#endif // CWEATHERAUTOMFORM_H

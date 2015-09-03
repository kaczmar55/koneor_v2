#ifndef CWEATHERAUTOMFORM_H
#define CWEATHERAUTOMFORM_H

#include <QWidget>

namespace Ui {
class CWeatherAutomForm;
}

class CWeatherAutomForm : public QWidget
{
    Q_OBJECT

public:
    explicit CWeatherAutomForm(QWidget *parent = 0);
    ~CWeatherAutomForm();

private:
    Ui::CWeatherAutomForm *ui;
};

#endif // CWEATHERAUTOMFORM_H

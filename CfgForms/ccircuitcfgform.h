#ifndef CCIRCUITCFGFORM_H
#define CCIRCUITCFGFORM_H

#include <QWidget>

namespace Ui {
class CCircuitCfgForm;
}

class CCircuitCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CCircuitCfgForm(QWidget *parent = 0);
    ~CCircuitCfgForm();

private:
    Ui::CCircuitCfgForm *ui;
};

#endif // CCIRCUITCFGFORM_H

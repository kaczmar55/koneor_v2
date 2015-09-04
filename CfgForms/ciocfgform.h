#ifndef CIOCFGFORM_H
#define CIOCFGFORM_H

#include <QWidget>

namespace Ui {
class CIOCfgForm;
}

class CIOCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CIOCfgForm(QWidget *parent = 0);
    ~CIOCfgForm();

private:
    Ui::CIOCfgForm *ui;
};

#endif // CIOCFGFORM_H

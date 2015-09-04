#ifndef CRS232CFGFORM_H
#define CRS232CFGFORM_H

#include <QWidget>

namespace Ui {
class CRs232CfgForm;
}

class CRs232CfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CRs232CfgForm(QWidget *parent = 0);
    ~CRs232CfgForm();

private:
    Ui::CRs232CfgForm *ui;
};

#endif // CRS232CFGFORM_H

#ifndef CMODBUSSLAVECFGFORM_H
#define CMODBUSSLAVECFGFORM_H

#include <QWidget>

namespace Ui {
class CModbusSlaveCfgForm;
}

class CModbusSlaveCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CModbusSlaveCfgForm(QWidget *parent = 0);
    ~CModbusSlaveCfgForm();

private:
    Ui::CModbusSlaveCfgForm *ui;
};

#endif // CMODBUSSLAVECFGFORM_H

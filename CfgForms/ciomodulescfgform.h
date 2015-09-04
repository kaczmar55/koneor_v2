#ifndef CIOMODULESCFGFORM_H
#define CIOMODULESCFGFORM_H

#include <QWidget>

namespace Ui {
class CIoModulesCfgForm;
}

class CIoModulesCfgForm : public QWidget
{
    Q_OBJECT

public:
    explicit CIoModulesCfgForm(QWidget *parent = 0);
    ~CIoModulesCfgForm();

private:
    Ui::CIoModulesCfgForm *ui;
};

#endif // CIOMODULESCFGFORM_H

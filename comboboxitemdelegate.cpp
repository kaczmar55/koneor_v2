#include "comboboxitemdelegate.h"
#include <QComboBox>

ComboBoxItemDelegate::ComboBoxItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}


ComboBoxItemDelegate::~ComboBoxItemDelegate()
{
}


QWidget* ComboBoxItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // ComboBox ony in column 1
    if (index.column() != 0)
        return QStyledItemDelegate::createEditor(parent, option, index);

    // Create the combobox and populate it
    QComboBox* cb = new QComboBox(parent);

    cb->addItem(QString("IO10/5"), 1);
    cb->addItem(QString("TH"), 3);
    cb->addItem(QString("I12"), 4);
    cb->addItem(QString("I20"), 5);
    cb->addItem(QString("O10"), 6);
    cb->addItem(QString("CVM"), 7);
    cb->addItem(QString("ISC3"), 10);
    cb->addItem(QString("IO4/7"), 11);
    cb->addItem(QString("O8"), 12);
    cb->addItem(QString("GMR IO"), 14);

    return cb;
}


void ComboBoxItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
       // get the index of the text in the combobox that matches the current value of the itenm
       QString currentText = index.data(Qt::EditRole).toString();
       int cbIndex = cb->findText(currentText);
       // if it is valid, adjust the combobox
       if (cbIndex >= 0)
           cb->setCurrentIndex(cbIndex);
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}


void ComboBoxItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (QComboBox* cb = qobject_cast<QComboBox*>(editor))
        // save the current text of the combo box as the current value of the item
        model->setData(index, cb->currentText(), Qt::EditRole);
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

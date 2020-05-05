#pragma once

#include <QWidget>
#include <QSettings>
#include <QFileDialog>
#include "ui_CostumePackageMaker.h"

class CostumePackageMaker : public QWidget
{
    Q_OBJECT

private slots:
    void btAddStepClick();
    void btSaveClick();
    void btCancelClick();
    void btFileClick(int row);

public:
    CostumePackageMaker(QWidget *parent = Q_NULLPTR);
    ~CostumePackageMaker();

private:
    int m_rowCount;

    QMap<QString, QString> m_costumeSteps;
    QDir m_defaultPath;
    QFileDialog m_fileDialog;
    Ui::CostumePackageMaker ui;
};

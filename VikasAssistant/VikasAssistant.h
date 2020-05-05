#pragma once

#include <QQueue>
#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QFileDialog>
#include <QtWidgets/QMainWindow>
#include "ui_VikasAssistant.h"

class VikasAssistant : public QMainWindow
{
    Q_OBJECT

public slots:
    void onListWidgetItemSelected(QListWidgetItem* item);

public:
    VikasAssistant(QWidget *parent = Q_NULLPTR);
    ~VikasAssistant();

private:
    void showFileDialog();
    void readPackage(QFileInfo packagePath);
    void paintEvent(QPaintEvent* event); 
    void closeEvent(QCloseEvent* event);

    QSettings m_config;
    std::unique_ptr<QSettings> m_currentCostume;

    QFileDialog m_fileDialog;

    QList<QString> ma_checkedItems;
    QVector<QPixmap*> ma_images;
    QVector<QPixmap*> m_drawnImages;
    QMap<QString, QPixmap*> m_nameToImageMap;
    Ui::VikasAssistantClass ui;
};

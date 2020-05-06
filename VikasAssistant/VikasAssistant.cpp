#include <QPainter>
#include <QTextCodec.h>
#include "VikasAssistant.h"

const int SCALE_HEIGHT = 1000;

void VikasAssistant::onListWidgetItemSelected(QListWidgetItem* item)
{
    if (item->text() == "Base")
    {
        item->setCheckState(Qt::Checked);
        return;
    }

    if (item->checkState() == Qt::Checked)
    {
        m_drawnImages.push_back(m_nameToImageMap[item->text()]);
        ma_checkedItems.append(item->text());
    }
    else
    {
        m_drawnImages.removeOne(m_nameToImageMap[item->text()]);
        ma_checkedItems.removeOne(item->text());
    }
}

VikasAssistant::VikasAssistant(QWidget *parent)
    : QMainWindow(parent), m_fileDialog(this), m_config("VikasAssistant.ini", QSettings::IniFormat), m_currentCostume(nullptr)
{
    ui.setupUi(this);
    ui.listWidget->adjustSize();

    QObject::connect(ui.listWidget, &QListWidget::itemChanged, this, &VikasAssistant::onListWidgetItemSelected);
    QObject::connect(ui.openFileAction, &QAction::triggered, this, &VikasAssistant::showFileDialog);
    QObject::connect(ui.closeAction, &QAction::triggered, this, &VikasAssistant::close);

    QString prevPath = m_config.value("Costume", "").toString();
    if (!prevPath.isEmpty())
    {
        readPackage(prevPath);
    }
}

VikasAssistant::~VikasAssistant()
{
}

void VikasAssistant::showFileDialog()
{
    m_fileDialog.setNameFilter("Costume.ini");
    m_fileDialog.setFileMode(QFileDialog::ExistingFile);
    if (m_fileDialog.exec() == QDialog::Accepted)
    {        
        readPackage(QFileInfo(m_fileDialog.selectedFiles()[0]));
    }

    m_config.setValue("Costume", QDir::current().relativeFilePath(m_fileDialog.selectedFiles()[0]));
}

void VikasAssistant::readPackage(QFileInfo packagePath)
{
    ui.listWidget->clear();

    QDir packageDir = packagePath.absoluteDir();

    m_currentCostume.reset(new QSettings(packagePath.absoluteFilePath(), QSettings::IniFormat));

    for (QString key : m_currentCostume->allKeys())
    {
        QString value = m_currentCostume->value(key, "").toString();

        auto it = new QListWidgetItem(key, ui.listWidget);
        it->setFlags(it->flags() | Qt::ItemIsUserCheckable);

        if (value.startsWith("+"))
        {
            value = value.remove(0, 1);
            it->setCheckState(Qt::Checked);
            it->setText(key);
        }
        else
        {
            it->setCheckState(Qt::Unchecked);
        }


        QString image = packageDir.absoluteFilePath(value);
        QPixmap* picture = new QPixmap(image);
        *picture = picture->scaledToHeight(SCALE_HEIGHT);
        m_nameToImageMap.insert(key, picture);

        if (it->checkState() == Qt::Checked)
        {
            if (key == "Base")
            {
                m_drawnImages.push_front(picture);
            }
            else
            {
                m_drawnImages.push_back(picture);
            }
        }

    }

    ui.lbCostumeName->setText(packageDir.dirName());
    ui.label->repaint();
}

void VikasAssistant::paintEvent(QPaintEvent * event)
{
    if (!m_drawnImages.isEmpty())
    {
        QPixmap result(m_drawnImages.front()->width(), m_drawnImages.front()->height());
        QPainter imagePainter(&result);

        for (auto img : m_drawnImages)
        {
            imagePainter.drawPixmap(0, 0, *img);
        }

        ui.label->setPixmap(result);
    }
}

void VikasAssistant::closeEvent(QCloseEvent* event)
{
    auto keyList = m_currentCostume->allKeys();
    for (auto key = keyList.begin(); key != keyList.end(); ++key)
    {
        QString value = m_currentCostume->value(*key, "").toString();
        if (!value.isEmpty())
        {
            if (std::find(ma_checkedItems.begin(), ma_checkedItems.end(), *key) != ma_checkedItems.end())
            {
                if (!value.startsWith("+"))
                    value = "+" + value;
            }
            else
            {
                if (value.startsWith("+"))
                    value = value.remove(0, 1);
            }
        }
        m_currentCostume->setValue(*key, value);
    }
}

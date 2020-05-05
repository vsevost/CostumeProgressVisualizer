#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include "CostumePackageMaker.h"

CostumePackageMaker::CostumePackageMaker(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_defaultPath = QDir::currentPath();

}

CostumePackageMaker::~CostumePackageMaker()
{
}

void CostumePackageMaker::btAddStepClick()
{
    QLineEdit* edStep = new QLineEdit(this);
    QLineEdit* edFile = new QLineEdit(this);
    QPushButton* btFile = new QPushButton(this);

    QHBoxLayout* fileLayout = new QHBoxLayout();
    fileLayout->addWidget(edFile, 1);
    fileLayout->addWidget(btFile, 1);

    QHBoxLayout* stepLayout = new QHBoxLayout();
    stepLayout->addWidget(edStep, 1);
    stepLayout->addLayout(fileLayout, 1);

    QVBoxLayout* formLayout = dynamic_cast<QVBoxLayout*>(ui.verticalLayout);
    formLayout->insertLayout(m_rowCount + 1, stepLayout);
    m_rowCount += 1;
}

void CostumePackageMaker::btSaveClick()
{
    QVBoxLayout* formLayout = dynamic_cast<QVBoxLayout*>(ui.verticalLayout);

    for (int i = 1; i < m_rowCount + 1; ++i)
    {
        QHBoxLayout* prevStep = dynamic_cast<QHBoxLayout*>(formLayout->itemAt(i));
        QString prevStepName = dynamic_cast<QLineEdit*>(prevStep->itemAt(0))->text();
        QString prevStepFile = dynamic_cast<QLineEdit*>(dynamic_cast<QHBoxLayout*>(prevStep->itemAt(1))->itemAt(0))->text();
        m_costumeSteps.insert(prevStepName, prevStepFile);
    }

    QString costumeIniFile = QFileDialog::getSaveFileName(this, "Save Costume...", m_defaultPath.absolutePath(), "*.ini");
    QSettings costumeIni(costumeIniFile, QSettings::IniFormat);

    for (auto step = m_costumeSteps.cbegin(); step != m_costumeSteps.cend(); ++step)
    {
        costumeIni.setValue(step.key(), step.value());
    }
}

void CostumePackageMaker::btCancelClick()
{
}

void CostumePackageMaker::btFileClick(int row)
{
    QVBoxLayout* formLayout = dynamic_cast<QVBoxLayout*>(ui.verticalLayout);
    QHBoxLayout* step = dynamic_cast<QHBoxLayout*>(formLayout->itemAt(row));
    QLineEdit* edFile = dynamic_cast<QLineEdit*>(dynamic_cast<QHBoxLayout*>(step->itemAt(1))->itemAt(0));

    edFile->setText(QFileDialog::getOpenFileName(this, "Picture...", m_defaultPath.absolutePath(), "*.png"));
}

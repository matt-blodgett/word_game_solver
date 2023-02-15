#include "controlsview.h"


#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

#include <QCheckBox>



#include <QDebug>




ControlsView::ControlsView(QWidget *parent) : QWidget(parent)
{
    QLabel *lblHeading1 = new QLabel(this);
    QLabel *lblMinLength = new QLabel(this);
    QLabel *lblMaxLength = new QLabel(this);
    m_cbxMinLength = new QComboBox(this);
    m_cbxMaxLength = new QComboBox(this);
    m_optNoMinMax = new QCheckBox(this);
    m_btnProcess = new QPushButton(this);

    QGridLayout *gridMain = new QGridLayout(this);

    gridMain->addWidget(lblHeading1, 0, 0, 1, 2);

    gridMain->addWidget(lblMinLength, 1, 0, 1, 1);
    gridMain->addWidget(m_cbxMinLength, 1, 1, 1, 1);

    gridMain->addWidget(lblMaxLength, 2, 0, 1, 1);
    gridMain->addWidget(m_cbxMaxLength, 2, 1, 1, 1);

    gridMain->addWidget(m_optNoMinMax, 3, 1, 1, 2);

    gridMain->addWidget(m_btnProcess, 4, 0, 1, 2);

    gridMain->setColumnStretch(1, 1);

    gridMain->setRowStretch(5, 1);
//    gridMain->setContentsMargins(0, 0, 0, 0);
//    gridMain->setHorizontalSpacing(0);
//    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);

    lblHeading1->setAlignment(Qt::AlignmentFlag::AlignCenter);

    lblHeading1->setText("String Lengths");
    lblMinLength->setText("Min");
    lblMaxLength->setText("Max");
    m_optNoMinMax->setText("Search All");
    m_btnProcess->setText("Process");

    QStringList items;
    for (int i = 0; i <= 8; i ++) {
        items << QString::number(i);
    }
    m_cbxMinLength->addItems(items);
    m_cbxMaxLength->addItems(items);
    m_cbxMaxLength->setCurrentIndex(6);


    connect(m_optNoMinMax, &QCheckBox::stateChanged, this, &ControlsView::onNoMinMaxChecked);
    connect(m_btnProcess, &QPushButton::released, this, [this](){emit processStarted();});

}


void ControlsView::onNoMinMaxChecked(int state)
{
    if (state == Qt::CheckState::Checked) {
        m_cbxMinLength->setCurrentIndex(0);
        m_cbxMaxLength->setCurrentIndex(m_cbxMaxLength->count() - 1);
        m_cbxMinLength->setDisabled(true);
        m_cbxMaxLength->setDisabled(true);
    } else if (state == Qt::CheckState::Unchecked) {
        m_cbxMinLength->setCurrentIndex(0);
        m_cbxMaxLength->setCurrentIndex(0);
        m_cbxMinLength->setDisabled(false);
        m_cbxMaxLength->setDisabled(false);
    }
}


void ControlsView::setDisabled(bool const &disabled)
{
    m_cbxMinLength->setDisabled(disabled);
    m_cbxMaxLength->setDisabled(disabled);
    m_optNoMinMax->setDisabled(disabled);
    m_btnProcess->setDisabled(disabled);
}

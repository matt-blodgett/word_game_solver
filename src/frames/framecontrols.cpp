#include "framecontrols.h"


#include <QGridLayout>

#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>


#include <QGroupBox>


#include <QDebug>



//QProgressBar *m_barProgress = nullptr;

//#include <QProgressBar>
//void ControlsView::test()
//{
//    int val = m_barProgress->value();
//    m_barProgress->setValue(val + 10);
//}

//m_barProgress = new QProgressBar(this);
//m_barProgress->setOrientation(Qt::Horizontal);
//m_barProgress->setTextVisible(true);
//m_barProgress->setRange(0, 100);
//m_barProgress->setValue(0);




// Seperator ?
//QFrame* line = new QFrame();
//line->setFrameShape(QFrame::HLine);
//line->setFrameShadow(QFrame::Sunken);
//boxLayout->addWidget(line);


FrameControls::FrameControls(QWidget *parent) : QFrame(parent)
{

    // --------------------------------------------------
    m_frmConfig = new QFrame(this);

    QLabel *lblMinLength = new QLabel(m_frmConfig);
    QLabel *lblMaxLength = new QLabel(m_frmConfig);

    m_cbxMinLength = new QComboBox(m_frmConfig);
    m_cbxMaxLength = new QComboBox(m_frmConfig);
    m_optNoMinMax = new QCheckBox(m_frmConfig);
    m_cbxBoardType = new QComboBox(m_frmConfig);
    m_btnProcess = new QPushButton(m_frmConfig);

    QGroupBox *groupBox1 = new QGroupBox(m_frmConfig);
    QGridLayout *gridBox1 = new QGridLayout();
    gridBox1->addWidget(lblMinLength, 0, 0, 1, 1);
    gridBox1->addWidget(m_cbxMinLength, 0, 1, 1, 1);
    gridBox1->addWidget(lblMaxLength, 1, 0, 1, 1);
    gridBox1->addWidget(m_cbxMaxLength, 1, 1, 1, 1);
    gridBox1->addWidget(m_optNoMinMax, 2, 1, 1, 2);
    gridBox1->setColumnStretch(1, 1);
    groupBox1->setLayout(gridBox1);
    groupBox1->setTitle("Limit Word Length");

    QGroupBox *groupBox2 = new QGroupBox(m_frmConfig);
    QGridLayout *gridBox2 = new QGridLayout();
    gridBox2->addWidget(m_cbxBoardType, 0, 0, 1, 1);
    groupBox2->setLayout(gridBox2);
    groupBox2->setTitle("Board Type");

    QGridLayout *gridConfig = new QGridLayout(m_frmConfig);
    gridConfig->addWidget(m_btnProcess, 0, 0, 1, 1);
    gridConfig->addWidget(groupBox1, 0, 1, 1, 1);
    gridConfig->addWidget(groupBox2, 0, 2, 1, 1);
    gridConfig->setColumnStretch(3, 1);
    gridConfig->setRowStretch(gridConfig->rowCount(), 1);
//    gridConfig->setContentsMargins(0, 0, 0, 0);
//    gridConfig->setHorizontalSpacing(0);
//    gridConfig->setVerticalSpacing(0);
    m_frmConfig->setLayout(gridConfig);


    // --------------------------------------------------
    m_frmLoading = new QFrame(this);

    QLabel *lblLoading = new QLabel(m_frmLoading);
    lblLoading->setText("Loading");

    QGridLayout *gridLoading = new QGridLayout(m_frmLoading);
    gridLoading->addWidget(lblLoading, 0, 0, 1, 1);
    m_frmLoading->setLayout(gridLoading);


    // --------------------------------------------------
    m_frmResults = new QFrame(this);

    QLabel *lblResults = new QLabel(m_frmResults);
    lblResults->setText("Results");

    m_btnReset = new QPushButton(m_frmResults);
    m_btnReset->setText("Reset");
    connect(m_btnReset, &QPushButton::released, this, [this](){emit resetClicked();});

    QGridLayout *gridResults = new QGridLayout(m_frmResults);
    gridResults->addWidget(lblResults, 0, 0, 1, 1);
    gridResults->addWidget(m_btnReset, 1, 0, 1, 1);
    gridResults->setColumnStretch(1, 1);
    m_frmResults->setLayout(gridResults);


    // --------------------------------------------------
    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_frmConfig, 0, 0, 1, 1);
    gridMain->addWidget(m_frmLoading, 0, 0, 1, 1);
    gridMain->addWidget(m_frmResults, 0, 0, 1, 1);
    gridMain->setColumnStretch(0, 1);
    gridMain->setRowStretch(0, 1);
//    gridMain->setContentsMargins(0, 0, 0, 0);
//    gridMain->setHorizontalSpacing(0);
//    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);

    setState("initial");


    // --------------------------------------------------
    lblMinLength->setText("Minimum");
    lblMaxLength->setText("Maximum");
    m_optNoMinMax->setText("All Lengths");
    m_btnProcess->setText("Process");

    QStringList items;
    for (int i = 0; i <= 8; i ++) {
        items << QString::number(i);
    }
    m_cbxMinLength->addItems(items);
    m_cbxMaxLength->addItems(items);
    m_cbxMinLength->setCurrentIndex(0);
    m_cbxMaxLength->setCurrentIndex(3);


    m_cbxBoardType->addItem("Normal");
    m_cbxBoardType->setCurrentIndex(0);

    connect(m_optNoMinMax, &QCheckBox::stateChanged, this, &FrameControls::onNoMinMaxChanged);
    connect(m_btnProcess, &QPushButton::released, this, &FrameControls::onProcessClicked);
}


void FrameControls::onNoMinMaxChanged(int state)
{
    if (state == Qt::Checked) {
        m_cbxMinLength->setCurrentIndex(0);
        m_cbxMaxLength->setCurrentIndex(m_cbxMaxLength->count() - 1);
        m_cbxMinLength->setDisabled(true);
        m_cbxMaxLength->setDisabled(true);
    } else if (state == Qt::Unchecked) {
        m_cbxMinLength->setCurrentIndex(0);
        m_cbxMaxLength->setCurrentIndex(3);
        m_cbxMinLength->setDisabled(false);
        m_cbxMaxLength->setDisabled(false);
    }
}

void FrameControls::onProcessClicked()
{
    int min = m_cbxMinLength->currentIndex();
    int max = m_cbxMaxLength->currentIndex();

    emit processClicked(min, max);
}

void FrameControls::setState(const QString &state)
{
    m_frmConfig->setVisible(false);
    m_frmLoading->setVisible(false);
    m_frmResults->setVisible(false);

    if (state == "initial") {
        m_frmConfig->setVisible(true);
    } else if (state == "loading") {
        m_frmLoading->setVisible(true);
    } else if (state == "done") {
        m_frmResults->setVisible(true);
    }
}
void FrameControls::setDisabled(const bool &disabled)
{
    m_btnProcess->setDisabled(disabled);
}




















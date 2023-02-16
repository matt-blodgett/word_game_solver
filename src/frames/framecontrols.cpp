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
    QLabel *lblMinLength = new QLabel(this);
    QLabel *lblMaxLength = new QLabel(this);

    m_cbxMinLength = new QComboBox(this);
    m_cbxMaxLength = new QComboBox(this);
    m_optNoMinMax = new QCheckBox(this);
    m_boxWordListPath = new QLineEdit(this);
    m_btnOpenFileDialog = new QPushButton(this);
    m_btnStartProcess = new QPushButton(this);

    QGroupBox *groupBox1 = new QGroupBox(this);
    QGridLayout *gridBox1 = new QGridLayout();

    gridBox1->addWidget(lblMinLength, 0, 0, 1, 1);
    gridBox1->addWidget(m_cbxMinLength, 0, 1, 1, 1);

    gridBox1->addWidget(lblMaxLength, 1, 0, 1, 1);
    gridBox1->addWidget(m_cbxMaxLength, 1, 1, 1, 1);

    gridBox1->addWidget(m_optNoMinMax, 2, 1, 1, 2);

    gridBox1->setColumnStretch(1, 1);

    groupBox1->setLayout(gridBox1);
    groupBox1->setTitle("Limit Word Length");

    QGroupBox *groupBox2 = new QGroupBox(this);
    QGridLayout *gridBox2 = new QGridLayout();
    gridBox2->addWidget(m_boxWordListPath, 0, 0, 1, 1);
    gridBox2->addWidget(m_btnOpenFileDialog, 0, 1, 1, 1);
    gridBox2->setColumnStretch(0, 1);
    groupBox2->setLayout(gridBox2);
    groupBox2->setTitle("Wordlist File");


    QGridLayout *gridMain = new QGridLayout(this);
    gridMain->addWidget(m_btnStartProcess, 0, 0, 2, 1);
    gridMain->addWidget(groupBox1, 0, 1, 1, 1);
    gridMain->addWidget(groupBox2, 1, 1, 1, 2);


    gridMain->setColumnStretch(2, 1);

    gridMain->setRowStretch(gridMain->rowCount(), 1);
//    gridMain->setContentsMargins(0, 0, 0, 0);
//    gridMain->setHorizontalSpacing(0);
//    gridMain->setVerticalSpacing(0);
    setLayout(gridMain);


    lblMinLength->setText("Minimum");
    lblMaxLength->setText("Maximum");
    m_optNoMinMax->setText("All Lengths");
    m_boxWordListPath->setText("wordlist.txt");
    m_btnOpenFileDialog->setText("...");
    m_btnStartProcess->setText("Process");


    QStringList items;
    for (int i = 0; i <= 8; i ++) {
        items << QString::number(i);
    }
    m_cbxMinLength->addItems(items);
    m_cbxMaxLength->addItems(items);
    m_cbxMinLength->setCurrentIndex(0);
    m_cbxMaxLength->setCurrentIndex(3);


    connect(m_optNoMinMax, &QCheckBox::stateChanged, this, &FrameControls::onNoMinMaxChanged);
    connect(m_btnStartProcess, &QPushButton::released, this, &FrameControls::onStartProcessClicked);


    m_btnOpenFileDialog->setObjectName("OpenFileDialog");
    m_btnStartProcess->setObjectName("StartProcess");
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

void FrameControls::onStartProcessClicked()
{
    int min = m_cbxMinLength->currentIndex();
    int max = m_cbxMaxLength->currentIndex();
    emit startProcessClicked(min, max);
}

void FrameControls::setDisabled(bool const &disabled)
{
    m_cbxMinLength->setDisabled(disabled);
    m_cbxMaxLength->setDisabled(disabled);
    m_optNoMinMax->setDisabled(disabled);
    m_btnStartProcess->setDisabled(disabled);
}

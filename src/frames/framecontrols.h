#ifndef FRAMECONTROLS_H
#define FRAMECONTROLS_H


#include <QFrame>


QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
class QCheckBox;
class QLineEdit;
QT_END_NAMESPACE


class FrameControls : public QFrame
{
    Q_OBJECT

public:
    explicit FrameControls(QWidget *parent = nullptr);

private:
    QFrame *m_frmConfig = nullptr;
    QComboBox *m_cbxMinLength = nullptr;
    QComboBox *m_cbxMaxLength = nullptr;
    QCheckBox *m_optNoMinMax = nullptr;
    QComboBox *m_cbxBoardType = nullptr;
    QPushButton *m_btnProcess = nullptr;

    QFrame *m_frmLoading = nullptr;

    QFrame *m_frmResults = nullptr;
    QPushButton *m_btnReset = nullptr;

private slots:
    void onNoMinMaxChanged(int state);
    void onProcessClicked();

public slots:
    void setState(const QString &state);
    void setDisabled(const bool &disabled);

signals:
    void processClicked(const int &min, const int &max);
    void resetClicked();
};

#endif // FRAMECONTROLS_H

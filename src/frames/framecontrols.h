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
    QComboBox *m_cbxMinLength = nullptr;
    QComboBox *m_cbxMaxLength = nullptr;
    QCheckBox *m_optNoMinMax = nullptr;
    QLineEdit *m_boxWordListPath = nullptr;
    QPushButton *m_btnOpenFileDialog = nullptr;
    QPushButton *m_btnStartProcess = nullptr;

private slots:
    void onNoMinMaxChanged(int state);
    void onStartProcessClicked();

public slots:
    void setDisabled(bool const &disabled);

signals:
    void startProcessClicked(const int &min, const int &max);
};

#endif // FRAMECONTROLS_H

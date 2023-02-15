#ifndef CONTROLSVIEW_H
#define CONTROLSVIEW_H


#include <QWidget>


QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
class QLabel;
class QCheckBox;
QT_END_NAMESPACE


class ControlsView : public QWidget
{
    Q_OBJECT

public:
    explicit ControlsView(QWidget *parent = nullptr);

private:
    QComboBox *m_cbxMinLength = nullptr;
    QComboBox *m_cbxMaxLength = nullptr;
    QCheckBox *m_optNoMinMax = nullptr;
    QPushButton *m_btnProcess = nullptr;

private slots:
    void onNoMinMaxChecked(int state);

public slots:
    void setDisabled(bool const &disabled);

signals:
    void processStarted();
};

#endif // CONTROLSVIEW_H

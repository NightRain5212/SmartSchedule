#include "offeringdialog.h"
#include "ui_offeringdialog.h"

OfferingDialog::OfferingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OfferingDialog)
{
    ui->setupUi(this);
    setupCheckBoxes();
}

OfferingDialog::~OfferingDialog()
{
    delete ui;
}

void OfferingDialog::setOffering(const Offering &offering)
{
    offeringToUi(offering);
}

Offering OfferingDialog::getOffering() const
{
    return uiToOffering();
}


void OfferingDialog::weeksToCheckBoxes(int weeks)
{
    if (m_weekCheckBoxes.size() < 18) return;
    // 处理二进制的每一位
    for(int i=0;i<18;i++) {
        if( (weeks>>i)  & 1) {
            m_weekCheckBoxes[i]->setChecked(1);
        } else {
            m_weekCheckBoxes[i]->setChecked(0);
        }
    }
}

int OfferingDialog::checkBoxesToWeeks() const
{
    // 构造二进制的每一位
    int weeks = 0;
    if (m_weekCheckBoxes.size() < 18) return 0;
    for(int i=0;i<18;i++) {
        if(m_weekCheckBoxes[i]->isChecked()) {
            weeks = weeks | (1<<i);
        }
    }
    return weeks;
}

void OfferingDialog::timesToCheckBoxes(const QVector<int> &times)
{
    // 同理
    for(int i=0;i<7;i++) {
        int time = times[i];
        for(int j=0;j<13;j++) {
            if( (time>>j) & 1) {
                m_timeCheckBoxes[i][j]->setChecked(1);
            } else {
                m_timeCheckBoxes[i][j]->setChecked(0);
            }
        }
    }
}

QVector<int> OfferingDialog::checkBoxesToTimes() const
{
    QVector<int> times(7,0);
    for(int i=0;i<7;i++) {
        int time = 0;
        for(int j=0;j<13;j++) {
            if(m_timeCheckBoxes[i][j]->isChecked()) {
                time = time | (1<<j);
            }
        }
        times[i]=(time);
    }
    return times;
}

void OfferingDialog::setupCheckBoxes()
{
    // 初始化存储checkbox的容器，方便调用

    // 使用findChildren可以更健壮地找到所有QCheckBox，无论它们在布局中如何排列
    m_weekCheckBoxes = ui->weeksGroupBox->findChildren<QCheckBox*>();
    // 因为findChildren不保证顺序，所以我们根据复选框的文本（"1", "2"等）进行排序
    std::sort(m_weekCheckBoxes.begin(), m_weekCheckBoxes.end(), [](QCheckBox* a, QCheckBox* b) {
        return a->text().toInt() < b->text().toInt();
    });

    QGridLayout* timelayout = qobject_cast<QGridLayout*>(ui->timesGroupBox->layout());
    if(timelayout) {
        m_timeCheckBoxes.resize(7);
        for(int day=0;day<7;day++) {
            m_timeCheckBoxes[day].resize(13);
            for(int slot =0;slot<13;slot++) {
                QCheckBox* cb = qobject_cast<QCheckBox*>(timelayout->itemAtPosition(day+1,slot+1)->widget());
                if(cb) m_timeCheckBoxes[day][slot] = cb;
                else {
                    // 如果UI布局与代码预期不符，这里会打印警告，便于调试
                    qWarning() << "在OfferingDialog中找不到位于 day" << day << "slot" << slot << "的复选框\n";
                }
            }
        }
    }

}

void OfferingDialog::offeringToUi(const Offering &offering)
{
    ui->lineEdit_id->setText(offering.id);
    ui->lineEdit_teacher->setText(offering.teacher);
    weeksToCheckBoxes(offering.weeks);
    timesToCheckBoxes(offering.times);

}

Offering OfferingDialog::uiToOffering() const
{
    Offering offering;
    offering.id = ui->lineEdit_id->text();
    offering.teacher = ui->lineEdit_teacher->text();
    offering.weeks = checkBoxesToWeeks();
    offering.times = checkBoxesToTimes();
    return offering;
}

#ifndef UTIL_H
#define UTIL_H
#include <QString>
#include <QVector>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

struct Offering {
    QString id;   // 开课时间编号
    QString teacher;
    QVector<int> times = QVector<int>(7, 0); // 由7个二进制下13位的整数表示每周内的开课时间
    int weeks;  // 是1个2进制下18位的整数表示开课周次

    // --- 新增成员，用于存储解码后的数据 ---
    QList<int> decoded_weeks;      // 存储解码后的具体周次列表
    QList<QList<int>> decoded_times; // 存储解码后的每日节次列表
};

struct Course {
    QString name;
    QString id;
    int credit;
    QList<Offering> offerings;
    QString semester;
    QString required;
    QStringList prerequisites; // 先修课程id

};

Q_DECLARE_METATYPE(Course)
Q_DECLARE_METATYPE(Offering)

struct ScheduledCourse {
    QString class_id;   // 开课时间编号
    QString course_id;  // 课程编号
    int semester;    //选课学期 0~7,不选为-1
};


// 解析course.json文件的函数,接受文件路径，返回包含所有Course的QList
QList<Course> loadCourses(const QString& filePath);

// 将修改的课表保存到 courses.json 的函数,接受文件路径和课表对象两个参数
void saveCourses(const QString& filePath,const QList<Course>& courses);

// 解析schedule.json文件的函数,接受文件路径，返回包含选课方案对象
QList<ScheduledCourse> loadSchedule(const QString& filePath);

// 将生成的选课方案保存到 schedule.json 的函数,接受文件路径和选课方案两个参数
void saveSchedule(const QString& filePath,const QList<ScheduledCourse>& schedule);


#endif // UTIL_H

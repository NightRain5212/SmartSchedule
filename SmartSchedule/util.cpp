#include "util.h"
#include <QDebug>
#include <utility> // 为 std::as_const 包含此头文件

QList<Course> loadCourses(const QString& filePath)
{
    QList<Course> courses;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开课程文件:" << filePath;
        return courses;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "课程文件格式错误，根元素不是一个数组";
        return courses;
    }

    QJsonArray courseArray = doc.array();
    for (const QJsonValue &value : std::as_const(courseArray)) {
        if (!value.isObject()) continue;

        QJsonObject obj = value.toObject();
        Course course;
        course.id = obj["id"].toString();
        course.name = obj["name"].toString();
        course.credit = obj["credit"].toInt();
        course.semester = obj["semester"].toString();
        course.required = obj["required"].toString();

        if (obj.contains("prerequisites") && obj["prerequisites"].isArray()) {
            QJsonArray prereqArray = obj["prerequisites"].toArray();
            for (const QJsonValue &prereqValue : std::as_const(prereqArray)) {
                course.prerequisites.append(prereqValue.toString());
            }
        }

        if (obj.contains("offerings") && obj["offerings"].isArray()) {
            QJsonArray offeringsArray = obj["offerings"].toArray();
            for (const QJsonValue &offeringValue : std::as_const(offeringsArray)) {
                if (!offeringValue.isObject()) continue;
                QJsonObject offeringObj = offeringValue.toObject();
                Offering offering;
                offering.id = offeringObj["id"].toString();
                offering.teacher = offeringObj["teacher"].toString();

                // --- 处理周次 ---
                if (offeringObj.contains("weeks")) {
                    int weeksValue = offeringObj["weeks"].toInt();
                    // 1. 填充原始 weeks 字段
                    offering.weeks = weeksValue;

                    // 2. 解码数据并填充新增的 decoded_weeks 字段
                    for (int i = 0; i < 18; ++i) {
                        if (weeksValue & (1 << i)) {
                            offering.decoded_weeks.append(i + 1);
                        }
                    }
                }

                // --- 处理时间 ---
                if (offeringObj.contains("times") && offeringObj["times"].isArray()) {
                    QJsonArray timesArray = offeringObj["times"].toArray();
                    int dayIndex = 0;
                    for (const QJsonValue &timeValue : std::as_const(timesArray)) {
                        int dayTimeValue = timeValue.toInt();

                        // 1. 填充原始 times 字段
                        if (dayIndex < offering.times.size()) {
                            offering.times[dayIndex] = dayTimeValue;
                        }

                        // 2. 解码数据并填充新增的 decoded_times 字段
                        QList<int> dailyPeriods;
                        for (int i = 0; i < 13; ++i) {
                            if (dayTimeValue & (1 << i)) {
                                dailyPeriods.append(i + 1);
                            }
                        }
                        offering.decoded_times.append(dailyPeriods);
                        dayIndex++;
                    }
                }
                course.offerings.append(offering);
            }
        }
        courses.append(course);
    }

    return courses;
}


// --- 以下函数保持不变 ---

// 将修改的课表保存到 courses.json 的函数
// 警告：此保存函数只会使用原始结构体成员，不会处理新增的decoded_成员。
// 如果要基于修改后的数据进行保存，需要添加将列表“编码”回位掩码整数的逻辑。
void saveCourses(const QString& filePath, const QList<Course>& courses)
{
    QJsonArray courseArray;
    for (const Course &course : courses) {
        QJsonObject courseObj;
        courseObj["id"] = course.id;
        courseObj["name"] = course.name;
        courseObj["credit"] = course.credit;
        courseObj["semester"] = course.semester;
        courseObj["required"] = course.required;

        QJsonArray prereqArray;
        for (const QString &prereq : course.prerequisites) {
            prereqArray.append(prereq);
        }
        courseObj["prerequisites"] = prereqArray;

        QJsonArray offeringsArray;
        for (const Offering &offering : course.offerings) {
            QJsonObject offeringObj;
            offeringObj["id"] = offering.id;
            offeringObj["teacher"] = offering.teacher;

            // 此处仅保存原始数据
            offeringObj["weeks"] = offering.weeks;

            QJsonArray timesArray;
            for (int time : offering.times) {
                timesArray.append(time);
            }
            offeringObj["times"] = timesArray;
            offeringsArray.append(offeringObj);
        }
        courseObj["offerings"] = offeringsArray;

        courseArray.append(courseObj);
    }

    QJsonDocument doc(courseArray);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "无法写入课程文件:" << filePath;
        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

// 解析schedule.json文件的函数
QList<ScheduledCourse> loadSchedule(const QString& filePath)
{
    QList<ScheduledCourse> schedule;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开方案文件:" << filePath;
        return schedule;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "方案文件格式错误，根元素不是一个数组";
        return schedule;
    }

    QJsonArray scheduleArray = doc.array();
    for (const QJsonValue &value : std::as_const(scheduleArray)) {
        if (!value.isObject()) continue;

        QJsonObject obj = value.toObject();
        ScheduledCourse scheduledCourse;
        scheduledCourse.course_id = obj["course_id"].toString();
        scheduledCourse.class_id = obj["class_id"].toString();
        scheduledCourse.semester = obj["semester"].toInt();
        schedule.append(scheduledCourse);
    }

    return schedule;
}

// 将生成的选课方案保存到 schedule.json 的函数
void saveSchedule(const QString& filePath, const QList<ScheduledCourse>& schedule)
{
    QJsonArray scheduleArray;
    for (const ScheduledCourse &scheduledCourse : schedule) {
        QJsonObject scheduledCourseObj;
        scheduledCourseObj["course_id"] = scheduledCourse.course_id;
        scheduledCourseObj["class_id"] = scheduledCourse.class_id;
        scheduledCourseObj["semester"] = scheduledCourse.semester;
        scheduleArray.append(scheduledCourseObj);
    }

    QJsonDocument doc(scheduleArray);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "无法写入方案文件:" << filePath;
        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

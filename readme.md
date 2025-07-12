### 项目概述与架构

本应用将遵循一个类似于**模型-视图-控制器 (MVC)** 的设计模式：

- **模型 (Model):** 这是您应用程序的数据核心。它包含了从 `course.json` 加载的所有课程数据 、用户的设置（如学分限制、无课时间）以及最终生成的选课方案 。这些数据将通过在`util.h` 中定义的数据结构进行管理，并由 `util.cpp` 中的函数进行处理。

- **视图 (View):** 这是图形用户界面 (GUI)。它由 `MainWindow`（用于显示最终的课程表）、`CourseManagerDialog`（用于查看/编辑课程）、`SettingsDialog` 和 `NoClassTimeDialog` 组成。视图负责将模型中的数据呈现给用户。

- **控制器 (Controller):** 这是连接模型和视图的逻辑部分。它主要位于 `mainwindow.cpp` 中，负责处理用户的操作（如按钮点击、菜单选择），调用排课算法，并用新数据更新视图。排课算法本身可以是一个独立的类，也可以是控制器逻辑的一部分。


```
SmartSchedule/ 
├── CMakeLists.txt // 构建配置文件 
├── course.json //  输入的课程数据
├── schedule.json // (程序生成) 输出的选课方案数据 
│ 
├── main.cpp //  应用程序入口点 
│ 
├── mainwindow.h // 主窗口头文件 
├── mainwindow.cpp // 主窗口实现文件 
├── mainwindow.ui // 主窗口 UI 定义 
│ 
├── util.h // 核心数据结构 (Course, Offering 等) 
├── util.cpp // 工具函数 (JSON 解析, 数据处理) 
│ 
├── coursemanagerdialog.h // 课程管理对话框头文件 
├── coursemanagerdialog.cpp // 课程管理对话框实现文件 
├── coursemanagerdialog.ui // 课程管理对话框 UI 定义 
│ 
├── settingsdialog.h // 设置对话框头文件 
├── settingsdialog.cpp //  设置对话框实现文件
├── settingsdialog.ui //  设置对话框 UI 定义 
│ 
├── noclasstimedialog.h // 无课时间对话框头文件 
├── noclasstimedialog.cpp //  无课时间对话框实现文件 
└── noclasstimedialog.ui //  无课时间对话框 UI 定义
```

##  用于储存数据的数据结构定义

### 1. 课程
```cpp
struct Course {
    QString name;
    QString id;
    int credit;
    QList<Offering> offerings;
    QString semester;
    QString required;
    QStringList prerequisites; // 先修课程id
};
```

### 2. 开课信息
```cpp
struct Offering {
    QString id;   // 开课时间编号
    QString teacher;
    // 由7个二进制下13位的整数表示每周内的开课时间
    QVector<int> times = QVector<int>(7, 0);   
    int weeks;  // 是1个2进制下18位的整数表示开课周次
};
```

### 3. 选中的加入选课方案的课程
```cpp
struct ScheduledCourse {
    QString class_id;   // 开课时间编号
    QString course_id;  // 课程编号
    int semester;    //选课学期 0~7,不选为-1
};
```

### 4. 全局数据存储
```cpp
// 常量
const int numSemesters = 8; //学期数
const int numWeeks = 18; // 每学期周数
const int numDays = 7; // 每周天数
const int numSlots = 13; // 每天课程数

int m_totalCredits;    // 总学分下限
int m_semesterCreditsLimit;  // 单学期学分上限
// 多维数组用于存放数据， 无课状态表
// 存储无课状态[8*18*7*13]即[学期][周次][天*numSlots + 课次],1表示对应时间无课
QVector<QVector<QVector<bool>>> m_mainScheduleData; 

QList<Course> m_allCourses; // 所有课程的列表
QList<ScheduledCourse> m_generatedSchedule; // 生成的选课方案
QMap<QString,Course> courseMap;   // 建立课程id到对象的映射
```

##  文件读写函数格式
```cpp

// 解析course.json文件的函数,接受文件路径，返回包含所有Course的QList
QList<Course> loadCourses(const QString& filePath);

// 将修改的课表保存到 courses.json 的函数,接受文件路径和课表对象两个参数
void saveCourses(const QString& filePath,const QList<Course>& courses);

// 解析schedule.json文件的函数,接受文件路径，返回包含选课方案对象
QList<ScheduledCourse> loadSchedule(const QString& filePath);

// 将生成的选课方案保存到 schedule.json 的函数,接受文件路径和选课方案两个参数
void saveSchedule(const QString& filePath,const QList<ScheduledCourse>& schedule);

```

## `MainWindow`所有关联的`action`

| `action`名称              | 含义      |
| ----------------------- | ------- |
| `action_load`           | 加载方案    |
| `action_quit`           | 退出      |
| `action_globalSettings` | 全局与学分设置 |
| `action_noClassTime`    | 无课时间设置  |
| `action_generate`       | 生成选课方案  |
| `action_reset`          | 重置所有    |
| `action_loadCourses`    | 导入课程    |
| `action_viewCourses`    | 查看课程列表  |
| `action_saveCourses`    | 保存课程    |
| `action_save`           | 保存方案    |

##  各对话框的接口及数据结构

### `SettingsDialog`：`QDialog`

- 用于进行设置`totalCredits 总学分下限`和`semesterCreditsLimit 单学期学分上限`的对话框窗口

| 公有函数接口                                                | 含义               |
| ----------------------------------------------------- | ---------------- |
| `void setValues(int totalCredits, int semesterLimit)` | 初始化窗口显示的数据       |
| `int totalCredits() const`                            | 返回窗口的数据(总学分下限)   |
| `int semesterCreditsLimit() const`                    | 返回窗口的数据(单学期学分上限) |

###  `OfferingDialog`: `QDialog`

- 用于修改编辑单个开课信息`Offering`的窗口

- 数据结构
```cpp
// 存放18个周次和91个时间复选框指针的容器，便于管理UI
QList<QCheckBox*> m_weekCheckBoxes;
QList<QList<QCheckBox*>> m_timeCheckBoxes;
```

| 公有接口                                         | 含义          |
| -------------------------------------------- | ----------- |
| `void setOffering(const Offering &offering)` | 初始化窗口显示的数据  |
| `Offering getOffering() const`               | 返回窗口状态对应的数据 |

| 私有方法                                                | 含义                         |
| --------------------------------------------------- | -------------------------- |
| `void weeksToCheckBoxes(int weeks)`                 | 将 `int weeks `转换为18个复选框的状态 |
| `int checkBoxesToWeeks() const`                     | 将18个复选框的状态转换为 `int weeks`  |
| `void timesToCheckBoxes(const QVector<int> &times)` | 将开课时间转换为`7*13`个复选框的状态      |
| `QVector<int> checkBoxesToTimes() const`            | 将  `7*13`个复选框的状态转换为开课时间    |
| `void setupCheckBoxes()`                            | 初始化UI的函数                   |
| `void offeringToUi(const Offering &offering)`       | 将数据渲染到UI                   |
| `Offering uiToOffering() const`                     | 将UI状态转化为数据                 |


### `NoClassTimeDialog` :  `QDialog`

- 用于编辑无课时间状态的对话框

- 数据结构
```cpp
// 多维数组用于存放数据，存储无课状态[8*18*7*13],[学期][周次][天*13 + 课次]
QVector<QVector<QVector<bool>>> scheduleFreeTime;
```

| 公有接口                                                                | 含义     |
| ------------------------------------------------------------------- | ------ |
| `void setScheduleData(const QVector<QVector<QVector<bool>>> &data)` | 设置初始数据 |
| `QVector<QVector<QVector<bool>>> scheduleData() const`              | 获取最终数据 |

| 槽函数                                                                                     | 含义             |
| --------------------------------------------------------------------------------------- | -------------- |
| `void updateScheduleView()`                                                             | 当下拉框选择改变时，更新UI |
| `void onScheduleCheckBoxStateChanged(int state,int semester,int week,int day,int slot)` | 当复选框被点击时更新数据   |

| 私有方法                                                | 含义           |
| --------------------------------------------------- | ------------ |
| `void setupScheduleSelectors()`                     | 初始化UI        |
| `void populateScheduleGrid(int semester, int week)` | 用于产生格子(更新UI) |
| `void clearLayout(QLayout* layout)`                 | 清空格子(重置UI)   |


### `CourseManagerDialog` :  `QDialog`

- 用于管理课程列表的对话框

- 数据结构
```cpp
// 用于管理tableView 和 listView
QStandardItemModel *m_courseModel;
QStandardItemModel *m_offeringsModel;

QList<Course> m_courses; // 对话框持有的数据副本
QModelIndex m_currentCourseIndex; // 记录当前选中的课程
```

| 公有接口                                               | 含义       |
| -------------------------------------------------- | -------- |
| `void setCourseList(const QList<Course> &courses)` | 用于传入初始数据 |
| `QList<Course> getCourseList() const`              | 用于输出最终数据 |

| 槽函数                                                                             | 含义               |
| ------------------------------------------------------------------------------- | ---------------- |
| `void onCourseSelectionChanged(const QModelIndex& cur,const QModelIndex& prev)` | 处理当在左侧列表中选择的课程变化 |
| `void on_btn_addCourse_clicked();`                                              | 处理添加课程按钮点击       |
| `void on_btn_deleteCourse_clicked();`                                           | 处理删除课程按钮点击       |
| `void on_btn_saveCourseChanges_clicked();`                                      | 处理保存课程按钮点击       |
| `void on_btn_addOffering_clicked();`                                            | 处理添加开课按钮点击       |
| `void on_btn_editOffering_clicked();`                                           | 处理编辑开课按钮点击       |
| `void on_btn_deleteOffering_clicked();`                                         | 处理删除开课按钮点击       |
| `void on_lineEdit_search_textChanged(const QString &text)`                      | 处理搜索框文本变化        |

| 私有方法                                                      | 含义          |
| --------------------------------------------------------- | ----------- |
| `void setupModels()`                                      | 初始化         |
| `void connectSignals()`                                   | 显式连接所有信号和槽  |
| `void populateCourseList()`                               | 产生列表        |
| `void displayCourseDetails(const Course &course)`         | 显示右侧课程详情    |
| `void displayOfferings(const QList<Offering> &offerings)` | 显示开课详情      |
| `void clearDetails()`                                     | 清空并禁用右侧面板   |
| `QString weeksToSummary(int weeks) const`                 | 将位掩码转为可读字符串 |
| `QString timesToSummary(const QVector<int>& times) const` | 将位掩码转为可读字符串 |


#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QPixmap>
#include <QDate>

#define SCROLLBAR_CSS             (\
"QScrollArea{ border:0px solid; border-radius: 3px;}" \
"QScrollBar:vertical{width: 6px; border:0px solid; border-radius: 3px; \
                    margin: 0px,0px,0px,0px; background-color: transparent; background:transparent;}" \
"QScrollBar::handle:vertical{width:6px; background:#212831; border-radius: 3px;}" \
"QScrollBar::handle:vertical:hover{background:#212831; border-radius: 3px;}" \
"QScrollBar::add-line:vertical{height:11px; background-color: transparent; subcontrol-position:bottom; border:0px solid; border-radius: 3px;}" \
"QScrollBar::sub-line:vertical{height:11px; background-color: transparent; subcontrol-position:top; border:0px solid; border-radius: 3px;}" \
"QScrollBar::add-page:vertical{background-color: transparent; border:0px solid; border-radius: 3px;}" \
"QScrollBar::sub-page:vertical{background-color: transparent; border:0px solid; border-radius: 3px;}"\
)

typedef struct {
    int stuId;
    QString stuName;
    QPixmap img;
} StudentInfo;

// 上课时间
typedef struct{
    QDate date;
    QString day;
    QString startTime;
    QString endTime;
    int index; // 第几场的索引
} ClassTime;

typedef struct{
    QString imgUrl;
    int type;  // 主讲 辅导 外教
    QString name;
} TeacherInfo;

typedef struct{
    QString text;
    int btnType; //0,直播按钮  1,课堂巩固   2,学习报告
    int status; //0 可用 , 1 不可用, 2 可用且高亮
} ButtonInfo;

typedef struct DateCourseInfo{
    QDate date;
    bool isHaveCourse;
    DateCourseInfo(){
        isHaveCourse = false;
    }
} DateCourseInfo;

//=====================================================
// 场次列表需要的数据结构
typedef struct ChapterInfo{
    bool isEngTitle ;   // true 标题Item  ，false 场次Item
    QString chapterName;
    bool isExchanged; //是否调讲

    ClassTime time;
    QList<TeacherInfo> teachers;

    QString classStatus;  //直播未完成，直播已完成，直播待开始

    QList<ButtonInfo> buttons; // 去上课，看回放 ，课堂巩固，学习报告

    ChapterInfo(){
        isEngTitle = false;
        isExchanged = false;
    }

} ChapterInfo;

typedef struct{
    QString courseName;  //课程名称
    int stuCouID;   // 学生购课id
    int courseType; // 直播类型 1直播 2录播 3讲座 4精品课

    QString deadLine; //课程结束日期

} CourseToChapterPar;
//=====================================================

//=====================================================
//下载列表
typedef struct MaterialInfo{
    QString format;
    QString name;
    QString url;
    QString uploadTime;
    int status; //0,未下载  1,已下载
    MaterialInfo(){
        status = 0;
    }
} MaterialInfo;
typedef struct MaterialUnit{
    QString title;
    QString uploadTime;
    bool isFolded;     // true 折叠, false 展开
    QList<MaterialInfo> lst;
    MaterialUnit(){
        title ="";
        isFolded = false;
    }
} MaterialUnit;

//=====================================================

//=====================================================
//课程卡片的数据结构
typedef struct{
 int status; // 0 全部, 1 未开始, 2正在学, 3已结束
 int subjectType; // 语文 英语  数学 ...
}FilterType;

typedef struct CourseCardInfo{
    QString courseName;
    QString subjectName;
    QList<TeacherInfo> teachers;
    bool isRefund;  //是否退费
    CourseCardInfo(){
        isRefund = false;
    }
}CourseCardInfo;

//=====================================================

//=====================================================
//直播卡片的数据结构

typedef struct ClassCardInfo{

    int type;  //0,无课卡片 1,上课卡片  2,空白页面

    ClassTime time;
    int classStatusType;  // 0 直播待开始  1 直播进行中 2 直播未完成 3 直播已完成
    QString classStatus;  //直播待开始,直播进行中,直播未完成,直播已完成
    QString classTip;    // 课程提示信息 比如：“开始上课前记得在APP完成预习哦~”
    QString btnText; // 去上课，看回放

    QString chapterName;
    QString subjectName;
    QString courseName;
    QList<TeacherInfo> teachers;

    ClassCardInfo(){
        type = 1;
    }

}ClassCardInfo;

typedef struct DateInfo{
    QDate date;
    int  num; //当天的直播场数
    DateInfo(){
        num = 0;
    }
}DateInfo;

//=====================================================

#endif // COMMON_H

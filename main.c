
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//定义学生结构体
typedef struct student{
    int id;//学号
    char name[20];//姓名
    int cGrade;//c语言成绩
    int englishGrade;//大英成绩
    int mathGrade;//高数成绩
    int total;//总分
}student;

//定义单链表中节点的类型
typedef struct node{
    student data;
    struct node *next;
}Node, *Link;

//函数声明
void Menu(void);
Link AddStudents(Link);
Link SortId(Link);
Link SearchName(Link, char*);
Link SearchId(Link, int);
void PrintData(Link);
void Modify(Link, char*);
void DelName(Link, char*);
void DelId(Link, int);
void Count(Link);
void ValidateId(Link, Link);
int IsIdRepeat(int, Link);
void Validate(Link, char);
void Save(Link);



//创建用户提示菜单
void Menu(void)
{
    printf("*****************************************\n");
    printf("*          学生成绩管理系统                *\n");
    printf("*                                       *\n");
    printf("*    1. 输入学生信息        2. 查询学生信息 *\n");
    printf("*                                       *\n");
    printf("*    3. 输出学生信息        4. 更新学生信息 *\n");
    printf("*                                       *\n");
    printf("*    5. 统计学生信息        6. 退出系统     *\n");
    printf("*                                       *\n");
    printf("*****************************************\n");
}




//输入学生信息
Link AddStudents(Link pHead)
{
    Link s = (Link) malloc(sizeof(Node));//创建节点s

    //将学生信息输入到节点s的data中
    printf("请输入学生的信息：\n");
    printf("姓名：");
    scanf("%s", s->data.name);
    printf("学号：");
    ValidateId(s, pHead);
    printf("高数成绩：");
    Validate(s, 'm');
    printf("大英成绩：");
    Validate(s, 'e');
    printf("c语言成绩：");
    Validate(s, 'c');
    s->data.total = s->data.cGrade + s->data.englishGrade + s->data.mathGrade;
    printf("\n输入成功。\n");
    return s;
}

//修改\验证学号
void ValidateId(Link s, Link pHead)
{
    int id, flag=1;
    while(flag){
        if( (scanf("%d", &id)) == 1 && id>=2008000000 && id<= 2023000000){
            if( IsIdRepeat(id, pHead) == 0){
                s->data.id = id;
                flag = 0;
            }
            else printf("您输入的学号已存在，请重新输入：");
        }
        else printf("您输入的学号有误，请输入正确的学号:");
    }
}

//检查输入（更改）的学号是否重复，若重复则返回1否则返回0
int IsIdRepeat(int id, Link pHead)
{
    Link p = pHead->next;
    int i=0;
    while(p){
        if(id == p->data.id) i=1;
        p = p->next;
    }
    return i;
}

//修改\验证成绩
void Validate(Link s, char x)
{
    int g, flag=1;
    while(flag){
        if( (scanf("%d", &g)) == 1 && g>=0 && g<=100){
            switch(x){
                case 'm': s->data.mathGrade = g; break;
                case 'e': s->data.englishGrade = g; break;
                case 'c': s->data.cGrade = g; break;
            }
            s->data.total =  s->data.total = s->data.cGrade + s->data.englishGrade + s->data.mathGrade;
            flag = 0;
        }
        else printf("您输入的成绩有误，请输入正确的成绩:");
    }
}

// 快速排序链表节点
Link QuickSort(Link pHead, Link pEnd) {
    if (pHead == pEnd || pHead->next == pEnd)
        return pHead;

    Link p = pHead->next;
    Link q = pHead;

    // 将小于基准值的节点放在基准值的左侧
    while (p != pEnd) {
        if (p->data.id < pHead->data.id) {
            q = q->next;

            // 交换节点数据
            student temp = p->data;
            p->data = q->data;
            q->data = temp;
        }
        p = p->next;
    }

    // 交换基准值和q节点的数据
    student temp = pHead->data;
    pHead->data = q->data;
    q->data = temp;

    // 递归排序左侧和右侧的链表节点
    QuickSort(pHead, q);
    QuickSort(q->next, pEnd);

    return pHead;
}

// 调用快速排序函数
Link SortId(Link pHead) {
    return QuickSort(pHead, NULL);
}


//查询学生信息（通过名字）
Link SearchName(Link pHead,char* name)
{
    Link s = pHead->next;
    while((s != NULL) && (strcmp(s->data.name, name)!= 0) )
        s = s->next;
    if(s == NULL){
        printf("\n您所查询的姓名不存在。\n");
        return NULL;
    }
    else{
        printf("\n结果如下：\n\n%d    %s\t高数成绩：%d\t大英成绩：%d\tC语言成绩：%d\t总分：%d\n",
               s->data.id, s->data.name, s->data.mathGrade, s->data.englishGrade, s->data.cGrade,s->data.total);
        return s;
    }
}

//查询学生信息（通过学号）
Link SearchId(Link pHead, int id)
{
    Link s = pHead->next;
    while( (s != NULL) && (s->data.id != id))
        s = s->next;
    if(s == NULL){
        printf("\n你所查询的学号不存在。\n");
        return NULL;
    }
    else{
        printf("\n结果如下：\n\n%d    %s\t高数成绩：%d\t大英成绩：%d\tC语言成绩：%d\t总分：%d\n",
               s->data.id, s->data.name, s->data.mathGrade, s->data.englishGrade, s->data.cGrade,s->data.total);
        return s;
    }
}

//输出学生信息
void PrintData(Link pHead)
{
    Link p =pHead->next;
    if(pHead->next == NULL)
        printf("\n学生信息为空。\n");
    else{
        printf("\n所有学生信息如下：\n");
        while(p){
            printf("%d    %s\t高数成绩：%d\t大英成绩：%d\tC语言成绩：%d\t总分：%d\n",
                   p->data.id,p->data.name,p->data.mathGrade,p->data.englishGrade,p->data.cGrade,p->data.total);
            p=p->next;
        }
    }
}

//修改学生信息（通过名字）
void Modify(Link pHead,char *name)
{
    int subject;
    Link q=pHead->next;
    while(strcmp(q->data.name, name)!= 0 && q->next != NULL)
        q=q->next;
    if(strcmp(q->data.name, name)!= 0)
        printf("\n您所希望修改的学生的名字不存在，请输入正确的名字！\n");
    else{
        printf("\n请输入您希望修改的该学生的数据的对应数字：\n0.学号\t1.高数\t2.大英\t3.C语言\n");
        printf("请输入：");
        scanf("%d", &subject);
        switch(subject){
            case 0:{
                printf("请输入更改后的学号:");
                ValidateId(q, pHead);
                SortId(pHead);
                printf("\n修改成功！\n\n");
            }break;
            case 1:{
                printf("请输入更改后的成绩:");
                Validate(q, 'm');
                printf("\n修改成功！\n\n");
            }break;
            case 2:{
                printf("请输入更改后的成绩:");
                Validate(q, 'e');
                printf("\n修改成功！\n\n");
            }break;
            case 3:{
                printf("请输入更改后的成绩:");
                Validate(q, 'c');
                printf("\n修改成功！\n\n");
            }break;
            default: printf("请输入正确的操作。");break;
        }
    }
}

//删除学生信息（通过名字）
void DelName(Link pHead,char* name)
{
    Link p = pHead;
    Link q = pHead->next;
    while((q != NULL) && (strcmp(q->data.name, name))!= 0 )
    {
        q = q->next;
        p = p->next;
    }
    if(q == NULL)
        printf("\n您所希望删除的姓名不存在\n");
    else{
        p->next = q->next;
        printf("\n删除完毕!\n");
        free(q);
    }
}

//删除学生信息（通过学号）
void DelId(Link pHead,int id)
{
    Link p = pHead;
    Link q = pHead->next;
    while((q != NULL) && q->data.id != id )
    {
        q = q->next;
        p = p->next;
    }
    if(q == NULL)
        printf("\n您所希望删除的姓名不存在\n");
    else{
        p->next = q->next;
        printf("\n删除完毕!\n");
    }
}

//统计学生信息
void Count(Link pHead)
{
    Link p = (Link) malloc(sizeof(Node));
    p=pHead->next;
    int tMax=p->data.total;
    int mMax=p->data.mathGrade;
    int eMax=p->data.englishGrade;
    int cMax=p->data.cGrade;//定义总分，高数，大英，C语言最高分
    float mAver;
    float eAver;
    float cAver;//定义各科平均分
    float mSum=0;
    float eSum=0;
    float cSum=0;
    int len = 0;
    printf("\n统计数据如下：\n\n");
    //总分第一名
    printf("总分第一名：\n");
    for(p=pHead->next;p!=NULL;p=p->next)
        if(tMax < p->data.total) tMax=p->data.total;
    for(p=pHead->next;p!=NULL;p=p->next)
        if(tMax==p->data.total) printf("%d    %s\t总分：%d\n",p->data.id,p->data.name,p->data.total);
    printf("\n");

    //单科第一名
    printf("高数第一名：\n");
    for(p=pHead->next;p!=NULL;p=p->next)
        if(mMax < p->data.mathGrade) mMax=p->data.mathGrade;
    for(p=pHead->next;p!=NULL;p=p->next)
        if(mMax==p->data.mathGrade) printf("%d    %s\t分数：%d\n",p->data.id,p->data.name,p->data.mathGrade);
    printf("\n");

    printf("大英第一名：\n");
    for(p=pHead->next;p!=NULL;p=p->next)
        if(eMax < p->data.englishGrade) eMax=p->data.englishGrade;
    for(p=pHead->next;p!=NULL;p=p->next)
        if(eMax==p->data.englishGrade) printf("%d    %s\t分数：%d\n",p->data.id,p->data.name,p->data.englishGrade);
    printf("\n");

    printf("C语言第一名：\n");
    for(p=pHead->next;p!=NULL;p=p->next)
        if(cMax < p->data.cGrade) cMax=p->data.cGrade;
    for(p=pHead->next;p!=NULL;p=p->next)
        if(cMax==p->data.cGrade) printf("%d    %s\t分数：%d\n",p->data.id,p->data.name,p->data.cGrade);
    printf("\n");

    //平均分
    for(p=pHead->next;p!=NULL;p=p->next)
    {
        mSum += p->data.mathGrade;
        eSum += p->data.englishGrade;
        cSum += p->data.cGrade;
        len++;
    }
    mAver = mSum/len;
    eAver = eSum/len;
    cAver = cSum/len;
    printf("高数平均分：%.2f\n",mAver);
    printf("大英平均分：%.2f\n",eAver);
    printf("C语言平均分：%.2f\n",cAver);

    //不及格人数
    int math=0,eng=0,c=0;//定义不及格人数
    for(p=pHead->next;p!=NULL;p=p->next)
    {
        if(p->data.mathGrade < 60) math++;
        if(p->data.englishGrade < 60) eng++;
        if(p->data.cGrade < 60) c++;
    }
    printf("\n不及格人数为：\n高数： %d\t大英： %d\tC语言：%d\n",math,eng,c);
}

//保存至文件
void Save(Link pHead)
{
    FILE *fp;
    Link p;

    if((fp=fopen("/Users/liuxian/CProjects/school/Student-Mangement-System/students_message.txt","w+"))==NULL)
    {
        printf("Cannot open the file.\n");
        return;
    }

    p = pHead->next;
    while(p)
    {
        if(p == pHead->next)
            fprintf(fp,"%d      %s    %d    %d    %d    %d\n",
                    p->data.id,p->data.name,p->data.mathGrade,p->data.englishGrade,p->data.cGrade,p->data.total);
        else
            fprintf(fp,"%d      %s    %d    %d    %d    %d\n",
                    p->data.id,p->data.name,p->data.mathGrade,p->data.englishGrade,p->data.cGrade,p->data.total);
        p = p->next;
    }

    fclose(fp);
}


int main()
{
    Link pHead = (Link) malloc(sizeof(Node));
    pHead->next = NULL;

    int choice;
    char name[20];
    int id;

    do {
        Menu();
        printf("请输入您的选择：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                pHead->next = AddStudents(pHead);
                break;
            case 2:
                printf("请输入要查询的学生姓名：");
                scanf("%s", name);
                SearchName(pHead, name);
                break;
            case 3:
                PrintData(pHead);
                break;
            case 4:
                printf("请输入要修改的学生姓名：");
                scanf("%s", name);
                Modify(pHead, name);
                break;
            case 5:
                Count(pHead);
                break;
            case 6:
                printf("退出系统。\n");
                break;
            default:
                printf("请输入正确的选项。\n");
                break;
        }

    } while (choice != 6);

    // 保存数据到文件
    Save(pHead);

    // 释放链表内存
    Link p = pHead->next;
    Link q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(pHead);

    return 0;
}

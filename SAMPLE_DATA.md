# 示例数据

本文档提供了在线校园管理系统的示例数据，便于用户快速熟悉系统。

## 学院数据示例

以下是学院数据的示例格式，存储在`colleges.txt`文件中：

```
1 计算机学院
2 电子工程学院
3 机械工程学院
4 外国语学院
5 经济管理学院
```

## 专业数据示例

以下是专业数据的示例格式，存储在`majors.txt`文件中：

```
1 1001 计算机科学与技术
1 1002 软件工程
1 1003 人工智能
2 2001 电子信息工程
2 2002 通信工程
```

第一列是学院ID，第二列是专业ID，第三列是专业名称。

## 学生数据示例

以下是学生数据的示例格式，存储在`Students_data.txt`文件中：

```
10001 张三 男 计算机科学与技术 计算机学院 1001
10002 李四 女 软件工程 计算机学院 1002
10003 王五 男 电子信息工程 电子工程学院 2001
```

每行依次为：学号、姓名、性别、专业、学院、班级。

## 教师数据示例

以下是教师数据的示例格式，存储在`Teachers_data.txt`文件中：

```
20001 赵老师 男 计算机学院 Math 1001
20002 钱老师 女 电子工程学院 English 2001
```

每行依次为：教师ID、姓名、性别、所属学院、授课科目、授课班级。

## 初始化数据

当您首次运行系统时，系统会提示您输入初始数据。您可以参考以上示例格式输入数据，也可以使用系统自动生成的数据。

系统会自动为学生分配宿舍，并为所有用户生成初始密码。初始密码会通过RSA算法加密存储。

## 校车路线数据

校车路线数据存储在`南湖-浑南.txt`和`浑南-南湖.txt`文件中，格式为：

```
1 2023-09-01 08:00
2 2023-09-01 12:00
3 2023-09-01 17:30
```

每行依次为：序号、日期、时间。

## 重置系统

如果您想重置系统数据，只需删除所有的.txt文件，然后重新运行程序即可。系统会引导您重新输入初始数据。 
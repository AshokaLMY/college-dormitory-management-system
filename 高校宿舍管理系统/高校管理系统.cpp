#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
using namespace std;

class Student{
private:
	string S_user,S_password;                //用户名，密码
	string S_name;                           //学生姓名
	string S_sex;                             //性别
	string S_major;                         //专业
	int S_class;                                    //班级
	string S_id;                             //学号
	string S_quarters;
	int S_bednum;                             //寝室号
	string S_date;                  //日期
	string S_time;                //时间
	char S_sign;               //早出晚归标志
	bool Open_flag;                     //文件是否载入标志
	bool Alter_flag;                         //修改标志
	bool Exit_flag;                       //退出标志
	int Recond,U_count;                       //记录学生信息数，用户数
	int S_position;                                        //查找学生的位置
public:
	Student();
	virtual ~Student();                      //析构函数
	void Start(Student &L);                          //启动界面
	void Register(Student &L);               //注册
	void Login(Student &L);                          //登陆
	void Menu(Student &L);                   //菜单
	void Load(Student &L);                           //验证是否载入信息
	void ReadFromFile(Student &L);           //从文件中读出数据
	void Search(Student &L);                         //搜索数据成员
	void Search_On_Name(Student &L);         //根据姓名搜索
	void Search_On_Id(Student &L);                   //根据学号搜索
	void ModifyMember(Student &L);           //修改成员数据
	void DeleteMember(Student &L);                   //删除成员
	void PrintAll(Student &L);               //打印所有数据
	void AddMember(Student &L);                       //添加成员
	void SaveToFile(Student &L);              //保存文件
	void ReturnMenu(Student &L);                        //返回菜单
	void S_exit(Student &L);                           //退出系统
	void Print(Student &L);                 //输出早出晚归信息
	void SaveFile(Student &L);            //保存早出晚归信息
	void ReadFile(Student &L);            //读取早出晚归系统
	void BackandOut(Student &L);          //输入早出晚归信息
};
//构造函数
Student::Student()
{
	Open_flag=false;
	Alter_flag=false;
	Exit_flag=true;
	Recond=U_count=0;
	S_position=-1;
}

Student stu[50];       //定义类成员-学生信息数
Student admin[50];       //定义类成员-管理员数量

Student::~Student(){}

//初始化界面函数
void Student::Start(Student &L)
{
	system("cls");
	cout<<"\n\n\n\n\t\t\t\   *欢迎进入华南师范大学宿舍管理系统*\n\n"<<endl;
    cout<<"\t\t1.用户注册";
    cout<<"\t\t2.用户登陆";
    cout<<"\t\t0.退出系统 "<<endl;
	cout<<"\n\n\t\t\t请选择你的操作： ";
	int Key;
point:
	cin>>Key;
	switch(Key)
	{
	case 0:exit(0);break;
	case 1:L.Register(L);break;
	case 2:L.Login(L);break;
	default:
		{
			cout<<"\n输入错误，请重新选择： ";
			L.Start(L);
			goto point;break;
		}
	}
}

//注册函数
void Student::Register(Student &L)
{
	system("cls");
	string _user,_password;
	ifstream infile;
	infile.open("administrator.txt",ios_base::in);
	if(!infile){
		cerr<<"打开失败！"<<endl;
		exit(1);
	}
	for(int i=0;!infile.eof();++i)
		{infile>>admin[i].S_user>>admin[i].S_password;U_count = i;}
	cout<<"\t\t\t    *欢迎使用华南师范大学宿舍管理系统，请先进行注册!*"<<endl;
	cout<<"\n\n\n\t\t请输入用户名（长度不超过10位）： ";
	cin>>_user;
	cout<<"\n\n\t\t请输入密码（密码长度为6位）： ";
	cin>>_password;
	for(int j=0;j<U_count;++j)
		if(admin[j].S_user==_user) {
			cout<<"\t\t*用户已存在！请重新注册！*"<<endl;
			getch();
			L.Register(L);
		}
	cout<<"\t\t注册成功！\n";
	infile.close();
	U_count++;
	admin[U_count-1].S_user=_user;
	admin[U_count-1].S_password=_password;
	ofstream outfile;
	outfile.open("administrator.txt",ios::out);
	for(int k=0;k<U_count;k++)
	outfile<<admin[k].S_user<<" "<<admin[k].S_password<<endl;
	outfile.close();
	L.Start(L);
	system("cls");
}
//登录验证函数
void Student::Login(Student &L)
{
	ifstream infile("administrator.txt",ios::in);
	if(!infile)  {
		cout<<"文件无法打开!"<<endl;
		exit(1);
	}
	for(int i=0;!infile.eof();++i)
		{infile>>admin[i].S_user>>admin[i].S_password;U_count = i;}
	char _user[10],_password[7];
	bool u=false,p=false;
	int c,t=1;
	do  {
		system("cls");
		cout<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"\t\t\t    *欢迎使用华南师范大学宿舍管理系统，请先进行登陆!*"<<endl;
		cout<<endl<<endl<<endl<<endl<<endl<<endl;
		cout<<"\t\t\t请输入用户名:";
		fflush(stdin);
		gets(_user);
		cout<<endl<<"\t\t\t请输入密码:";
		for(int i=0;i<6;i++){
			c=getch();
			if(c==13) break;
			if(i&&(c=='\b')){
				i-=2;
				cout<<'\b';
				cout<<' ';
				cout<<'\b';
			}
			else if(c=='\b')
				i--;
			else {
				_password[i]=c;
				cout<<"*";
			}
		}
		_password[6]='\0';
		getch();
		for(int j=0;j<=U_count;++j){
			if(admin[j].S_user==_user) {
				u=true;
				if(admin[j].S_password==_password) p=true;
			}
		}
		if(!u){
			cout<<"\n\t\t用户不存在！请重新登陆！"<<endl;
			getch();
			t++;
			continue;
		}
		else if(!p){
			cout<<"\n\t\t密码错误，请重新登陆！"<<endl;
			getch();
			t++;
			continue;
		}
		else L.Menu(L);
	}while(t<=3);
	if(t>3){
		cout<<"\n\n\t\t连续3次登陆失败，系统自动关闭"<<endl;
		if(getch()=='\r') cout<<"\b";
		exit(1);
	}
	infile.close();
	system("cls");
}


//主菜单
void Student::Menu(Student &L)
{
	system("cls");
	cout<<"\n\n\n\n\t\t------------华南师范大学宿舍管理系统------------\n\n"<<endl;
	cout<<"\t*************************************************************"<<endl;
	cout<<"\t\t1、初始化系统  \t\t2、添加学生信息"<<endl;
	cout<<"\t\t3、查询学生信息\t\t4、修改学生信息"<<endl;
	cout<<"\t\t5、删除学生信息\t\t6、保存学生信息"<<endl;
	cout<<"\t\t7、输出学生信息\t\t8、早出晚归登记"<<endl;
	cout<<"\t\t9、早出晚归信息\t\t0、退出系统"<<endl;
	cout<<"\t*************************************************************"<<endl;
	cout<<"\n\n\t请选择功能： ";
	int i;
point:
		cin>>i;
	switch(i)
	{
	case 1:L.ReadFromFile(L);break;
	case 2:L.AddMember(L);break;
	case 3:L.Search(L);break;
	case 4:L.ModifyMember(L);break;
	case 5:L.DeleteMember(L);break;
	case 6:L.SaveToFile(L);break;
	case 7:L.PrintAll(L);break;
	case 8:L.BackandOut(L);break;
	case 9:L.Print(L);break;
	case 0:exit(1);break;
	default:
		{
			cout<<"命令输入错误，请重新选择：";
			goto point;break;
		}
	}

}

//从文件中读取数据成员函数
void Student::ReadFromFile(Student &L)
{
	system("cls");
	ifstream file;
	file.open("Student.txt",ios_base::in);
	if(!file){
		cerr<<"can't open the file!"<<endl;
		exit(1);
	}
	cout<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;!file.eof();++i)
		{file>>stu[i].S_name>>stu[i].S_sex>>stu[i].S_major>>stu[i].S_class>>stu[i].S_id>>stu[i].S_quarters>>stu[i].S_bednum;Recond = --i;}
	Open_flag=true;
	cout<<"\t\t载入数据完毕！请选择操作："<<endl;
	cout<<"*************************************************************\n"<<endl;
	file.close();
	L.ReturnMenu (L);
}
void Student::ReadFile(Student &L)
{
	system("cls");
	ifstream file;
	file.open("BackandOut.txt",ios_base::in);
	if(!file){
		cerr<<"can't open the file!"<<endl;
		exit(1);
	}
	cout<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;!file.eof();++i)
		{file>>stu[i].S_name>>stu[i].S_sex>>stu[i].S_id>>stu[i].S_sign>>stu[i].S_date>>stu[i].S_time;Recond = --i;}
	Open_flag=true;
	cout<<"\t\t载入数据完毕！请选择操作："<<endl;
	cout<<"*************************************************************\n"<<endl;
	file.close();
	L.ReturnMenu (L);
}

//载入信息函数
void Student::Load(Student &L)
{
	char load_temp;
	if(!Open_flag){
		cout<<"尚未载入信息，现在是否载入信息（Y/N）?"<<endl;
		cin>>load_temp;
		if(load_temp=='Y'||load_temp=='y'){
			L.ReadFromFile(L);
		}
		else
			exit(1);
	}
}

//打印成员函数
void Student::PrintAll(Student &L)
{
	system("cls");
	L.Load(L);
	cout<<setw(6)<<"姓 名"<<setw(8)<<"性 别"<<setw(10)<<"专 业"<<setw(8)<<"班 级"
		<<setw(11)<<"学 号"<<setw(9)<<"寝室号"<<setw(7)<<"床号"<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++){
		cout<<setw(6)<<stu[i].S_name<<setw(8)<<stu[i].S_sex<<setw(10)<<stu[i].S_major
			<<setw(6)<<stu[i].S_class<<setw(14)<<stu[i].S_id<<setw(6)<<stu[i].S_quarters<<setw(6)<<stu[i].S_bednum<<endl;
	}
	cout<<"*************************************************************"<<endl;
	cout<<"\n输出完毕！请选择操作："<<endl;
	L.ReturnMenu (L);
}
void Student::Print(Student &L)
{
	system("cls");
	L.Load(L);
	cout<<"  "<<"姓 名"<<"   "<<"性 别"<<"    "<<"学 号"
	    <<"     "<<"早出/晚归"<<"     "<<"日期"<<"       "<<"时间"<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++){
		cout<<" "<<stu[i].S_name<<"    "<<stu[i].S_sex<<"    "
		    <<stu[i].S_id<<"     "<<stu[i].S_sign<<"       "<<stu[i].S_date<<"     "<<stu[i].S_time<<endl;
	}
	cout<<"*************************************************************"<<endl;
	cout<<"\n输出完毕！请选择操作："<<endl;
	L.ReturnMenu (L);
}
//添加成员函数
void Student::AddMember(Student &L)
{
	system("cls");
	L.Load(L);
	Recond++;
	cout<<"请输入姓名："<<endl;
	cin>>stu[Recond].S_name;
	cout<<"请输入性别："<<endl;
	cin>>stu[Recond].S_sex;
	cout<<"请输入专业："<<endl;
	cin>>stu[Recond].S_major;
	cout<<"请输入班级"<<endl;
	cin>>stu[Recond].S_class;
	cout<<"请输入学号："<<endl;
	cin>>stu[Recond].S_id;
	cout<<"请输入寝室号："<<endl;
	cin>>stu[Recond].S_quarters;
	cout<<"请输入床号："<<endl;
	cin>>stu[Recond].S_bednum;
	cout<<"\n添加信息完毕！请选择操作："<<endl;
	char temp;
	cout<<"是否保存(Y/N)?"<<endl;
	cin>>temp;
	if(temp=='y'||temp=='Y'){
		L.SaveToFile(L);
	}
	else{
		cout<<"若暂不保存，";
		L.ReturnMenu (L);
	}
}
void Student::BackandOut(Student &L)
{
	system("cls");
	L.Load(L);
	Recond++;
	cout<<"请输入姓名："<<endl;
	cin>>stu[Recond].S_name;
	cout<<"请输入性别："<<endl;
	cin>>stu[Recond].S_sex;
	cout<<"请输入学号："<<endl;
	cin>>stu[Recond].S_id;
	cout<<"晚归输入B，早出输入O："<<endl;
	cin>>stu[Recond].S_sign;
	cout<<"请输入日期："<<endl;
	cin>>stu[Recond].S_date;
	cout<<"请输入时间："<<endl;
	cin>>stu[Recond].S_time;
	cout<<"\n添加信息完毕！请选择操作："<<endl;
	char temp;
	cout<<"是否保存(Y/N)?"<<endl;
	cin>>temp;
	if(temp=='y'||temp=='Y'){
		L.SaveFile(L);
	}
	else{
		cout<<"若暂不保存，";
		L.ReturnMenu (L);
	}
}
//搜索函数
void Student::Search(Student &L)
{
	system("cls");
	L.Load(L);
	cout<<"搜索条件："<<endl;
	cout<<"\t1、姓名 \t 2、学号 \t 0、退出搜索"<<endl;
	int i;
	cin>>i;
	switch(i)
	{
	case 1:L.Search_On_Name(L);break;
	case 2:L.Search_On_Id(L);break;
	case 0:exit(1);break;
	default:
		{
			cout<<"查找失败！";
			L.ReturnMenu (L);
		}
	}
}

//根据姓名搜索
void Student::Search_On_Name(Student &L)
{
	cout<<"寻找成员： ";
	string _name;
	cin>>_name;
	for(int i=0;i<=Recond;i++){
		if(_name==stu[i].S_name)
			S_position=i;
	}
	if(S_position==-1){
		cout<<"查找失败！";
		L.ReturnMenu (L);
	}
	system("cls");
	cout<<setw(6)<<"姓 名"<<setw(8)<<"性 别"<<setw(8)<<"专 业"<<setw(8)<<"班 级"
		<<setw(9)<<"学 号"<<setw(10)<<"寝室号"<<setw(8)<<"床号"<<endl;
	cout<<"*************************************************************"<<endl;
	cout<<setw(5)<<stu[S_position].S_name<<setw(8)<<stu[S_position].S_sex<<setw(10)<<stu[S_position].S_major
			<<setw(6)<<stu[S_position].S_class<<setw(14)<<stu[S_position].S_id<<setw(6)<<stu[S_position].S_quarters<<setw(6)<<stu[S_position].S_bednum<<endl;
	cout<<"*************************************************************"<<endl;
	cout<<"\n搜索成功！";
	L.ReturnMenu (L);
}

//根据学号搜索
void Student::Search_On_Id(Student &L)
{
	cout<<"寻找成员： ";
	string _id;
	cin>>_id;
	for(int i=0;i<=Recond;i++){
		if(_id==stu[i].S_id)
			S_position=i;
	}
	if(S_position==-1){
		cout<<"查找失败！是否返回菜单(Y/N)？";
			char temp;
	        cin>>temp;
			if(temp=='y'||temp=='Y'){
				L.Menu(L);
			}
			else
				exit(1);
	}
	system("cls");
	cout<<setw(6)<<"姓 名"<<setw(8)<<"性 别"<<setw(8)<<"专 业"<<setw(8)<<"班 级"
		<<setw(9)<<"学 号"<<setw(10)<<"寝室号"<<setw(10)<<"床号"<<endl;
	cout<<"*************************************************************"<<endl;
	cout<<setw(6)<<stu[S_position].S_name<<setw(8)<<stu[S_position].S_sex<<setw(10)<<stu[S_position].S_major
			<<setw(6)<<stu[S_position].S_class<<setw(14)<<stu[S_position].S_id<<setw(6)<<stu[S_position].S_quarters<<setw(6)<<stu[S_position].S_bednum<<endl;
	cout<<"*************************************************************"<<endl;
	cout<<"\n搜索成功！";
	L.ReturnMenu (L);
	if(!Exit_flag) L.Menu(L);
}

//修改成员函数
void Student::ModifyMember(Student &L)
{
	system("cls");
	L.Load(L);
	int _point;
	Alter_flag=false;
	cout<<"修改学生信息:\n"<<endl;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++)
		cout<<"\t"<<i<<"、"<<stu[i].S_name<<endl;
	cout<<"*************************************************************\n"<<endl;
	cin>>_point;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++){
		if(_point==i){
			cout<<setw(6)<<stu[_point].S_name<<setw(8)<<stu[_point].S_sex<<setw(10)<<stu[_point].S_major
				<<setw(6)<<stu[_point].S_class<<setw(14)<<stu[_point].S_id<<setw(6)<<stu[_point].S_quarters<<setw(6)<<stu[_point].S_bednum<<endl;
			Alter_flag=true;
		}
	}
	if(!Alter_flag){
		cerr<<"修改失败！";
		L.ReturnMenu (L);
	}
	cout<<"*************************************************************"<<endl;
	cout<<"修改信息"<<endl;
	cout<<"1、姓名\t2、性别\t3、专业\n4、班级\t5、学号\t6、寝室号7、床号"<<endl;
	int t;
	char second;
	char b;
point:
	cin>>t;
	switch(t)
	{
	case 1:
		{
			cout<<"请输入姓名：";
			cin>>stu[_point].S_name;
			cout<<"修改成功，是否还要修改（Y/N）?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"是否保存修改（Y/N）?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		 }
	case 2:
		{
			cout<<"请输入性别：";
			cin>>stu[_point].S_sex;
			cout<<"修改成功，是否还要修改（Y/N）?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"是否保存修改（Y/N）?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		}
	case 3:
		{
			cout<<"请输入专业：";
			cin>>stu[_point].S_major;
			cout<<"修改成功，是否还要修改（Y/N）?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"是否保存修改（Y/N）?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		}
	case 4:
		{
			cout<<"请输入班级：";
			cin>>stu[_point].S_class;
			cout<<"修改成功，是否还要修改（Y/N）?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"是否保存修改（Y/N）?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		}
	case 5:
		{
			cout<<"请输入学号：";
			cin>>stu[_point].S_id;
			cout<<"修改成功，是否还要修改（Y/N）?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"是否保存修改（Y/N）?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		}
	case 6:
		{
			cout<<"请输入寝室号：";
			cin>>stu[_point].S_quarters;
			cout<<"修改成功，是否还要修改（Y/N）?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"是否保存修改（Y/N）?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else L.Menu(L);
			}
			break;
		}
		case 7:
		{
			cout<<"请输入床号：";
			cin>>stu[_point].S_bednum;
			cout<<"修改成功，是否还要修改（Y/N）?"<<endl;
			cin>>second;
			if(second=='y'||second=='Y')
				goto point;
			else {
				cout<<"是否保存修改（Y/N）?"<<endl;
				cin>>b;
				if(b=='y'||b=='Y')
					L.SaveToFile(L);
				else exit(1);
			}
			break;
		 }
	default:
		{
			cerr<<"修改失败！";
			L.ReturnMenu (L);
			if(!Exit_flag) L.Menu(L);
		}
	}
}

//删除成员函数
void Student::DeleteMember(Student &L)
{
	system("cls");
	L.Load(L);
	cout<<"删除成员"<<endl;
	cout<<"*************************************************************\n"<<endl;
	for(int i=0;i<=Recond;i++)
		cout<<"\t"<<i<<"、"<<stu[i].S_name<<endl;
	cout<<"*************************************************************\n"<<endl;
	int _point;
	bool Del_flag;
	cin>>_point;
	cout<<"*************************************************************"<<endl;
	for(int i=0;i<=Recond;i++){
		if(_point==i){
			cout<<setw(6)<<stu[_point].S_name<<setw(8)<<stu[_point].S_sex<<setw(10)<<stu[_point].S_major
				<<setw(6)<<stu[_point].S_class<<setw(14)<<stu[_point].S_id<<setw(6)<<stu[_point].S_quarters<<setw(6)<<stu[_point].S_bednum<<endl;
			Del_flag=true;
		}
	}
	cout<<"*************************************************************"<<endl;
	if(Del_flag){
		cout<<"确定要删除？（Y/N）"<<endl;
		char _temp;
		cin>>_temp;
		if(_temp=='y'||_temp=='Y'){
			for(int j=_point;j<=Recond;j++){
				stu[j].S_name=stu[j+1].S_name;
				stu[j].S_sex=stu[j+1].S_sex;
				stu[j].S_major=stu[j+1].S_major;
				stu[j].S_class=stu[j+1].S_class;
				stu[j].S_id=stu[j+1].S_id;
				stu[j].S_quarters=stu[j+1].S_quarters;
				stu[j].S_bednum=stu[j+1].S_bednum;
			}
			Recond--;
			cout<<"删除成功！是否保存修改(Y/N)？"<<endl;
			char temp;
			cin>>temp;
			if(temp=='y'||temp=='Y'){
				L.SaveToFile(L);
			}
			else {
				cout<<"若暂不保存,";
				L.ReturnMenu (L);
				if(!Exit_flag) L.Menu(L);
				}
		}
		else L.Menu(L);
	}
	else L.ReturnMenu(L);
	if(!Exit_flag) L.Menu(L);
}

//保存文件函数
void Student::SaveToFile(Student &L)
{
	system("cls");
	L.Load(L);
	ofstream ofile;
	ofile.open("Student.txt",ios_base::out);
	for(int i=0;i<=Recond;i++)
	ofile<<stu[i].S_name<<' '<<stu[i].S_sex<<' '<<stu[i].S_major<<' '
		<<stu[i].S_class<<' '<<stu[i].S_id<<' '<<stu[i].S_quarters<<' '<<stu[i].S_bednum<<endl;
	ofile.close();
	cout<<"*************************************************************"<<endl;
	cout<<"\t\t信息保存完毕！"<<endl;
	cout<<"*************************************************************"<<endl;
	L.ReturnMenu (L);
	if(!Exit_flag) L.Menu(L);
}
void Student::SaveFile(Student &L)
{
	system("cls");
	L.Load(L);
	ofstream ofile;
	ofile.open("BackandOut.txt",ios_base::out);
	for(int i=0;i<=Recond;i++)
	ofile<<stu[i].S_name<<' '<<stu[i].S_sex<<' '
		 <<stu[i].S_id<<' '<<stu[i].S_date<<' '<<stu[i].S_time<<endl;
	ofile.close();
	cout<<"*************************************************************"<<endl;
	cout<<"\t\t信息保存完毕！"<<endl;
	cout<<"*************************************************************"<<endl;
	L.ReturnMenu (L);
	if(!Exit_flag) L.Menu(L);
}
//返回菜单函数
void Student::ReturnMenu (Student &L)
{
	cout<<"是否返回菜单(Y/N)?"<<endl;
	char temp;
	cin>>temp;
	if(temp=='y'||temp=='Y')
		L.Menu(L);
	else
		L.S_exit(L);
}

//退出系统函数
void Student::S_exit(Student &L)
{
	cout<<"*************************************************************"<<endl;
	cout<<"确定退出系统(Y/N)?"<<endl;
	char temp;
	cin>>temp;
	if((temp=='y'||temp=='Y'))
		exit(0);
	else
		Exit_flag=false;
}

int main()
{
	Student L;
	L.Start(L);
	return 0;
}

#include <iostream> 
#include <fstream> 
#include<stdio.h>
#include <string.h> 
#include<time.h> 
using namespace std;  
void welcome();
//��ӭ�Ӻ���
void choose();                           //ѡ���Ӻ���
void banciluru();                        //���¼���Ӻ���
void liulanbancixinxi();                 //��������Ϣ�Ӻ���
void shoupiao();                         //��Ʊ�Ӻ���
void tuipiao();                          //��Ʊ�Ӻ���
void quit();                             //�˳��Ӻ���
void chaxun();                           //��ѯ�Ӻ���
int loading();                           //�ļ������Ӻ���
void adminLogin();
void userLogin();
void userRegister();
void adminMenu();
void userMenu();
void userChoose();
void adminChoose();
int fileExists(string filename);
const int MAX=20;                        //ʹ�������ֵ�ɵ�
const int N=50;
int ifAdmin=0;								//�ж��ǽ������Ա���滹�ǽ����û����� 
struct time {                            //ʱ��ṹ��,Ϊ����ϵͳʱ�����Ƚ�.
	int hour;
	int minutes;
};
struct ticket {                          //��Ʊ�ṹ��,��������,ʱ��ṹ��,���,�յ�,�г�ʱ��,��ؿ���,�Ѷ�Ʊ����
	string Number;
	struct time Setout;
	char Qidian[MAX];
	char Zhongdian[MAX];
	float Lasttime;
	int Fixnumber;
	int Fixednumber;
} car[N];  //������
int main() {
	
	welcome();
	return 0;
}
//��ӭ�Ӻ���
void welcome() {
	system("title ��Ʊ����ϵͳ");//����cmd���ڱ���
    system("color 0A");
    
	cout<<"________________________________________________________"<<endl;
	cout<<"| �� * ӭ * ʹ * �� * �� * �� * Ʊ * �� * �� * ϵ * ͳ |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|             ������ϵͳ�����¹���:                    |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|                 1 ����Ա����                         |"<<endl;
	cout<<"|                 2 �û���¼                           |"<<endl;
	cout<<"|                 3 �û�ע��                           |"<<endl;
	cout<<"|______________________________________________________|"<<endl;
	cout<<"��ѡ����ݣ�"<<endl;
	string user;
	cin>>user;
	if(user == "1"){
		adminLogin();
	}
	if(user == "2"){
		userLogin();
	}
	if(user == "3"){
		userRegister();
	}
	welcome();
	
	
}

void adminLogin(){
	string name;
	string pwd;
	cout<<"admin's username:";
	cin>>name;
	cout<<"admin's password:";
	cin>>pwd;//
	if(name == "admin"){
		if(pwd == "password"){
			ifAdmin=1;
			adminMenu();
		}
		else{
			cout << "�û������������������" << endl;
			adminLogin();
		}
	}else{
		cout << "�û������������������" << endl;
		adminLogin();
	}
}

void userLogin(){
	string username;
	string password;
	string s;
	cout << "�������û���:";
	cin >> username;
	cout << "����������:";
	cin >>  password;
	ifstream userfile;
	
	userfile.open(username.c_str(),ios::in);
	while(getline(userfile,s)){
		if(password == s){
			userMenu();
		}else{
			cout << "�û������������";
			userLogin();
		}
	}
	welcome();

}

void userRegister(){
	string username;
	string password;

	cout << "your username:";
	cin >> username;
	cout << "your password:";
	cin >> password;
	  
	 /*�ж��û��Ƿ��Ѵ���*/
	if(fileExists(username)){
		cout << "user has already exists"<<endl;
		cout << fileExists(username);
		
		welcome();
	}
	ofstream userfile;
	userfile.open(username.c_str(),ios::out);
	if(userfile<<password){
		ifAdmin=0; 
		userfile.close();
		cout << "register success";
		userLogin();
		
	}else{
		ifAdmin=0;
		userfile.close();
		cout << "register fail";
		welcome();
}
	userfile.close();
	
}
//ѡ���Ӻ���
void adminChoose() {
	string i;
	cin>>i;
	if(i=="1")
		banciluru();
	if(i=="2")
		liulanbancixinxi();
	if(i=="3")
		chaxun();
	if(i=="4")
		shoupiao();
	if(i=="5")
		tuipiao();
	if(i=="6")
		quit();
	else  {
		cout<<"��������!��������1-6֮��������������ѡ��!"<<endl;
		adminChoose();
	}
}

void userChoose(){
	string i;
	cin>>i;
	if(i=="1")
		liulanbancixinxi();
	if(i=="2")
		chaxun();
	if(i=="3")
		shoupiao();
	if(i=="4")
		tuipiao();
	if(i=="5")
		quit();
	else  {
		cout<<"��������!��������1-5֮��������������ѡ��!"<<endl;
		userChoose();
	}
}
//���¼���Ӻ���
void banciluru() {
	string t="1";        //�������Ӻ���
	ofstream outfile;
	outfile.open("�����Ϣ.txt",ios::app);
	for(int i=0; t=="1"; i++)  {
		cout<<"��������Ҫ��ӵĻ𳵰��:"<<endl;
		cin>>car[i].Number;
		cout<<"������˰�η���ʱ��(��ʽ:������Сʱ,�س�,���������):"<<endl;
		cin>>car[i].Setout.hour;
		cin>>car[i].Setout.minutes;
		cout<<"���������վ:"<<endl;
		cin>>car[i].Qidian;
		cout<<"�������յ�վ:"<<endl;
		cin>>car[i].Zhongdian;
		cout<<"�������г�ʱ��:"<<endl;
		cin>>car[i].Lasttime;
		cout<<"�������ؿ���:"<<endl;
		cin>>car[i].Fixnumber;
		cout<<"�������Ѷ�Ʊ����:"<<endl;
		cin>>car[i].Fixednumber;
		outfile<<car[i].Number<<" "<<car[i].Setout.hour<<" "<<car[i].Setout.minutes<<" "<<car[i].Qidian<<" "<<car[i].Zhongdian<<" "<<car[i].Lasttime<<" "<<car[i].Fixnumber<<" "<<car[i].Fixednumber<<endl;
		cout<<"�Ƿ����¼��?(������1,������������������˵�)"<<endl;
		cin>>t;
		if(t!="1")   {
			if(ifAdmin==1){
				adminMenu();
			}else{
				userMenu();
			}
		}
	}
	outfile.close();
	cout<<"����س�������"<<endl;
	getchar();
	getchar();
	if(ifAdmin==1){
		adminMenu();
	}else{
		userMenu();
	}
}
void liulanbancixinxi() {
	int c;
	c=loading();
	cout<<"���"<<" "<<"����ʱ��"<<" "<<"���վ"<<" "<<"�յ�վ"<<" "<<"�г�ʱ��"<<" "<<"��ؿ���"<<" "<<"�Ѷ�Ʊ����"<<endl;
	for(int i=0; i<c; i++)  {
		cout<<car[i].Number<<"     "<<car[i].Setout.hour<<":"<<car[i].Setout.minutes<<"    "<<car[i].Qidian<<"    "<<car[i].Zhongdian<<"      "<<car[i].Lasttime<<"      "<<car[i].Fixnumber<<"      "<<car[i].Fixednumber<<endl;
		time_t tval;
		struct tm *now;
		tval = time(NULL);
		now = localtime(&tval);
		if((now->tm_hour==car[i].Setout.hour&&now->tm_min>car[i].Setout.minutes)||(now->tm_hour>car[i].Setout.hour))    cout<<"�˳��ѷ���"<<endl;
	}
	cout<<"����س�������"<<endl;
	getchar();
	getchar();
	if(ifAdmin==1){
		adminMenu();
	}else{
		userMenu();
	}
}   //���β�ѯ�Ӻ���

void Numbersearch();
void Finalsearch();
void chaxun() {
	 
	string t;
    cout<<"________________________________________________________"<<endl;
	cout<<"| �� * ӭ * ʹ * �� * �� * �� * Ʊ * �� * �� * ϵ * ͳ |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|                 1.����β�ѯ                         |"<<endl;
	cout<<"|                 2.���յ�վ��ѯ                       |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|����������ѡ��Ĳ�ѯ����ǰ������:                     |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|______________________________________________________|"<<endl;
	cin>>t;
	if(t=="1")   Numbersearch();
	if(t=="2")   Finalsearch();
	if(t!="1"||t!="2")  {
		cout<<"��������,����������"<<endl;
		chaxun();
	}
}

void Numbersearch() {//��β�ѯ�Ӻ���
	loading();     
	string SearchNumber;
	cout<<"����������Ҫ���ҵİ�κ�:"<<endl;
	cin>>SearchNumber;
	cout<<"���"<<" "<<"����ʱ��"<<" "<<"���վ"<<" "<<"�յ�վ"<<" "<<"�г�ʱ��"<<" "<<"��ؿ���"<<" "<<"�Ѷ�Ʊ����"<<endl;
	for(int len=1;len<(sizeof(car)/sizeof(car[0]));len++){
		if(car[len-1].Number == SearchNumber){
			cout<<car[len-1].Number<<"     "<<car[len-1].Setout.hour<<":"<<car[len-1].Setout.minutes<<"     "<<car[len-1].Qidian<<"   "<<car[len-1].Zhongdian<<"     "<<car[len-1].Lasttime<<"     "<<car[len-1].Fixnumber<<"        "<<car[len-1].Fixednumber<<endl;		
		}
	}
	cout<<"����س�������"<<endl;
	getchar();
	getchar();
	if(ifAdmin==1){
		adminMenu();
	}else{
		userMenu();
	}
}
void Finalsearch() {//�յ�վ��ѯ�Ӻ���
	int R;
	R=loading();
	int i;
	char Address[MAX];
	cout<<"�������յ�վ����:"<<endl;
	cin>>Address;
	cout<<"���"<<" "<<"����ʱ��"<<" "<<"���վ"<<" "<<"�յ�վ"<<" "<<"�г�ʱ��"<<" "<<"��ؿ���"<<" "<<"�Ѷ�Ʊ����"<<endl;
	for(i=0; i<R; i++)  {
		if((strcmp(Address,car[i].Zhongdian))==0)    
		cout<<car[i].Number<<"     "<<car[i].Setout.hour<<":"<<car[i].Setout.minutes<<"    "<<car[i].Qidian<<"    "<<car[i].Zhongdian<<"     "<<car[i].Lasttime<<"      "<<car[i].Fixnumber<<"          "<<car[i].Fixednumber<<endl;
	}
	cout<<"����س�������"<<endl;
	getchar();
	getchar();
	if(ifAdmin==1){
		adminMenu();
	}else{
		userMenu();
	}
}
    ��void shoupiao() {
	int R;
	R=loading();
	int i=0;
	string SearchNumber;
	cout<<"������Ҫ�����ĳ�Ʊ�İ�Σ�����ǰһ��Сʱ�޷���Ʊ��:"<<endl;
	cin>>SearchNumber;
	time_t tval;
	struct tm *now;
	tval = time(NULL);
	now = localtime(&tval);
	
	for(int len=1;len<(sizeof(car)/sizeof(car[0]));len++){
		if(car[len-1].Number == SearchNumber){
			if(car[len-1].Setout.hour-now->tm_hour==1) {                   //����ǰһ��Сʱ�޷���Ʊ 
			    if(now->tm_min<car[len-1].Setout.minutes){
				    if(car[len-1].Fixednumber<car[len-1].Fixnumber)   {
					(car[len-1].Fixednumber)++;
					ofstream outfile;
					outfile.open("�����Ϣ.txt",ios::out);
					for(i=0; i<R; i++)     {
						outfile<<car[i].Number<<" "<<car[i].Setout.hour<<" "<<car[i].Setout.minutes<<" "<<car[i].Qidian<<" "<<car[i].Zhongdian<<" "<<car[i].Lasttime<<" "<<car[i].Fixnumber<<" "<<car[i].Fixednumber<<endl;
					}
					outfile.close();
					cout<<"��Ķ�Ʊ�ɹ����밴ʱ�ϳ���ллʹ��!"<<endl;
				    }          else cout<<"�Բ��𣬽�������˳���Ʊ������,������������лл����"<<endl;
			    }
			    else cout<<"�Բ��𣬽�������˳��ѹ�����Ʊʱ��,������������лл����"<<endl; 
			}  
			if(car[len-1].Setout.hour-now->tm_hour>=2||car[len-1].Setout.hour-now->tm_hour==0&&car[len-1].Setout.minutes-now->tm_min>30��) {
				if(car[len-1].Fixednumber<car[len-1].Fixnumber)  {
					(car[len-1].Fixednumber)++;
					ofstream outfile;
					outfile.open("�����Ϣ.txt",ios::out);
					for(i=0; i<R; i++)     {
						outfile<<car[i].Number<<" "<<car[i].Setout.hour<<" "<<car[i].Setout.minutes<<" "<<car[i].Qidian<<" "<<car[i].Zhongdian<<" "<<car[i].Lasttime<<" "<<car[i].Fixnumber<<" "<<car[i].Fixednumber<<endl;
					}
					outfile.close();
					cout<<"��Ķ�Ʊ�ɹ����밴ʱ�ϳ���ллʹ��!"<<endl;
				}         
				else cout<<"�Բ��𣬽�������˳���Ʊ������,������������лл����"<<endl;
			}
			 
			
		    else	cout<<"�Բ��𣬽�������˳��ѹ�����Ʊʱ��,������������лл����"<<endl;
		
		
			
			cout<<"����س�������"<<endl;
			getchar();
			getchar();
		}
	}
	
	if(ifAdmin==1){
		adminMenu();
	}else{
		userMenu();
	}
}   //�˶���Ʊ�Ӻ���
void tuipiao() {
	int R;
	R=loading();
	int i=0;
	string SearchNumber;
	cout<<"������Ҫ�˹��ĳ�Ʊ�İ��:"<<endl;
	cin>>SearchNumber;
	time_t tval;
	struct tm *now;
	tval = time(NULL);
	now = localtime(&tval);
	for(int len=1;len<(sizeof(car)/sizeof(car[0]));len++){
		if(car[len-1].Number == SearchNumber){
				if((now->tm_hour==car[len-1].Setout.hour&&now->tm_min<car[len-1].Setout.minutes)||(now->tm_hour<car[len-1].Setout.hour))  {
					if(car[len-1].Fixednumber>=1)    {
						car[len-1].Fixednumber-=1;
						ofstream outfile;
						outfile.open("�����Ϣ.txt",ios::out);
						for(i=0; i<R; i++)     {
							outfile<<car[i].Number<<" "<<car[i].Setout.hour<<" "<<car[i].Setout.minutes<<" "<<car[i].Qidian<<" "<<car[i].Zhongdian<<" "<<car[i].Lasttime<<" "<<car[i].Fixnumber<<" "<<car[i].Fixednumber<<endl;
						}
						outfile.close();
						cout<<"�˶���Ʊ�ɹ���ллʹ��!"<<endl;
					}           else cout<<"�Բ���,��������˳���Ʊ��δ����,�޷������Ʊ!"<<endl;
				} else cout<<"�Բ��𣬽�������˳��ѷ���,�޷������Ʊ!"<<endl;
				cout<<"����س�������"<<endl;
				getchar();
				getchar();
		}
	}
	
	if(ifAdmin==1){
		adminMenu();
	}else{
		userMenu();
	}
}
//�˳��Ӻ���
void quit() {
	cout<<"*********************ллʹ�ñ�ϵͳ����ӭ�´μ���ʹ��***********************"<<endl;
	welcome() ;
}
//�ļ������Ӻ���
int loading() {
	int i;
	ifstream infile;
	infile.open("�����Ϣ.txt",ios::in);
	if(!infile)  {
		cout<<"��鿴ԭ�ļ��Ƿ����!"<<endl;
		cout<<"�����������";
		getchar();
		getchar();
		if(ifAdmin==1){
			adminMenu();
		}else{
			userMenu();
		}
	}
	for(i=0; !infile.eof(); i++)  {
		infile>>car[i].Number>>car[i].Setout.hour>>car[i].Setout.minutes>>car[i].Qidian>>car[i].Zhongdian>>car[i].Lasttime>>car[i].Fixnumber>>car[i].Fixednumber;
	}
	return i-1;
}
int fileExists(string filename){
	fstream _file;
	_file.open(filename.c_str(),ios::in);
	if(!_file){
		_file.close();
		return 0;
    }else{
    	_file.close();
		return 1;
    }
}

void adminMenu(){
	cout<<"________________________________________________________"<<endl;
	cout<<"| �� * ӭ * ʹ * �� * �� * �� * Ʊ * �� * �� * ϵ * ͳ |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|             ������ϵͳ�����¹���:                    |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|                 1 ���¼��                           |"<<endl;
	cout<<"|                 2 ��������Ϣ                       |"<<endl;
	cout<<"|                 3 ��ѯ����Ϣ                       |"<<endl;
	cout<<"|                 4 �����Ʊ                         |"<<endl;
	cout<<"|                 5 �˶���Ʊ                         |"<<endl;
	cout<<"|                 6 �˳�ϵͳ                           |"<<endl;
	cout<<"|______________________________________________________|"<<endl;
	cout<<"��������Ҫִ�й���ǰ������: " << endl;
	adminChoose();
}

void userMenu(){
	cout<<"________________________________________________________"<<endl;
	cout<<"| �� * ӭ * ʹ * �� * �� * �� * Ʊ * �� * �� * ϵ * ͳ |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|             ������ϵͳ�����¹���:                    |"<<endl;
	cout<<"|                                                      |"<<endl;
	cout<<"|                 1 ��������Ϣ                       |"<<endl;
	cout<<"|                 2 ��ѯ����Ϣ                       |"<<endl;
	cout<<"|                 3 �����Ʊ                         |"<<endl;
	cout<<"|                 4 �˶���Ʊ                         |"<<endl;
	cout<<"|                 5 �˳�ϵͳ                           |"<<endl;
	cout<<"|______________________________________________________|"<<endl;
	cout<<"��������Ҫִ�й���ǰ������: "<<endl;
	userChoose();	
}



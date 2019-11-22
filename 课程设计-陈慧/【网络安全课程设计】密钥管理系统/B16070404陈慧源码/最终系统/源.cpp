#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>
#include <fstream> 
#include <string>
#include <sstream>

using namespace std;


//RSA�㷨�������
typedef struct  RSA_PARAM_Tag
{
    unsigned __int64    p, q;   //������������������ܽ�������
    unsigned __int64    f;      //f=(p-1)*(q-1)����������ܽ�������
    unsigned __int64    n, e;   //���ף�n=p*q��gcd(e,f)=1
    unsigned __int64    d;      //˽�ף�e*d=1 (mod f)��gcd(n,d)=1'
    unsigned __int64    s;      //�鳤������2^s<=n������s����log2(n)
} RSA_PARAM;

//С������
const static long g_PrimeTable[]=
{

    3,5,7,11,13,17,19,23,29,31,37,41,43,

    47,53,59,61,67,71,73,79,83,89,97

};

const static long       g_PrimeCount=sizeof(g_PrimeTable) / sizeof(long);
const unsigned __int64  multiplier=12747293821;
const unsigned __int64  adder=1343545677842234541;//�������

//���������
class       RandNumber
{
private:
   unsigned __int64    randSeed;
public:
    RandNumber(unsigned __int64 s=0);
    unsigned __int64    Random(unsigned __int64 n);
};

RandNumber::RandNumber(unsigned __int64 s)
{
    if(!s)
	{
        randSeed= (unsigned __int64)time(NULL);
    }
    else
    {
        randSeed=s;
    }
}

unsigned __int64 RandNumber::Random(unsigned __int64 n)
{
    randSeed=multiplier * randSeed + adder;
    return randSeed % n;
}static RandNumber   g_Rnd;

//ģ�����㣬����ֵ x=a*b mod n
inline unsigned __int64 MulMod(unsigned __int64 a, unsigned __int64 b, unsigned __int64 n)
{
    return a * b % n;
}

//ģ�����㣬����ֵ x=base^pow mod n
unsigned __int64 PowMod(unsigned __int64 &base, unsigned __int64 &pow, unsigned __int64 &n)
{
    unsigned __int64    a=base, b=pow, c=1;
    while(b)
    {
        while(!(b & 1))
        {
            b>>=1;            //a=a * a % n;    
			//�������������Դ���64λ������������������a*a��a>=2^32ʱ�Ѿ��������������ʵ�ʴ���Χû��64λ
            a=MulMod(a, a, n);
        }        b--;        //c=a * c % n;        //����Ҳ�����������64λ������Ϊ����32λ������֪�Ƿ���Խ��������⡣

        c=MulMod(a, c, n);
    }    return c;
}

/*
Rabin-Miller�������ԣ�ͨ�����Է���1�����򷵻�0��
n�Ǵ���������
*/

long RabinMillerKnl(unsigned __int64 &n)
{
    unsigned __int64    b, m, j, v, i;
    m=n-1;
    j=0;    //�����m��j��ʹ��n-1=m*2^j������m����������j�ǷǸ�����
    while(!(m & 1))
    {
        ++j;
        m>>=1;
    }    //���ȡһ��b��2<=b<n-1
    b=2 + g_Rnd.Random(n - 3);    //��v=b^m mod n
    v=PowMod(b, m, n);    //���v==1��ͨ������
    if(v == 1)
    {
        return 1;
    }    //��i=1
    i=1;    //v=n-1��ͨ������
    while(v != n - 1)
    {
       //i==l��������������
        if(i == j)
        {
            return 0;
        }        //v=v^2 mod n��i=i+1
        unsigned __int64  xxx;
        int xxxx = 2;
        xxx = xxxx;
        v = PowMod(v, xxx, n);
        ++i;        //ѭ����5
    }    return 1;
}

/*
Rabin-Miller�������ԣ�ѭ�����ú���loop��
ȫ��ͨ������1�����򷵻�0
*/

long RabinMiller(unsigned __int64 &n, long loop)
{
    //��С����ɸѡһ�Σ����Ч��
    for(long i=0; i < g_PrimeCount; i++)
    {
        if(n % g_PrimeTable[i] == 0)
        {
            return 0;
        }
    }    //ѭ������Rabin-Miller����loop�Σ�ʹ�÷�����ͨ�����Եĸ��ʽ�Ϊ(1/4)^loop
    for(long i=0; i < loop; i++)
    {
        if(!RabinMillerKnl(n))
        {
            return 0;
        }
    }    return 1;
}

/*�������һ��bitsλ(������λ)�����������32λ*/
unsigned __int64 RandomPrime(char bits)
{
    unsigned __int64    base;
    do
    {
       base= (unsigned long)1 << (bits - 1);   //��֤���λ��1
       base+=g_Rnd.Random(base);               //�ټ���һ�������
        base|=1;    //��֤���λ��1������֤������
    } while(!RabinMiller(base, 30));    //�������������ղ���30��
    return base;    //ȫ��ͨ����Ϊ������
}


/*ŷ����÷������Լ��*/
unsigned __int64 EuclidGcd(unsigned __int64 &p, unsigned __int64 &q)
{
    unsigned __int64    a=p > q ? p : q;
    unsigned __int64    b=p < q ? p : q;
    unsigned __int64    t;
    if(p == q)
    {
        return p;   //������ȣ����Լ�����Ǳ���
    }
    else
    {
        while(b)    //շת�������gcd(a,b)=gcd(b,a-qb)
        {
            a=a % b;
            t=a;
            a=b;
            b=t;
        }        return a;
    }

}

/*Stein�������Լ��*/
unsigned __int64 SteinGcd(unsigned __int64 &p, unsigned __int64 &q)
{
    unsigned __int64    a=p > q ? p : q;
    unsigned __int64    b=p < q ? p : q;
    unsigned __int64    t, r=1;
    if(p == q)
    {
       return p;           //������ȣ����Լ�����Ǳ���
    }
    else
    {
        while((!(a & 1)) && (!(b & 1)))
        {
            r<<=1;          //a��bΪż��ʱ��gcd(a,b)=2*gcd(a/2,b/2)
            a>>=1;
            b>>=1;
        }       
		if(!(a & 1))
        {
            t=a;            //aΪż��������a��b
            a=b;
            b=t;
        }       
		do
        {
            while(!(b & 1))
            {
                b>>=1;      //bΪż����aΪ����ʱ��gcd(b,a)=gcd(b/2,a)
            }           
			if(b < a)
            {
                t=a;        //bС��a������a��b
                a=b;
                b=t;
            }           
			b=(b - a) >> 1; //b��a����������gcd(b,a)=gcd((b-a)/2,a)
        } while(b);
        return r * a;
    }
}

/*
��֪a��b����x������a*x =1 (mod b)
�൱�����a*x-b*y=1����С������
*/

unsigned __int64 Euclid(unsigned __int64 &a, unsigned __int64 &b)
{
    unsigned __int64    m, e, i, j, x, y;
    long                xx, yy;
    m=b;e=a;x=0;y=1;xx=1;yy=1;
    while(e)
    {
        i=m / e;j=m % e;
       m=e;e=j;j=y;y*=i;
        if(xx == yy)
        {
            if(x > y)
                y=x - y;
            else{
                y-=x;
                yy=0;
            }
        }
        else
        {
            y+=x;
           xx=1 - xx;
           yy=1 - yy;
        }       
		x=j;
    }    
    if(xx == 0)
        x=b - x;
    return x;
}

/*
�������һ��RSA���ܲ���
*/
RSA_PARAM RsaGetParam(void)
{
    RSA_PARAM           Rsa={ 0 };//�Զ����RSA��������
    unsigned __int64    t;
    Rsa.p=RandomPrime(16);          //���������������
    Rsa.q=RandomPrime(16);
    Rsa.n=Rsa.p * Rsa.q;
    Rsa.f=(Rsa.p - 1) * (Rsa.q - 1);
    do
    {
        Rsa.e=g_Rnd.Random(65536);  //С��2^16��65536=2^16
        Rsa.e|=1;                   //��֤���λ��1������֤����������fһ����ż����Ҫ���أ�ֻ��������
    } while(SteinGcd(Rsa.e, Rsa.f) != 1);    
    Rsa.d=Euclid(Rsa.e, Rsa.f);
    Rsa.s=0;
    t=Rsa.n >> 1;
    while(t)
    {
        Rsa.s++;                    //s=log2(n)
        t>>=1;
    }    
    return Rsa;
}

/*
���������ղ���
*/

void TestRM(void)
{
    unsigned long   k=0;
   cout << "���������ղ���\n" << endl;
    for(unsigned __int64 i=4197900001; i < 4198000000; i+=2)
    {
        if(RabinMiller(i, 30))
        {
            k++;
            cout<<i<<endl;
        }
    }   
	cout << "Total: " << k << endl;
}

//��Կ��ȫ�Լ��
int fun(int k)
{        
    int count=1;//˽Կ5λ������

        if(k>5) 
			count++;//˽Կ6-7λ��
       if(k>7) 
			count++;//˽Կ8-9λǿ
       if(k>9)
			count++;//˽Կ10λ���Ϸǳ���
  
       return count;
}

//�ж�����λ��
int get_length(char x[])
{
	int leng=0,i;
	string str;
     str = x;
	stringstream ss;
	ss<<str;
    ss>>i;

	while(i)
	{
		i/=10;
		leng++;
	}
	return leng;
}

//���ܺ���
void decode(char cipher[])
{
int s[256],t[256],i,j,temp;
char k[256];//�û��������Կ
char plaintext[1024];
cout<<"\n��������������Կ:";
cin>>k;

//��ʼ��S
for(i=0;i<256;i++)    {
s[i]=i;
t[i]=k[i%strlen(k)];
}

//S�ĳ�ʼ�û�����������s����
j=0;
for( i=0;i<256;i++) //��Կ���ȿɱ�
{
j=(j+s[i]+t[i])%256;
temp=s[i];
s[i]=s[j];
s[j]=temp;
}

int m,n,key[256],q;
m=n=0;
cout<<"\n����������ܵõ��������ǣ�"<<endl;

//������
for(i=0;i<strlen(cipher);i++){
m=(m+1)% 256;
n=(n+s[n])% 256;
temp=s[m];
s[m]=s[n];
s[n]=temp;
q=(s[m]+s[n])%256;
key[i]=s[q];
plaintext[i]=cipher[i]^key[i]; //�������ַ����н���
cout<<plaintext[i];
}
cout<<endl;
}

ofstream fout1("��Կ����.txt");     //����һ����Կ����.txt���ļ�
int baocun(char x[],char y[],int kkk)
{
	fout1.open( "��Կ����.txt", ios::app ); 
	fout1 << kkk <<"      "<< x<<"     "<< y<<"\n";
	fout1.close();
	return kkk++;
}

string ReadText(int line)
{
	ifstream inff("��Կ����.txt") ;
	string strVec[100];     //�ı����ܹ���10��
	int i = 0;
	while (!inff.eof())
	{
		string inbuf;
		getline(inff, inbuf, '\n');
		strVec[i] = inbuf;
		i = i + 1;
	}
	return strVec[line - 1];
}

string CharToStr(char * contentChar)//�ַ���תstring����
{
	string tempStr;
	for (int i=0;contentChar[i]!='\0';i++)
	{
		tempStr+=contentChar[i];
	}
	return tempStr;
}

int main(void)
{ 
	int c=0;
	RSA_PARAM           r;
	char miyao[50]={0};//���ѡȡ����Կ������ڸ�������
	string lineData ;
	string tmpLine ;
	char siyao[50]={0},gongyao[50]={0};
	string in_1;
	char pSrc[100]={0};
	const unsigned long n = sizeof(pSrc);
	unsigned char       *q, pDec[n];
	unsigned __int64    pEnc[n];
	int kk,kkkk;
	int yonghu=0,sc=0;
  
	int i=0,j=0,si=0;
    int length ;
	int g;
	char ciphertext1[1024]={0},ciphertext2[1024]={0};
	char k[256]={0};//���û��������Կ�����K�����У���Կ�������Ϊ256λ
	int temp,s[256]={0},t[256]={0};

	ofstream fout("��Կ��.txt");     //����һ��data.txt���ļ�
	for(int i=0;i<=100;i++)
	{
		r = RsaGetParam();
		fout << r.e << "," << r.d << endl;  //��������ֵд���ļ�
	}
	fout.close();                  //�ر��ļ�
  
	do{
		system("cls");
	cout << "--------------------------------------------------------\n"  ;
    cout << "                  ��ӭ������Կ����ϵͳ\n\n";
	cout << "----------by��B16070404�»�+B16070405��ѩȻ-------------\n\n";
	cout << "           1.��Կ�ַ�+��Կ��ȫ������ \n\n";
	cout << "           2.��Կ���ܴ洢 \n\n";
	cout << "           3.�鿴ϵͳ�û�������Կ           \n\n";
	cout << "           4.�����û�������Կ           \n\n";
	cout << "           5.��ԿӦ�ã�ʹ����Կ�Խ��м��ܽ���           \n\n";
	cout << "           6.ɾ���û���Ϣ           \n\n";
	cout << "           0.�˳� \n\n";
	cout << "--------------------------------------------------------\n\n";
	cout <<"����0-6��ѡ���Իس���������";
	cin >>c;

	ifstream inff("��Կ��.txt") ;
	switch(c)
	{
	  case 1:
		    system("cls");
	//���ļ������ѡ��һ����Կ
			yonghu++;
			i=1;
			srand((unsigned int)time(NULL)) ;
			while (getline(inff, tmpLine))
			{
				
				if (rand()%i == 0)
					lineData = tmpLine ;
				++ i ;
			}
			inff.close() ;

			strcpy(miyao, lineData.c_str());
			length = sizeof(miyao)/sizeof(char);
			i=0;
			while (i<length) 
			{
				while ( miyao[i]!=',' && i==j)
				{
					gongyao[i]=miyao[i];
					i++;
					j++;

				}
			siyao[i-j]=miyao[i+1];
			i++;
			}//ʵ�ֹ�Կ˽Կ�ֱ��������

		  cout << "\nϵͳ�����ַ�����Կ��Ϊ����Կ��˽Կ��: ("<<gongyao<<","<<siyao<<")"<<endl;

			si=get_length(siyao);
			cout<<"\n�������жϣ�����ǿ��Ϊ��";
			switch(fun(si))
			{
			case 1:cout<<"�� ��"<<endl;break;
			case 2:cout<<"�� �� ��"<<endl;break;
			case 3:cout<<"ǿ �� �� ��"<<endl;break;
			case 4:cout<<"�ǳ��� �� �� �� ��"<<endl;break;
			}
		
			cout<<"\n\nע��ǿ�ȼ������Ϊ��\n";
			cout<<"        ˽Կλ��5λ��������\n";
			cout<<"                6-7λ�� �� ��\n";
			cout<<"                8-9λǿ�� �� ��\n";
			cout<<"                10λ���Ϸǳ��á� �� �� ��";

			cout <<"\n\n��������������˵���0���˳�\n";
			cin>>c;
			break;

	  case 2:
		  system("cls");
		  	cout << "\n��Կ�ļ��ܱ���͹���RC4�㷨    \n";

		
		cout<<"��������������Կ:";
		cin>>k;


		//��Կ����gongyao
		//��ʼ��S
		for( i=0;i<256;i++) 
		{
			s[i]=i;
			t[i]=k[i%strlen(k)]; //��K����ʱ����T���и�ֵ
		}
		//S�ĳ�ʼ�û�
		j=0; 
		for(i=0;i<256;i++)
		{
			j=(j+s[i]+t[i])%256;
			temp=s[i];
			s[i]=s[j];
			s[j]=temp;
		}

		cout<<"\n\n��Կ���ܵõ�������Ϊ:";
		int m,n,key[256],ff;
		m=n=0;
		//������
		 g=get_length(gongyao);
		for(i=0;i<g;i++)//�������ַ����м���
		{
			m=(m+1)% 256;
			n=(n+s[n])% 256;
			temp=s[m];
			s[m]=s[n];
			s[n]=temp;
			ff=(s[m]+s[n])%256;
			key[i]=s[ff];
			ciphertext1[i]=gongyao[i]^key[i];//���ܹ��̣�Kֵ�����ĵ���һ�ֽ������
			cout<<ciphertext1[i];
		}
			ciphertext1[i]='\0';
			cout<<endl;

		//˽Կ����r.d

        cout<<"\n˽Կ���ܵõ�������Ϊ:";
		int l;
		m=n=0;

		//��ʼ��S
		for(i=0;i<256;i++) 
		{
			s[i]=i;
			t[i]=k[i%strlen(k)]; //��K����ʱ����T���и�ֵ
		}
		//S�ĳ�ʼ�û�
		j=0; 
		for( i=0;i<256;i++)
		{
			j=(j+s[i]+t[i])%256;
			temp=s[i];
			s[i]=s[j];
			s[j]=temp;
		}
		//������
		 si=get_length(siyao);
		 i=0;
		for(  i;i<si;i++)//�������ַ����м���
		{
		m=(m+1)% 256;
		n=(n+s[n])% 256;
		temp=s[m];
		s[m]=s[n];
		s[n]=temp;
		ff=(s[m]+s[n])%256;
		key[i]=s[ff];
		ciphertext2[i]=siyao[i]^key[i];//���ܹ��̣�Kֵ�����ĵ���һ�ֽ������
		cout<<ciphertext2[i];
		}
		ciphertext2[i]='\0';

		if(yonghu==1)
		{
		ofstream fout1("��Կ����.txt");     //����һ����Կ����.txt���ļ�
		}
		else
		{
		fout1.open( "��Կ����.txt", ios::app ); 
		}
		fout1 << yonghu <<"      "<< ciphertext1<<"     "<< ciphertext2<<"\n";
		fout1.close();
		cout<<"\n\n��"<<yonghu<<"λ�û�ϵͳ�������Կ�Ѿ����ܴ洢";
		cout<<endl;

		  cout <<"\n\n��������������˵���0���˳�";
		  cin>>c;
		  break;

		case 3:
			system("cls");
			cout<<"�鿴�û�������Կ,�������û����:";
			cin>>kkkk;
			cout <<"\n�û����  ��Կ��������  ˽Կ��������"<<endl;
			cout <<ReadText(kkkk)<<endl;
			cout <<"\n\n��������������˵���0���˳�";
			cin>>c;
			break;

		case 4:
			system("cls");
			cout<<"\n��Կ���ܵ�";
			decode(ciphertext1);//���ܺ���
			cout<<"\n˽Կ���ܵ�";
			decode(ciphertext2);//���ܺ���
			cout <<"\n\n��������������˵���0���˳�";
			cin>>c;
			break;

	  case 5:
		  system("cls");
		  cout << "\nRSA�㷨�ӽ���Ӧ�ã� \n";
		  cout << "����������ܵ����ݣ�֧����ĸ�����֡��Լ��������ź��»��ߣ���\n";
		fflush(stdin);
		scanf("%[^\n]s",pSrc);
		q = (unsigned char*)pSrc;
		cout << "\n\n���ܣ�����ASCII�룩:\n";
		for (unsigned long i = 0; i < n; i++)
		{
			unsigned __int64  xxx;
			unsigned __int64 xxxx = q[i];
			xxx = xxxx;
			pEnc[i] = PowMod(xxx, r.e, r.n);
			cout << hex << pEnc[i] << " ";
		}    
		cout << "\n\n";    
		cout << "���ܣ�����ASCII�룩:\n";
		for (unsigned long i = 0; i < n; i++)
		{
			pDec[i] = PowMod(pEnc[i], r.d, r.n);
			cout << hex << (unsigned long)pDec[i] << " ";
		}    
		cout << "\n\n";
		cout << "���ܺ���ĵ���\n";
		cout << (char *)pDec << endl;

		  cout <<"\n\n��������������˵���0���˳�";
		  cin>>c;
		  break;


	  case 6:
		  {
		  cout <<"��������Ҫɾ�����û����";
		  cin>>sc;
		  ifstream in;
	      in.open("��Կ����.txt");
	
		string strFileData = "";
		int line = 1;
		char lineData[1024] = {0};
		while(in.getline(lineData, sizeof(lineData)))
		{
			if (line == sc)
			{
				strFileData += "\n";
			}
			else
			{
				strFileData += CharToStr(lineData);
				strFileData += "\n";
			}
			line++;
		}
		in.close();
			ofstream out;
	out.open("��Կ����.txt");
	out.flush();
	out<<strFileData;
	out.close();
		  cout <<"\n\n��������������˵���0���˳�";
		  cin>>c;
		  break;
		  }
	}
	}while (c!=0);

	cout <<"ллʹ�ã��ټ���"; 
	system ("pause");
}


 


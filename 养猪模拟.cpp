using namespace std;
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#define random(a,b) (rand()%(b-a+1))+a
//添加全局变量
int samount,bwamount,bamount; //去记录当前猪圈何种猪的数量
 
struct pig{
	int spiece=0;//spiece=1为黑猪，spiece=2是小猪，是spiece=3是大花猪
	double weight=0;
	int days=0;
	pig *next=NULL; 
};
class pigcircle{
	private:
		int sum;//记录猪圈猪的总数
		pig *head;//一个猪圈猪链表的头指针
		int ifblack; //如果是黑猪圈则，ifblack=1
		int number;
	public:
		pigcircle();
		int searchweight(int i);
		int searchdate(int i);
		int searchspiece(int i);
		int pigcirclestatistics();
		void uppig() ;
	    int  price();
	    int insert(pig *p);
		int initialaddpig(pig *p);
		void inFile();
		void outFile();
		int getnumber();
		void sendnumber(int i);
};
pigcircle::pigcircle()
{
	sum=0;
	head=NULL;
	ifblack=0;//未标注是黑猪，该值默认为0 
}
//
int pigcircle::getnumber()
{
	return number;
}
void pigcircle::sendnumber(int i)
{
	number=i;
}
int pigcircle::searchspiece(int i)
{
	int j=0;
	pig *p=head;
	if(p==NULL) return -1;
	for(;j<i&&p!=NULL;j++)
	p=p->next ;
	if(p==NULL)
	return -1;//-1表示这个猪序号超过了猪圈内猪的数量
	else
	return p->spiece;
}
int pigcircle::searchdate(int i)
{
	int j=0;
	pig *p=head;
	if(p==NULL) return -1;
	for(;j<i&&p!=NULL;j++)
	p=p->next;
	if(p==NULL)
	return -1;//同上
	else
	return p->days;
}
int pigcircle::searchweight(int i)
{
	int j=0;
	pig *p=head;
	if(p==NULL) return -1;
	for(;j<i&&p!=0;j++)
	p=p->next;
	if(p==NULL)
	return -1;//同上
	else
	return p->weight; 
}
int pigcircle::pigcirclestatistics()
{
	int j;
	pig *p=head;
	bamount=samount=bwamount=0;
	if(ifblack==1)
	{
		bamount=sum;
		return 1;
	}
	else 
	{
		while(p!=NULL)
		{
			if(p->spiece==2)
			samount+=1;
			else
			bwamount+=1;
			p=p->next;
		}
		return 2;
	}
}
 //在这个函数中，我们来统计一个猪圈中猪的品种和数量，
 //将得到的数量传递进入三个全局变量中，并返回不同的对应值 
void pigcircle::uppig()
{
	pig *p=head;
	while(p!=NULL)
	{
		p->weight=((double)random(0,12))/10;
		p->days+=1;
		p=p->next;
	}
 }//这个为增加函数，目的在于改变当前猪圈每一只猪的重量与天数
 int pigcircle::price()
 {
 	int sumprice=0;
 	pig *p=head,*p1;
 	while(p!=NULL)
 	{
 		if(p->weight>75||p->days>360)
 		{
 		  if(p->spiece==1)
		   	sumprice+=p->weight*15;
		   else if(p->spiece==2)
		   sumprice+=p->weight*7;
		   else
		   sumprice+=p->weight*6;
		   p1->next=p->next;
		   p=p->next;
		   delete p;
		}
		 p1=p;
		 p=p->next;
	 }
	 return sumprice;
 }
  //在这个函数里面，我们来记录出圈的猪价值多少，并实现出圈的猪从链表中删除；
int pigcircle::initialaddpig(pig* p)
{
    if(p->spiece==1)
    {
    	if(sum>0&&sum<10&&ifblack==1)
    	{
    		p->next=head;
    		head=p;
    		sum++;
    		return 1;
		}
		else if(sum==0)
		{
			p->next=head;
			sum++;
			ifblack=1;
			return 1;
		}
		return 0;
	}
	else
	{
		if(sum>0&&sum<10&&ifblack==0)
		{
			p->next=head;
			head=p;
			sum++;
			return 1;
		}
		else if(sum==0)
		{
			p->next=head;
			head=p;
			sum++;
			ifblack=0;
			return 1;
	    }
	    return 0;
	}		
}
int pigcircle::insert(pig *p)
{
	if(sum==10) return 0;//不能再原来的基础上插入新猪
	if(ifblack!=p->spiece) return 0;//同上
	if(p==NULL)
	head=p;
	else
	{
		p->next=head;
		head=p;
	}
	return 1;//插入成功 
}
 //我们暂时结束对猪圈和猪的处理，开始对整体的猪场进行处理
//对猪场初始化
void initialnumber(pigcircle pc[])
{
	int i;
	for(i=1;i<=100;i++)
	{
		pc[i].sendnumber(i);
	}
}
void initial(pigcircle pc[])
{
	int count=200;
	int i,flag;
	pig *p;
	while(count--)
{
	p=new pig;
	p->spiece=random(1,3);
	p->weight=random(20,50);
	p->days=0;
	for(i=1;i<=100;i++)
	{
	flag=pc[i].initialaddpig(p);
	if(flag==0&&i==100)
	{
		delete p;
		break;
	} 
	else if(flag==1)
	break;
	else if(flag==0&&i<100)
	continue;
    }
 } 
}
void pigcircle::inFile()
{
	int i;
	pig *p=head;
	ofstream destFile;
	destFile.open("pigsmessage.txt",ios::out);
	destFile<<getnumber()<<endl;
	for(i=1;i<=sum;i++)
	{	
		 destFile<<p->spiece<<' '<<p->weight<<' '<<p->days<<endl<<p->next<<endl;
		 p=p->next;
	}
	destFile.close();
}
/*void pigcircle::outFile()
{
	int i;
	pig *p=head;
	ifstream srcFile("pigmessage.txt",ios::in|);
	for(i=1;i<sum;i++)
	{
		
	}
}*/
void buypigs(pigcircle pc[])
{
     
}
int main()
{
	pigcircle pc[101];
	initialnumber(pc);
	initial(pc);
	pc[3].inFile();
 } 

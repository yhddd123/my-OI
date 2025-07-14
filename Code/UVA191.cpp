#include<iostream>
#define y1 _y1
using namespace std;

double x,y,xx,yy,x1,y1,x2,y2;
struct poi{
	double x,y;
}a[15];
struct line{
	double a,b,c;
}l[15];
line get(poi u,poi v){
	if(u.x==v.x)return {1,0,-u.x};
	if(u.y==v.y)return {0,1,-u.y};
	return {y1-y2,-(x1-x2),x1*y2-y1*x2};
}
double calc(poi u,line v){
	return u.x*v.a+u.y*v.b+v.c;
}
int t;
void sovle(int id){
	cin>>x>>y>>xx>>yy>>x1>>y1>>x2>>y2;
	if(x1>x2)swap(x1,x2);
	if(y1>y2)swap(y1,y2);
	a[1]=a[5]={x1,y1};a[2]={x1,y2};a[3]={x2,y2};a[4]={x2,y1};a[6]={x,y};a[7]={xx,yy};
	for(int i=1;i<=4;i++)l[i]=get(a[i],a[i+1]);
	if(calc(a[6],l[1])>=0&&calc(a[6],l[2])<=0&&calc(a[6],l[3])<=0&&calc(a[6],l[4])>=0){
		cout<<"T";
		return ;
	}
	if(calc(a[7],l[1])>=0&&calc(a[7],l[2])<=0&&calc(a[7],l[3])<=0&&calc(a[7],l[4])>=0){
		cout<<"T";
		return ;
	}
	cout<<"F";
}

signed main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	
	cin>>t;
	for(int i=1;i<=t;i++)sovle(i);
}


// Problem: P3788 幽幽子吃西瓜
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3788
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-02 14:27:05
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
const double pi=acos(-1);
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

double n,m,ans;
double calc(double x){
	if(x<0)return 0;
	return cos(x/180.0*pi)*pi/2;
}
double calc1(double x){
	if(x<0)return 0;
	return (1-cos(x/180.0*pi))*pi/2;
}
void work(){
	n=read();m=read();
	if(n<m){
		if((n<90&&m<=180)||(n>=180&&m>270)){
			if(n>=180&&m>270)n=360-n,m=360-m,swap(n,m);
			// cout<<n<<" "<<m<<" "<<calc1(90-n)<<" "<<calc1(abs(m-90))<<" "<<pi-calc1(m-90)<<"\n";
			ans=max(0.0,(calc1(90-n)-calc1(abs(m-90)))/(pi-calc1(m-90))*100.0);
			printf("%.1lf%\n",ans);
		}
		else puts("0.0%");
	}
	else{
		if(n<=270&&m>=90)puts("100.0%");
		else if(n>=270&&m<=90){
			ans=(calc(n-270)+calc(90-m))/pi*100.0;
			printf("%.1lf%\n",ans);
		}
		else if(n>=180&&m<=180){
			// cout<<n<<" "<<m<<" "<<pi-calc(abs(n-270))-calc(abs(90-m))<<" "<<pi-calc(270-n)-calc(m-90)<<"\n";
			ans=(pi-calc1(abs(n-270))-calc1(abs(90-m)))/(pi-calc1(270-n)-calc1(m-90))*100.0;
			printf("%.1lf%\n",ans);
		}
		else{
			if(n>=180)n=360-n,m=360-m,swap(n,m);
			ans=max(0.0,(pi/2-calc1(90-m))/(pi/2-calc1(90-n))*100.0);
			printf("%.1lf%\n",ans);
		}
	}
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("zjy.in","r",stdin);
	// freopen("zjy.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}

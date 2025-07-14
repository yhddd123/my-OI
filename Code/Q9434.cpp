#include<bits/stdc++.h>
#define int __int128
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
inline void write(__int128 x){static char buf[100];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}

bool Mbe;

int n,x,y,c;
pii a[maxn];
int aabs(int x){
	if(x>0)return x;
	return -x;
}
int calc(pii a,pii b,pii c){
	return aabs(a.fi*b.se+b.fi*c.se+c.fi*a.se-a.fi*c.se-b.fi*a.se-c.fi*b.se);
}
bool chk(pii u,pii v,__int128 x,__int128 y,__int128 r){
	__int128 a=v.se-u.se,b=u.fi-v.fi,c=-a*u.fi-b*u.se;
	// cout<<a<<" "<<b<<" "<<c<<" "<<(a*u.fi+b*u.se+c==0)<<" "<<(a*v.fi+b*v.se+c==0)<<"\n";
	// int dis=(__int128)(a*x+b*y+c)*(a*x+b*y+c)/(a*a+b*b);
	// write(a*x+b*y+c),putchar(' '),write(a*a+b*b),puts("");
	// cout<<dis<<"\n";
	if((a*x+b*y+c)*(a*x+b*y+c)>r*r*(a*a+b*b))return 1;
	if((a*x+b*y+c)*(a*x+b*y+c)==r*r*(a*a+b*b)){
		pii v1={u.fi-v.fi,u.se-v.se},v2={x-v.fi,y-v.se};
		if(v1.fi*v2.fi+v1.se*v2.se>0)return 1;
		v1={v.fi-u.fi,v.se-u.se},v2={x-u.fi,y-u.se};
		if(v1.fi*v2.fi+v1.se*v2.se>0)return 1;
	}
	return 0;
}
int get(pii a,pii b,pii c){
	b.fi-=a.fi,b.se-=a.se,c.fi-=a.fi,c.se-=a.se;
	return b.fi*c.se-b.se*c.fi;
}
int ans;
void work(){
	n=read();x=read(),y=read(),c=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=a[i+n]={read(),read()};
	for(int i=1,j=2,sum=0;i<=n;i++){
		while(j<=2*n){
			if(!chk(a[i],a[j],x,y,c))break;
			// cout<<i<<" "<<j<<"\n";
			if(j>i+1){
			// cout<<i<<" "<<j<<" "<<get(a[i],{x,y},a[j])<<" "<<get(a[i],{x,y},a[j-1])<<"\n";
				if((__int128)get(a[i],{x,y},a[j])*get(a[i],{x,y},a[j-1])<=0)break;
			}
			if(j>i+1)sum+=calc(a[i],a[j-1],a[j]);
			j++;
		}
		ans=max(ans,sum);
		// write(i),putchar(' '),write(j),putchar(' '),write(sum),puts("");
		if(j>i+2)sum-=calc(a[i],a[i+1],a[j-1]);
		if(i+1==j)j++;
	}
	write(ans);puts("");
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}


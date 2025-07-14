#include<bits/stdc++.h>
#define int long long
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e5;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn];
int X(int u){return u;}
int Y(int u){return a[u];}
db slope(int u,int v){return 1.0*(Y(u)-Y(v))/(X(u)-X(v));}
int q[maxn],h=1,t;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read()*inf;
	for(int i=0;i<=n+1;i++){
		while(t>1&&slope(q[t-1],q[t])<slope(q[t-1],i))t--;
		q[++t]=i;
	}
	for(int i=1;i<=n;i++){
		while(q[h+1]<=i)h++;
		//y=k(x-x0)+y0;
		db ans=((Y(q[h])-Y(q[h+1]))*(i-X(q[h]))+Y(q[h])*(X(q[h])-X(q[h+1])))/(X(q[h])-X(q[h+1]));
		printf("%lld\n",(int)ans);
	}
}

int T;
signed main(){
//		freopen("P5155_hack.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)work();
}

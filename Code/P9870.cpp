#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,q;
int a[maxn],b[maxn],c[maxn],d[maxn];
int preamx[maxn],preamn[maxn],prebmx[maxn],prebmn[maxn];
int sufamx[maxn],sufamn[maxn],sufbmx[maxn],sufbmn[maxn];
bool check1(int x,int y){
	if(x==1||y==1)return 1;
	if(a[preamn[x-1]]<b[prebmn[y-1]])return check1(preamn[x-1],y);
	if(a[preamx[x-1]]<b[prebmx[y-1]])return check1(x,prebmx[y-1]);
	return 0;
}
bool check2(int x,int y){
	if(x==n||y==m)return 1;
	if(a[sufamn[x+1]]<b[sufbmn[y+1]])return check2(sufamn[x+1],y);
	if(a[sufamx[x+1]]<b[sufbmx[y+1]])return check2(x,sufbmx[y+1]);
	return 0;
}
bool check(){
	if(a[1]>b[1]){
		for(int i=1;i<=n;i++)a[i]*=-1;
		for(int i=1;i<=m;i++)b[i]*=-1;
	}
	preamn[1]=preamx[1]=1;
	for(int i=2;i<=n;i++){
		if(a[i]<a[preamn[i-1]])preamn[i]=i;
		else preamn[i]=preamn[i-1];
		if(a[i]>a[preamx[i-1]])preamx[i]=i;
		else preamx[i]=preamx[i-1];
	}
	prebmn[1]=prebmx[1]=1;
	for(int i=2;i<=m;i++){
		if(b[i]<b[prebmn[i-1]])prebmn[i]=i;
		else prebmn[i]=prebmn[i-1];
		if(b[i]>b[prebmx[i-1]])prebmx[i]=i;
		else prebmx[i]=prebmx[i-1];
	}
	sufamn[n]=sufamx[n]=n;
	for(int i=n-1;i>=1;i--){
		if(a[i]<a[sufamn[i+1]])sufamn[i]=i;
		else sufamn[i]=sufamn[i+1];
		if(a[i]>a[sufamx[i+1]])sufamx[i]=i;
		else sufamx[i]=sufamx[i+1];
	}
	sufbmn[m]=sufbmx[m]=m;
	for(int i=m-1;i>=1;i--){
		if(b[i]<b[sufbmn[i+1]])sufbmn[i]=i;
		else sufbmn[i]=sufbmn[i+1];
		if(b[i]>b[sufbmx[i+1]])sufbmx[i]=i;
		else sufbmx[i]=sufbmx[i+1];
	}
	if(a[preamn[n]]>=b[prebmn[m]])return 0;
	if(a[preamx[n]]>=b[prebmx[m]])return 0;
	return check1(preamn[n],prebmx[m])&check2(preamn[n],prebmx[m]);
}

int T,op;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	op=read();
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)a[i]=c[i]=read();
	for(int i=1;i<=m;i++)b[i]=d[i]=read();
	printf("%lld",(int)check());
	while(q--){
		for(int i=1;i<=n;i++)a[i]=c[i];
		for(int i=1;i<=m;i++)b[i]=d[i];
		int kx=read(),ky=read();
		while(kx--){
			int u=read(),v=read();
			a[u]=v;
		}
		while(ky--){
			int u=read(),v=read();
			b[u]=v;
		}
		printf("%lld",(int)check());
	}
}

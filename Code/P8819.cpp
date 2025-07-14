#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,q,a[maxn],cur,sum;
int d[maxn],s[maxn],nw[maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	srand(time(0));
	for(int i=1;i<=n;i++)a[i]=rand()*rand()%inf*rand()%inf+rand();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		d[v]++;s[v]+=a[u];nw[v]+=a[u];
	}
	for(int i=1;i<=n;i++)sum+=a[i],cur+=s[i];
	q=read();
	while(q--){
		int opt=read();
		if(opt==1){
			int u=read(),v=read();
			nw[v]-=a[u];cur-=a[u];
		}
		else if(opt==2){
			int v=read();
			cur-=nw[v];nw[v]=0;
		}
		else if(opt==3){
			int u=read(),v=read();
			nw[v]+=a[u];cur+=a[u];
		}
		else{
			int v=read();
			cur+=s[v]-nw[v];nw[v]=s[v];
		}
		if(cur==sum)printf("YES\n");
		else printf("NO\n");
	}
}

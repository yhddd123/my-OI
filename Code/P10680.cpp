#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
int val[maxn][10];
int st[maxn],tp;
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=val[i][0]=read();
	for(int j=1;j<=9;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)val[i][j]=abs(val[i][j-1]-val[i+(1<<j-1)][j-1]);
	}
	while(q--){
		int op=read(),p=read(),w=read();
		if(op==1){
			a[p]=val[p][0]=w;
			for(int j=1;j<=9;j++){
				for(int i=max(1,p-(1<<j)+1);i<=p;i++)val[i][j]=abs(val[i][j-1]-val[i+(1<<j-1)][j-1]);
			}
		}
		else{
			if(w<=9)printf("%lld\n",val[p][w]);
			else{
				tp=0;for(int i=p;i<=p+(1<<w)-1;i+=1<<9)st[++tp]=val[i][9];
				while(tp>1){
					int nw=0;for(int i=1;i<=tp;i+=2)st[++nw]=abs(st[i]-st[i+1]);tp=nw;
				}
				printf("%lld\n",st[1]);
			}
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}
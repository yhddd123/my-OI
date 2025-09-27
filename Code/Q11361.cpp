#include<bits/stdc++.h>
#define int long long
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

int n,m,u,r,d,l;
vector<char> a[maxn];
int p[maxn];
void work(){
	n=read();m=read();u=read(),r=read(),d=read(),l=read();
	for(int i=0;i<=n+1;i++){
		a[i].resize(m+2);
		for(int j=0;j<=m+1;j++)a[i][j]='.';
	}
	if(u<n-1||r<m-1){cout<<"impossible";return ;}
	a[1][m]='*';
	for(int j=m;j;j--){
		for(int i=n;i>1;i--){
			if(l)a[i][j]='L',l--;
		}
	}
	for(int i=2;i<=n;i++){
		p[i]=0;
		for(int j=m;j;j--)if(a[i][j]=='.'){p[i]=j;break;}
	}
	while(u){
		for(int i=n;i>1;i--)if(p[i]>=1&&u)a[i][p[i]]='U',p[i]--,u--;
	}
	for(int i=n,j=1;j<m;j++){
		while(a[i][j]!='.')i--;
		a[i][j]='R',r--;
	}
	for(int i=n-1;i;i--){
		for(int j=1;j<=m;j++)if(a[i][j]=='.'&&r)a[i][j]='R',r--;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]=='.')a[i][j]='D',d--;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)cout<<a[i][j];
		if(i<n)cout<<"\n";
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	for(int t=1;t<=T;t++){
		work();
		if(t!=T)puts(""),puts("");
	}
}
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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn];
int sa[maxn],rk[maxn],tmp[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)sa[i]=i,rk[i]=s[i];
	for(int len=1;len<n;len<<=1){
		sort(sa+1,sa+n+1,[&](int u,int v){
			return rk[u]==rk[v]?rk[u+len]<rk[v+len]:rk[u]<rk[v];
		});
		for(int i=1;i<=n;i++)tmp[i]=rk[i];
		for(int i=1,v=0;i<=n;i++){
			if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+len]==tmp[sa[i-1]+len])rk[sa[i]]=v;
			else rk[sa[i]]=++v;
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",sa[i]);
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
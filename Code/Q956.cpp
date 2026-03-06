#include<bits/stdc++.h>
//#define int long long
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

struct SA{
int sa[maxn],rk[maxn<<1],tmp[maxn<<1],cnt[maxn],id[maxn];
void init(char *s,int n){
	int w=127;
	for(int i=1;i<=n;i++)++cnt[rk[i]=s[i]];
	for(int i=1;i<=w;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[rk[i]]--]=i;
	for(int i=1;i<=w;i++)cnt[i]=0;
	for(int len=1;len<=n;len<<=1){
		int cur=0;for(int i=n-len+1;i<=n;i++)id[++cur]=i;
		for(int i=1;i<=n;i++)if(sa[i]>len)id[++cur]=sa[i]-len;
		for(int i=1;i<=n;i++)cnt[tmp[i]=rk[i]]++;
		for(int i=1;i<=w;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i;i--)sa[cnt[rk[id[i]]]--]=id[i];
		for(int i=1;i<=w;i++)cnt[i]=0;
		int p=0;for(int i=1;i<=n;i++){
			if(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+len]==tmp[sa[i-1]+len])rk[sa[i]]=p;
			else rk[sa[i]]=++p;
		}
		w=p;
		if(w==n)break;
	}
}	
}sa;
int n;
char s[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	sa.init(s,n);
	for(int i=1;i<=n;i++)printf("%d ",sa.sa[i]);
}

bool med;
int T;
signed main(){
//	 freopen("A.in","r",stdin);
//	 freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}
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

int n,ans;
char s[maxn];
int len[maxn],lnk[maxn];
int a[maxn][26];
int p=1,cur=1;
int siz[maxn];
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;siz[nd]=1;
	while(p&&!a[p][c])a[p][c]=nd,p=lnk[p];
	if(!p){lnk[p=nd]=1;return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])lnk[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1,lnk[cl]=lnk[q];
		memcpy(a[cl],a[q],sizeof(a[q]));
		lnk[nd]=lnk[q]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=lnk[p];
	}
	p=nd;
}
void work(){
	n=read();scanf("%s",s+1);
	int fl=-1;
	for(int i=1;i<=n;i++){
		if(fl==-1)fl=s[i]-'a';
		else if(fl!=s[i]-'a')fl=-2;
	}
	if(fl>=0){
		printf("%lld\n",(n+2)*(n-1));
		return ;
	}
	for(int i=1;i<=n;i++){
		insert(s[i]-'a');
		// cout<<len[p]<<" "<<len[lnk[p]]<<"\n";
		ans+=len[p]-len[lnk[p]];
	}
	ans+=n*(n+1)/2-2;
	printf("%lld\n",ans);
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
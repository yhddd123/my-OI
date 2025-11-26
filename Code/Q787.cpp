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
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,ans;
char s[maxn],t[maxn];
int len[maxn];
void work(){
	scanf("%s",t+1);n=strlen(t+1);
	s[0]=s[1]='#';for(int i=1;i<=n;i++)s[i<<1]=t[i],s[i<<1|1]='#';
	n=2*n+1;
	for(int i=1,mxr=0,mid=0;i<=n;i++){
		if(i<mxr)len[i]=min(len[2*mid-i],len[mid]+mid-i);
		else len[i]=1;
		while(s[i+len[i]]==s[i-len[i]])len[i]++;
		if(len[i]+i>mxr)mxr=len[i]+i,mid=i;
	}
	for(int i=1;i<=n;i++)ans=max(ans,len[i]);
	printf("%lld\n",ans-1);
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
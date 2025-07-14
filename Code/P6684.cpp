// Problem: P6684 [BalticOI 2020 Day1] 小丑
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6684
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-09-11 14:59:21
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=400010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
char s[maxn],t[maxn],tmp[maxn],ss[maxn],tt[maxn];
vector<pii> ans,res;
void sovle(){
	res.clear();
	n++,m++;reverse(s+1,s+n+1),reverse(t+1,t+m+1);
	int cnt1=0,cnt2=0;
	for(int i=2;i<=n;i++)if(s[i]!=s[i-1])++cnt1;
	for(int i=2;i<=m;i++)if(t[i]!=t[i-1])++cnt2;
	int val=cnt1+cnt2,l=0,r=0,mn=inf,val1=(val-1)/2;
	if(!val)return ;
	// cout<<val<<"\n";
	cnt1=0;
	for(int i=2;i<=n;i++){
		cnt2=0;
		for(int j=m;j>=2;j--){
			int num=val-(s[i]!=s[i-1])-(t[j]!=t[j-1])+(s[i]!=t[j-1])+(t[j]!=s[i-1]);
			if(mn>max(cnt1+cnt2+(t[j]!=s[i-1]),num-cnt1-cnt2-(t[j]!=s[i-1]))){
				mn=max(cnt1+cnt2+(t[j]!=s[i-1]),num-cnt1-cnt2-(t[j]!=s[i-1]));
				l=i,r=j;
			}
			if(t[j]!=t[j-1])++cnt2;
		}
		if(s[i]!=s[i-1])++cnt1;
	}
	// cout<<l<<" "<<r<<" "<<mn<<"\n";
	res.pb({n-l+1,m-r+1});
	int nn=n,mm=m;
	for(int j=l;j<=nn;j++)tmp[j]=s[j];
	for(int j=r;j<=mm;j++)s[j-r+l]=t[j];
	for(int j=l;j<=nn;j++)t[j-l+r]=tmp[j];
	n=mm-r+l,m=nn-l+r;
	// for(int i=1;i<=n;i++)cout<<s[i];cout<<"\n";
	// for(int i=1;i<=m;i++)cout<<t[i];cout<<"\n";
	bool fl=0;l=r=2;
	while(1){
		if(!fl){
			while(l<=n&&s[l]==s[1])l++;
			while(r<=m&&t[r]==t[1])r++;
			if(l>n&&r>m)break;
			res.pb({n-l+1,m-r+1});
		}
		else{
			while(l<=n&&s[l]==t[1])l++;
			while(r<=m&&t[r]==s[1])r++;
			if(l>n&&r>m)break;
			res.pb({m-r+1,n-l+1});
		}
		fl^=1;
	}
	return ;
}
void work(){
	scanf("%s%s",s+1,t+1);n=strlen(s+1),m=strlen(t+1);
	for(int i=1;i<=n;i++)ss[i]=s[i];
	for(int i=1;i<=m;i++)tt[i]=t[i];
	int nn=n,mm=m;
	s[n+1]='a',t[m+1]='b';
	sovle();
	swap(res,ans);
	n=nn,m=mm;
	for(int i=1;i<=n;i++)s[i]=ss[i];
	for(int i=1;i<=m;i++)t[i]=tt[i];
	s[n+1]='b',t[m+1]='a';
	// for(int i=1;i<=n+1;i++)cout<<s[i];cout<<"\n";
	// for(int i=1;i<=m+1;i++)cout<<t[i];cout<<"\n";
	sovle();
	if(res.size()<ans.size()){
		printf("%lld\n",res.size());
		for(pii p:res)printf("%lld %lld\n",p.fi,p.se);
	}
	else{
		printf("%lld\n",ans.size());
		for(pii p:ans)printf("%lld %lld\n",p.fi,p.se);	
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("sort.in","r",stdin);
//	freopen("sort.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}

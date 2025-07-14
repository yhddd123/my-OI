// Problem: P4081 [USACO17DEC] Standing Out from the Herd P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4081
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
char c[maxn];
int len[maxn],fa[maxn];
int a[maxn][26];
int p=1,cur=1;
int flag[maxn];
void insert(int c){
	int nd=++cur;len[nd]=len[p]+1;
	while(p&&!a[p][c])a[p][c]=nd,p=fa[p];
	if(!p){fa[p=nd]=1;return ;}
	int q=a[p][c];
	if(len[p]+1==len[q])fa[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1;fa[cl]=fa[q];
		memcpy(a[cl],a[q],sizeof(a[q]));
		fa[q]=fa[nd]=cl;
		while(p&&a[p][c]==q)a[p][c]=cl,p=fa[p];
	}
	p=nd;
}
string s[maxn];
int ans[maxn],num[maxn];
void go(int p,int id){
	while(p&&~num[p]&&num[p]!=id){
		num[p]=num[p]?-1:id;
		p=fa[p];
	}
}
void work(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];p=1;
		for(char c:s[i])insert(c-'a');
	}
	// cout<<p<<" "<<cur<<"\n";
	for(int i=1;i<=n;i++){
		int p=1;
		for(int c:s[i])go(p=a[p][c-'a'],i);
	}
	for(int i=2;i<=cur;i++)if(~num[i]){
		ans[num[i]]+=len[i]-len[fa[i]];
		// cout<<num[i]<<" ";
	}
	// cout<<"\n";
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}

// Problem: P10349 [PA2024] Mrówki
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10349
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-13 14:18:11
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,ans[maxn];
char s[maxn];
void work(){
	n=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++)m+=s[i]=='L';
	for(int i=1,res=0;i<=m;i++){
		if(s[i]=='L'){
			if(res&1)res++;
		}
		else{
			if(res&1)res+=2;
			else res++;
		}
		ans[i]=res;
	}
	for(int i=n,res=0;i>m;i--){
		if(s[i]=='P'){
			if(res&1)res++;
		}
		else{
			if(res&1)res+=2;
			else res++;
		}
		ans[i]=res;		
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("ant.in","r",stdin);
	// freopen("ant.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}

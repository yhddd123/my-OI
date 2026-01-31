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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int op,n,m,k,a[maxn];
void work(){
	op=read();n=read();m=read();
	vector<pii> edge;
	if(op==1){
		for(int i=1;i<=m;i++){
			int u=read(),v=read();
		}
		int k=read();
		for(int i=1;i<=k;i++)a[i]=read();
		pii mn={a[1],1};
		for(int i=1;i<=k;i++)mn=min(mn,{a[i],i});
		rotate(a+1,a+mn.se,a+k+1);
		for(int i=1;i<=k;i++)cout<<a[i]<<" ";cout<<"\n";
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
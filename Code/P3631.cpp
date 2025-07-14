// Problem: P3631 [APIO2011] 方格染色
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3631
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-09-04 14:46:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000000ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
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

int n,m,q;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int f[maxn],siz[maxn],val[maxn],num;
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
void work(){
	n=read();m=read();q=read();num=n+m-1;
	for(int i=1;i<=n+m;i++)f[i]=i,siz[i]=1;
	for(int i=1;i<=q;i++){
		int u=read(),v=read()+n,fl=read();
		if((u&1)&&((v-n)&1))fl^=1;
		if(fd(u)!=fd(v)){
			int uu=u,vv=v;
			while(f[uu]!=uu){
				fl^=val[uu];uu=f[uu];
			}
			while(f[vv]!=vv){
				fl^=val[vv];vv=f[vv];
			}
			if(siz[uu]<siz[vv])swap(uu,vv);
			siz[uu]+=siz[vv],f[vv]=uu,val[vv]=fl;
			num--;
		}
		else{
			int uu=u,vv=v;
			while(uu!=vv){
				if(siz[uu]>siz[vv])swap(uu,vv);
				fl^=val[uu],uu=f[uu];
			}
			if(fl){
				puts("0");
				return ;
			}
		}
		// cout<<i<<" "<<num<<"\n";
	}
	printf("%lld\n",ksm(2,num));
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("color.in","r",stdin);
//	freopen("color.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}

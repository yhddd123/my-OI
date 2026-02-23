#include<bits/stdc++.h>
// #define int long long
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

int n;
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int pre1[maxn],ed1[maxn];
int pre2[maxn],ed2[maxn];
int l[maxn],r[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)f[i]=i,ed1[i]=ed2[i]=i,l[i]=r[i]=i;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		if(f[v]!=v){puts("Bad oriented forest");fflush(stdout);return ;}
		int rt=fd(u);f[v]=rt;
		if(r[rt]+1==l[v]){
			while(ed1[rt]&&ed1[rt]!=u)ed1[rt]=pre1[ed1[rt]];
			if(!ed1[rt]){printf("Bad segment at %d\n",u);fflush(stdout);return ;}
			pre1[v]=ed1[rt],ed1[rt]=ed1[v];
			r[rt]=r[v];
		}else if(r[v]+1==l[rt]){
			while(ed2[rt]&&ed2[rt]!=u)ed2[rt]=pre2[ed2[rt]];
			if(!ed2[rt]){printf("Bad segment at %d\n",u);fflush(stdout);return ;}
			pre2[v]=ed2[rt],ed2[rt]=ed2[v];
			l[rt]=l[v];
		}
		else{printf("Bad segment at %d\n",rt);fflush(stdout);return ;}
		puts("Good");fflush(stdout);
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}
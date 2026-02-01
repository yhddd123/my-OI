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

int n,lim,a[3],id[3],rk[3],sum[3];
multiset<int> s[3];
bool chk(int tim){
	if((!sum[0]||tim+sum[0]<=a[0])&&(!(sum[0]+sum[1])||tim+sum[0]+sum[1]<=a[1])&&tim+sum[0]+sum[1]+sum[2]<=a[2])return true;
	return false;
}
bool ban[3];
void work(){
	n=read();a[0]=read(),a[1]=read(),a[2]=read();
	id[0]=0,id[1]=1,id[2]=2;
	sort(id,id+3,[&](int u,int v){return a[u]<a[v];});
	for(int i=0;i<3;i++)rk[id[i]]=i;
	sort(a,a+3);
	for(int i=0;i<3;i++)sum[i]=0,s[i].clear();
	for(int i=1;i<=n;i++){
		int p=rk[read()-1],t=read();
		sum[p]+=t;s[p].insert(t);
	}
	lim=read();
	if(!chk(0)){puts("NO");return ;}
	int val=0;
	for(int tt=1,tim=0;tt<=n;tt++){
		ban[0]=ban[1]=ban[2]=0;
		bool fl=0;
		for(int ttt=0;ttt<3;ttt++){
			pii mn={inf,0};
			for(int i=0;i<3;i++)if(s[i].size()&&!ban[i])mn=min(mn,{*s[i].begin(),i});
			tim+=mn.fi,sum[mn.se]-=mn.fi;
			if(!chk(tim)){
				tim-=mn.fi,sum[mn.se]+=mn.fi;
				ban[mn.se]=1;
			}
			else{
				s[mn.se].erase(s[mn.se].find(mn.fi));
				val+=tim;fl=1;
				break;
			}
		}
	}
	if(val<lim)puts("YES");
	else puts("NO");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}
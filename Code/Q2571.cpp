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
const int maxn=531441;
const int inf=3e7;
bool mbe;

int n,a[maxn];
vector<pii> va,vb;
void dfs1(int d,int s0,int s1,int s2){
	if(d==n/2+1){
		va.pb({s1-s0,s2-s1});
		return ;
	}
	dfs1(d+1,s0+a[d],s1,s2);
	dfs1(d+1,s0,s1+a[d],s2);
	dfs1(d+1,s0,s1,s2+a[d]);
}
void dfs2(int d,int s0,int s1,int s2){
	if(d==n+1){
		vb.pb({s0-s1,s1-s2});
		return ;
	}
	dfs2(d+1,s0+a[d],s1,s2);
	dfs2(d+1,s0,s1+a[d],s2);
	dfs2(d+1,s0,s1,s2+a[d]);
}
int v1,v2,v3,v4;
bool check(int d){
	int pl=va.size(),pr=va.size()-1;
	for(auto[x,y]:vb){
		while(pl&&va[pl-1].fi+x>=0)pl--;
		while(~pr&&va[pr].fi+x>d)pr--;
		pii mn=que(pl,pr);
		if(y+mn.fi<=d){
			v3=x,v4=y,v1=mn.se,v2=mn.fi;
			return 1;
		}
	}
	return 0;
}
int col[maxn];bool fl;
void dfs3(int d,int s0,int s1,int s2){
	if(d==n/2+1){
		if(s1-s0==v1&&s2-s1==v2)fl=1;
		return ;
	}
	col[d]=1;
	dfs3(d+1,s0+a[d],s1,s2);
	if(fl)return ;
	col[d]=2;
	dfs3(d+1,s0,s1+a[d],s2);
	if(fl)return ;
	col[d]=3;
	dfs3(d+1,s0,s1,s2+a[d]);
}
void dfs4(int d,int s0,int s1,int s2){
	if(d==n+1){
		if(s0-s1==v3&&s1-s2==v4)fl=1;
		return ;
	}
	col[d]=1;
	dfs4(d+1,s0+a[d],s1,s2);
	if(fl)return ;
	col[d]=2;
	dfs4(d+1,s0,s1+a[d],s2);
	if(fl)return ;
	col[d]=3;
	dfs4(d+1,s0,s1,s2+a[d]);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	dfs1(1,0,0,0);
	dfs2(n/2+1,0,0,0);
	sort(va.begin(),va.end());
	sort(vb.begin(),vb.end());
	set<pii> s;
	int mn=inf;
	for(int i=0,j=0;i<va.size();i++){
		while(j<vb.size()&&vb[j].fi<=va[i].fi){
			auto it=s.insert({vb[j].se,vb[j].fi+vb[j].se}).se;
			while(it!=s.begin()){
				it--;
				if((*it).se)
			}
			auto it=s.upper_bound({vb[j].fi,inf});
			if(it!=s.begin()){
				it--;
				if(va[i].fi+va[i].se-(*it).se<mn){
					mn=va[i].fi+va[i].se-(*it).se;
					v1=va[i].fi,v2=va[i].se,v3=(*it).se-(*it).fi,v4=(*it).fi;
				}
			}
			j++;
		}
	}
	dfs3(1,0,0,0);
	fl=0;
	dfs4(n/2+1,0,0,0);
	for(int i=1;i<=n;i++)cout<<col[i]<<" ";	
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
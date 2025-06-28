// Problem: P11820 [PA 2015] 健身房 / Siłownia
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11820
// Memory Limit: 512 MB
// Time Limit: 8100 ms
// Written by yhm.
// Start codeing:2025-04-11 15:03:24
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1000010;
const int inf=2e9;
bool mbe;

int n,k,ans;
vector<tuple<int,int,int>> a[maxn];
map<int,int> mp;
tuple<int,int,int,int> b[maxn];
struct node{
	int l,r;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
set<node> s;
set<pii> ss[maxn];
set<pair<pii,int>> mn;
int res[maxn];
void work(){
	n=read();k=read();k=0;
	for(int i=1;i<=n;i++){
		int l=read(),r=read(),p=read();
		if(!mp[p])mp[p]=++k;
		a[mp[p]].pb({l,r,i});
	}
	n=0;
	for(int i=1;i<=k;i++){
		sort(a[i].begin(),a[i].end(),[&](tuple<int,int,int> u,tuple<int,int,int> v){return get<0>(u)>get<0>(v);});
		s.clear();
		for(auto[l,r,id]:a[i]){
			auto it=s.find({r,r});
			if(it!=s.end()){
				auto tmp=it;
				int ll=(*it).l,rr=(*it).r;
				it=s.erase(it);
				while(it!=s.end()&&rr+1==(*it).l)rr=(*it).r,it=s.erase(it);
				while(it!=s.begin()){
					it--;
					if((*it).r+1==ll)ll=(*it).l;
					else break;
					it=s.erase(it);
				}
				if(l>ll-1){puts("NIE");return ;}
				b[++n]={l,ll-1,i,id};
				s.insert({ll-1,rr});
			}
			else{
				b[++n]={l,r,i,id};
				s.insert({r,r});
			}
		}
	}
	b[++n]={inf,inf,1,0};
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		auto[l,r,p,id]=b[i];
		// cout<<l<<" "<<r<<" "<<p<<"\n";
		while(mn.size()&&(*mn.begin()).fi.fi<l){
			++ans;
			vector<pair<pii,int>> tmp;
			for(auto pp:mn)tmp.pb(pp);
			int tim=(*mn.begin()).fi.fi;
			mn.clear();
			for(auto[p,pp]:tmp){
				res[p.se]=tim;
				ss[pp].erase(p);
				if(ss[pp].size())mn.insert({*ss[pp].begin(),pp});
			}
			// cout<<mn.size()<<" "<<ans<<endl;
		}
		if(ss[p].size())mn.erase({*ss[p].begin(),p});
		ss[p].insert({r,id});
		mn.insert({*ss[p].begin(),p});
	}
	printf("%lld\n",ans);
	for(int i=1;i<n;i++)printf("%lld\n",res[i]);
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
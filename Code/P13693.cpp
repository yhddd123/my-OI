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
const int maxn=600010;
const int inf=1e9;
bool mbe;

#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int cov[maxn<<2];
void down(int nd){cov[ls]=cov[nd],cov[rs]=cov[nd],cov[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){cov[nd]=w;return ;}
	if(cov[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
int query(int nd,int l,int r,int p){
	if(cov[nd])return cov[nd];
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
int n,q,a[maxn];
struct node{
	int l,r,v,t;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};set<node> s;
int pos[maxn],lst[maxn];
bool vis[maxn];
vector<tuple<int,int,int,int>> upd[maxn];
vector<tuple<int,int,int>> que[maxn];
vector<tuple<int,int,int>> mdf[maxn];
vector<pii> ask[maxn];
vector<int> ans;
int lsh[maxn*3],len;
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int nxt[maxn],to[20][maxn];
std::vector<int> solve(int N, std::vector<int>& V, int Q, std::vector<std::pair<int,int>>& queries){
	n=N;q=Q;ans.resize(q);
	for(int i=1;i<=n;i++)a[i]=V[i-1];
	for(int i=1;i<=n;i++){
		lst[i]=pos[a[i]];
		pos[a[i]]=i;
	}
	for(int i=n,mex=1;i;i--){
		vis[a[i]]=1;
		while(vis[mex])mex++;
		s.insert({i,i,mex,n});
	}
	for(int i=n;i;i--){
		int p=lst[i];
		auto it=s.find({p+1,p+1,0,0});
		if((*it).l<=p){
			auto[l,r,v,t]=*it;it=s.erase(it);
			s.insert({l,p,v,t}),s.insert({p+1,r,v,t});
		}
		it=s.find({p+1,p+1,0,0});
		while(it!=s.end()&&(*it).v>=a[i]){
			auto[l,r,v,t]=*it;it=s.erase(it);
			upd[v].pb({l,r,i,t});
			mdf[i].pb({l,r,v});
			// cout<<l<<" "<<r<<" "<<i<<" "<<t<<" "<<v<<"\n";
		}
		int nw=(it==s.end()?i-1:(*it).l-1);
		if(p+1<=nw)s.insert({p+1,nw,a[i],i-1});
		if(s.size()&&(*--s.end()).r==i){
			auto[l,r,v,t]=*--s.end();s.erase(--s.end());
			if(l<r)s.insert({l,r-1,v,t});
			upd[v].pb({i,i,i,t}),mdf[i].pb({i,i,v});
		}
	}
	for(int i=0;i<q;i++){
		int l=queries[i].fi,r=queries[i].se;
		ask[r].pb({l,i});
	}
	for(int i=1;i<=n;i++){
		for(auto[l,r,v]:mdf[i])updata(1,1,n,l,r,v);
		for(auto[l,id]:ask[i]){
			int v=query(1,1,n,l);
			que[v].pb({l,i,id});
		}
	}
	for(int v=1;v<=n;v++)if(que[v].size()){
		len=0;for(auto[l1,r1,l2,r2]:upd[v])lsh[++len]=l1,lsh[++len]=l2+1;
		for(auto[l,r,id]:que[v])lsh[++len]=l;
		sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;lsh[len+1]=n+2;
		for(int i=1;i<=len+1;i++)f[i]=i,nxt[i]=len+1;
		sort(upd[v].begin(),upd[v].end(),[&](tuple<int,int,int,int> u,tuple<int,int,int,int> v){return get<2>(u)<get<2>(v);});
		for(auto[l1,r1,l2,r2]:upd[v]){
			int pl=lower_bound(lsh+1,lsh+len+1,l1)-lsh;
			int p=lower_bound(lsh+1,lsh+len+1,l2+1)-lsh;
			for(int i=fd(pl);lsh[i]<=r1;i=fd(i)){
				nxt[i]=p;
				f[i]=fd(i+1);
			}
		}
		for(int i=1;i<=len+1;i++)to[0][i]=nxt[i];
		for(int j=1;j<20;j++){
			for(int i=1;i<=len+1;i++)to[j][i]=to[j-1][to[j-1][i]];
		}
		for(auto[l,r,id]:que[v]){
			int p=lower_bound(lsh+1,lsh+len+1,l)-lsh;
			// cout<<v<<" "<<l<<" "<<r<<" "<<p<<"\n";
			for(int i=19;~i;i--)if(lsh[to[i][p]]<=r+1)p=to[i][p],ans[id]+=1<<i;
		}
	}
	return ans;
}

// int main()
// {
	// std::ios_base::sync_with_stdio(false);
	// std::cin.tie(0);
	// int n,q;
	// std::cin>>n>>q;
	// std::vector<int> vec;
	// for(int i=0;i<n;i++)
	// {
		// int x;
		// std::cin>>x;
		// vec.push_back(x);
	// }
	// std::vector<std::pair<int,int>> queries;
	// for(int i=0;i<q;i++)
	// {
		// int l,r;
		// std::cin>>l>>r;
		// queries.push_back(std::make_pair(l,r));
	// }
	// std::vector<int> res=solve(n,vec,q,queries);
	// for(int i=0;i<q;i++)
		// std::cout<<res[i]<<'\n';
	// return 0;
// }
// Problem: P10436 [JOIST 2024] 卡牌收集 / Card Collection
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10436
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2026-01-27 20:35:10
// 
// Powered by CP Editor (https://cpeditor.org)

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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=200010;
const int inf=1e9;
bool mbe;

namespace automation{
	bool f[110][110][9];
	map<vector<int>,bool> mp;
	int op1(int o1,int o2){
		int a=o1/3-1,b=o1%3-1,c=o2/3-1,d=o2%3-1;
		return (min(a,c)+1)*3+min(b,d)+1;
	}
	int op2(int o1,int o2){
		int a=o1/3-1,b=o1%3-1,c=o2/3-1,d=o2%3-1;
		return (max(a,c)+1)*3+max(b,d)+1;
	}
	bool calc(vector<int> &a){
		if(mp.find(a)!=mp.end())return mp[a];
		int n=a.size();
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				for(int o=0;o<9;o++)f[i][j][o]=0;
			}
			f[i][i][a[i-1]]=1;
		}
		for(int len=2;len<=n;len++){
			for(int i=1,j=len;j<=n;i++,j++){
				for(int k=i;k<j;k++){
					for(int o1=0;o1<9;o1++)if(f[i][k][o1]){
						for(int o2=0;o2<9;o2++)if(f[k+1][j][o2]){
							f[i][j][op1(o1,o2)]=1;
							f[i][j][op2(o1,o2)]=1;
						}
					}
				}
			}
		}
		return mp[a]=f[1][n][4];
	}
	struct node{
		vector<int> sta;
		vector<int> nxt;
	}dfa[55];int idx;
	int to[55][9];
	bool ok[55];
	int pw[5]={1,9,81,729,6561};
	node init(vector<int> a,int lim){
		node res;
		res.sta=a;
		for(int i=0;i<=lim;i++){
			for(int s=0;s<pw[i];s++){
				vector<int> b=a;
				for(int j=0;j<i;j++)b.pb((s/pw[j])%9);
				res.nxt.pb(calc(b));
			}
		}
		return res;
	}
	void init(int lim){
		dfa[0]=init({},lim);
		queue<int> q;q.push(0);
		for(int id=0;id<=idx;id++){
			// cout<<id<<"\n";
			ok[id]=calc(dfa[id].sta);
			for(int c=0;c<9;c++){
				vector<int> b=dfa[id].sta;b.pb(c);
				node nw=init(b,lim);
				int p=-1;for(int j=0;j<=idx;j++)if(dfa[j].nxt==nw.nxt){p=j;break;}
				if(p==-1)dfa[++idx]=nw,p=idx;
				to[id][c]=p;
				// cout<<p<<" ";
			}
			// cout<<"\n";
		}
		// cout<<idx<<"\n";
	}
}
using automation::to;
using automation::ok;
int n,q;
pii a[maxn<<1];
int lshx[maxn<<1],lenx,lshy[maxn<<1],leny;
int pos[maxn],sta[maxn],nxt[maxn][9];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],mx[maxn<<2];
int pl[maxn<<2],pr[maxn<<2],pp[maxn];
void build(int nd,int l,int r){
	mn[nd]=leny+1,mx[nd]=0;pl[nd]=l,pr[nd]=r;
	if(l==r){pp[l]=nd;return ;}
	build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p,int w){
	mn[nd]=min(mn[nd],w),mx[nd]=max(mx[nd],w);
	if(l==r)return ;
	if(p<=mid)modif(ls,l,mid,p,w);
	else modif(rs,mid+1,r,p,w);
}
int quemn(int p,int w){
	int nd=pp[p];
	if(mn[nd]<=w)return p;
	while(nd){
		int lst=nd;nd>>=1;
		if(lst==ls){
			if(mn[rs]<=w){nd=rs;break;}
		}
	}
	if(!nd)return n+1;
	int l=pl[nd],r=pr[nd];
	while(l^r){
		if(mn[ls]<=w)nd=ls,r=mid;
		else nd=rs,l=mid+1;
	}
	return l;
}
int quemx(int p,int w){
	int nd=pp[p];
	if(mx[nd]>=w)return p;
	while(nd){
		int lst=nd;nd>>=1;
		if(lst==ls){
			if(mx[rs]>=w){nd=rs;break;}
		}
	}
	if(!nd)return n+1;
	int l=pl[nd],r=pr[nd];
	while(l^r){
		if(mx[ls]>=w)nd=ls,r=mid;
		else nd=rs,l=mid+1;
	}
	return l;
}
int id[maxn<<1];
inline void chkmn(int &u,int v){(u>v)&&(u=v);}
set<int> s1[maxn<<1];
void sovle(int o=0){
	build(1,1,n);
	for(int i=1;i<=leny;i++)s1[i].insert(n+1);
	for(int l=1,r;l<=n+q;l=r+1){
		r=l;while(r+1<=n+q&&a[id[l]].fi==a[id[r+1]].fi)r++;
		map<int,int> mp2;
		for(int ii=l;ii<=r;ii++){
			int i=id[ii];
			if(i>n){
				i-=n;
				if(pos[i]==n)continue;
				// cout<<i<<" "<<quemn(1,1,n,pos[i]+1,a[i+n].se-1)<<" "<<*s1[a[i+n].se].lower_bound(pos[i]+1)<<" "<<quemx(1,1,n,pos[i]+1,a[i+n].se+1)<<"\n";
				chkmn(nxt[i][!o?0:8],quemn(pos[i]+1,a[i+n].se-1));
				chkmn(nxt[i][!o?1:7],*s1[a[i+n].se].lower_bound(pos[i]+1));
				chkmn(nxt[i][!o?2:6],quemx(pos[i]+1,a[i+n].se+1));
			}
		}
		for(int ii=l;ii<=r;ii++){
			int i=id[ii];
			if(i<=n){
				modif(1,1,n,i,a[i].se);
				s1[a[i].se].insert(i);
			}
		}
		set<int> s2;s2.insert(n+1);
		for(int ll=l,rr;ll<=r;ll=rr+1){
			rr=ll;while(rr+1<=r&&a[id[ll]].se==a[id[rr+1]].se)rr++;
			vector<int> lsh={n+1};
			for(int ii=ll;ii<=rr;ii++){
				int i=id[ii];
				if(i>n){
					i-=n;
					if(pos[i]==n)continue;
					chkmn(nxt[i][!o?3:5],*s2.lower_bound(pos[i]+1));
				}
			}
			for(int ii=ll;ii<=rr;ii++){
				int i=id[ii];
				if(i<=n){
					s2.insert(i);
					if(!o)lsh.pb(i);
				}
				else{
					i-=n;
					if(pos[i]==n)continue;
					if(!o){
						if(id[ii-1]<=n)sort(lsh.begin(),lsh.end());
						chkmn(nxt[i][4],*lower_bound(lsh.begin(),lsh.end(),pos[i]+1));
					}
				}
			}
		}
	}
	for(int i=1;i<=leny;i++)set<int>().swap(s1[i]);
}
void work(){
	automation::init(2);
	n=read();q=read();
	for(int i=1;i<=n+q;i++)a[i]={read(),read()};
	for(int i=1;i<=n+q;i++)lshx[++lenx]=a[i].fi,lshy[++leny]=a[i].se;
	sort(lshx+1,lshx+lenx+1),lenx=unique(lshx+1,lshx+lenx+1)-lshx-1;
	sort(lshy+1,lshy+leny+1),leny=unique(lshy+1,lshy+leny+1)-lshy-1;
	for(int i=1;i<=n+q;i++){
		a[i].fi=lower_bound(lshx+1,lshx+lenx+1,a[i].fi)-lshx;
		a[i].se=lower_bound(lshy+1,lshy+leny+1,a[i].se)-lshy;
	}
	for(int i=1;i<=n+q;i++)id[i]=i;
	sort(id+1,id+n+q+1,[&](int u,int v){return a[u]<a[v]||(a[u]==a[v]&&u<v);});
	for(int t=1;t<8;t++){
		for(int i=1;i<=q;i++){
			for(int c=0;c<9;c++)nxt[i][c]=n+1;
		}
		sovle();
		reverse(id+1,id+n+q+1);
		for(int i=1;i<=n+q;i++)a[i].fi=lenx-a[i].fi+1,a[i].se=leny-a[i].se+1;
		sovle(1);
		reverse(id+1,id+n+q+1);
		for(int i=1;i<=n+q;i++)a[i].fi=lenx-a[i].fi+1,a[i].se=leny-a[i].se+1;
		for(int i=1;i<=q;i++){
			if(pos[i]==n)continue;
			pii p={n+1,0};
			// for(int c=0;c<9;c++)cout<<i<<" "<<c<<" "<<nxt[i][c]<<"\n";
			for(int c=0;c<9;c++)if(to[sta[i]][c]!=sta[i])p=min(p,{nxt[i][c],c});
			if(p.fi!=n+1){
				pos[i]=p.fi;
				sta[i]=to[sta[i]][p.se];
			}
		}
		// cout<<t<<"\n";
		// for(int i=1;i<=q;i++)cout<<pos[i]<<" "<<sta[i]<<"\n";
	}
	for(int i=1;i<=q;i++)if(ok[sta[i]])write(i),putchar(' ');
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
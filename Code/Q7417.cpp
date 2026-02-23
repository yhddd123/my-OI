#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<ll,int>
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
const int maxn=35010;
const int inf=1.3e9;
bool mbe;

int n,q,a[maxn];
pii f[maxn][2];
inline void calcf(int l,int r,int c,pii &f0,pii &f1){
	f[l-1][0]=f0,f[l-1][1]=f1;
	for(int i=l;i<=r;i++){
		f[i][0]=max({f[i-1][0],{f[i-1][0].fi+a[i]-a[i-1]-c,f[i-1][0].se+1},{f[i-1][1].fi+a[i]-c,f[i-1][1].se+1}});
		f[i][1]=max({f[i-1][1],{f[i-1][1].fi-c,f[i-1][1].se+1},{f[i-1][0].fi-a[i-1],f[i-1][0].se}});
	}
	f0=f[r][0],f1=f[r][1];
}
pii operator+(pii u,pii v){return {u.fi+v.fi,u.se+v.se};}
struct mat{
	pii e00,e01,e10,e11;
};
inline mat operator*(const mat &u,const mat &v){
	mat res;
	res.e00=max(u.e00+v.e00,u.e01+v.e10);
	res.e01=max(u.e00+v.e01,u.e01+v.e11);
	res.e10=max(u.e10+v.e00,u.e11+v.e10);
	res.e11=max(u.e10+v.e01,u.e11+v.e11);
	return res;
}
struct node{
	vector<int> e00,e01,e10,e11;
}val[maxn];
inline void vecmax(vector<int> &u,const vector<int> v){
	u.resize(max(u.size(),v.size()),-inf);
	for(int i=0;i<v.size();i++)u[i]=max(u[i],v[i]);
}
inline vector<int> operator*(const vector<int> &u,const vector<int> &v){
	if(!u.size())return v;
	if(!v.size())return u;
	int n=u.size()-1,m=v.size()-1;
	int p=0,q=0,t=0;
	while(p<=n&&u[p]==-inf)p++;
	while(q<=m&&v[q]==-inf)q++;
	if(p>n||q>m)return {-inf};
	vector<int> res;
	res.reserve(n+m+1);
	for(int i=1;i<=p+q;i++)res.pb(-inf);
	res.pb(u[p]+v[q]),p++,q++;
	while(p<=n&&q<=m){
		if(u[p]-u[p-1]>v[q]-v[q-1])res.pb(res.back()+u[p]-u[p-1]),p++;
		else res.pb(res.back()+v[q]-v[q-1]),q++;
	}
	while(p<=n)res.pb(res.back()+u[p]-u[p-1]),p++;
	while(q<=m)res.pb(res.back()+v[q]-v[q-1]),q++;
	return res;
}
inline node operator*(node &u,node &v){
	node res;
	vecmax(res.e00,u.e00*v.e00);
	vecmax(res.e00,u.e01*v.e10);
	vecmax(res.e01,u.e00*v.e01);
	vecmax(res.e01,u.e01*v.e11);
	vecmax(res.e10,u.e10*v.e00);
	vecmax(res.e10,u.e11*v.e10);
	vecmax(res.e11,u.e10*v.e01);
	vecmax(res.e11,u.e11*v.e11);
	return res;
}
inline pii calc(vector<int> &w,int x){
	if(!w.size())return {-inf,0};
	int l=0,r=w.size()-2,res=0;
	while(l<=r){
		int mid=l+r>>1;
		if(-1ll*mid*x+w[mid]<=-1ll*(mid+1)*x+w[mid+1])res=mid+1,l=mid+1;
		else r=mid-1;
	}
	return {-1ll*res*x+w[res],res};
}
const int B=300;
const int maxm=maxn/B+10;
int bel[maxn],pl[maxm],pr[maxm],num;
node sum[maxm],pre[maxn],suf[maxn];
inline void get(node &v,int c,mat &w){
	w.e00=calc(v.e00,c);
	w.e01=calc(v.e01,c);
	w.e10=calc(v.e10,c);
	w.e11=calc(v.e11,c);
}
// void print(mat u){
	// cout<<u.e00.fi<<" "<<u.e00.se<<" "<<u.e10.fi<<" "<<u.e11.se<<"\n";
// }
// pii calc(int l,int r,int c){
	// mat res;res.e00={0,0},res.e01=res.e10=res.e11={-inf,0};
	// if(bel[l]==bel[r]){
		// for(int i=l;i<=r;i++)res=get(val[i],c)*res;
	// }
	// else{
		// res=get(suf[l],c)*res;
		// for(int i=bel[l]+1;i<bel[r];i++)res=get(pre[pr[i]],c)*res;
		// res=get(pre[r],c)*res;
	// }
	// return res.e00;
// }
vector<int> ask;
int ans[maxn];
mat vv[maxm];
pii calc(int l,int r,int c){
	if(bel[l]==bel[r]){
		pii f0={0,0},f1={-inf,0};
		calcf(l,r,c,f0,f1);
		return f0;
	}
	else{
		pii f0={0,0},f1={-inf,0},g0,g1;mat w;
		get(suf[l],c,w);
		g0=max(w.e00+f0,w.e01+f1);
		g1=max(w.e10+f0,w.e11+f1);
		f0=g0,f1=g1;
		for(int i=bel[l]+1;i<bel[r];i++){
			w=vv[i];
			g0=max(w.e00+f0,w.e01+f1);
			g1=max(w.e10+f0,w.e11+f1);
			f0=g0,f1=g1;
		}
		get(pre[r],c,w);
		g0=max(w.e00+f0,w.e01+f1);
		g1=max(w.e10+f0,w.e11+f1);
		f0=g0,f1=g1;
		return f0;
	}
}
tuple<int,int,int> que[maxn];
void sovle(int l,int r,vector<int> &ask){
	if(!ask.size()||l>r)return ;
	int mid=((ll)l+r)>>1;
	for(int i=1;i<=num;i++)get(sum[i],mid,vv[i]);
	vector<int> al,ar;
	for(int id:ask){
		auto[l,r,k]=que[id];
		pii dp=calc(l,r,mid);
		if(dp.se<k)al.pb(id);
		else ar.pb(id),ans[id]=dp.fi+k*mid;
	}
	sovle(l,mid-1,al),sovle(mid+1,r,ar);
	vector<int>().swap(ask);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=n;i++){
		val[i].e00={0,a[i]-a[i-1]};
		val[i].e01={-inf,a[i]};
		val[i].e10={-a[i-1]};
		val[i].e11={0,0};
	}
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+B-1,n);pl[++num]=l,pr[num]=r;
		for(int i=l;i<=r;i++)bel[i]=num;
		pre[l]=val[l];for(int i=l+1;i<=r;i++)pre[i]=val[i]*pre[i-1];
		suf[r]=val[r];for(int i=r-1;i>=l;i--)suf[i]=suf[i+1]*val[i];
		sum[num]=pre[r];
	}
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),k=read();
		que[i]={l,r,k},ask.pb(i);
	}
	sovle(-35000,inf,ask);
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen("sequence.in","r",stdin);
	// freopen("sequence.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}
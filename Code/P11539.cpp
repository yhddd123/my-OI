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

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn<<1],inv[maxn<<1],ni[maxn<<1];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
    ni[0]=ni[1]=1;for(int i=2;i<=n;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
}
int Cat(int n){return C(2*n,n)*ni[n+1]%mod;}
int n,a[maxn],b[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct ST{
	pii st[20][maxn];
	void init(){
		for(int j=1;j<20;j++){
			for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
		}
	}
	pii que(int l,int r){
		int k=__lg(r-l+1);
		return max(st[k][l],st[k][r-(1<<k)+1]);
	}
}t1,t2;
int v[maxn];
pii mn[maxn<<2];int tag[maxn<<2];
void build(int nd,int l,int r){
	if(l==r){mn[nd]={v[l],-l};return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]);
}
void upd(int nd,int w){mn[nd].fi+=w;tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
}
pii query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mn[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int st1[maxn],tp1,st2[maxn],tp2;
vector<tuple<int,int,int>> mdf[maxn];
int pos;
void ask(int p){
	while(pos>p){
		for(auto[l,r,w]:mdf[pos])updata(1,1,n,l,r,-w);
		pos--;
	}
}
int sovle(int pl,int pr){
	if(pl==pr)return 1;
	int vl=-t1.que(pl,pr).fi,vr=t2.que(pl,pr).fi;
	// cout<<pl<<" "<<pr<<endl;
	int res=1,num=0;
	if(b[vl]<b[vr]){
		int p=pr;
		while(p>=pl){
			int q=t2.que(pl,p).se;
			ask(p);
			int nw=-query(1,1,n,1,q).se;
			res=res*sovle(nw,p)%mod,++num;
			p=nw-1;
		}
	}
	else{
		int p=pr;
		while(p>=pl){
			int q=t1.que(pl,p).se;
			ask(p);
			int nw=-query(1,1,n,1,q).se;
			res=res*sovle(nw,p)%mod,++num;
			p=nw-1;
		}
	}
	res=res*Cat(num-1)%mod;
	return res;
}
void work(){
	n=read();init(2*n);
	for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]=i;
	for(int i=1;i<=n;i++){
		while(tp1&&a[i]<a[st1[tp1]]){
			mdf[i].pb({st1[tp1-1]+1,st1[tp1],a[st1[tp1]]-a[i]});
			tp1--;
		}
		while(tp2&&a[i]>a[st2[tp2]]){
			mdf[i].pb({st2[tp2-1]+1,st2[tp2],-a[st2[tp2]]+a[i]});
			tp2--;
		}
		st1[++tp1]=i,st2[++tp2]=i;
	}
	for(int i=n,mn=a[n],mx=a[n];i;i--){
		mn=min(mn,a[i]),mx=max(mx,a[i]);
		v[i]=mx-mn-n+i;
	}
	build(1,1,n);
	for(int i=1;i<=n;i++)t1.st[0][i]={-a[i],i},t2.st[0][i]={a[i],i};
	t1.init(),t2.init();
	pos=n;int f=sovle(1,n);
	printf("%lld\n",f);
}

bool med;
int T;
signed main(){
	// freopen("random.in","r",stdin);
	// freopen("random.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}
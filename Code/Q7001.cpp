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

int n,a[maxn],ans;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2],num[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	tag[nd]=0;
	if(l==r){mn[nd]=l,num[nd]=1;return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	mn[nd]=min(mn[ls],mn[rs]);
	num[nd]=(mn[nd]==mn[ls])*num[ls]+(mn[nd]==mn[rs])*num[rs];
}
void upd(int nd,int w){mn[nd]+=w;tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
	num[nd]=(mn[nd]==mn[ls])*num[ls]+(mn[nd]==mn[rs])*num[rs];
}
int st1[maxn],tp1,st2[maxn],tp2;
int pre[maxn];
map<int,int> pos;
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	pos.clear();
	tp1=tp2=0;
	for(int i=1;i<=n;i++){
		pre[i]=pos[a[i]],pos[a[i]]=i;
		updata(1,1,n,1,pre[i],1);
		while(tp1&&a[i]<a[st1[tp1]]){
			updata(1,1,n,st1[tp1-1]+1,st1[tp1],a[st1[tp1]]-a[i]);
			tp1--;
		}
		while(tp2&&a[i]>a[st2[tp2]]){
			updata(1,1,n,st2[tp2-1]+1,st2[tp2],-a[st2[tp2]]+a[i]);
			tp2--;
		}
		st1[++tp1]=i,st2[++tp2]=i;
		ans+=num[1];
		// cout<<mn[1]<<" "<<num[1]<<"\n";
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	for(int t=1;t<=T;t++){
		printf("Case #%d: ",t);
		work();
	}
}
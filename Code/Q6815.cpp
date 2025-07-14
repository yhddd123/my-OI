#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,q,a[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int mx,sum,mxsum,ans;
}tree[maxn<<2];
int tag[maxn<<2],laz[maxn<<2];
int pos[maxn],pl[maxn<<2],pr[maxn<<2];
void add(int nd,int w){
	int len=pr[nd]-pl[nd]+1;
	tree[nd].mx+=w,tree[nd].ans+=len*w*w+tree[nd].sum*w+tree[nd].mxsum*w,tree[nd].sum+=len*w,tree[nd].mxsum+=len*w;
	if(~laz[nd])laz[nd]+=w;
	else tag[nd]+=w;
}
void cov(int nd,int w){
	int len=pr[nd]-pl[nd]+1;
	tree[nd].mx=w,tree[nd].sum=len*w,tree[nd].mxsum=len*w,tree[nd].ans=len*w*w;
	tag[nd]=0;laz[nd]=w;
}
void down(int nd){
	int l=pl[nd],r=pr[nd];
	if(l==r)return ;
	if(tag[nd])add(ls,tag[nd]),add(rs,tag[nd]),tag[nd]=0;
	if(~laz[nd])cov(ls,laz[nd]),cov(rs,laz[nd]),laz[nd]=-1;
}
int que1(int nd,int w){
	int l=pl[nd],r=pr[nd];
	if(l==r)return max(w,tree[nd].mx);
	down(nd);
	if(tree[ls].mx<=w)return w*(mid-l+1)+que1(rs,w);
	else return que1(ls,w)+tree[nd].mxsum-tree[ls].mxsum;
}
int que2(int nd,int w){
	int l=pl[nd],r=pr[nd];
	if(l==r)return max(w,tree[nd].mx)*tree[nd].mx;
	down(nd);
	if(tree[ls].mx<=w)return w*tree[ls].sum+que2(rs,w);
	else return que2(ls,w)+tree[nd].ans-tree[ls].ans;
}
void up(int nd){
	tree[nd].mx=max(tree[ls].mx,tree[rs].mx),tree[nd].sum=tree[ls].sum+tree[rs].sum;
	// cout<<pl[nd]<<" "<<pr[nd]<<" "<<que1(rs,tree[ls].mx)<<" "<<que2(rs,tree[ls].mx)<<" up\n";
	tree[nd].mxsum=tree[ls].mxsum+que1(rs,tree[ls].mx);
	tree[nd].ans=tree[ls].ans+que2(rs,tree[ls].mx);
}
void build(int nd,int l,int r){
	laz[nd]=-1;pl[nd]=l,pr[nd]=r;
	if(l==r){pos[l]=nd;tree[nd]={a[l],a[l],a[l],a[l]*a[l]};return ;}
	build(ls,l,mid),build(rs,mid+1,r);
	up(nd);
	// cout<<l<<" "<<r<<" "<<tree[nd].mx<<" "<<tree[nd].sum<<" "<<tree[nd].mxsum<<" "<<tree[nd].ans<<" \n";
}
void updata(int nd,int ql,int qr,int w,int op){
	int l=pl[nd],r=pr[nd];
	if(l>=ql&&r<=qr){
		if(op==1)add(nd,w);
		else cov(nd,w);
		return ;
	}
	down(nd);
	if(ql<=mid)updata(ls,ql,qr,w,op);
	if(qr>mid)updata(rs,ql,qr,w,op);
	up(nd);
}
int mx,sum;
int st[maxn],tp;
int ask(int p,int t){
	int nd=pos[p];
	for(int i=nd;i;i>>=1)st[++tp]=i;
	while(tp--)down(st[tp]);
	if(tree[nd].mx*max(mx,tree[nd].mx)>=t)return p-1;
	int res=p;mx=max(mx,tree[nd].mx),sum=tree[nd].mx*mx;
	while(nd!=1){
		if(nd&1)nd>>=1;
		else{
			nd>>=1;
			int tmp=que2(rs,mx);
			if(sum+tmp<t){
				res=pr[rs],mx=max(mx,tree[rs].mx),sum+=tmp;
			}
			else{
				down(nd);nd=rs;
				while(pl[nd]!=pr[nd]){
					down(nd);
					int tmp=que2(ls,mx);
					if(sum+tmp<t){
						res=pr[ls],sum+=tmp,mx=max(mx,tree[ls].mx);
						nd=rs;
					}
					else{
						nd=ls;
					}
				}
				if(sum+tree[nd].mx*max(mx,tree[nd].mx)<t){
					res=pr[nd],mx=max(mx,tree[nd].mx),sum+=tree[nd].mx*mx;
				}
				return res;
			}
		}
	}
	return res;
}
int que(int p,int t){
	mx=sum=0;int res=ask(p,t);
	if(res<n-1)return res+1;
	t-=sum,sum=0;res=ask(0,t);
	if(res<n-1)return res+1;
	t-=sum,sum=0;
	t-=t/(tree[1].mx*tree[1].sum)*(tree[1].mx*tree[1].sum);
	res=ask(0,t);return res+1;	
}
void work(){
	n=read();q=read();
	for(int i=0;i<n;i++)a[i]=read();
	build(1,0,n-1);
	for(int i=1;i<=q;i++){
		char op[3];scanf("%s",op+1);
		if(op[1]=='Q'){
			int p=read(),t=read();
			printf("%lld\n",que(p,t+1));
		}
		if(op[1]=='P'){
			int l=read(),r=read(),x=read();
			if(l<=r)updata(1,l,r,x,1);
			else updata(1,0,r,x,1),updata(1,l,n-1,x,1);
		}
		if(op[1]=='R'){
			int l=read(),r=read(),x=read();
			if(l<=r)updata(1,l,r,x,2);
			else updata(1,0,r,x,2),updata(1,l,n-1,x,2);
		}
	}
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}

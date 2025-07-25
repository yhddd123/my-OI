#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=50010;
const int inf=1e9;

int n,m;
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
int num[maxn<<6],suml[maxn<<6],sumr[maxn<<6];
int lc[maxn<<6],rc[maxn<<6],idx,rt[maxn];
void updata(int &nd,int l,int r,int p,int wl,int wr){
    int lst=nd;nd=++idx;ls=lc[lst],rs=rc[lst];
    num[nd]=num[lst]+1,suml[nd]=suml[lst]+wl,sumr[nd]=sumr[lst]+wr;
    if(l==r)return ;
    if(p<=mid)updata(ls,l,mid,p,wl,wr);
    else updata(rs,mid+1,r,p,wl,wr);
}
int quenum(int nd,int nd1,int l,int r,int ql,int qr){
	if(num[nd]==num[nd1]||ql>qr)return 0;
	if(ql>qr)return 0;
    if(l>=ql&&r<=qr)return num[nd]-num[nd1];
    if(qr<=mid)return quenum(ls,lc[nd1],l,mid,ql,qr);
    if(ql>mid)return quenum(rs,rc[nd1],mid+1,r,ql,qr);
    return quenum(ls,lc[nd1],l,mid,ql,qr)+quenum(rs,rc[nd1],mid+1,r,ql,qr);
}
int quesl(int nd,int nd1,int l,int r,int ql,int qr){
	if(num[nd]==num[nd1]||ql>qr)return 0;
    if(l>=ql&&r<=qr)return suml[nd]-suml[nd1];
    if(qr<=mid)return quesl(ls,lc[nd1],l,mid,ql,qr);
    if(ql>mid)return quesl(rs,rc[nd1],mid+1,r,ql,qr);
    return quesl(ls,lc[nd1],l,mid,ql,qr)+quesl(rs,rc[nd1],mid+1,r,ql,qr);
}
int quesr(int nd,int nd1,int l,int r,int ql,int qr){
	if(num[nd]==num[nd1]||ql>qr)return 0;
    if(l>=ql&&r<=qr)return sumr[nd]-sumr[nd1];
    if(qr<=mid)return quesr(ls,lc[nd1],l,mid,ql,qr);
    if(ql>mid)return quesr(rs,rc[nd1],mid+1,r,ql,qr);
    return quesr(ls,lc[nd1],l,mid,ql,qr)+quesr(rs,rc[nd1],mid+1,r,ql,qr);
}
int quenum(int l,int r,int pl,int pr){return quenum(rt[r],rt[l-1],1,n,pl,pr);}
int quesl(int l,int r,int pl,int pr){return quesl(rt[r],rt[l-1],1,n,pl,pr);}
int quesr(int l,int r,int pl,int pr){return quesr(rt[r],rt[l-1],1,n,pl,pr);}
int que(int l,int r){
    int ans=quenum(1,l,r,n);
    ans+=quenum(l,r,l,r)*(-l+r)+quesl(l,r,l,r)-quesr(l,r,l,r);
    ans+=quenum(1,l-1,l,mid)*(-l)+quesr(1,l-1,l,mid);
    ans+=quenum(1,l-1,mid+1,r)*r-quesr(1,l-1,mid+1,r);
    ans+=quenum(l,mid,r+1,n)*(-l)+quesl(l,mid,r+1,n);
    ans+=quenum(mid+1,r,r+1,n)*r-quesl(mid+1,r,r+1,n);
    return ans;
}
vector<int> upd[maxn];
int dp[maxn];
int calc(int j,int i){return dp[j]+que(j,i);}
struct node{
	int p,l,r;
}q[maxn];int h,t;
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++)upd[read()].pb(read());
    for(int i=1;i<=n;i++){
        rt[i]=rt[i-1];
        for(int j:upd[i])updata(rt[i],1,n,j,i,j);
    }
    dp[1]=0;q[h=t=1]={1,2,n};
    for(int i=2;i<=n;i++){
    	dp[i]=calc(q[h].p,i);
    	// cout<<i<<" "<<q[h].p<<" "<<dp[i]<<"\n";
    	if((++q[h].l)>q[h].r)h++;
    	while(h<=t){
    		if(calc(q[t].p,q[t].l)<=calc(i,q[t].l))break;
    		t--;
    	}
    	if(h>t)q[++t]={i,i+1,n};
    	else{
    		auto[p,l,r]=q[t];int res=r+1;
    		while(l<=r){
				if(calc(p,mid)<=calc(i,mid))l=mid+1;
				else res=mid,r=mid-1;
    		}
    		if(res<=n)q[t].r=res-1,q[++t]={i,res,n};
    	}
    }
    printf("%lld\n",dp[n]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}
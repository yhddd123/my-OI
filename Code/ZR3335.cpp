#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0;char c=getchar();while(c<'0'||c>'9'){c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x;}
inline void write(long long x){static char buf[20];static int n=-1;if(x<0)putchar('-'),x=-x;do buf[++n]=x%10,x/=10;while(x);while(n>=0)putchar(buf[n--]+48);}
const int maxn=500010;
const int inf=2e9+1;
bool mbe;

int n,q;
pii a[maxn];
int id[maxn],rnk[maxn];
int lsh[maxn];
vector<pii> ask[maxn];
int mx[maxn];
int f[2000010];
int *val[maxn],*lst=f;
// vector<int> val[maxn];
pii st1[maxn],st2[maxn];int tp1,tp2;
int tmp[maxn],tmp1[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct sgt{
	int pos[maxn];
    pii mn[maxn<<2];
    void build(int nd,int l,int r){
        mn[nd]={inf,l};
        if(l==r){pos[l]=nd;return ;}
        build(ls,l,mid),build(rs,mid+1,r);
    }
    void modif(int p,int w,int op){
    	int nd=pos[p];
        if(op)mn[nd]={w,p};
        else mn[nd]={inf,p};
        nd>>=1;
        while(nd)mn[nd]=min(mn[ls],mn[rs]),nd>>=1;
    }
    pii query(int nd,int l,int r,int ql,int qr){
        if(ql>qr)return {inf,0};
        if(l>=ql&&r<=qr)return mn[nd];
        if(qr<=mid)return query(ls,l,mid,ql,qr);
        if(ql>mid)return query(rs,mid+1,r,ql,qr);
        return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
    }
}t1,t2;
pii que[maxn];
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++){
        int x=read(),y=read();
        a[i]={x+y,x-y};
        lsh[i]=a[i].se;
    }
    sort(lsh+1,lsh+n+1);
    for(int i=1;i<=n;i++)a[i].se=lower_bound(lsh+1,lsh+n+1,a[i].se)-lsh,lsh[a[i].se]--;
    for(int i=1;i<=n;i++)id[i]=i;
    sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
    for(int i=1;i<=n;i++)rnk[id[i]]=i;
    sort(a+1,a+n+1);
    for(int i=1;i<=q;i++){
        int u=read(),k=read();u=rnk[u];
        que[i]={u,k};
        mx[u]=max(mx[u],k);
    }
    for(int i=1;i<=n;i++){
    	val[i]=lst,lst+=mx[i];
    	for(int j=0;j<mx[i];j++)val[i][j]=inf;
    	// val[i].resize(mx[i],inf);
    }
    // for(int i=1;i<=n;i++)cout<<a[i].fi<<" "<<lsh[a[i].se]<<"\n";
    t1.build(1,1,n),t2.build(1,1,n);
    for(int i=1;i<=n;i++){
		tp1=tp2=0;
        pii up=t1.query(1,1,n,a[i].se,n),dw=t2.query(1,1,n,1,a[i].se-1);
        // cout<<up.fi<<" "<<dw.fi<<"\n";
        int val1=up.fi+a[i].fi-lsh[a[i].se],val2=dw.fi+a[i].fi+lsh[a[i].se];
        for(int j=1;j<=mx[i]&&j<i;j++){
            if(up.fi!=inf&&(val1<val2||dw.fi==inf)){
                tmp[j]=val1;
                t1.modif(up.se,up.fi,0);
                st1[++tp1]=up;up=t1.query(1,1,n,a[i].se,n);
                val1=up.fi+a[i].fi-lsh[a[i].se];
            }
            else{
                tmp[j]=val2;
                t2.modif(dw.se,dw.fi,0);
                st2[++tp2]=dw;dw=t2.query(1,1,n,1,a[i].se-1);
                val2=dw.fi+a[i].fi+lsh[a[i].se];
            }
        }
        // for(int j=1;j<=mx;j++)cout<<tmp[j]<<" ";cout<<"\n";
        for(int j=1;j<=mx[i]&&j<i;j++)val[i][j-1]=tmp[j];
        if(i==n)break;
        for(int j=1;j<=tp1;j++)t1.modif(st1[j].se,st1[j].fi,1);
        for(int j=1;j<=tp2;j++)t2.modif(st2[j].se,st2[j].fi,1);
        t1.modif(a[i].se,-a[i].fi+lsh[a[i].se],1);
        t2.modif(a[i].se,-a[i].fi-lsh[a[i].se],1);
        // cout<<i<<" "<<-a[i].fi+lsh[a[i].se]<<" "<<-a[i].fi-lsh[a[i].se]<<"\n";
    }
    t1.build(1,1,n),t2.build(1,1,n);
    for(int i=n;i;i--){
        tp1=tp2=0;
        pii up=t1.query(1,1,n,a[i].se,n),dw=t2.query(1,1,n,1,a[i].se-1);
        int val1=up.fi-a[i].fi-lsh[a[i].se],val2=dw.fi-a[i].fi+lsh[a[i].se];
        for(int j=1;j<=mx[i]&&j<=n-i;j++){
            if(up.fi!=inf&&(val1<val2||dw.fi==inf)){
                tmp[j]=val1;
                t1.modif(up.se,up.fi,0);
                st1[++tp1]=up;up=t1.query(1,1,n,a[i].se,n);
                val1=up.fi-a[i].fi-lsh[a[i].se];
            }
            else{
                tmp[j]=val2;
                t2.modif(dw.se,dw.fi,0);
                st2[++tp2]=dw;dw=t2.query(1,1,n,1,a[i].se-1);
                val2=dw.fi-a[i].fi+lsh[a[i].se];
            }
        }
        // for(int j=1;j<=mx[i];j++)cout<<tmp[j]<<" ";cout<<"\n";
        for(int j=1;j<=mx[i]&&j<i;j++)tmp1[j]=val[i][j-1];
        int p=1,q=1;
        // assert(val[i].size()<=mx[i]);
        for(int j=0;j<mx[i];j++){
        	if(p<=min(i-1,mx[i])&&q<=min(mx[i],n-i)){
        		if(tmp1[p]<tmp[q])val[i][j]=tmp1[p++];
        		else val[i][j]=tmp[q++];
        	}
        	else if(p<=min(i-1,mx[i]))val[i][j]=tmp1[p++];
        	else val[i][j]=tmp[q++];
        	// cout<<i<<" "<<p<<" "<<q<<endl;
        }
        if(i==1)break;
        for(int j=1;j<=tp1;j++)t1.modif(st1[j].se,st1[j].fi,1);
        for(int j=1;j<=tp2;j++)t2.modif(st2[j].se,st2[j].fi,1);
        t1.modif(a[i].se,a[i].fi+lsh[a[i].se],1);
        t2.modif(a[i].se,a[i].fi-lsh[a[i].se],1);
    }
    for(int i=1;i<=q;i++){
        auto[u,k]=que[i];
        long long ans=0;for(int j=0;j<k;j++)ans+=val[u][j];
        write(ans/2),puts("");
    }
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}
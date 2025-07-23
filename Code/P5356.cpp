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
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=110000;
const int B=4000;
const int maxm=maxn/B+5;
const int inf=2e9;
bool mbe;

int n,q,sum;
int tag[maxm];
pii a[maxn],tmp1[maxn],tmp2[maxn];int p;
int pl[maxm],pr[maxm];
void upd(int l,int r,int k){
    if(l/B==r/B){
        int p1=0,p2=0;
        for(int i=pl[l/B];i<=pr[l/B];i++){
            if(l<=a[i].se&&a[i].se<=r)tmp1[++p1]=a[i],tmp1[p1].fi+=k;
            else tmp2[++p2]=a[i];
        }
        p=pl[l/B];
        int u=1,v=1;
        while(u<=p1&&v<=p2){
            if(tmp1[u]<tmp2[v])a[p++]=tmp1[u++];
            else a[p++]=tmp2[v++];
        }
        while(u<=p1)a[p++]=tmp1[u++];
        while(v<=p2)a[p++]=tmp2[v++];
        return ;
    }
    else{
        upd(l,pr[l/B],k),upd(pl[r/B],r,k);
        for(int i=l/B+1;i<r/B;i++)tag[i]+=k;
    }
}
int que(int l,int r,int k){
    int res=0;
	int ll=n+1,rr=p,vv=ll-1;
    while(ll<=rr){
        int mid=ll+rr>>1;
        if(a[mid].fi<=k)vv=mid,ll=mid+1;
        else rr=mid-1;
    }
    res+=vv-n;
    for(int i=l/B+1;i<r/B;i++){
    	k-=tag[i];
        int ll=pl[i],rr=pr[i],vv=ll-1;
        while(ll<=rr){
            int mid=ll+rr>>1;
            if(a[mid].fi<=k)vv=mid,ll=mid+1;
            else rr=mid-1;
        }
        res+=vv-pl[i]+1;
    	k+=tag[i];
    }
    return res;
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++)a[i]={read(),i};
    for(int i=0;i<=n/B;i++){
    	pl[i]=max(1,i*B),pr[i]=min(n,(i+1)*B-1);
    	sort(a+pl[i],a+pr[i]+1);
    }
    while(q--){
        int op=read(),l=read(),r=read(),k=read();
        if(op==1){
            if(k>r-l+1)puts("-1");
            else{
            	if(l/B!=r/B){
            		int p1=0,p2=0;
            		for(int i=pl[l/B];i<=pr[l/B];i++)if(a[i].se>=l)tmp1[++p1]=a[i],tmp1[p1].fi+=tag[l/B];
            		for(int i=pl[r/B];i<=pr[r/B];i++)if(a[i].se<=r)tmp2[++p2]=a[i],tmp2[p2].fi+=tag[r/B];
            		p=n;
            		int u=1,v=1;
			        while(u<=p1&&v<=p2){
			            if(tmp1[u]<tmp2[v])a[++p]=tmp1[u++];
			            else a[++p]=tmp2[v++];
			        }
			        while(u<=p1)a[++p]=tmp1[u++];
			        while(v<=p2)a[++p]=tmp2[v++];
            	}
            	else{
            		p=n;
            		for(int i=pl[l/B];i<=pr[l/B];i++)if(l<=a[i].se&&a[i].se<=r)a[++p]=a[i],a[p].fi+=tag[l/B];
            	}
            	// for(int i=n+1;i<=p;i++)cout<<a[i].fi<<" ";cout<<"\n";
                int ll=-inf,rr=inf,res=-inf;
                while(ll<=rr){
                    int mid=(long long)ll+rr>>1ll;
                    if(que(l,r,mid)<k)res=mid+1,ll=mid+1;
                    else rr=mid-1;
                }
                write(res),puts("");
            }
        }
        else upd(l,r,k);
    }
}
bool med;

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}
#include <algorithm>
#include<bits/stdc++.h>
#define int long long
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
const int maxn=2100;
const int maxm=11;
const int inf=1e9;

int n,m,k,l,d,s[maxm];
struct mat{
    int e[maxm][maxm];
    mat(){memset(e,0,sizeof(e));}
    mat operator*(const mat&tmp)const{
        mat res;
        for(int i=0;i<=m;i++){
            for(int k=i;k<=m;k++){
                for(int j=k;j<=m;j++)(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
            }
        }
        return res;
    }
}a[maxn];
mat one(){mat res;for(int i=0;i<=m;i++)res.e[i][i]=1;return res;}
mat ksm(mat a,int b){
    mat ans=one();
    while(b){
        if(b&1)ans=ans*a;
        a=a*a;
        b>>=1;
    }
    return ans;
}
int num[maxn];
void exgcd(int a,int b,int &x,int &y){
    if(!b){x=1,y=0;return ;}
    exgcd(b,a%b,y,x);
    y-=a/b*x;
}
int ni(int v,int p){
    int x,y;exgcd(v,p,x,y);
    return (x%p+p)%p;
}
int lsh[maxn],len;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
mat tree[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
    tree[nd]=tag[nd]=one();
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,mat w){tree[nd]=tree[nd]*w,tag[nd]=tag[nd]*w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=one();}
void updata(int nd,int l,int r,int ql,int qr,mat w){
    if(ql>qr)return ;
    if(l>=ql&&r<=qr)return upd(nd,w);
    down(nd);
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
    tree[nd]=tree[ls]*tree[rs];
}
void down(int nd,int l,int r){
    if(l==r){a[l]=tree[nd];return ;}
    down(nd);
    down(ls,l,mid),down(rs,mid+1,r);
}
void sovle(int l,int d){
    // cout<<l<<" "<<d<<endl;
    // cout<<n<<"\n";
    // for(int i=1;i<=n;i++)cout<<num[i]<<" ";cout<<"\n";
    if(l==1)return ;
    if(2*d>l){
        if(num[1]>1){
            for(int i=n;i;i--)a[i+1]=a[i],num[i+1]=num[i];n++;
            num[1]=1,num[2]--;
        }
        reverse(a+2,a+n+1),reverse(num+2,num+n+1);
        sovle(l,l-d);
    }
    else{
        lsh[len=1]=0;for(int i=1,sum=0;i<=n;i++)(sum+=num[i])%=d,lsh[++len]=sum;lsh[++len]=d;
        sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
        build(1,1,len-1);
        for(int i=1,sum=0;i<=n;i++){
            int l=lower_bound(lsh+1,lsh+len+1,sum%d)-lsh;
            int r=lower_bound(lsh+1,lsh+len+1,(sum+num[i])%d)-lsh;
            if(sum+num[i]<d){
                updata(1,1,len-1,l,r-1,a[i]);
            }
            else{
                updata(1,1,len-1,l,len-1,a[i]);
                int tim=(sum+num[i])/d-1;
                mat aa=ksm(a[i],tim);
                upd(1,aa);
                updata(1,1,len-1,1,r-1,a[i]);
            }
            (sum+=num[i])%=d;
        }
        down(1,1,len-1);
        for(int i=1;i<len;i++)num[i]=lsh[i+1]-lsh[i];
        n=len-1;
        return sovle(d,d-l%d);
    }
}
void work(){
    n=read();m=read();k=read();l=read();d=ni(k,l);
    for(int i=1;i<=m;i++)s[i]=read();
    for(int i=1;i<=n;i++){
        int l=read(),v=read();
        num[i]=l;a[i]=one();
        for(int j=1;j<=m;j++)if(v==s[j])a[i].e[j-1][j]=1;
    }
    sovle(l,d);
    printf("%lld\n",a[1].e[0][m]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}
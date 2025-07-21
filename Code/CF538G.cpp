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
const int maxn=200010;
const int inf=1e9;

int n,m;
struct node{
    int t,k,x,y;
}a[maxn];
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        int t=read(),u=read(),v=read();
        if((t+u+v)&1){puts("NO");return ;}
        a[i]={t%m,t/m,(t+u+v)/2,(t+v-u)/2};
    }
    a[++n]={0,0,0,0};a[++n]={m,-1,0,0};
    sort(a+1,a+n+1,[&](node u,node v){return u.t<v.t;});
    // for(int i=1;i<=n;i++)cout<<a[i].t<<" "<<a[i].k<<" "<<a[i].x<<" "<<a[i].y<<"\n";
    int lx=0,rx=m,ly=0,ry=m;
    for(int i=2;i<=n;i++){
        int tt=a[i].t-a[i-1].t,kk=a[i].k-a[i-1].k,xx=a[i].x-a[i-1].x,yy=a[i].y-a[i-1].y;
        if(!kk){
            if(!(xx>=0&&xx-tt<=0)){puts("NO");return ;}
            if(!(yy>=0&&yy-tt<=0)){puts("NO");return ;}
        }
        else if(kk>0){
            lx=max(lx,(xx-tt+kk-1)/kk);
            rx=min(rx,xx/kk);
            ly=max(ly,(yy-tt+kk-1)/kk);
            ry=min(ry,yy/kk);
        }
        else if(kk<0){
            kk=-kk;
            lx=max(lx,(-xx+kk-1)/kk);
            rx=min(rx,(-xx+tt)/kk);
            ly=max(ly,(-yy+kk-1)/kk);
            ry=min(ry,(-yy+tt)/kk);
        }
    }
    // cout<<lx<<" "<<rx<<" "<<ly<<" "<<ry<<"\n";
    if(lx>rx||ly>ry){puts("NO");return ;}
    int x=0,y=0;
    for(int i=2;i<=n;i++){
        int xx=a[i].x-a[i].k*lx,yy=a[i].y-a[i].k*ly;
        for(int j=1;j<=a[i].t-a[i-1].t;j++){
            if(x<xx&&y<yy)putchar('U'),x++,y++;
            else if(x<xx)putchar('R'),x++;
            else if(y<yy)putchar('L'),y++;
            else putchar('D');
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}
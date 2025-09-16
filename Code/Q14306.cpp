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
bool mbe;

int n=30,x,y,a[35][35];
void col(int u,int v){
    cout<<u<<" "<<v<<endl;
    a[u][v]=1;
    x=read(),y=read();
    if(!x&&!y)exit(0);
}
#define d(a,b,c,d) abs(a-b)+abs(c-d)
int num1,num2;
void mov(){
    if(x>=28){
        if(!a[30][y])return col(30,y);
        if(!a[30][y-1]&&!a[30][y-2])return col(30,y-1);
        if(!a[30][y+1]&&!a[30][y+2])return col(30,y+1);
        if(!a[30][y-1])return col(30,y-1);
        if(!a[30][y+1])return col(30,y+1);
    }
    if(y>=28){
        if(!a[x][30])return col(x,30);
        if(!a[x-1][30]&&!a[x-2][30])return col(x-1,30);
        if(!a[x+1][30]&&!a[x+2][30])return col(x+1,30);
        if(!a[x-1][30])return col(x-1,30);
        if(!a[x+1][30])return col(x+1,30);
    }
    int mn=60;
    for(int j=2;j<=30;j+=2)if(!a[30][j])mn=min(mn,d(x,30,y,j));
    for(int j=2;j<=30;j+=2)if(!a[j][30])mn=min(mn,d(x,j,y,30));
    // cout<<mn<<" "<<num1<<" "<<num2<<"\n";
    if(num1>num2){
        for(int j=2;j<=30;j+=2)if(!a[j][30]&&mn==d(x,j,y,30)){col(j,30),++num2;return;}
    }
    for(int j=2;j<=30;j+=2)if(!a[30][j]&&mn==d(x,30,y,j)){col(30,j),++num1;return;}
    for(int j=2;j<=30;j+=2)if(!a[j][30]&&mn==d(x,j,y,30)){col(j,30),++num2;return;}
    for(int j=1;j<=30;j+=2)if(!a[30][j]){col(30,j);return;}
    for(int j=1;j<=30;j+=2)if(!a[j][30]){col(j,30);return;}
}
void work(){
    x=read();y=read();
    col(28,30),col(29,30),col(30,30),col(30,29),col(30,28);
    for(int i=6;i<=59;i++)mov();
    int l1=1,r1=29,l2=1,r2=29;
    while(l1<=r1&&l2<=r2){
        if(l1-r1>=l2-r2){
            int mid=l1+r1>>1;
            for(int j=l2;j<=r2;j++)col(mid,j);
            if(x<mid)r1=mid-1;
            else l1=mid+1;
        }
        else{
            int mid=l2+r2>>1;
            for(int j=l1;j<=r1;j++)col(j,mid);
            if(y<mid)r2=mid-1;
            else l2=mid+1;
        }
    }
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
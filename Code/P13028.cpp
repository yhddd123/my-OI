#include<bits/stdc++.h>
#include <cstdio>
#include <iostream>
#define ll __int128
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
inline void write(ll x){static char buf[40];static int len=-1;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=125;

int n,m;
char a[maxn],b[maxn],c[maxn];
int va,vb,vc;
ll C[maxn][maxn];
ll val[16];
ll gcd(ll a,ll b) {
    return b==0?a:gcd(b, a%b);
}
void work(){
    n=read();m=read();
    if(n==1){
        scanf("%s",a+1);va=read();
        if(va<=m/2){
            for(int i=1;i<=m;i++){
                if(a[i]=='F')a[i]='T';
                else a[i]='F';
            }
            va=m-va;
        }
        for(int i=1;i<=m;i++)cout<<a[i];cout<<" "<<va<<"/1"<<"\n";
    }
    if(n==2){
        scanf("%s",a+1);va=read();
        scanf("%s",b+1);vb=read();
        if(va<vb)swap(a,b),swap(va,vb);
        int num=0;for(int i=1;i<=m;i++)if(a[i]==b[i])++num;
        int cnt=(va+vb-m+num)/2,lst=va-cnt;
        if(cnt<=num/2){
            for(int i=1;i<=m;i++)if(a[i]==b[i]){
                if(a[i]=='F')a[i]='T';
                else a[i]='F';
            }
            cnt=num-cnt;
        }
        for(int i=1;i<=m;i++)cout<<a[i];cout<<" "<<cnt+lst<<"/1"<<"\n";
    }
    if(n==3){
        scanf("%s",a+1);va=read();
        scanf("%s",b+1);vb=read();
        scanf("%s",c+1);vc=read();
        int num=0,num1=0,num2=0,num3=0;
        for(int i=1;i<=m;i++){
            if(a[i]==b[i]&&a[i]==c[i])++num;
            else if(b[i]==c[i])++num1;
            else if(a[i]==c[i])++num2;
            else ++num3;
        }
        for(int s=0;s<16;s++)val[s]=0;ll tot=0;
        // cout<<num<<" "<<num1<<" "<<num2<<" "<<num3<<"\n";
        for(int w=0;w<=min({num,va,vb,vc});w++){
            va-=w+num1,vb-=w+num2,vc-=w+num3;
            int sum=va+vb+vc;
            int x=(sum-va)/2,y=(sum-vb)/2,z=(sum-vc)/2;
            va+=w+num1,vb+=w+num2,vc+=w+num3;
            if(x>=0&&x<=num1&&y>=0&&y<=num2&&z>=0&&z<=num3&&va==w+num1-x+y+z&&vb==w+num2-y+x+z&&vc==w+num3-z+x+y){
                // cout<<w<<" "<<x<<" "<<y<<" "<<z<<"\n";
                ll cnt=C[num][w]*C[num1][x]*C[num2][y]*C[num3][z];tot+=cnt;
                for(int s=0;s<16;s++){
                    val[s]+=(ll)(((s&1)?num-w:w)+((s&2)?num1-x:x)+((s&4)?num2-y:y)+((s&8)?num3-z:z))*cnt;
                }
            }
        }
        pair<ll,int> mx={0,0};
        for(int s=0;s<16;s++)mx=max(mx,{val[s],s});
        for(int i=1;i<=m;i++){
            if(a[i]==b[i]&&a[i]==c[i]){
                if(mx.se&1){
                    if(a[i]=='F')a[i]='T';
                    else a[i]='F';
                }
            }
            else if(b[i]==c[i]){
                if(mx.se&2){
                    if(b[i]=='F')a[i]='T';
                    else a[i]='F';
                }
                else a[i]=b[i];
            }
            else if(a[i]==c[i]){
                if(mx.se&4){
                    if(a[i]=='F')a[i]='T';
                    else a[i]='F';
                }
            }
            else{
                if(mx.se&8){
                    if(a[i]=='F')a[i]='T';
                    else a[i]='F';
                }
            }
        }
        // write(mx.fi);puts("");write(tot);puts("");
        ll g=gcd(mx.fi,tot);
        mx.fi/=g,tot/=g;
        for(int i=1;i<=m;i++)cout<<a[i];cout<<" ";write(mx.fi);cout<<"/";write(tot);cout<<"\n";
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    for(int i=0;i<maxn;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    T=read();
    for(int t=1;t<=T;t++){
        cout<<"Case #"<<t<<": ";
        work();
    }
}
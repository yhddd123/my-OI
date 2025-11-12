#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=110;
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
int a,b,c,x,y,z,ans;
int C[maxn][maxn];
int calc(int a,int b,int x,int y){return a*b%mod*(ksm(a,y/b-1)+ksm(b,x/a-1)-1)%mod;}
void work(){
	a=read(),b=read(),c=read(),x=read(),y=read(),z=read();
	if(x%a||y%b||z%c){puts("0");return ;}
	(ans+=a*ksm(calc(b,c,y,z),x/a)+b*ksm(calc(a,c,x,z),y/b)+c*ksm(calc(a,b,x,y),z/c))%=mod;
	(ans+=3*mod-a*b%mod*ksm(c,x/a*y/b)%mod-a*c%mod*ksm(b,x/a*z/c)%mod-b*c%mod*ksm(a,y/b*z/c)%mod)%=mod;
	(ans+=a*b*c)%=mod;
	for(int i=0;i<=maxn-10;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=1;i<x/a;i++){
		for(int j=1;j<y/b;j++){
			int res=0;for(int k=0;k<=x/a-i;k++)(res+=((k&1)?mod-1:1)*C[x/a-i][k]%mod*ksm(ksm(c,x/a-i-k)-1,y/b-j))%=mod;
			int coef=C[x/a][i]*C[y/b][j]%mod*a*b*c%mod*res%mod;
			// cout<<i<<" "<<j<<" "<<res<<" "<<coef<<"\n";
			(ans+=coef*(ksm(ksm(b,i)+ksm(a,j)-1,z/c)+2*mod-ksm(b,i*z/c)-ksm(a,j*z/c)+1))%=mod;
		}
	}
	printf("%lld\n",ans);
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
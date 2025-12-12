#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=5010;
const int inf=1e9;

int n,m,ans;pii a[maxn<<1];
int C[maxn][maxn],pw[maxn];
int suf[maxn<<1];
inline bool cmp(pii u,pii v){
	if(u.fi!=v.fi)return u.fi>v.fi;
	if((u.se&1)!=(v.se&1))return (u.se&1)>(v.se&1);
	return u.se<v.se;
}
inline bool cmp1(int u1,int u2,int v1,int v2){
	if(u1!=v1)return u1>v1;
	if((u2&1)!=(v2&1))return (u2&1)>(v2&1);
	return u2<v2;
}
bool odd[maxn<<1];
void work(){
	n=read();m=read();ans=0;
	for(int i=1;i<=n;i++){
		int x=read();
		a[i]={2*x,2*i};a[i+n]={x,2*i+1};
	}a[2*n+1]={0,0};
	sort(a+1,a+2*n+1,cmp);
	// for(int i=1;i<=2*n;i++)cout<<a[i].fi<<" "<<a[i].se<<"\n";
	suf[2*n+1]=0;for(int i=2*n;i;i--)suf[i]=suf[i+1]+(!(a[i].se&1));
	for(int i=1;i<=2*n;i++)odd[i]=a[i].se&1;
	for(int i=1,n1=0,n2=0;i<=2*n;i++){
		if(!odd[i]){
			int num1=n1,num2=n2;
			for(int j=i+1,k=i+1;j<=2*n;j++){
				if(odd[j]){
					if(a[i].fi==a[j].fi*2&&a[i].se==(a[j].se^1))continue;
					while(k<=2*n&&(odd[k]||a[i].fi+a[k].fi>=a[j].fi*2)){
						k++;
					}
					if(k==2*n+1&&a[i].fi+a[k].fi>=a[j].fi*2)break;
					// cout<<a[i].fi<<" "<<a[k].fi<<" "<<a[j].fi*2<<"\n";
					bool fl=cmp1(a[j].fi*2,a[j].se^1,a[i].fi,a[i].se);
					fl&&num2--;
					(m-2-num1<=num2)&&((ans+=C[num2][m-2-num1]*(pw[suf[k]]-(a[i].fi==2*a[j].fi)))%=mod,0);
					// cout<<i<<" "<<j<<" "<<k<<" "<<num1<<" "<<num2<<" "<<suf[k]<<" "<<ans<<"\n";
					fl?(num1++,num2++):(num1+=2);
					if(num1>m-2)break;
				}
			}
		}
		if(!(a[i].se&1))n2++;
		else n1++;
	}
	ans=(pw[n]+mod-ans)%mod;
	printf("%lld\n",ans);
}


int T;
signed main(){
	// freopen("sale.in","r",stdin);
	// freopen("sale.out","w",stdout);
	
	n=5000;
	for(int i=0;i<=n;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	
	read();T=read();
	while(T--)work();
}
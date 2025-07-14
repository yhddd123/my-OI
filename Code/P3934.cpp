#include<iostream>
#define int long long
using namespace std;
const int maxn=500010;
const int maxm=20000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int tree[maxn];
int lowbit(int x){return x&(-x);}
void updata(int x,int w){
	while(x<=n){
		tree[x]+=w;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}
inline int ksm(int a,int b,int mod){
	if(a>=mod)a%=mod,a+=mod;
	int ans=1;
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		if(ans>=mod)ans%=mod,ans+=mod;
		if(a>=mod)a%=mod,a+=mod;
		b>>=1;
	}
	return ans;
}
int pre[maxm],cnt;
bool vis[maxm];
int ph[maxm];
void sovle(int n){
	ph[1]=1;
	for(int i=2;i<=n;++i){
		if(!vis[i]){
			pre[++cnt]=i;
			ph[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*pre[j]<=n;++j){
			vis[i*pre[j]]=1;
			if(i%pre[j]==0){
				ph[i*pre[j]]=ph[i]*pre[j];
				break;
			}
			ph[i*pre[j]]=ph[i]*(pre[j]-1);
		}
	}
}
int s(int l,int r,int mod){
	if(l>r||mod==1)return 1;
	return ksm(query(l),s(l+1,r,ph[mod]),mod);
}
int opt,u,v,p;

signed main(){
	sovle(maxm-10);
	n=read();m=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		updata(i,a[i]-a[i-1]);
	}
	for(int i=1;i<=m;++i){
		opt=read();u=read();v=read();p=read();
		if(opt==1){
			updata(u,p);
			updata(v+1,-p);
		}
		else{
			printf("%lld\n",s(u,v,p)%p);
		}
	}
}

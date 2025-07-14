#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,k,val,ans,cur;
int p,r;
struct nd{
	int e[2][2];
	nd operator * (const nd &u) const{
		nd nw;
		for(int i=0;i<=1;i++){
			for(int j=0;j<=1;j++){
				nw.e[i][j]=0;
				for(int k=0;k<=1;k++)nw.e[i][j]+=e[i][k]*u.e[k][j];
			}
		}
		return nw;
	}
	nd operator % (const int&x){
		nd nw;
		for(int i=0;i<=1;i++){
			for(int j=0;j<=1;j++)nw.e[i][j]=e[i][j]%x;
		}
		return nw;
	}
};
nd ksm(nd a,int b,int p){
	nd ans;
	ans.e[0][0]=1;ans.e[0][1]=0;
	ans.e[1][0]=0;ans.e[1][1]=1;
	if(b<0)return ans;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		n=read();k=read();
		if(n==k){
			printf("0\n");
			continue;
		}
		nd a,m;
		a.e[0][0]=0;a.e[0][1]=1;
		a.e[1][0]=1;a.e[1][1]=1;
		m.e[0][0]=0;m.e[0][1]=0;
		m.e[1][0]=1;m.e[1][1]=0;
		p=n/k;r=n%k;
		nd res;
		res=ksm(a,k-1,mod)*m%mod;
		cur=res.e[1][0];
		if(p&1){
			res=ksm(a,k-r-1,mod)*m%mod;
			val=res.e[1][0];
			//val=f[k-r];
//			cout<<val<<"\n";
			if((k*(p+1)/2+k-r-1)&1)ans=(-val+mod+cur)%mod;
			else ans=val;
		}
		else{
			res=ksm(a,r-1,mod)*m%mod;
			val=res.e[1][0];
			//val=f[r];
//			cout<<val<<"\n";
			if((k*p/2)&1)ans=(-val+mod+cur)%mod;
			else ans=val;
		}
		printf("%lld\n",ans%mod);
	}
}

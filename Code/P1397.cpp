#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;

int n,m,a,b,c,d;
string inn,inm;
int num;
struct nd{
	int e[2][2];
	nd operator *(const nd&u)const{
		nd nw;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				nw.e[i][j]=0;
				for(int k=0;k<2;k++){
					nw.e[i][j]+=e[i][k]*u.e[k][j]%mod;
					nw.e[i][j]%=mod;
				}
			}
		}
		return nw;
	}
	nd operator %(const int&x)const{
		nd nw;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				nw.e[i][j]=e[i][j]%x;
			}
		}
		return nw;
	}
}x,y,z,w;
inline nd ksm(nd a,int b){
	nd ans;
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			if(i==j)ans.e[i][j]=1;
			else ans.e[i][j]=0;
		}
	}
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

signed main(){
	cin>>inn>>inm>>a>>b>>c>>d;
	for(int i=0;i<inn.size();i++){
		n=(n<<1)+(n<<3)+(inn[i]-'0');
		if(a==1)n%=mod;
		else n%=(mod-1);
	}
	for(int i=0;i<inm.size();i++){
		m=(m<<1)+(m<<3)+(inm[i]-'0');
		if(a==1)m%=mod;
		else m%=(mod-1);
	}
	x.e[0][0]=1;x.e[0][1]=1;
	x.e[1][0]=0;x.e[1][1]=0;
	y.e[0][0]=a;y.e[0][1]=0;
	y.e[1][0]=b;y.e[1][1]=1;
	z.e[0][0]=c;z.e[0][1]=0;
	z.e[1][0]=d;z.e[1][1]=1;
	x=x*ksm(ksm(y,m-1)*z%mod,n-1)%mod*ksm(y,m-1)%mod;
	printf("%lld\n",x.e[0][0]);
}
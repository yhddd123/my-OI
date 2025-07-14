#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100010;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x*fl;
}

int n,a[5],ans;
int vis[maxn];

signed main(){
//	freopen("lock.in","r",stdin);
//	freopen("lock.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<5;j++)a[j]=read();
		for(int j=0;j<5;j++){
			for(int k=0;k<10;k++){
				if(k==a[j])continue;
				int mul=0;
				for(int l=0;l<5;l++){
					if(l==j)mul*=10,mul+=k;
					else mul*=10,mul+=a[l];
				}
				vis[mul]++;
				// cout<<mul<<"\n";
			}
		}
		for(int j=0;j<4;j++){
			for(int k=1;k<10;k++){
				int mul=0;
				for(int l=0;l<5;l++){
					if(l==j)mul*=10,mul+=(a[j]+k)%10;
					else if(l==j+1)mul*=10,mul+=(a[j+1]+k)%10;
					else mul*=10,mul+=a[l];
				}
				vis[mul]++;
				// cout<<mul<<"\n";
			}
		}
	}
	for(int i=0;i<100000;i++)if(vis[i]==n)++ans;
	printf("%lld\n",ans);
}

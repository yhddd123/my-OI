#include<bits/stdc++.h>
#define int long long
#define y1 _y1
#define mod 19260817
using namespace std;
const int maxn=200010;
const int inf=2e9;

int n,s,a[maxn],k;
int pos[maxn],lc[maxn],rc[maxn];
int step[maxn],to[maxn];
int opt,x,y;
int ask(int x){
	int ans=0;
	while(x<=n){
		ans+=step[x];
		x=to[x];
	}
	return ans;
}
void updata(int l,int r){
	for(int i=r;i>=l;i--){
		if(i+a[i]>rc[i]){
			to[i]=i+a[i];
			step[i]=1;
		}
		else{
			to[i]=to[i+a[i]];
			step[i]=step[i+a[i]]+1;
		}
	}
}
void sovle(){
	cin>>n;s=sqrt(n);
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>k;
	
	for(int i=1;i<=n;i++){
		pos[i]=(i-1)/s+1;
		lc[i]=(pos[i]-1)*s+1;
		rc[i]=pos[i]*s;
	}
	for(int i=n;pos[i]==pos[n];i--)rc[i]=n;
	updata(1,n);
//	for(int i=1;i<=n;i++)cout<<pos[i]<<" "<<lc[i]<<" "<<rc[i]<<" "<<to[i]<<" "<<step[i]<<"\n";
	
	while(k--){
		cin>>opt>>x;x++;
		if(opt==1)cout<<ask(x)<<"\n";
		else{
			cin>>y;a[x]=y;
			updata(lc[x],rc[x]);
		}
	}
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	T=1;
	while(T--)sovle();
}


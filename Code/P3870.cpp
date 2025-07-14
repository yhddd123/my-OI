//P3870
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;

int n,q,m,s,a[maxn],res;
int opt,x,y,ll,rr;
int pos[maxn],lc[maxn],rc[maxn];
int num[maxn],l[maxn],r[maxn],ans[maxn],sum[maxn],tag[maxn];
int cnt;
signed main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>q;s=sqrt(n);
	for(int i=1;i<=n;i++)pos[i]=(i-1)/s+1;
	m=pos[n];
	for(int i=1;i<=m;i++){
		lc[i]=(i-1)*s+1;
		rc[i]=i*s;
	}
	rc[m]=n;
	while(q--){
		cin>>opt>>x>>y;
		ll=pos[x],rr=pos[y];
		if(opt==0){
			if(ll!=rr){
				for(int i=x;i<=rc[ll];i++){
					sum[ll]-=(a[i]^tag[ll]);
					a[i]^=1;
					sum[ll]+=(a[i]^tag[ll]);
				}
				for(int i=ll+1;i<=rr-1;i++)tag[i]^=1,sum[i]=rc[i]-lc[i]+1-sum[i];
				for(int i=lc[rr];i<=y;i++){
					sum[rr]-=(a[i]^tag[rr]);
					a[i]^=1;
					sum[rr]+=(a[i]^tag[rr]);
				}
			}
			else{
				for(int i=x;i<=y;i++){
					sum[ll]-=(a[i]^tag[ll]);
					a[i]^=1;
					sum[ll]+=(a[i]^tag[ll]);
				}
			}
		}
		if(opt==1){
			res=0;
			if(ll!=rr){
				for(int i=x;i<=rc[ll];i++)res+=a[i]^tag[ll];
				for(int i=ll+1;i<=rr-1;i++)res+=sum[i];
				for(int i=lc[rr];i<=y;i++)res+=a[i]^tag[rr];
			}
			else{
				for(int i=x;i<=y;i++)res+=a[i]^tag[ll];
			}
			cout<<res<<"\n";
		}
	}
}
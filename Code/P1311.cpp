#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,k,p,a[maxn],val[maxn],res;
int st[maxn][21];
int lg[maxn],pw[21];
vector<int> col[maxn];
int query(int i,int j){
	int k=lg[j-i+1];
	return min(st[i][k],st[j-pw[k]+1][k]);
}
signed main(){
//	freopen("P1311_2.in","r",stdin);
	n=read();k=read();p=read();
	lg[1]=0;pw[0]=1;
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=20;i++)pw[i]=pw[i-1]<<1;
	for(int i=1;i<=n;i++)a[i]=read()+1,col[a[i]].push_back(i),st[i][0]=read();
	for(int j=1;j<=lg[n];j++){
		for(int i=1;i+pw[j]-1<=n;i++){
			st[i][j]=min(st[i][j-1],st[i+pw[j-1]][j-1]);
		}
	}
	for(int i=1;i<=k;i++){
		if(!col[i].size())continue;
		for(int j=0;j<col[i].size();j++){
			int l=j+1,r=col[i].size()-1,mid,ans=0;
			while(l<=r){
				mid=l+r>>1;
				if(query(col[i][j],col[i][mid])<=p){
					r=mid-1;
					ans=mid;
				}
				else l=mid+1;
			}
			if(ans){
				res+=col[i].size()-1-ans+1;
			}
		}
	}
	printf("%lld\n",res);
}


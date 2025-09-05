#include<bits/stdc++.h>
#include "highest.h"
using namespace std;
const int maxn=500010;
int n,q;
int a[maxn],b[maxn];
int f[19][maxn],g[19][maxn];
int mx1[19][maxn],mx2[19][maxn];
int max1(int u,int v){return a[u]>a[v]?u:v;}
int max2(int u,int v){return b[u]>b[v]?u:v;}
int que1(int l,int r){
	int k=__lg(r-l+1);
	return max1(mx1[k][l],mx1[k][r-(1<<k)+1]);
}
int que2(int l,int r){
	int k=__lg(r-l+1);
	return max2(mx2[k][l],mx2[k][r-(1<<k)+1]);
}
vector<int> solve(vector<int> &v, vector<int> &w, vector<pair<int, int>> &que) {
	n=v.size(),q=que.size();
	for(int i=1;i<=n;i++)a[i]=min(n,i+v[i-1]),b[i]=min(n,i+w[i-1]);
	for(int i=1;i<=n;i++)mx1[0][i]=mx2[0][i]=i;
	for(int j=1;j<19;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mx1[j][i]=max1(mx1[j-1][i],mx1[j-1][i+(1<<j-1)]);
	}
	for(int j=1;j<19;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mx2[j][i]=max2(mx2[j-1][i],mx2[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)f[0][i]=a[i],g[0][i]=i,f[1][i]=b[i],g[1][i]=a[i];
	for(int j=1;j<19;j++){
		for(int i=1;i<=n;i++){
			f[j][i]=max({f[j][i],f[j-1][que1(i,f[j-1][i])],f[j-1][que2(i,f[j-1][i])]});
			int p=b[que2(i,g[j-1][i])];
			f[j][i]=max({f[j][i],g[j-1][p],g[j-1][que1(i,p)],g[j-1][que2(i,p)]});
			g[j][i]=max({g[j][i],g[j-1][f[j-1][i]],g[j-1][que1(i,f[j-1][i])],g[j-1][que2(i,f[j-1][i])]});
			g[j][i]=max({g[j][i],f[j-1][que1(i,g[j-1][i])],f[j-1][que2(i,g[j-1][i])]});
		}
	}
	vector<int> ans;
	for(int i=0;i<q;i++){
		auto[l,r]=que[i];l++,r++;
		int res=n,p=l,p1=0;for(int j=18,sum=0;~j;j--){
			int np=max(f[j][que1(l,p)],f[j][que2(l,p)]);
			int np1=max({g[j][p],g[j][que1(l,p)],g[j][que2(l,p)]});
			if(p1){
				int pp=b[que2(l,p1)];
				np=max({np,g[j][pp],g[j][que1(l,pp)],g[j][que2(l,pp)]});
				np1=max({np1,f[j][que1(l,p1)],f[j][que2(l,p1)]});
			}
			// cout<<j<<" "<<p<<" "<<p1<<" "<<np<<" "<<np1<<" "<<sum<<"\n";
			// cout<<que1(l,p)<<" "<<que2(l,p)<<"\n";
			if(np1>=r)res=min(res,sum+(1<<j)-1);
			if(np<r)sum+=1<<j,p=np,p1=np1;
			else res=min(res,sum+(1<<j));
		}
		ans.push_back(res);
	}
	return ans;
}

int main() {
ios::sync_with_stdio(false); cin.tie(nullptr);
int n;cin >> n;
vector<int> v(n);
for (int i = 0; i < n; i++)cin >> v[i];
vector<int> w(n);
for (int i = 0; i < n; i++)cin >> w[i];
int m;cin >> m;
vector<pair<int, int>> queries(m);
for (int i = 0; i < m; i++)cin >> queries[i].first >> queries[i].second;
vector<int> results = solve(v, w, queries);
for (int i = 0; i < m; i++)cout << results[i] << "\n";
}
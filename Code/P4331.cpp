#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1000010;

int n,a[maxn],ans;
priority_queue<int> q;
signed main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]-=i;
	for(int i=1;i<=n;i++){
		q.push(a[i]);
		if(a[i]<q.top()){
			ans+=q.top()-a[i];
			q.pop();q.push(a[i]);
		}
		a[i]=q.top();
	}
	cout<<ans<<"\n";
	for(int i=n-1;i>=1;i--)a[i]=min(a[i],a[i+1]);
	for(int i=1;i<=n;i++)cout<<a[i]+i<<" ";
}

#include<bits/stdc++.h>
using namespace std;
long long a,b,f[10000010],ans;
signed main(){
	cin>>a>>b;
	for(int i=1;i<=b;i++)for(int j=2;i*j<=b;j++)f[i*j]+=i;
	for(int i=a;i<=b;i++)ans+=abs(i-f[i]);
	cout<<ans;
}


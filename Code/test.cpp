#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1010;
const int maxm=1e6+10;
int n,m,x,y,d[maxn];
vector<pair<int,int> > E;
char a[maxn][maxn];
bitset<maxn> s[maxn];
inline int C2(int x)
{
	if(x<=1)return 0;
	return x*(x-1)/2;
}
inline int C3(int x)
{
	if(x<=2)return 0;
	return x*(x-1)*(x-2)/6;
}
inline int com(int x,int y)
{
	return (s[x]&s[y]).count();
}
inline int G1()
{
	int res=0;
	for(auto now:E)
	{
		x=now.first,y=now.second;
		res+=com(x,y);
	}
	return res/3;
}
inline int G2()
{
	int res=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)res+=C2(com(i,j));
	}
	return res/2;
}
inline int G3(){return (int)E.size();}
inline int G4()
{
	int res=0;
	for(int i=1;i<=n;i++)res+=C2(d[i]);
	return res;
}
inline int G5()
{
	int res=0;
	for(auto now:E)
	{
		x=now.first,y=now.second;
		res+=(d[x]-1)*(d[y]-1);
	}
	res-=3*G1();
	return res;
}
inline int G6()
{
	int res=0;
	for(int i=1;i<=n;i++)res+=C3(d[i]);
	return res;
}
inline int G7()
{
	int res=0;
	for(auto now:E)
	{
		x=now.first,y=now.second;
		res+=C2(com(x,y));
	}
	return res;
}
inline int G8()
{
	int res=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j || d[i]<2)continue;
			res+=C2(com(i,j))*(d[i]-2-(a[i][j]=='1'));
		}
	}
	return res;
}
inline int G9()
{
	int res=0;
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		for(int j=1;j<=n;j++)
		{
			if(i==j)continue;
			sum+=((a[i][j]=='1')*com(i,j));
		}
		sum/=2;res+=C2(sum);
	}
	res-=2*G7();
	return res;
}
signed main()
{
	freopen("A.in","r",stdin);
	while(scanf("%lld",&n) != EOF)
	{
		E.clear();
		for(int i=1;i<=n;i++)s[i].reset(),d[i]=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%s",a[i]+1);
			for(int j=i+1;j<=n;j++)if(a[i][j]=='1')E.push_back(make_pair(i,j));
			for(int j=1;j<=n;j++)if(a[i][j]=='1')s[i].set(j);
		}
		for(auto now:E)d[now.first]++,d[now.second]++;
		int ans=0;
		ans+=G1()*24;ans+=G2()*48;ans+=G3()*2;ans+=G4()*12;
		ans+=G5()*6;ans+=G6()*12;ans+=G7()*36;ans+=G8()*12;
		ans+=G9()*24;
		cout<<G1()<<" "<<G2()<<" "<<G3()<<" "<<G4()<<" "<<G5()<<" "<<G6()<<" "<<G7()<<" "<<G8()<<" "<<G9()<<" "<<ans<<endl;
		printf("%lld\n",ans);
	}
	return 0;
}
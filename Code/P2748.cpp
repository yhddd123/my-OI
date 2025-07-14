#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,x,y,z,a[maxn],b[maxn],ans;
priority_queue<int> q,q1;
//q:少土，q1：多土  
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();x=read();y=read();z=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=n;i++){
		if(a[i]<b[i]){
			for(int j=1;j<=b[i]-a[i];j++){
				if(q.empty()||i*z-q.top()>=x){
					ans+=x;
					q1.push(i*z+x);
				}
				else{
					ans+=i*z-q.top();
					q1.push(i*z*2-q.top());
					q.pop();
				}
			}
		}
		else{
			for(int j=1;j<=a[i]-b[i];j++){
				if(q1.empty()||i*z-q1.top()>=y){
					ans+=y;
					q.push(i*z+y);
				}
				else{
					ans+=i*z-q1.top();
					q.push(i*z*2-q1.top());
					q1.pop();
				}
			}
		}
	}
	printf("%lld\n",ans);
}



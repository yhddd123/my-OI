#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
const int inf=1e8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

char c[]={"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
int n;
void sovle(){
	unsigned int t=0;
	while(1){
		t++;
		srand(t);
		if(c[rand()%62]=='X'&&c[rand()%62]=='H'&&c[rand()%62]=='L'){
			cout<<t<<"\n";
			return ;
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}

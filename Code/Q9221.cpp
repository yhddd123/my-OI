#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 4e5 + 10;

struct node{
	int l, r;
	int id;
}; node a[MAX];

bool cmp(node x, node y){
	return x.l < y.l;
}

void solve(){
	int n = read(), L = read();
	int n2 = 0;
	int cnt2 = 0;
	for(int i = 1; i <= n; i++){
		int l = read(), r = read();
		if(l == -1 and r == -1){
			cnt2++;
			continue;
		}
		n2++;
		if(l == -1)	l = r, a[n2].id = 1;
		else if(r == -1)	r = l, a[n2].id = 2;
		else a[n2].id = 3;
		a[n2].l = l, a[n2].r = r;
	}
	if(!n2){
		if(L<cnt2)puts("NIE");
		else puts("TAK");
		return ;
	}
	sort(a + 1, a + n2 + 1, cmp);
	int nowr = 0;
	int cnt4 = 0;
	int lft = L;
	if(a[1].l != 1 and a[1].id != 1){
		cnt4++;
	}
	for(int i = 1; i <= n2; i++){
		if(a[i].l == a[i - 1].l or a[i].r == a[i - 1].r){
			puts("NIE");
			return ;
		}
		if(a[i].l <= nowr){
			puts("NIE");
			return ;
		}
		if(a[i].id == 3 or a[i].id == 2){
			if(a[i - 1].id == 2){
				
			}else if(a[i - 1].id == 3 or a[i - 1].id == 1){
				if(a[i - 1].r != a[i].l - 1){
					cnt4++;
				}
			}
		}else{
			
		}
		lft -= a[i].r - a[i].l + 1;
		nowr = a[i].r;
	}
	if(a[n2].r != L and a[n2].id != 2){
		cnt4++;
	}
	if(cnt4 > cnt2){
		puts("NIE");
		return ;
	}
	if(lft < cnt2){
		puts("NIE");
		return ;
	}
	puts("TAK");
	return ;
}

signed main(){
	int t = read();
	while(t--)	solve();
	return 0;
}
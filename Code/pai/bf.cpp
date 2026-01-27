#include<bits/stdc++.h>
using namespace std;bool Mbe;
namespace MAOJUN{

int n;

int tp=0,sk[70];
inline void main(){
	scanf("%d",&n);
	vector<int>A;int t=0;
	for(int i=1;i<=n;i++){
		long long x;scanf("%lld",&x);
		tp=0;
		for(int i=__lg(x);~i;i--){
			sk[++tp]=x>>i&1;
			// printf("%d",x>>i&1);
			while(tp>1&&sk[tp-1]>sk[tp]){
				int w=sk[tp]-sk[tp-1];
				if(tp>2)sk[tp-=2]+=w;
				else{t+=w;tp=0;}
			}
		}
		// puts("");
		for(int i=1;i<=tp;i++)A.emplace_back(sk[i]);
	}
	sort(A.begin(),A.end(),greater<int>());
	if(t)A.emplace_back(t);
	int z=A.size(),s=0;
	for(int i=0;i<z;i++)s+=i&1?-A[i]:A[i];
	printf("%d\n",s);
}

}bool Med;int main(){
#ifdef IO
	freopen("2.in","r",stdin);
	freopen(".out","w",stdout);
#endif
#ifdef TM
	atexit([]{fprintf(stderr,"%.lfms\n%lfMB\n",clock()*1000./CLOCKS_PER_SEC,(&Mbe-&Med)/1024./1024);});
#endif
	MAOJUN::main();
	return 0;
}
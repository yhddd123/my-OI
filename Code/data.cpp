#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,k;
vector<pii> edges;
vector<int> deg;

void generateTree(){
	// 计算参数
	int numStars = max(1LL, n / (k + 10)); // 星形结构的数量
	int nodesPerStar = n / numStars; // 每个星形结构大约的节点数
	int remainingNodes = n - numStars * nodesPerStar;
	
	// 创建星形结构
	int nodeId = 1;
	vector<int> starCenters; // 存储每个星形结构的中心点
	
	for(int i = 0; i < numStars; i++){
		int starSize = nodesPerStar;
		if(i < remainingNodes) starSize++; // 分配剩余节点
		
		int center = nodeId++;
		starCenters.pb(center);
		deg.resize(max((int)deg.size(), center + 1));
		
		// 为这个星形结构添加叶子节点
		for(int j = 1; j < starSize; j++){
			edges.pb({center, nodeId});
			deg[center]++;
			nodeId++;
		}
	}
	
	// 连接星形结构形成树
	for(int i = 1; i < starCenters.size(); i++){
		edges.pb({starCenters[i-1], starCenters[i]});
		deg[starCenters[i-1]]++;
		deg[starCenters[i]]++;
	}
	
	// 如果还有剩余节点，连接到某个中心点
	while(nodeId <= n){
		edges.pb({starCenters[0], nodeId});
		deg[starCenters[0]]++;
		nodeId++;
	}
	
	// 随机打乱边的顺序
	random_shuffle(edges.begin(), edges.end());
}

void work(){
	n=1000000,k=1000; // 先用小数据测试
	
	// 初始化
	edges.clear();
	deg.clear();
	
	// 生成树
	generateTree();
	
	// 输出结果
	cout<<n<<" "<<k<<" "<<mod<<"\n";
	
	// 输出边
	for(auto edge : edges){
		cout<<edge.fi<<" "<<edge.se<<"\n";
	}
	
	// 统计度数>=k的点的数量
	// int highDegCount = 0;
	// for(int i = 1; i <= n; i++){
		// if(deg[i] >= k) highDegCount++;
	// }
	
	// cerr << "高度数点(度数>=" << k << ")数量: " << highDegCount << "\n";
	// cerr << "总边数: " << edges.size() << "\n";
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	freopen("1.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}
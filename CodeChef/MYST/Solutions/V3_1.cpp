#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

const int mxN=100;
int t, n, ca, ba[mxN][mxN], tba[mxN][mxN], qu[mxN], qh, qt, prv[mxN], p[mxN];
vector<pii> ops;

inline void bfs(int s, int t) {
	qh=qt=0;
	qu[qt++]=s;
	memset(prv, -1, 4*n);
	prv[s]=-2;
	while(qh<qt&&(t==-1||prv[t]==-1)) {
		int u=qu[qh++];
		for(int v=0; v<n; ++v) {
			if(ba[u][v]&&prv[v]==-1) {
				qu[qt++]=v;
				prv[v]=u;
			}
		}
	}
}

inline bool tv(int ta, int cb) {
	if(cb>=0)
		--ba[ca][cb];
	bfs(ca, ta);
	if(prv[ta]==-1) {
		if(cb>=0)
			++ba[ca][cb];
		return 0;
	}
	if(cb>=0)
		++ba[ta][cb];
	vector<pii> to;
	for(int i=ta; i!=ca; i=prv[i])
		to.push_back({i, cb});
	for(int i=(int)to.size()-1; i>=0; --i)
		ops.push_back(to[i]);
	ca=ta;
	return 1;
}

inline void solve() {
	cin >> n;
	ca=0;
	for(int i=0; i<n; ++i) {
		int bi;
		cin >> bi;
		for(int j=0; j<bi; ++j) { 
			int bij;
			cin >> bij, --bij;
			++ba[bij][i];
		}
		for(int j=0; j<bi; ++j) {
			int bij;
			cin >> bij, --bij;
			++tba[bij][i];
		}
	}
	bool ch=1;
	while(ch) {
		ch=0;
		bool f=0;
		bfs(ca, -1);
		memcpy(p, qu, 4*n);
		for(int i=0; i<n&&!f; ++i) {
			for(int j=0; j<n&&!f; ++j) {
				if(ba[p[i]][j]<=tba[p[i]][j])
					continue;
				ch=1;
				int k=0;
				for(; k<n; ++k) {
					if(ba[k][j]>=tba[k][j])
						continue;
					int tos=ops.size(), tca=ca;
					if(tv(p[i], -1)&&tv(k, j))	
						break;
					while(ops.size()>tos)
						ops.pop_back();
					ca=tca;
				}
				if(k<n)
					f=1;
			}
		}
		if(ch&&!f) {
			cout << "-1\n";
			exit(0);
		}
	}
	cout << ops.size() << "\n";
	for(pii op : ops)
		cout << op.fi+1 << " " << op.se+1 << "\n";
	for(int i=0; i<n; ++i) {
		memset(ba[i], 0, 4*n);
		memset(tba[i], 0, 4*n);
	}
	ops.clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t;
	while(t--)
		solve();
}

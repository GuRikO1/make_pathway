#include <bits/stdc++.h>
#include <thread>


using namespace std;
typedef long long ll;

int seed = 4;
mt19937 mt(seed);
int n;

pair<int,int> diff() {
    int dx, dy;
    if (mt()%2) {
        dx = 0;
        dy = (mt()%2==0) ? 1 : -1;
    } else {
        dx = (mt()%2==0) ? 1 : -1;
        dy = 0;
    }
    return make_pair(dx,dy);
}

int main(){
    cout << "input the size of maze" << endl;
    cin >> n;
    if (n%2==1) {
        cout << "input even number" << endl;
        return 0;
    }
    n++;
    vector<vector<int>> arr(n,vector<int>(n));
    for (int i = 0; i < n; i++) {
        arr[0][i] = 1;
        arr[n-1][i] = 1;
        arr[i][0] = 1;
        arr[i][n-1] = 1;
    }
    deque<pair<int,int>> dq;
    for (int i = 2; i < n-1; i+=2) {
        for (int j = 2; j < n-1; j+=2) {
            dq.push_back(make_pair(i,j));
        }
    }
    while (dq.size() > 0) {
        ll m = dq.size();
        ll i = mt()%m;
        pair<int,int> p = dq[i];
        int x = p.first;
        int y = p.second;
        set<pair<int,int>> s;
        if (arr[x][y] == 1) {
            dq.erase(dq.begin()+i);
            continue;
        }
        s.insert(make_pair(x, y));
    	if (m%1000==0) cout << m << endl; 
        while (1) {
            pair<int,int> d = diff();
            if (s.find(make_pair(x+2*d.first, y+2*d.second))!=s.end()) {
		while (s.size() > 0) {
                    s.erase(s.begin()); 
        	}
                break;
            } else if (arr[x+2*d.first][y+2*d.second]==true) {
                s.insert(make_pair(x+d.first, y+d.second));
                dq.erase(dq.begin()+i);
                break;
            } else {
                s.insert(make_pair(x+d.first, y+d.second));
                x+=2*d.first; y+=2*d.second;
                s.insert(make_pair(x, y));
            }
        }
        while (s.size() > 0) {
            pair<int,int> sp = *(s.begin());
            arr[sp.first][sp.second] = 1;
	    s.erase(s.begin());    
        }
    }
    ofstream file;
    file.open("size_"+to_string(n-2)+"_"+to_string(seed)+".csv");
    file << n-2 << "\n";
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < n-1; j++) {
            if (arr[i][j]==1) file << 0;
            else file << 1;
            if (j!=n-2) file << ',';
        }
        file << "\n";
    }
    return 0;
}

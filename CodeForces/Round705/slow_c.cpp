#include <bits/stdc++.h>

using namespace std;

// ios::sync_with_stdio(0);
// cin.tie(0);

# define deb_v(x) cerr << #x << " = ("; \
    for (auto item: x) cerr << item << " "; \
    cerr << ")\n";

# define deb(x) cerr << #x << " = " << x << "\n";

# define deb_v_p(x) cerr << #x << " = ("; \
    for (auto item: x) cerr << "(" << item.first << ", " << item.second << ") "; \
    cerr << ")\n";

bool can_finish(map<char, int>& counter, int i, int n, int k) {
    int left = n - i - 1;
    for (char c = 'a'; c <= 'z'; c++) {
        int have = counter[c] % k;
        if (have == 0) {
            continue;
        }
        left -= k - have;
    }
    return (left >= 0) && (left % k == 0);
}

void solve(int t) {
    int n, k;
    scanf("%d%d", &n, &k);
    string s;
    cin >> s;
    if (n % k != 0) {
        printf("-1\n");
        return;
    }
    map<char, int> counter;
    for (int i = 0; i < n; i++) {
        counter[s[i]]++;
    }
    bool ok = true;
    for (pair<char, int> p : counter) {
        if (p.second % k != 0) {
            ok = false;
        }
    }
    if (ok) {
        cout << s << "\n";
        return;
    }
    counter.clear();
    int index = -1;
    int used_c = '{';
    for (int i = 0; i < n; i++) {
        for (char c = s[i] + 1; c <= 'z'; c++) {
            counter[c]++;
            if (can_finish(counter, i, n, k)) {
                if (index < i || c < used_c) {
                    index = i;
                    used_c = c;
                }
            }
            counter[c]--;
        }
        counter[s[i]]++;
    }
    counter.clear();
    string out = "";
    for (int i = 0; i < index; i++) {
        counter[s[i]]++;
        out += s[i];
    }
    counter[used_c]++;
    out += used_c;
    int i = index + 1;
    string suff = "";
    for (char c = 'a'; c <= 'z'; c++) {
        int curr = counter[c] % k;
        if (curr == 0) {
            continue;
        }
        while (curr < k) {
            i++;
            suff += c;
            curr++;
        }
    }
    for (int x = i; x < n; x++) {
        out += 'a';
    }
    out += suff;
    cout << out << "\n";
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
}
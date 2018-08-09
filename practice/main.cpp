
/*
#include "test.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <utility>




int main() {
	
	test();
	return 0;

}
*/


/*
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <string>


using namespace std;

void bfs(int x, int y, vector<vector<int>>& distance, vector<vector<bool>>& get, 
	const vector<vector<char>>& mark, const vector<pair<int, int>>& step) {

	for (int i = 0; i<step.size(); i++) {
		int x_ = step[i].first + x;
		int y_ = step[i].second + y;

		if (x_ >= 0 && x_<get.size() && y_ >= 0 && y_<get[0].size() && !get[x_][y_]) {
			if (mark[x_][y_] == 'X')
				continue;

			distance[x_][y_] = distance[x][y] + 1;
			get[x_][y_] = true;
			bfs(x_, y_, distance, get, mark, step);
		}
	}
}
*/

/*
int min_escape(int x0, int y0, const vector<vector<char>>& mark, 
	const vector<pair<int, int>>& step) {
	if (mark.size() == 0 || mark[0].size() == 0)
		return -1;

	int n = mark.size();
	int m = mark[0].size();
	vector<vector<bool>> get(n, vector<bool>(m, false));
	get[x0][y0] = true;
	vector<vector<int>> distance(n, vector<int>(m, 0));
	distance[x0][y0] = 0;

	queue<pair<int, int>> point;
	point.push(pair<int, int>(x0, y0));
	while (!point.empty()) {
		pair<int, int> t = point.front();
		point.pop();

		for (int i = 0; i<step.size(); i++) {
			int x_ = step[i].first + t.first;
			int y_ = step[i].second + t.second;

			if (x_ >= 0 && x_<get.size() && y_ >= 0 && y_<get[0].size() && !get[x_][y_]) {
				if (mark[x_][y_] == 'X')
					continue;

				get[x_][y_] = true;
				distance[x_][y_] = distance[t.first][t.second] + 1;
				point.push(pair<int, int>(x_, y_));
			}
		}
	}

	int max = -1;
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<m; j++) {
			if (mark[i][j] == 'x')
				continue;;

			if (mark[i][j] == '.'&&get[i][j] == false) {
				return -1;
			}

			if (mark[i][j] == '.'&&distance[i][j] > max) {
				max = distance[i][j];

			}
		}
	}
	return max;
}

int main() {

	int m, n;
	cin >> n >> m;
	if (n <= 0 || m <= 0)
		return 0;

	vector<vector<char>>  mark;
	char ch;
	int n1 = n;
	while (n1--) {
		int m1 = m;
		vector<char> vec_ch;
		while (m1--) {
			cin >> ch;
			vec_ch.push_back(ch);
		}
		mark.push_back(vec_ch);
	}

	int x0, y0;
	cin >> x0 >> y0;
	int k;
	cin >> k;
	int k1 = k;
	vector<pair<int, int>> step;
	while (k1--) {
		pair<int, int> p_t;
		cin >> p_t.first >> p_t.second;
		step.push_back(p_t);
	}

	cout << min_escape(x0, y0, mark, step) << endl;
	return 0;

}

*/

/*
int cal(int x1, int y1, int x2, int y2, const vector<vector<int>>& sum) {
	if (x1 - 1<0 && y1 - 1<0)
		return sum[x2 - 1][y2 - 1];
	else if (x1 - 1<0)
		return sum[x2 - 1][y2 - 1] - sum[x2 - 1][y1 - 1];
	else if (y1 - 1<0)
		return sum[x2 - 1][y2 - 1] - sum[x1 - 1][y2 - 1];
	else
		return sum[x2 - 1][y2 - 1] - sum[x2 - 1][y1 - 1] - sum[x1 - 1][y2 - 1] + sum[x1 - 1][y1 - 1];
}

bool isArea(int count, const vector<vector<int>>& sum) {
	for (int x1 = 1; x1 <= sum.size() - 3; x1++) {
		for (int x2 = x1 + 1; x2 <= sum.size() - 2; x2++) {
			for (int x3 = x2 + 1; x3 <= sum.size() - 1; x3++) {
				int cnt = 0;
				int y1 = 0;
				for (int y = 1; y <= sum[0].size(); y++) {
					if (cal(0, y1, x1, y, sum)>=count && cal(x1, y1, x2, y, sum) >= count && cal(x2, y1, x3, y, sum) >= count && cal(x3, y1, sum.size(), y, sum) >= count) {
						cnt++;
						y1 = y;
					}
				}

				if (cnt >= 4)
					return true;
			}
		}
	}

	return false;
}

int main() {
	int n, m;
	cin >> n >> m;
	if (n<4 || n>75 || m<4 || m>75)
		return 0;

	vector<vector<int>> value;
	int n1 = n;
	//这里有问题，原因在于输入是不间断的，以字符串形式给出的
	while (n1--) {
		vector<int> t;

		//int m1=m;
		//int number;
		//while(m1--){
		//cin>>number;
		//t.push_back(number);
		//}

		string str;
		cin >> str;
		int i = 0;
		while (i<m) {
			t.push_back(str[i] - '0');
			i++;
		}

		value.push_back(t);
	}

	vector<vector<int>> sum(n, vector<int>(m));
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<m; j++) {
			if (i == 0 && j == 0)
				sum[i][j] = value[i][j];
			else if (i == 0)
				sum[i][j] = value[i][j] + sum[0][j - 1];
			else if (j == 0)
				sum[i][j] = value[i][j] + sum[i - 1][0];
			else
				sum[i][j] = value[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	}

	int l = 0, h = sum[n - 1][m - 1];
	int ans = 0;
	while (l<h) {
		int mid = (l + h) / 2;
		if (isArea(mid, sum)) {
			l = mid + 1;
			ans = mid;
		}
		else {
			h = mid - 1;
		}
	}

	cout << ans << endl;
	return 0;

}
*/

/*
int main() {
	string s, t;
	cin >> s >> t;
	if (t.empty()) {
		cout << "Yes" << endl;
		return 0;
	}

	
	int s_s = 0, s_t = 0;
	while (s_s<s.size()) {
		while (s_s<s.size()&&s[s_s] != t[s_t]) {
			s_s++;
		}
		if (s_s<s.size()&&s[s_s] == t[s_t]) {
			s_t++;
			s_s++;
		}
	}
	if (s_t == t.size()) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}

	return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int reverse_count(int pos, int value, const vector<int>& vec) {
	int count = 0;
	for (int i = 1; i<pos; i++) {
		if (vec[i] == 0)
			continue;
		if (vec[i]<value)
			count++;
	}
	for (int i = pos + 1; i<vec.size(); i++) {
		if (vec[i] == 0)
			continue;
		if (vec[i]>value)
			count++;
	}
	return count;
}

int reverse_count(const vector<int>& vec) {
	int count = 0;
	for (int i = 1; i < vec.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (vec[j] < vec[i])
				count++;
		}
	}
	return count;
}

int main() {
	int n, k;
	cin >> n >> k;
	if (n <= 0 || k<0)
		return 0;
	if (k>(n*(n - 1)) / 2)
		return 0;

	int n1 = n;
	vector<int> num{ 0 };
	while (n1--) {
		int number;
		cin >> number;
		if (number<0)
			return 0;
		num.push_back(number);
	}

	int reverse1 = 0;
	for (int i = 1; i<num.size(); i++) {
		if (num[i] == 0)
			continue;
		reverse1 += reverse_count(i, num[i], num);
	}
	reverse1 /= 2;

	unordered_set<int> hash_existed;
	for (int i = 0; i<num.size(); i++) {
		if (num[i] != 0)
			hash_existed.insert(num[i]);
	}
	vector<int> missing;
	for (int i = 1; i <= n; i++) {
		if (hash_existed.find(i) == hash_existed.end())
			missing.push_back(i);
	}
	sort(missing.begin(), missing.end());
	

	int res = 0;
	do {
		int reverse2 = reverse_count(missing);
		int reverse3 = 0;
		int misssing_pos = 0;
		for (int i = 1; i < num.size(); i++) {
			if (num[i] == 0) {
				reverse3 += reverse_count(i, missing[misssing_pos], num);
				misssing_pos++;
			}
		}
		if (reverse1 + reverse2 + reverse3 == k)
			res++;

	} while (next_permutation(missing.begin(), missing.end()));
	
	cout << res << endl;
	return 0;
}

*/

/*
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {

	int n;
	cin >> n;
	if (n<1 || n>1000000000)
		return 0;

	vector<string>  name{ "Alice", "Bob", "Cathy", "Dave" };
	int den = log(n) / log(2);
	int left = n - pow(2, den);
	if (left == 0) {
		cout << name[3] << endl;
	}
	int number = pow(2, den - 2);
	int pos = left / number;
	cout << name[pos] << endl;
	return 0;

}

*/

/*
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	vector<int> w;
	while (cin >> n) {
		if (n < 100 || n>300)
			return 0;
		w.push_back(n);
	}
	sort(w.begin(), w.end());

	int res = 0;
	int l = 0;
	int r = w.size() - 1;
	while (l < r) {
		if (w[l] + w[r]<=300) {
			l++;
			r--;
			cout << (res + (r - l + 1) / 2) << endl;
			return 0;
		}
		else {
			r--;
			res++;
		}
	}
	cout << res << endl;
	return 0;
}

*/

/*
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
			
	vector<vector<int>> vec(n, vector<int>(26, 0));

	int n1 = n;
	while (n1--) {
		string str;
		cin >> str;
		for (int i = 0; i < n; i++) {
			vec[i][str[i] - 'a']++;
		}
	}

	vector<int> max;
	for (int i = 0; i < n; i++) {
		max.push_back(i);
	}

	for (int i = 0; i < 26; i++) {
		if (max.empty()) {
			cout << -1 << endl;
			return 0;
		}

		vector<int> temp{ max[0] };

		int count = vec[max[0]][i];
		for (int j = 1; j < max.size(); j++) {
			if (vec[max[j]][i] == count) {
				temp.push_back(max[j]);
			}
			else if (vec[max[j]][i] > count) {
				count = vec[max[j]][i];
				temp.clear();
				temp.push_back(max[j]);
			}
			else if (vec[max[j]][i] < count)
				continue;
		}

		max = temp;
	}

	if (max.empty()) {
		cout << -1 << endl;
		return 0;
	}
	cout << max[0] << endl;
	return 0;
	
}

*/

/*
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	string str;
	cin >> str;
	if (str.size() != n)
		return 0;


}

*/

/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<char> v1{ 'a','b' };
	vector<char> v2{ 'b','a' };
	if (v1 > v2)
		cout << "v1>v2" << endl;
	else
		cout << "v1<v2" << endl;

	return 0;
}

*/

/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	if (n <= 0 || n>1000) {
		cout << 0 << endl;
		return 0;
	}

	vector<vector<int>> trap(2, vector<int>{0});
	int n1 = n;
	while (n1--) {
		int x;
		cin >> x;
		trap[0].push_back(x);
	}
	n1 = n;
	while (n1--) {
		int y;
		cin >> y;
		trap[1].push_back(y);
	}

	int dis = trap[0][1] + trap[1][1] - 2;
	for (int i = 2; i <= n; i++) {
		if (trap[0][i] + trap[1][i] - 2<dis)
			dis = trap[0][i] + trap[1][i] - 2;
	}
	cout << dis << endl;

	return 0;

}
*/

/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> vec(n + 1, 0);
	for (int i = 1; i <= n; i += 2) {
		vec[i] = i;
	}
	for (int i = 2; i <= n; i += 2) {
		int t = i;
		while (t % 2 == 0) {
			t /= 2;
		}
		vec[i] = t;
	}

	int sum = 0;
	for (int i = 0; i <= n; i++)
		sum += vec[i];

	cout << sum << endl;

	return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	multiset<int> table;
	while (n--) {
		int t;
		cin >> t;
		table.insert(t);
	}

	vector<pair<int, int>> customer;
	while (m--) {
		pair<int, int> c;
		cin >> c.first >> c.second;
		customer.push_back(c);
	}

	sort(customer.begin(), customer.end(), [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
		return lhs.second<rhs.second || (lhs.second == rhs.second && lhs.first<rhs.first);
	});

	int sum = 0;
	while (!table.empty() && !customer.empty()) {
		pair<int, int> c = customer[customer.size() - 1];
		auto it = table.lower_bound(c.second);
		if (it != table.end()) {
			sum += c.second;
			table.erase(it);
		}
		customer.pop_back();
	}

	cout << sum << endl;
	return 0;

}
*/

/*
#include <iostream>
#include <vector>

using namespace std;

//vector<vector<long long>> dp(1001,vector<long long>(1001,0));
//long long dp[1000][1000];

int main() {
	int n, m;
	cin >> n >> m;
	if (n<1 || n>1000 || m<1 || m>1000) {
		cout << 0 << endl;
		return 0;
	}

	vector<int> v{ 0 };
	int n1 = n;
	while (n1--) {
		int t;
		cin >> t;
		v.push_back(t);
	}

	vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

	for (int i = 0; i <= n; i++) {
		dp[i][0] = 1;
	}
	for (int i = 1; i<m; i++) {
		dp[0][i] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (v[i] <= j)
				dp[i][j] = dp[i - 1][j] + dp[i - 1][j - v[i]];
			else
				dp[i][j] = dp[i - 1][j];
		}
	}


	cout << dp[n][m] << endl;
	return 0;
}

*/

/*
#include <iostream>
#include <string>

using namespace std;

int main() {
	string t;
	cin >> t;

	int start = 0, max = 0;
	int begin = 0;
	for (int i = 0; i<t.size();) {
		while (!(t[i] >= '0'&&t[i] <= '9') && i<t.size())
			i++;
		begin = i;
		while (t[i] >= '0'&&t[i] <= '9'&&i<t.size())
			i++;
		if (i - begin>max) {
			start = begin;
			max = i - begin;
		}
	}

	cout << t.substr(start, start + max) << endl;
	return 0;
}
*/

/*
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {

	string s;
	vector<string> v;
	while (cin >> s) {
		v.push_back(s);
	}

	string s2 = v.back();
	v.pop_back();

	unordered_set<char> hash;
	for (int i = 0; i<s2.size(); i++) {
		hash.insert(s2[i]);
	}

	for (int i = 0; i<v.size(); i++) {
		string s1 = v[i];
		for (auto it = s1.begin(); it != s1.end(); ) {
			if (hash.find(*it) != hash.end()) {
				s1.erase(it);
			}
			else {
				it++;
			}
		}
		v[i] = s1;
	}

	for (int i = 0; i<v.size() - 1; i++) {
		cout << v[i] << " ";
	}
	cout << v.back() << endl;

	return 0;
}

*/

/*
#include <iostream>
#include <string>

using namespace std;

int main() {

	string s = "asdfg";
	auto it = s.begin();
	s.erase(it);
	cout << *it << endl;//s
	it += 2;
	s.erase(it);
	cout << *it << endl;//f
	cout << s << endl;//sdg
	
	return 0;
}
*/

/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	if (n<3 || n>1000) {
		cout << -1 << endl;
		return 0;
	}

	vector<bool> dp(n + 1, true);
	dp[2] = dp[3] = true;
	for (int i = 4; i <= n; i++) {
		for (int j = 2; j <= i / 2; j++) {
			if (i%j == 0) {
				dp[i] = false;
				break;
			}
		}
	}
	dp[0] = dp[1] = false;


	int count = 0;
	for (int i = 0; i <= n / 2; i++) {
		if (dp[i] && dp[n - i])
			count++;
	}

	cout << count << endl;
	return 0;
}
*/

/*
#include <vector>
using std::vector;

int uniquePaths(int m, int n) {
	if (m <= 0 || n <= 0)
		return -1;
	vector<int> dp(n, 1);
	for (int i = 1; i < m; ++i) {
		for (int j = 1; j < n; ++j) {
			dp[j] += dp[j - 1];
		}
	}
	return dp[n - 1];
}

int main() {
	int count = uniquePaths(5, 6);//126
	int count2= uniquePaths(6, 5);//126
	return 0;
}

*/

/*
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main() {
	
	string str="4 3\n0,1 0,2";

	cout << str << endl;
	cout << str.size();
	cout << str[2];
	cout << str[3];
	cout << str[4];
	cout << endl;
	string str1 = "4a原来";
	cout << str1.size();
	cout << endl;
	if (str1[2] == ',' || str1[2] == ' ' || str1[2] == '\n' || (str1[2] >= '0'&& str1[2] <= '9'))
		cout << str1[2] << endl;

	for (int i = 0; i < str1.size(); i++) {
		if (str1[i] == ',' || str1[i] == ' ' || str1[i] == '\n' || (str1[i] >= '0'&& str1[i] <= '9'))
			cout << str1[i] << endl;
	}
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ',' || str[i] == ' ' || str[i] == '\n' || (str[i] >= '0'&& str[i] <= '9'))
			cout << str[i] << endl;
	}

	cout << str1[2] << endl;
	cout << str1[3] << endl;
	char* p = "4 3\n0,1 0,2";
	cout << strlen(p);
	cout << endl;
	char* p1 = "4a原来";
	cout << strlen(p1);
	cout << endl;
	cout << p1[2] << endl;
	cout << p1[3] << endl;
	
	

	string str3 = "23 45 76";
	int m1 = stoi(str3);
	cout << m1 << endl;

	string str7 = "0123456";
	int m7 = stoi(str7);//error
	cout << m7 << endl;

	string str8 = "56w";
	int m8 = stoi(str8);
	cout << m8 << endl;

	string str9 = "";
	int m9 = stoi(str9);
	cout << m9 << endl;


	string str6 = "4564654564897897984654";
	int m6 = stoi(str6);//error
	cout << m6 << endl;


	string str4 = "   \n";
	int m2 = stoi(str4);//error
	cout << m2 << endl;
	string str5 = "";
	int m3 = stoi(str5);
	cout << m3 << endl;

	return 0;
}

*/

/*
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	char a[] = { 1,2,3,4,5,6,7,8 };
	int *p = (int*)a + 1;
	int n = *p;

	string s = "hello";
	reverse(s.begin(), s.end());
	cout << s << endl;

	return 0;
}
*/


/*
#include <algorithm>

struct Node
{
	int data;
	Node* left;
	Node* right;
};

int height_of_binary_tree(Node* n) {
	if (n == nullptr)
		return -1;

	return std::max(height_of_binary_tree(n->left), height_of_binary_tree(n->right)) + 1;
}
*/

/*
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {

	string s, s1, s2;
	while (cin >> s >> s1 >> s2) {
		bool forward = true;
		auto pos1 = s.find(s1);
		auto pos2 = s.find(s2);

		if (pos1 == -1 || pos2 == -1 || pos2<pos1 + s1.size())
			forward = false;

		bool backward = true;
		reverse(s.begin(), s.end());
		pos1 = s.find(s1);
		pos2 = s.find(s2);

		if (pos1 == -1 || pos2 == -1 || pos2<pos1 + s1.size())
			forward = false;

		if (forward&&backward)
			cout << "both" << endl;
		else if (forward && !backward)
			cout << "forward" << endl;
		else if (!forward&&backward)
			cout << "backward" << endl;
		else
			cout << "invalid" << endl;

	}

	return 0;
}
*/

/*
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	int n1 = n;
	vector<int> num;
	while (n1--) {
		int l;
		cin >> l;
		num.push_back(l);
	}

	int count = 0;
	for (int i = 0; i<n - 1; i++) {
		for (int j = i + 1; j<n; j++) {
			int result = num[i] ^ num[j];
			if (result > m)
				count++;
		}
	}
	cout << count << endl;

	return 0;
}
*/

/*
#include <algorithm>
#include <queue>

struct Node
{
	int data;
	Node* left;
	Node* right;
	Node() :data(0), left(nullptr), right(nullptr) {}

};

//递归版本
int height_of_binary_tree_recursive(Node* n) {
	if (n == nullptr)
		return -1;

	return std::max(height_of_binary_tree_recursive(n->left), height_of_binary_tree_recursive(n->right)) + 1;
}

//非递归版本，层次遍历
int height_of_binary_tree1(Node* n) {
	if (n == nullptr)
		return -1;

	int height = 0;
	std::queue<Node*> q1, q2;
	q1.push(n);
	while (!q1.empty() || !q2.empty()) {
		if (!q1.empty()) {
			while (!q1.empty()) {
				Node* t = q1.front();
				q1.pop();

				if (t->left != nullptr)
					q2.push(t->left);
				if (t->right != nullptr)
					q2.push(t->right);
			}
			if (!q2.empty())
				height++;
		}
		else if (!q2.empty()) {
			while (!q2.empty()) {
				Node* t = q2.front();
				q2.pop();

				if (t->left != nullptr)
					q1.push(t->left);
				if (t->right != nullptr)
					q1.push(t->right);
			}
			if (!q1.empty())
				height++;
		}

	}

	return height;
}
*/

/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {

	vector<int> v{ 0 };//value
	vector<int> w{ 0 };//weight
	int s;//storage

	string s1, s2;
	cin >> s1 >> s2 >> s;
	int l1 = 0, r1 = 0;
	while (r1 <= s1.size()) {
		if (s1[r1] >= '0'&&s1[r1] <= '9')
			r1++;
		else if (s1[r1] == ',' || r1==s1.size()) {
			int i = stoi(s1.substr(l1, r1 - l1));
			v.push_back(i);
			r1++;
			l1 = r1;
		}
	}

	int l2 = 0, r2 = 0;
	while (r2 <= s2.size()) {
		if (s1[r2] >= '0'&&s1[r2] <= '9')
			r2++;
		else if (s2[r2] == ',' || r2 == s2.size()) {
			int i = stoi(s2.substr(l2, r2 - l2));
			w.push_back(i);
			r2++;
			l2 = r2;
		}
	}
	
	

	vector<vector<int>> dp(v.size(), vector<int>(s + 1, 0));

	for (int i = 1; i < v.size(); i++) {
		for (int j = 1; j <= s; j++) {
			if (j > w[i])
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			else
				dp[i][j] = dp[i - 1][j];
		}
	}

	int res = 0;
	for (int i = 1; i < v.size(); i++) {
		for (int j = 1; j <= s; j++) {
			if (dp[i][j] > res)
				res = dp[i][j];
		}
	}
	cout << res << endl;

	return 0;

}
*/

/*
#include <string>
#include <iostream>
#include <map>

using namespace std;

int handle(map<string, string>& m, string& s) {
	if (s.size() < 11)
		return -1;

	int space = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ')
			space++;
	}
	if (space != 2)
		return -1;

	if (s.substr(0, 8) != "typedef ")
		return -1;

	int pos2 = s.find_last_of(' ');
	string s1 = s.substr(8, pos2 - 8);
	string s2 = s.substr(pos2 + 1);
	if (s1.empty() || s2.empty())
		return -1;

	m[s2] = s1;
	return 0;
}

int main() {
	string input;
	getline(cin, input);
	if (input.empty() || input.back() != ';') {
		cout << "none" << endl;
		return 0;
	}

	map<string, string> m;

	int end = 0;
	while (!input.empty()) {
		end = input.find_first_of(';');

		string s = input.substr(0, end);
		if (handle(m, s) == -1) {
			cout << "none" << endl;
			return 0;
		}
		end++;
		while (end != input.size() && input[end] == ' ')
			end++;

		if (end == input.size())
			break;
		input = input.substr(end);

	}

	string target;
	cin >> target;

	if (m.find(target) == m.end()) {
		cout << "none" << endl;
		return 0;
	}
	int count_pt = 0;
	while (m.find(target) != m.end()) {
		auto it = m.find(target);
		string t = it->second;
		int pos = t.find_first_of('*');
		if (pos != -1) {
			count_pt += t.size() - pos;
		}
		target = t.substr(0, pos);
	}
	cout << target;
	for (int i = 0; i < count_pt; i++) {
		cout << " " << '*';
	}
	cout << endl;

	return 0;
}
*/

/*
#include <string>
#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	if (n <= 0 || n > 100) {
		cout << "n is not correvt" << endl;
		return 0;
	}

	string str;
	while (n--) {
		cin >> str;
		if (str.size() != 8) {
			cout << "input error" << endl;
			return 0;
		}

		if (str[0] > '2') {
			str[0] = '0';			
		}
		if (str[0] == '2'&&str[1] > '3') {
			str[0] = '0';		
		}
		if (str[3] > '5') {
			str[3] = '0';			
		}
		if (str[6] > '5') {
			str[6] = '0';
		}
		cout << str << endl;
	}
	return 0;
}
*/

/*
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		list<int> l;
		unordered_map<int, list<int>::iterator> m;
		while (n--) {
			int id;
			cin >> id;
			if (m.find(id) == m.end()) {
				auto it = l.insert(l.begin(), id);
				m[id] = it;
			}
			else {
				auto it = m[id];
				l.splice(l.begin(), l, it);
			}
		}
		for (auto it = l.begin(); it != l.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;

	}
}
*/

/*
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
				
		int m, n;
		cin >> m >> n;
		vector<string> dict(m);
		for (int i = 0; i < m; i++) {
			cin >> dict[i];
		}
		string target;
		cin >> target;
		int len = target.size();
		if (len < 2 || len>9)
			return 0;
		
		int count = 0;
		for (int i = 0; i < m ; i++) {
			for (int j = 0; j < n ; j++) {
				if (dict[i][j] == target[0]) {
					for (int s = 1; s < target.size(); s++) {
						if (j + s >= n)
							break;
						if (dict[i][j + s] != target[s])
							break;
						if (s == target.size() - 1)
							count++;
					}

					for (int s = 1; s < target.size(); s++) {
						if (i + s >= m)
							break;
						if (dict[i + s][j] != target[s])
							break;
						if (s == target.size() - 1)
							count++;
					}

					for (int s = 1; s < target.size(); s++) {
						if (i + s >= m || j + s >= n)
							break;
						if (dict[i + s][j + s] != target[s])
							break;
						if (s == target.size() - 1)
							count++;
					}
					
				}
			}
		}
		cout << count << endl;
	}
	return 0;
}
*/

#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
	int t;
	cin >> t;
	//t = 2;
	while (t--) {
		int n;
		cin >> n;
		//n = 3;
		string pre, add;
		map<string, string> con;
		//con["1357"] = "GuangZhou01";
		//con["13680"] = "GuangZhou02";
		//con["13799"] = "HangZhou01";

	
		while (n--) {
			cin >> pre >> add;
			string pre1 = pre.substr(0, pre.find_first_of('x'));
			con[pre1] = add;
		}
		

		int m;
		cin >> m;
		string phone;
		vector<string> v;
		while (m--) {
			cin >> phone;
			v.push_back(phone);
		}
		
		//vector<string> v = { "13579246810","13680246810","13799999999" };
		for (int i = 0; i < v.size(); i++) {
			bool p = false;
			for (auto it : con) {
				string com = v[i].substr(0, it.first.size());
				if (it.first == com) {
					cout << it.second << endl;
					p = true;
					break;
				}
			}
			if (!p)
				cout << "unknown" << endl;
		}
	
	}
	return 0;
}
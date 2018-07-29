#ifndef TEST_H_
#define TEST_H_
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <exception>
using std::string;
using std::vector;
using std::list;
using std::stack;
using std::unordered_set;
using std::unordered_map;
using std::exception;
using namespace std;

bool compare_string(const string& lhs, const string& rhs) {
	string str1 = lhs + rhs;
	string str2 = rhs + lhs;
	for (auto it1 = str1.begin(), it2 = str2.begin(); it1 != str1.end() && it2 != str2.end(); it1++, it2++) {
		if (*it1>*it2)
			return false;
	}
	return true;
}

string PrintMinNumber(vector<int> numbers) {
	//convert number to string

	vector<string> num_str;
	for (auto it = numbers.begin(); it != numbers.end(); it++) {
		if (*it <= 0)
			throw exception();

		stack<int> s;
		while (*it != 0) {
			s.push(*it % 10);
			*it /= 10;
		}
		string str;
		while (!s.empty()) {
			str += ('0' + s.top());
			s.pop();
		}
		num_str.push_back(str);
	}

	//sort
	sort(num_str.begin(), num_str.end());
	sort(num_str.begin(), num_str.end(), [](const string& lhs, const string& rhs) {
		return lhs > rhs;
	});
	sort(num_str.begin(), num_str.end(), [](const string& lhs, const string& rhs)->bool {
		//return (lhs+rhs) < (rhs+lhs);
		
		string str1 = lhs + rhs;
		string str2 = rhs + lhs;
		/*
		//bug is here!!
		for (auto it1 = str1.begin(), it2 = str2.begin(); it1 != str1.end() && it2 != str2.end(); it1++, it2++) {
			if (*it1>*it2)
				return false;
		}
		*/
		return str1<str2;

	});

	//connect sorted strings
	string result;
	for (auto it = num_str.begin(); it != num_str.end(); it++) {
		result += *it;
	}
	return result;
}

int GetNumberOfK(vector<int> data, int k) {
	int count = 0;
	
	//get first k
	int begin = 0;
	int end = data.size() - 1;
	while (end >= begin) {
		if (data[(begin + end) / 2]>k) {
			end = (begin + end) / 2 - 1;
		}
		else if (data[(begin + end) / 2]<k) {
			begin = (begin + end) / 2 + 1;
		}
		else if (data[(begin + end) / 2] == k) {
			if ((begin + end) / 2 == 0 || ((begin + end) / 2>0 && data[(begin + end) / 2 - 1] != k))
				break;
			else
				end = (begin + end) / 2 - 1;
		}
	}
	int first_k = -1;
	if (end >= begin) {//mean it exist
		first_k = (begin + end) / 2;
	}

	//get last k
	begin = 0;
	end = data.size() - 1;
	while (end >= begin) {
		if (data[(begin + end) / 2]>k) {
			end = (begin + end) / 2 - 1;
		}
		else if (data[(begin + end) / 2]<k) {
			begin = (begin + end) / 2 + 1;
		}
		else if (data[(begin + end) / 2] == k) {
			if ((begin + end) / 2 == data.size() - 1 || ((begin + end) / 2<(data.size() - 1) && data[(begin + end) / 2 + 1] != k))
				break;
			else
				begin = (begin + end) / 2 + 1;
		}
	}
	int last_k = -1;
	if (end >= begin) {//mean it exist
		last_k = (begin + end) / 2;
	}

	if (first_k != -1 && first_k != -1) {
		count = last_k - first_k + 1;
	}

	return count;


}

void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
	*num1 = 0;
	*num2 = 0;
	if (data.size()<2) {
		return;
	}

	int result_or = 0;
	for (auto it = data.begin(); it != data.end(); it++) {
		result_or = result_or ^ (*it);
	}

	int first1 = result_or;
	int index = 0;
	while ((first1 & 1) == 0 && (index<8 * sizeof(int))) {
		first1 = first1 >> 1;
		index++;
	}

	for (auto it = data.begin(); it != data.end(); it++) {
		int result = (*it) >> index;
		if (result & 1)
			*num1 = (*num1) ^ (*it);
		else
			*num2 = (*num2) ^ (*it);
	}

	return;

}

vector<vector<int>> FindContinuousSequence(int sum) {
	vector<vector<int>> result;
	if (sum <= 1)
		return result;

	if (sum == 2) {
		result.push_back(vector<int>{sum});
		return result;
	}


	int small = 1;
	int big = 2;
	int add = small + big;

	while ((small<big) && (big<sum)) {
		if (add == sum) {
			vector<int> tmp;
			for (int i = small; i <= big; i++) {
				tmp.push_back(i);
			}
			result.push_back(tmp);
			big++;
			add += big;
		}
		else if (add<sum) {
			big++;
			add += big;
		}
		else {
			add -= small;
			small++;
		}
	}

	return result;
}

string ReverseSentence(string str) {
	int pos = 0;
	int count = 0;
	if (str.empty())
		return str;

	vector<string> vec;
	for (int i = 0; i<str.size(); i++) {
		if (str[i] == ' ' || i== str.size()-1) {
			string tmp = str.substr(pos, count);
			vec.push_back(tmp);
			pos = i + 1;
			count = 0;
		}
		else {
			count += 1;
		}	
	}

	string result;
	for (int i = vec.size() - 1; i>0; i--) {
		result = result + vec[i] + ' ';

	}
	result = result + vec[0];
	return result;

}

struct Node;
struct Node {
	int number;
	Node* next;
};

int LastRemaining_Solution(int n, int m)
{
	if (n<0 || m<0)
		return 0;

	Node* head = new Node;
	head->number = 0;
	Node* t = head;
	int i = 1;
	while (i<n) {
		t->next = new Node;
		t = t->next;
		t->number = i++;
	}
	t->next = head;

	while (head->next != head) {
		for (int i = 0; i<m-1; i++) {
			t = head;
			head = head->next;
		}

		t->next = head->next;
		delete head;
		head = t->next;
	}

	int result = head->number;
	delete head;
	return result;
}

bool duplicate(int numbers[], int length, int* duplication) {
	if (numbers == nullptr || length <= 0)
		return false;

	for (int i = 0; i<length; i++) {
		if (numbers[i]<0 || numbers[i]>length - 1)
			return false;
	}

	for (int i = 0; i<length; i++) {
		while (numbers[i] != i) {
			if (numbers[i] == numbers[numbers[i]]) {
				*duplication = numbers[i];
				return true;
			}

			int tmp = numbers[i];
			numbers[i] = numbers[tmp];
			numbers[tmp] = tmp;
		}
	}
	return false;
}


int getNSumCountNotRecusion(int n, vector<int>& count) {
	count[0] = 0;
	count[1] = count[2] = count[3] = count[4] = count[5] = count[6] = 1;
	if (n == 1) return 0;
	/*
	for (int i = 2; i <= n; ++i) {
		for (int sum = 6 * i; sum >= i; --sum) {
			int tmp1 = ((sum - 1 - (i - 1)) >= 0 ? count[sum - 1 - (i - 1)] : 0); //上一阶段点数和sum-1的排列总数
			int tmp2 = (sum - 2 - (i - 1) >= 0 ? count[sum - 2 - (i - 1)] : 0);
			int tmp3 = (sum - 3 - (i - 1) >= 0 ? count[sum - 3 - (i - 1)] : 0);
			int tmp4(sum - 4 - (i - 1) >= 0 ? count[sum - 4 - (i - 1)] : 0);
			int tmp5 = (sum - 5 - (i - 1) >= 0 ? count[sum - 5 - (i - 1)] : 0);
			int tmp6 = (sum - 6 - (i - 1) >= 0 ? count[sum - 6 - (i - 1)] : 0);
			count[sum - i] = tmp1 + tmp2 + tmp3 + tmp4 + tmp5 + tmp6;
		}
	}
	*/
	for (int i = 2; i <= n; ++i) {
		for (int sum = 6 * i; sum>=i; --sum) {
			int tmp1 = ((sum - 1 - (i - 1)) >= 0 ? count[sum - 1] : 0); //上一阶段点数和sum-1的排列总数
			int tmp2 = ((sum - 2 - (i - 1)) >= 0 ? count[sum - 2] : 0);
			int tmp3 = ((sum - 3 - (i - 1)) >= 0 ? count[sum - 3] : 0);
			int tmp4 = ((sum - 4 - (i - 1)) >= 0 ? count[sum - 4] : 0);
			int tmp5 = ((sum - 5 - (i - 1)) >= 0 ? count[sum - 5] : 0);
			int tmp6 = ((sum - 6 - (i - 1)) >= 0 ? count[sum - 6] : 0);
			count[sum] = tmp1 + tmp2 + tmp3 + tmp4 + tmp5 + tmp6;
		}
	}
	return 0;
}

//n个骰子的点数，好看好懂的代码
void getNsum(int number) {
	if (number < 1)
		return;
	
	int g_face = 6;
	vector<int> count(g_face*number + 1);

	getNSumCountNotRecusion(number, count);

	for (int i = number; i <= number*g_face; i++) {
		printf("%d\n", count[i]);
	}

	return;

}

int lengthOfLongestSubstring(string s) {
	int answer = 0, left = 0, len = s.length();
	int last[255];
	memset(last, -1, sizeof(last));

	for (int i = 0; i<len; ++i) {
		if (left <= last[s[i]])
			left = last[s[i]] + 1;
		last[s[i]] = i;
		answer = std::max(answer, i - left + 1);
	}
	return answer;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	
};

//merge k sorted lists
ListNode* mergeKLists(vector<ListNode*>& lists) {
	if (lists.size() == 0)
		return nullptr;
	if (lists.size() == 1)
		return lists[0];

	vector<ListNode*> heap_node{};
	for (size_t i = 0; i<lists.size(); i++) {
		if (lists[i] != nullptr)
			heap_node.push_back(lists[i]);
	}
	if (heap_node.size() == 0)
		return nullptr;
	std::make_heap(heap_node.begin(), heap_node.end(), [](ListNode* &lhs, ListNode* &rhs) {
		return lhs->val>rhs->val;
	});

	ListNode* p = new ListNode(0);
	ListNode* result = p;

	ListNode* current = nullptr;
	ListNode* next = nullptr;
	while (heap_node.size() != 0) {
		current = heap_node[0];
		next = current->next;
		p->next = current;
		p = p->next;

		std::pop_heap(heap_node.begin(), heap_node.end(), [](ListNode* &lhs, ListNode* &rhs) {
			return lhs->val>rhs->val;
		});
		heap_node.pop_back();

		if (next != nullptr) {
			heap_node.push_back(next);
			std::push_heap(heap_node.begin(), heap_node.end(), [](ListNode* &lhs, ListNode* &rhs) {
				return lhs->val>rhs->val;
			});
		}
		else {
			std::make_heap(heap_node.begin(), heap_node.end(), [](ListNode* &lhs, ListNode* &rhs) {
				return lhs->val>rhs->val;
			});
		}

	}

	ListNode* reverse = result->next;
	delete result;
	return reverse;
}



void test_casual() {
	string s1{ "戴愿桥" };
	string s2{ "dai" };
	std::cout << s1[0] << s1[2] << std::endl;
	std::cout << "戴" << std::endl;
	std::cout << s1.size() << std::endl;
	

	std::cout << s2[0] << s2[2] << std::endl;
	std::cout << s2.size() << std::endl;


	ListNode* n1 = new ListNode(1);
	n1->next = new ListNode(4);
	n1->next->next= new ListNode(5);
	n1->next->next->next = nullptr;

	ListNode* n2 = new ListNode(1);
	n2->next = new ListNode(3);
	n2->next->next = new ListNode(4);
	n2->next->next->next = nullptr;

	ListNode* n3 = new ListNode(2);
	n3->next = new ListNode(6);
	n3->next->next = nullptr;
	
	vector<ListNode*> n{ n1,n2,n3 };
	mergeKLists(n);

	int num = 2;
	num = num*num*num;
	std::printf("the number tested: %d\n", num);


	auto it1 = [](const int& lhs, const int& rhs)->bool {
		if (lhs < rhs)
			return true;
		else
			return false;
	};

	auto it2 = [](const int& lhs, const int& rhs) {
		return lhs > rhs;
	};

	auto it3 = [](const int& lhs, const int& rhs) {
		int i = 0;

		if (lhs == rhs)
			return true;
		else
			return false;
	};

	bool b1 = it1(1, 3);
	bool b2 = it2(1, 3);
	bool b3 = it3(1, 3);
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};
void inorder(TreeNode* root, vector<int>& result) {
	if (root == nullptr)
		return;

	inorder(root->left, result);
	result.push_back(root->val);
	inorder(root->right, result);

}

bool isValidBST(TreeNode* root) {
	vector<int> result;
	inorder(root, result);

	for (int i = 0; i<result.size() - 1; i++) {
		if (result[i] >= result[i + 1])
			return false;
	}

	return true;
}


bool findPath(TreeNode* root, TreeNode* p, list<TreeNode*>& path) {
	if (root == nullptr)
		return false;

	bool find = false;
	path.push_back(root);

	if (root == p) {
		find = true;
	}
	if (!find && root->left != nullptr) {
		find = findPath(root->left, p, path);
	}
	if (!find && root->right != nullptr) {
		find = findPath(root->right, p, path);
	}
	if (!find)
		path.pop_back();

	return find;
}



TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

	if (root == nullptr || p == nullptr || q == nullptr)
		return nullptr;

	list<TreeNode*> path1;
	list<TreeNode*> path2;
	bool find1 = findPath(root, p, path1);
	bool find2 = findPath(root, q, path2);

	if (!find1 || !find2)
		return nullptr;

	auto it1 = path1.begin();
	auto it2 = path2.begin();
	TreeNode* result = nullptr;
	while (it1 != path1.end() && it2 != path2.end()) {
		if (*it1 == *it2)
			result = *it1;

		it1++;
		it2++;
	}
	return result;

	/*
	if (!root || p == root || q == root) return root;
	TreeNode *left = lowestCommonAncestor(root->left, p, q);
	if (left && left != p && left != q) return left;
	TreeNode *right = lowestCommonAncestor(root->right, p , q);
	if (right && right != p && right != q) return right;
	if (left && right) return root;
	return left ? left : right;
	*/
}

void test_lowestCommonAncestor() {
	TreeNode* root = new TreeNode(1);
	root->left= new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = nullptr;
	root->left->right = nullptr;
	root->right->left = nullptr;
	root->right->right = nullptr;

	lowestCommonAncestor(root, root->left, root->right);
}

vector<vector<int>> generate1(int numRows) {
	vector<vector<int>> res;

	if (numRows <= 0)
		return res;

	res.push_back(vector<int>{1});
	int n = 2;
	while (n <= numRows) {
		if (n % 2 == 0) {
			vector<int> t;
			t.push_back(1);
			for (int i = 1; i<=res[n - 2].size() / 2; i++) {
				t.push_back(res[n - 2][i] + res[n - 2][i - 1]);
			}
			for (int i = n / 2 - 1; i >= 0; i--) {
				t.push_back(t[i]);
			}
			res.push_back(t);
		}
		else {
			vector<int> t;
			t.push_back(1);
			for (int i = 1; i<=res[n - 2].size() / 2; i++) {
				t.push_back(res[n - 2][i] + res[n - 2][i - 1]);
			}
			//t.push_back(res[n - 2][n / 2] * 2);
			for (int i = n / 2 - 1; i >= 0; i--) {
				t.push_back(t[i]);
			}
			res.push_back(t);
		}

		n++;
	}

	return res;
}

int maxProfit(vector<int>& prices) {
	if (prices.size() <= 1)
		return 0;

	int max = 0;
	int pre = prices[0];

	for (int i = 1; i<prices.size(); i++) {
		if (prices[i]<pre) {
			pre = prices[i];
			continue;
		}
		else if (prices[i]>pre) {
			max += (prices[i] - pre);
			pre = prices[i];
		}
	}

	return max;
}

void wordBreakCore(const string& s, int start, const unordered_set<string>& word, vector<string>& out, vector<string>& result) {
	if (start == s.size()) {
		string t;
		for (int i = 0; i<out.size()-1; i++) {
			t += out[i];
			t += ' ';
		}
		t += out[out.size() - 1];
		result.push_back(t);
		return;
	}

	for (int i = start; i<s.size(); i++) {
		if (word.find(s.substr(start, i - start + 1)) != word.end()) {
			out.push_back(s.substr(start, i - start + 1));
			wordBreakCore(s, i+1, word, out, result);
			out.pop_back();
		}
		
	}

}

vector<string> wordBreak(string s, vector<string>& wordDict) {
	unordered_set<string> word(wordDict.begin(), wordDict.end());
	vector<string> out;
	vector<string> res;
	wordBreakCore(s, 0, word, out, res);
	return res;
}


int count_and_consume_core(int number, int cost_sum, int& max_consume, vector<int>& cost,
	unordered_map<int, vector<int>>& m) {

	int count = 0;
	if (m.find(number) == m.end()) {
		max_consume = max(max_consume, cost_sum + cost[number]);
		return 1;
	}
	else {
		for (auto it : m[number]) {
			count += count_and_consume_core(it, cost_sum + cost[number], max_consume, cost, m);
		}
	}
	return count;
}
void count_and_consume() {
	int m, n;
	cin >> m >> n;
	int m1 = m;
	vector<int> cost{ 0 };
	int consume;
	while (m--) {
		cin >> consume;
		cost.push_back(consume);
	}
	
	
	vector<int> in(m1 + 1, 0);
	unordered_map<int, vector<int>> connect;
	int sys1, sys2;
	while (n--) {
		cin >> sys1 >> sys2;
		if (connect.find(sys2) == connect.end()) {
			connect[sys2] = vector<int>{ sys1 };
		}
		else {
			connect[sys2].push_back(sys1);
		}
		in[sys1]++;
	}
	
	int max = 0, count = 0;
	for (int i = 1; i <= m1; i++) {
		if (in[i] == 0) {
			count += count_and_consume_core(i, 0, max, cost, connect);
		}
	}

	cout << count <<"  "<< max << endl;

	return;
}


int trailingZeroes(int n) {
	int res = 0;
	while (n) {
		res += n / 5;
		n /= 5;
	}
	return res;

}

void test() {
	vector<int> str1{ 321,32,3 };
	vector<int> str2{ 3,5,1,4,2 };
	//PrintMinNumber(str1);
	PrintMinNumber(str2);

	vector<int> str3{ 3,3,3,3,4,5 };
	GetNumberOfK(str3, 3);

	vector<int> str4{ 2,4,3,6,3,2,5,5 };
	int num1;
	int num2;
	FindNumsAppearOnce(str4, &num1, &num2);

	FindContinuousSequence(9);

	string str5{ "I am a student." };
	ReverseSentence(str5);

	LastRemaining_Solution(5, 3);

	int numbers[5] = { 2,1,3,1,4 };
	int t = 0;
	int* duplication = &t;
	duplicate(numbers, 5, duplication);

	vector<string> v{ 10,"hello" };
	size_t i = v.size();

	getNsum(3);

	string s{ "abcabcbb" };
	lengthOfLongestSubstring(s);

	test_lowestCommonAncestor();

	generate1(5);

	vector<int> prices{ 7,1,5,3,6,4 };
	maxProfit(prices);

	string wordBreaks{ "catsanddog" };
	vector<string> wordDict{ "cat","cats","and","sand","dog" };
	vector<string> res = wordBreak(wordBreaks, wordDict);

	//count_and_consume();

	int res2016 = trailingZeroes(2016);

	test_casual();

	return;
}



#endif // !TEST_H_
#21740 도도의 수학놀이 by joshua5301

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp_str(string s1, string s2) {
	return s1+s2 > s2+s1;
}

void reverse_num(string& s) {
	char t;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '9') s[i] = '6';
		else if (s[i] == '6') s[i] = '9';
	}
	for (int i = 0; i < s.length() / 2; i++) {
		t = s[i];
		s[i] = s[s.length() - i - 1];
		s[s.length() - i - 1] = t; 
	}

}

void add_additional_num(vector<string>& l){
	string max_s = "";
	for (int i = 0; i < l.size(); i++){
		if(max_s.length() < l[i].length()){
			max_s = l[i];
		}
		else if(max_s.length() == l[i].length()){
			if(max_s < l[i]){
				max_s = l[i];
			}
		}
	}
	l.push_back(max_s);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int num;
	vector<string> input_list;
	string t1, t2;
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> t1;
		reverse_num(t1);
		input_list.push_back(t1);
	}
	add_additional_num(input_list);
	sort(input_list.begin(), input_list.end(), cmp_str);

	string result = "";
	for (int i = 0; i < num + 1; i++) {
		result += input_list[i];
	}
	reverse_num(result);
	cout << result;
	return 0;
}
//2042 구간 합 구하기 by joshua5301

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

ll initSeg(vector<ll>& arr, vector<ll>& seg_tree, int idx, ll start, ll end){
    if(start == end){
        seg_tree[idx] = arr[end];
    }
    else {
        seg_tree[idx] = 
        initSeg(arr, seg_tree, idx * 2, start, (start + end) / 2) + 
        initSeg(arr, seg_tree, idx * 2 + 1, (start + end) / 2 + 1, end);
    }
    return seg_tree[idx];
}

ll findSeg(vector<ll>& seg_tree, ll idx, ll start, ll end, ll q_start, ll q_end){
    if(end < q_start || q_end < start){
        return 0;
    }
    else if(q_start <= start && end <= q_end){
        return seg_tree[idx];
    }
    else{
        return findSeg(seg_tree, idx * 2, start, (start + end) / 2, q_start, q_end) + 
        findSeg(seg_tree, idx * 2 + 1, (start + end) / 2 + 1, end, q_start, q_end);
    } 
}

void updateSeg(vector<ll>& seg_tree, ll idx, ll start, ll end, ll target, ll diff){
    if(start > target || end < target){
        return;
    }
    seg_tree[idx] += diff;
    if(start != end){
        updateSeg(seg_tree, idx * 2, start, (start + end) / 2, target, diff);
        updateSeg(seg_tree, idx * 2 + 1, (start + end) / 2 + 1, end, target, diff);
    } 
}

void printVec(vector<ll>& vec){
    for(int i; i < vec.size(); i++){
        cout << vec[i] << '\n';
    }
    cout << '\n';
}

int main(){
    ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    ll num_num, update_num, query_num;
    ll a, b, c;
    vector<ll> arr;
    vector<ll> seg_tree;

    cin >> num_num >> update_num >> query_num;
    arr.resize(num_num);
    seg_tree.resize(num_num * 4);
    for(int i = 0; i < num_num; i++){
        cin >> arr[i];
    }
    initSeg(arr, seg_tree, 1, 0, num_num - 1);
    //printVec(seg_tree);
    
    for(int i = 0; i < update_num + query_num; i++){
        cin >> a >> b >> c;
        if(a == 1){
            updateSeg(seg_tree, 1, 0, num_num - 1, b - 1, c - arr[b - 1]);
            arr[b - 1] = c;
        }
        else if(a == 2){
            cout << findSeg(seg_tree, 1, 0, num_num - 1, b - 1, c - 1) << '\n';
        }
        //printVec(seg_tree);
    }
    return 0;
}
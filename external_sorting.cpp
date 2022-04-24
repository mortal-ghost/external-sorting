#include <bits/stdc++.h>
using namespace std;


// Get one sorted page on each call
void merge(vector<vector<int>> &runs, vector<int> &temp){
    vector<int> pointer;
    int num = 0;
    int min, k, i, j;

    for (i = 0; i < runs.size(); i++){
        pointer.push_back(0);
        num += runs[i].size();
    }

    for (i = 0; i < num; i++){
        min = INT_MAX;
        k = 0;

        for (j = 0; j < pointer.size(); j++){
            if (pointer[j] < runs[j].size() && runs[j][pointer[j]] < min){
                min = runs[j][pointer[j]];
                k = j;
            }
        }

        temp.push_back(min);
        pointer[k]++;
    }
}

void external_sort(vector<vector<int>>& runs, int buffer){
    // Intially sorting each page
    for (int i = 0; i < runs.size(); i++){
        sort(runs[i].begin(), runs[i].end());
    }

    while (runs.size() > 1){
        vector<vector<int>> sorted_runs;
        int k = 0, i = 0;
        vector<vector<int>> temp;
        vector<int> temp1;

        while (i < runs.size()){
            temp.clear();
            for (k = 0; k < buffer - 1 && i + k < runs.size(); k++){
                temp.push_back(runs[i + k]);
            }
            temp1.clear();
            // Merging buffer-1 runs
            merge(temp, temp1);
            sorted_runs.push_back(temp1);
            i += k;
        }
        runs = sorted_runs;
    }
}

int main(){
    int buffer, page_size, total_records;

    cin >> buffer >> page_size >> total_records;

    vector<vector<int>> runs;

    int k = 0, i = 0, a;
    vector<int> temp;

    while (i < total_records){
        temp.clear();
        for (k = 0; k < page_size && i + k < total_records; k++){
            cin >> a;
            temp.push_back(a);
        }
        runs.push_back(temp);
        i += k;
    }
    external_sort(runs, buffer);
    for (i = 0; i < runs[0].size(); i++){
        cout << runs[0][i] << "\n";
    }
    return 0;
}
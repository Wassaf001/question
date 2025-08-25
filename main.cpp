#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Order{
public:
    int truck_id;
    int units;
    int timestamp;

    Order(){
        this->truck_id = 0;
        this->units = 0;
        this->timestamp = 0;
    }
};

bool cmp(const Order& a, const Order& b) {
    return a.timestamp < b.timestamp; 
}

vector<vector<int>> get_all_combinations(int k, int a[]){
    vector<vector<int>> res;
    int n = 3; 
    for (int mask = 1; mask < (1 << n); mask++) {
        int sum = 0;
        vector<int> comb;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += a[i];
                comb.push_back(i); 
            }
        }
        if (sum >= k) { 
            res.push_back(comb);
        }
    }
    return res;
}

vector<vector<int>> intersect(vector<vector<int>> a, vector<vector<int>> b){
    vector<vector<int>> res;
    set<vector<int>> s(b.begin(), b.end()); 
    for (auto &x : a) {
        if (s.count(x)) {
            res.push_back(x);
        }
    }
    return res;
}

int find_min_cost_at_timestamp(int i, vector<int> at_timestamp, vector<Order>& orders, int tw[], int tv[], int dd, int dw, int unit_v, int unit_w, int cf1, int cf2, int cf3){
    int cost = 0;
    int total_weight = at_timestamp[i]*unit_w;
    int total_volume = at_timestamp[i]*unit_v;
    vector<vector<int>> volume_fit = get_all_combinations(total_volume, tv);
    vector<vector<int>> weight_fit = get_all_combinations(total_weight, tw);
    vector<vector<int>> possible_combinations = intersect(volume_fit, weight_fit);
    
    cout << "Timestamp " << i << " (needs " << total_volume << " volume, " << total_weight << " weight):" << endl;
    cout << "  Volume-fit combinations: ";
    for(auto& comb : volume_fit) {
        cout << "[";
        for(int j = 0; j < comb.size(); j++) {
            cout << tv[comb[j]];
            if(j < comb.size()-1) cout << "+";
        }
        cout << "] ";
    }
    cout << endl;
    
    cout << "  Weight-fit combinations: ";
    for(auto& comb : weight_fit) {
        cout << "[";
        for(int j = 0; j < comb.size(); j++) {
            cout << tw[comb[j]];
            if(j < comb.size()-1) cout << "+";
        }
        cout << "] ";
    }
    cout << endl;
    
    cout << "  Feasible combinations: ";
    for(auto& comb : possible_combinations) {
        cout << "[";
        for(int j = 0; j < comb.size(); j++) {
            cout << "Truck" << comb[j] << "(" << tv[comb[j]] << "v," << tw[comb[j]] << "w)";
            if(j < comb.size()-1) cout << "+";
        }
        cout << "] ";
    }
    cout << endl;
    
    vector<int> costs;
    for(auto m: possible_combinations){
        int temp = 0;
        for(auto j: m){
            if(j==0){
                temp += cf1*dw;
            }
            else if(j==1){
                temp += cf2*dw;
            }
            else{
                temp += cf3*dw;
            }
        }
        costs.push_back(temp);
    }
    if (costs.empty()) {
        cout << "  No feasible combination found!" << endl;
        return -1;
    }
    cost = *min_element(costs.begin(), costs.end());
    cout << "  Minimum cost: " << cost << endl << endl;
    return cost;
}

int find_min_cost_for_replenishment(vector<Order>& orders, int tw[], int tv[], int dd, int dw, int unit_v, int unit_w, int cf1, int cf2, int cf3){
   int res = 0;
   // sorting orders on the basis of timestamp
   sort(orders.begin(), orders.end(), cmp);
   int start_time = orders[0].timestamp;
   int end_time = orders[orders.size()-1].timestamp;
   // find the total quantity at each timestamp
   vector<int> at_timestamp(end_time+1);
   for(int i=start_time; i<=end_time; i++){
        for(const Order& order : orders){
            if(order.timestamp == i){
                at_timestamp[i] += order.units;
            }
        }
    }
   cout << "at_timestamp: " << " ";
   for(auto i: at_timestamp){
    cout << i << " ";
   }
   cout << endl;
   int min_cost = 0;
   for(int i=start_time; i<=end_time; i++){
     min_cost += find_min_cost_at_timestamp(i, at_timestamp, orders, tw, tv, dd, dw, unit_v, unit_w, cf1, cf2, cf3);
   }
   return min_cost;
}

int main(){
   vector<Order> orders;
   cout << "Enter the number of orders: ";
//    Like:
//    3
//    1 200 1
//    2 100 1
//    3 500 4
    int n; cin >> n;
    cout << "Enter the orders: " << endl;
    for(int i=0; i<n; i++){
        Order order;
        cin >> order.truck_id >> order.units >> order.timestamp;
        orders.push_back(order);
    }
    int unit_w = 1; // 1 unit weight is 1 kg
    int unit_v = 20; // 1 unit volume is 20 cubic meter
    int dw = 1; // distance between dark store and warehouse, same for all
    // cout << "Enter distance of dark stores from warehouse: ";
    // cin >> dw;
    int dd = 2; // distance between each dark store
    int cf1 = 1, cf2 = 2, cf3 = 3; // cost factor for each truck i.e. its weight divided by 100
    int truck_w[3] = {100, 200, 500};
    int truck_v[3] = {1000, 2000, 5000};
    //  cost = cost_factor_of_truck*total_distance_travelled
    int cost = find_min_cost_for_replenishment(orders, truck_w, truck_v, dd, dw, unit_v, unit_w, cf1, cf2, cf3);
    cout << "Minimum cost to replenish all orders: " << cost << endl;
    return 0;
}   
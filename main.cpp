#include <iostream>
#include <vector>
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

bool cmp(Order& a, Order& b) {
    return a.timestamp < b.timestamp; 
}

vector<vector<int>> get_all_combinations(int k, int a[]){
    vector<vector<int>> res;

    return res;
}

vector<vector<int>> intersect(vector<vector<int>> a, vector<vector<int>> b){
    vector<vector<int>> res;

    return res;
}

int find_min_cost_at_timestamp(int i, vector<int> at_timestamp, vector<Order>& orders, int tw[], int tv[], int dd, int dw, int unit_v, int unit_w, int cf1, int cf2, int cf3){
    int cost = 0;
    int total_weight = at_timestamp[i]*unit_w;
    int total_volume = at_timestamp[i]*unit_v;
    vector<vector<int>> volume_fit = get_all_combinations(total_volume, tv);
    vector<vector<int>> weight_fit = get_all_combinations(total_weight, tw);
    vector<vector<int>> possible_combinations = intersect(volume_fit, weight_fit);
    // for example for 300, 
    vector<int> costs;
    for(auto i: possible_combinations){
        int temp = 0;
        for(auto j: i){
            // need to figure out the total distance travelled by each truck, as of now lets assume all dark stores are at origin
            // these if-else can be removed if we just take the truck cost factors as an array, then we can reference them using index
            if(j==0){

            }
            else if(j==1){

            }
            else{

            }
        }
    }
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
     min_cost += find_min_cost_at_timestamp(i, at_timestamp, orders, tw, tv, dd, dw, unit_v, unit_w, cf1, cf2, cf3)
   }
   return min_cost;
}

void main(){
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
    int dw = 1.5; // distance between dark store and warehouse, same for all
    // cout << "Enter distance of dark stores from warehouse: ";
    // cin >> dw;
    int dd = 2; // distance between each dark store
    int cf1 = 1, cf2 = 2, cf3 = 3; // cost factor for each truck i.e. its weight divided by 100
    int truck_w[3] = {100, 200, 500};
    int truck_v[3] = {1000, 2000, 5000};
    //  cost = cost_factor_of_truck*total_distance_travelled
   int cost = find_min_cost_for_replenishment(orders, truck_v, truck_w, dd, dw, unit_v, unit_w, cf1, cf2, cf3);
   cout << "Minimum cost to replenish all orders: " << cost << endl;
}   
#include <iostream>
using namespace std;

struct Truck {
    int id;
    int weightCap;
    int volCap;
    int costFactor;
};

struct Order {
    int units;
    int store;
    int timestamp;
};

double wh_to_store = 1.5;  // warehouse to any store
double store_to_store = 2.0;
int unitWeight = 1;
int unitVol = 20;

// Compute best distance for visiting multiple stores (simple TSP for <=3 stores)
double bestRouteDistance(vector<int> stores) {
    if (stores.size() == 1) {
        return 2 * wh_to_store; // go and return
    }
    if (stores.size() == 2) {
        // Try both orders: W->S1->S2->W  OR  W->S2->S1->W
        double d1 = wh_to_store + store_to_store + wh_to_store;
        double d2 = wh_to_store + store_to_store + wh_to_store;
        return min(d1, d2);
    }
    // For more stores, try all permutations (brute force small TSP)
    vector<int> perm = stores;
    double best = 1e9;
    sort(perm.begin(), perm.end());
    do {
        double dist = 0;
        dist += wh_to_store; // W -> first
        for (int i = 0; i + 1 < perm.size(); i++)
            dist += store_to_store;
        dist += wh_to_store; // last -> W
        best = min(best, dist);
    } while (next_permutation(perm.begin(), perm.end()));
    return best;
}

int main() {
    // Define trucks
    vector<Truck> trucks = {
        {1, 100, 1000, 1},
        {2, 200, 2000, 2},
        {3, 500, 5000, 5}
    };

    // Define orders
    vector<Order> orders = {
        {200, 1, 1},
        {100, 2, 1},
        {500, 3, 3}
    };

    // Group orders by timestamp
    map<int, vector<Order>> grouped;
    for (auto &o : orders) grouped[o.timestamp].push_back(o);

    double totalCost = 0;

    for (auto &[t, ords] : grouped) {
        cout << "\nProcessing timestamp " << t << "...\n";

        // Gather stores, weight, volume
        vector<int> stores;
        int totalWeight = 0, totalVol = 0;
        for (auto &o : ords) {
            stores.push_back(o.store);
            totalWeight += o.units * unitWeight;
            totalVol += o.units * unitVol;
        }

        // Try each truck
        vector<pair<int,double>> candidates;
        for (auto &tr : trucks) {
            int trips = max(
                (totalWeight + tr.weightCap - 1) / tr.weightCap,
                (totalVol + tr.volCap - 1) / tr.volCap
            );
            if (trips > 0) {
                double routeDist = bestRouteDistance(stores);
                double cost = tr.costFactor * (routeDist * trips);
                candidates.push_back({tr.id, cost});
            }
        }

        // Pick cheapest
        auto best = *min_element(candidates.begin(), candidates.end(),
            [](auto &a, auto &b){ return a.second < b.second; });

        cout << "Best Truck = " << best.first 
             << " | Cost = " << best.second << "\n";

        totalCost += best.second;
    }

    cout << "\nTotal Optimised Cost = " << totalCost << endl;
    return 0;
}

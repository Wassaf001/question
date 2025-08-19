# 🚚 Truck Delivery Optimisation Problem

## 📌 Problem Statement
We have a set of **warehouses**, **trucks**, and **dark stores**. Each dark store places orders that must be fulfilled at specific timestamps. Each order has a **weight** and **volume requirement**, and each truck has corresponding **capacity constraints**.  

We want to **optimise overall delivery cost** while ensuring that all orders are fulfilled.

---

## 🚛 Constraints

### Trucks at Warehouse
- Truck 1 → **Capacity:** 100 kg, 1000 m³ | **Cost Factor (CF):** 1  
- Truck 2 → **Capacity:** 200 kg, 2000 m³ | **Cost Factor (CF):** 2  
- Truck 3 → **Capacity:** 500 kg, 5000 m³ | **Cost Factor (CF):** 5  

### Orders
- `200 units` at Dark Store 1, Timestamp 1  
- `100 units` at Dark Store 2, Timestamp 1  
- `500 units` at Dark Store 3, Timestamp 3  

### Unit Constraints
- Each unit = **1 kg** and **20 m³**  

### Distances
- Warehouse → any Dark Store = **1.5 km**  
- Dark Store ↔ Dark Store = **2 km**  

---

## 🎯 Goal
Deliver all orders at their required timestamps **with minimum delivery cost**, where:  

Cost = Cost Factor (CF) × Total Distance Travelled


---

## 🧩 Algorithm

1. **Group Orders by Timestamp**  
   - All orders with the same timestamp can be considered together.  

2. **Calculate Weight and Volume Requirements**  
   - Weight = units × 1  
   - Volume = units × 20  

3. **Check Feasible Trucks**  
   - A truck can only be used if both **weight** and **volume** fit within its capacity.  
   - If not, the order must be split into **multiple trips**.  

4. **Route Optimisation**  
   - For multiple stores in one timestamp, compute the **minimum route distance**:  
     - Warehouse → Store1 → Store2 … → Warehouse  
     - Try all permutations (TSP brute force) since ≤4 stores.  

5. **Cost Calculation**  

Cost = CF × (Route Distance × Trips)


6. **Choose Truck Combination with Lowest Cost**.  

---

## ⚡ Complexity Analysis

- **Order Grouping:** O(N log N), where N = number of orders (due to sorting by timestamp).  
- **Truck Assignment:** O(N × T), where T = number of trucks.  
- **Route Optimisation:** O(k!), where k = number of stores in a single timestamp. (Since k ≤ 4, this is feasible.)  
- **Overall:**  

Time Complexity = O(N log N + N × T + k!)
Space Complexity = O(N + T)


---

## 🖥️ Example Walkthrough

### Timestamp 1
Orders:  
- 200 units (D1) → 200 kg, 4000 m³  
- 100 units (D2) → 100 kg, 2000 m³  

Combined Requirement: **300 kg, 6000 m³**  

- Truck 1 → Not possible (too small).  
- Truck 2 → Not possible (too small).  
- Truck 3 → Possible with **2 trips**.  

Route distance: `W → D1 → D2 → W = 1.5 + 2 + 1.5 = 5 km`  
Total distance = `2 trips × 5 km = 10 km`  
Cost = `CF(5) × 10 = 50`  

---

### Timestamp 3
Orders:  
- 500 units (D3) → 500 kg, 10000 m³  

- Needs **2 trips of Truck 3** (since max volume = 5000 m³).  

Route distance = `W → D3 → W = 1.5 + 1.5 = 3 km`  
Total distance = `2 trips × 3 km = 6 km`  
Cost = `CF(5) × 6 = 30`  

---

✅ **Total Optimised Cost = 80**

---

## 📝 C++ Code

The implementation of the above algorithm is provided in [`main.cpp`](./main.cpp).  
It handles:
- Multiple orders at same timestamp (batched together).  
- Splitting across multiple trips when capacity exceeded.  
- Route optimisation (shortest permutation).  

---

## 🚀 How to Run

```bash
g++ main.cpp -o delivery
./delivery


Expected output (for given test case):

Processing timestamp 1...
Best Truck = 3 | Cost = 50

Processing timestamp 3...
Best Truck = 3 | Cost = 30

Total Optimised Cost = 80

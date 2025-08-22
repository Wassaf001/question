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
   - If not, the order must be split into **multiple trucks**.  

4. **Route Optimisation**  
   - For multiple stores in one timestamp, compute the **minimum route distance**:  
     - Warehouse → Store1 → Store2 … → Warehouse  
     - Try all permutations.  

5. **Cost Calculation**  

Cost = CF × (Route Distance)


6. **Choose Truck Combination with Lowest Cost**.  

---

## ⚡ Complexity Analysis


---

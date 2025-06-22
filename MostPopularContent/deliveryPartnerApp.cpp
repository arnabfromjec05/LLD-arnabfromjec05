/**
 * Delivery app with partners doing multiple deliveries in a day.
 * Functional req:
 * 1. Compute the average rating of all the deliveries a partner would have done.
 * 2. Top k delivery partners
 */

#include<bits/stdc++.h>
#include<iostream>
using namespace std;

class Order {
    public:
        int orderId;
        double amount;
        double rating;

        Order(int orderId, double amount, int rating) {
            this->orderId = orderId;
            this->amount = amount;
            this->rating = rating;
        }
};

class DeliveryPartner {
    public:
        int partnerId;
        string name;
        vector<Order*> orders;
        double avgOrderRating;

        DeliveryPartner(int partnerId, string name) {
            this->partnerId = partnerId;
            this->name = name;
            this->avgOrderRating = 0;
        }

        void deliveredOrder(Order* order) {
            int numOrders = orders.size();
            orders.push_back(order);
            avgOrderRating = (avgOrderRating * numOrders + order->rating) * 1.0 / (numOrders + 1);
        }

        double getRating() {
            return avgOrderRating;
        }
};

struct Comp {
    bool operator()(DeliveryPartner* p1, DeliveryPartner* p2) {
        if (p1->avgOrderRating > p2->avgOrderRating) {
            return true;
        } else if(p1->avgOrderRating == p2->avgOrderRating) {
            return p1->orders.size() > p2->orders.size();
        }
        return false;
    }
};

class DeliveryApp {
    vector<DeliveryPartner*> partners;

    bool static comp(DeliveryPartner* p1, DeliveryPartner* p2) {
        return p1->avgOrderRating > p2->avgOrderRating;
    }

    public:
        DeliveryPartner* addDeliveryPartner(int partnerId, string name) {
            DeliveryPartner* p = new DeliveryPartner(partnerId, name);
            partners.push_back(p);
            return p;
        }

        void addOrderDelivery(DeliveryPartner* partner, Order* order) {
            partner->deliveredOrder(order);
        }

        vector<DeliveryPartner*> topK(int k) {
            vector<DeliveryPartner*> res;
            
            // 1> Using sorting to find top k delivery partners:
            //sort(partners.begin(), partners.end(), comp);
            // for (int i=0; i<k; i++) {
            //     res.push_back(partners[i]);
            // }

            // 2> Using Priority queue
            priority_queue<DeliveryPartner*, vector<DeliveryPartner*>, Comp> pq;
            for (auto p: partners) {
                if (pq.size() < k) {
                    pq.push(p);
                } else {
                    if (p->avgOrderRating > pq.top()->avgOrderRating) {
                        pq.pop();
                        pq.push(p);
                    }
                }
            }
            
            while(!pq.empty()) {
                res.push_back(pq.top());
                pq.pop();
            }
            return res;
        }
};

int main() {

    DeliveryApp* app = new DeliveryApp();
    DeliveryPartner* p1 = app->addDeliveryPartner(1, "abc");
    DeliveryPartner* p2 = app->addDeliveryPartner(2, "def");
    DeliveryPartner* p3 = app->addDeliveryPartner(3, "ghi");

    app->addOrderDelivery(p1, new Order(1, 100, 4));
    app->addOrderDelivery(p1, new Order(2, 100, 6));
    app->addOrderDelivery(p1, new Order(3, 100, 5));

    app->addOrderDelivery(p2, new Order(4, 100, 1));
    app->addOrderDelivery(p2, new Order(5, 100, 2));

    app->addOrderDelivery(p3, new Order(6, 100, 10));
    app->addOrderDelivery(p3, new Order(7, 100, 11));
    app->addOrderDelivery(p3, new Order(8, 100, 12));

    cout<<p1->getRating()<<endl;
    cout<<p2->getRating()<<endl;
    cout<<p3->getRating()<<endl;

    for(auto p: app->topK(2)) {
        cout<<"PartnerId: "<<p->partnerId<<" Rating: "<<p->getRating()<<endl;
    }

    return 0;
}
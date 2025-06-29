/**
 * 
 * Subscription of products
Given is the pricing plan (monthly) for products and customers would subsrcibe to the list of products.

// Atlassian pricing plans[
  {
     "planId": "BASIC",
     "monthlyCost": "9.99" 
  },
  {
     "planId": "STANDARD",
     "monthlyCost": "49.99" 
  },
  {
     "planId": "PREMIUM",
     "monthlyCost": "249.99" 
  }
]//Customersubscriptioninformation {
   "customerId": "c1",
   "product": {
     "name": "Jira",
     "subscription": {
       "planId": "BASIC",
       "startDate": "2021-01-01"//YYYY-MM-DDformat 
    } 
  } 
}
Create model classes and service classe(s) (CostExplorer) to expose the below two APIs:

monthlyCostList(): Array/List of size 12 filled with cost incurred in each month of the unit year annualCost(): Total cost in a unit year

Consider the annual package from JAN - DEC. For simplicity, let's assume we will charge the customer for the entire month even if the customer is subscribing any day after the 1st of the month.
 */

#include<bits/stdc++.h>
#include<iostream>
#include<map>
using namespace std;

enum Plan {
    BASIC,
    STANDARD,
    PREMIUM
};

class PlanPrices {
    static map<Plan, double> planPrices;
    public:
        static void initPlanPrices(map<Plan, double> planPrices) {
            PlanPrices::planPrices = planPrices;
        }

        static double getPriceForPlan(Plan plan) {
            if (planPrices.find(plan) == planPrices.end()) {
                throw std::runtime_error("Plan price not found");
            }
            return planPrices[plan];
        }
};
map<Plan, double> PlanPrices::planPrices;

class ProductSubscription {
    string productName;
    Plan planId = Plan::BASIC;
    string startDate;

    static vector<string> tokenize(string word, char del) {
        vector<string> res;
        string temp = "";
        for (auto ch: word) {
            if (ch != del) {
                temp += ch;
            } else {
                res.push_back(temp);
                temp = "";
            }
        }
        res.push_back(temp);
        return res;
    }

    public:
        ProductSubscription(string productName, Plan planId, string startDate) {
            this->productName = productName;
            this->planId = planId;
            this->startDate = startDate;
        }

        Plan getPlanId() {
            return planId;
        }

        int getSubscribedMonth() {
            vector<string> tokens = tokenize(this->startDate, '-');
            return stoi(tokens[1]); // extract month value from the date
        }
};

class Customer {
    string customerId;
    vector<ProductSubscription*> productSubs;

    public:
        Customer(string customerId, vector<ProductSubscription*> prodcutSubs) {
            this->customerId = customerId;
            this->productSubs = prodcutSubs;
        }

        vector<double> getMonthlyCostList() {
            vector<double> prefixSum(12, 0);
            for(auto ps: productSubs) {
                Plan planId = ps->getPlanId();
                double priceForPlan = PlanPrices::getPriceForPlan(planId);
                prefixSum[ps->getSubscribedMonth() - 1] += priceForPlan;
            }
            for(int i=1; i<12; i++) {
                prefixSum[i] += prefixSum[i-1];
            }
            return prefixSum;
        }
};

class CostExplorer {
    public:
        vector<double> monthlyCostList(Customer* customer) {
            return customer->getMonthlyCostList();
        }

        double annualCost(Customer* customer) {
            double annualCost = 0;
            for(auto monthCost: customer->getMonthlyCostList()) {
                annualCost += monthCost;
            }
            return annualCost;
        }
};

int main() {
    PlanPrices::initPlanPrices(
        {
            {Plan::BASIC, 9.99},
            {Plan::STANDARD, 49.99},
            {Plan::PREMIUM, 249.99},
        }
    );

    Customer* c1 = new Customer(
        "c1",
        {
            new ProductSubscription("Jira", Plan::BASIC, "2021-01-01"),
            new ProductSubscription("Confluence", Plan::STANDARD, "2021-02-03"),
            new ProductSubscription("Stories", Plan::PREMIUM, "2021-03-05"),
        }
    );

    Customer* c2 = new Customer(
        "c2",
        {
            new ProductSubscription("Jira", Plan::BASIC, "2021-12-01")
        }
    );

    CostExplorer* ce = new CostExplorer();
    
    // Monthly cost list for c1
    cout<<"(c1) Monthly cost: ";
    for (auto costPerMonth: ce->monthlyCostList(c1)) {
        cout<<costPerMonth<<", ";
    }
    cout<<"Annual cost: "<<ce->annualCost(c1)<<endl;

    // Monthly cost list for c2
    cout<<"(c2) Monthly cost: ";
    for (auto costPerMonth: ce->monthlyCostList(c2)) {
        cout<<costPerMonth<<", ";
    }
    cout<<"Annual cost: "<<ce->annualCost(c2)<<endl;
    return 0;
}

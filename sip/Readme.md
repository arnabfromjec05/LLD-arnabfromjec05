<!--

Brainstorming the entities and relations


/**
 * MutualFund
 *  - id: string
 *  - name: string
 *  - currentVal: double
 *  + updateVal(latestVal): void
 * 
 * enum Cadence { Weekly, Monthly, Quarterly}
 * 
 * Sip
 *  - userId: string
 *  - mutualFundId: string
 *  - amount: double
 *  - cadence: Cadence
 *  - createdTime: int // for simplicity taking day value
 *  - status: Active/Pause/Stopped
 * 
 * User
 *  - id: string
 *  - name: string
 *  - sips: vector<Sip> 
 * 
 * FundService
 *  - map<id, MutualFund>
 * 
 * UserService
 *  - map<id, User>
 * 
 * SipService
 *  + getMutualFunds() : gets all mutual funds present
 *  + setupSip(User, MutualFund, Amount, Cadence, Day)
 *  + sipExecute() : bg task that runs every day and triggers payment activity if cadence criteria is met
 *  + displaySips(User) : display all user sips
 * 
 * 


 execute using g++ sip.cpp, ./a.out
 
 */ -->
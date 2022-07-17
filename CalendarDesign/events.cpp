#include <iostream>
using namespace std;

/**
Abstract class for any Event
Event types can be Reminder, Meeting, Task etc .. which can be extended
*/

export class Events {
    string eventName;
    string eventDesc;
    datetime startDate;
    datetime endDate;
}
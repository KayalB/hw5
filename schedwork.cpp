#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here



bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    // Number of Workers time Number of days
    // avail.size() = day;
    // avail[0].size() = workers

    // Keep track of the hours each worker has worked
    vector<int> hours_worked(avail[0].size(), 0);

    if (avail[0].size() * maxShifts < avail.size() * dailyNeed){
      return false;
    }


    // Initialize sched as a List[List[int]]. 
    // First one makes shced.size = number of days
    sched.resize(avail.size());
    for(size_t the_days = 0; the_days < avail.size(); the_days++){
      sched[the_days].resize(dailyNeed);
      for(size_t needed = 0; needed < dailyNeed; needed++){
          sched[the_days][needed] = -1;
      }
    }

    return helper(avail, dailyNeed, maxShifts, sched, 0, 0, hours_worked);
}


bool helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    // std::vector<int>& vect, 
    // int currWorkerSchedule,
    size_t currDay,
    int num_assigned,
    vector<int>& hours_worked
){
  // cout << "0" << endl;
  // cout << num_assigned << ", " << dailyNeed << endl;
  // Base Case: Our current day is the number of days
  if(currDay == avail.size()){
    // cout << "-- 1 --" << endl;
    return true;
  }

  // Recuresive Case 1: If we have assigned everyone for a day, go onto the next dat
  if((int)num_assigned == (int)dailyNeed){
        // cout << "-- 2 --" << endl;

    if(helper(avail, dailyNeed, maxShifts, sched, currDay+1, 0, hours_worked)){
      // cout << " -- TEST -- " << endl;
      return true;
    }

  }
    
  // cout << "currDay: " << currDay << endl;
  //   cout << "num_assigned: " << num_assigned << endl;
    // cout << "-- 3 --" << endl;

  // Recuresive Case 2: test every worker who is free and hasnt exceeded maxiumum hours for the current day
  for(int worker = 0; worker < (int)avail[currDay].size(); worker++){
    // If the worker is free during the timeslot
    // cout << "currDay: " << currDay << " worker: " << worker << endl;
    if(avail[currDay][worker] != 0){
      if(hours_worked[worker] < (int)maxShifts){
        if(num_assigned > (int)sched[currDay].size()){
          return false;
        }
        // cout << "sched[currDay].size(): " << sched[currDay].size() << endl;
        // // Go to row DAY and col CURR SHIFT WE'RE SETTITNG
        // cout << "-- currDay: " << currDay << endl;
        // cout << "-- num_assigned: " << num_assigned << endl;
        // cout << "sched[currDay][num_assigned]" << sched[currDay][num_assigned] << endl;
        // cout << worker << endl;
        sched[currDay][num_assigned] = worker;
        // increment the corresponding hours worked
        hours_worked[worker]++;
        // cout << "-- sched[currDay].size(): " << sched[currDay].size() << endl;

        // Recurse, but increase the one we are on by 1
        if(helper(avail, dailyNeed, maxShifts, sched, currDay, num_assigned+1, hours_worked)){
            // cout << "-- currDay: " << currDay << endl;
            // cout << "-- num_assigned: " << num_assigned << endl;
          return true;
        }
        // cout << "** sched[currDay].size(): " << sched[currDay].size() << endl;
        hours_worked[worker]--;
        sched[currDay][num_assigned] = -1;
        // cout << "&& sched[currDay].size(): " << sched[currDay].size() << endl;
      }
    }
  }
  // cout << "-- FALSE --" << endl;
  // For every worker, we recurse, and if it doesnt work, backtrack?
  // Backtrak by 
  return false;
}
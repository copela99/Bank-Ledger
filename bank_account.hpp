#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iterator>
#include <iomanip>

using std::string;
using std::ostringstream;
using std::istringstream;
using std::vector;
using std::endl;
using std::stod;
using std::to_string;
using std::floor;
using std::istream_iterator;
using std::cout;
using std::setprecision;
using std::fixed;

double rounder(double &val)
{
  //rounding the value based off of neg or pos
  if(val < 0)
  {
    val = floor(val * -100.0) / -100.0;
  }
  else
  {
    val = floor(val * 100.0) / 100.0;
  }
  return val;
}

double deposit(double &bal, double &amt)
{
  //depositting the amt into the balance
  bal += amt;
  return bal;
}

bool withdraw(double &bal, double amt)
{
  //if the balance is is available, the withdraw succeeds
  if(bal > amt)
  {
    bal -= amt;
    return true;
  }
  return false;
}

double overdraft(double &bal, double &amt)
{
  //function assess the bal in case of an overdraft
  double fee = 35.00;
  bal = bal - amt - fee;
  return bal;
}

double interest_for_month(double bal, double const apr)
{
  //calculating apr per month, multiplying by the balance to get the total int for month, then rounding
  double bal_new;
  double apr_per_month = (apr / 12) / 100;
  bal *= apr_per_month;
  bal_new = rounder(bal);
  return bal_new;
}

void string_date_to_int_ptrs(string date, int *year, int *month, int *day)
{
  //function loops through a string using multiple for loops to capture the data before and after '-'
  int i,y = 0, m = 0, d = 0;
  for (i = 0; i < date.length(); i++)
  {
    if(date[i] == '-')
    {
      break;
    }
    y = y * 10 + (date[i] - '0');
  }
  //assigning the pointer the value y accumulates
  *year = y;
  for(i += 1; i < date.length(); i++)
  {
    if(date[i] == '-')
    {
      break;
    }
    m = m * 10 + (date[i] - '0');
  }
  //assigning the pointer the value m accumulates
  *month = m;
  for(i += 1; i < date.length(); i++)
  {
    d = d * 10 + (date[i] - '0');
  }
  //assigning the pointer the value d accumulates
  *day = d;
}

void string_date_to_ints(string date, int &year, int &month, int &day)
{
  //functions works just as above but instead of assigning values to the pointers, I do so to the references
  year = 0;
  month = 0;
  day = 0;
  int i;
  for (i = 0; i < date.length(); i++)
  {
    if(date[i] == '-')
    {
      break;
    }
    year = year * 10 + (date[i] - '0');
  }
  for(i += 1; i < date.length(); i++)
  {
    if(date[i] == '-')
    {
      break;
    }
    month = month * 10 + (date[i] - '0');
  }
  for(i += 1; i < date.length(); i++)
  {
    day = day * 10 + (date[i] - '0');
  }
}

double number_of_first_of_months(string  &date1,string & date2)
{
  //the function parses substrings to obtain the day, month, year values then calculates accordingly
  double yr1 = stod(date1.substr(0,4));
  double yr2 = stod(date2.substr(0,4));
  double mth1 = stod(date1.substr(5,2));
  double mth2 = stod(date2.substr(5,2));
  double yr_diff_months = ((yr2 - yr1) * 12);
  double num_of_first_months;
  if(yr1 == yr2)
  {
    num_of_first_months = mth2 - mth1;
  }
  else
  {
      num_of_first_months = (mth2 - mth1) + yr_diff_months;
  }
  return num_of_first_months;
}

double interest_earned(double bal, double const apr, string & date1, string & date2)
{
  //the function accumulates the balance with interest for a certain n months
  //first months
  double bal_new = bal + interest_for_month(bal,apr);
  for(int i = 0; i < number_of_first_of_months(date1,date2) - 1; i++)
  {
    bal_new = bal_new + interest_for_month(bal_new,apr);
  }
  double tot_interest = bal_new - bal;
  return tot_interest;
}

vector<string> split_line(string &line)
{
  //splitting a line by the delimeter whitespace
  istringstream iss(line);
  vector<string> v ((istream_iterator<string>(iss)),(istream_iterator<string>()));
  return v;
}

string process_command(string &command, string &prev_date, double &bal, double const &apr)
{
  //function accounts for deposit with and without interest, and withdraw with and whitout interest
  ostringstream oss;
  vector<string> vec = split_line(command);
  string curr_date = vec[0];
  string amt = vec[2].substr(1,(vec[2].length() - 1));
  double amt_db = stod(amt);
  string s = "";
  //assigning a prev date if it is null
  if(prev_date == "")
  {
    prev_date = curr_date;
  }
  double first_months = number_of_first_of_months(prev_date,curr_date);
  double int_earned = interest_earned(bal,apr,prev_date,curr_date);
  //deposit without
  if(vec[1] == "Deposit" && first_months == 0)
  {
    bal = deposit(bal, amt_db);
    oss << "On " << vec[0] << ": " << "Instructed to perform " << "\"" << vec[1] << " " <<  vec[2] << "\"" << '\n' << "Balance: " << fixed << setprecision(2) << bal << '\n';
    string s2 = oss.str();
    s += s2;
    oss.clear();
  }
  //deposit with
  else if(first_months > 0 && vec[1] == "Deposit")
  {
    if(bal < 0)
    {
      int_earned = 0.0;
    }
    bal = deposit(bal, amt_db);
    bal += int_earned;
    oss << "On " << vec[0] << ": " << "Instructed to perform " << "\"" << vec[1] << " " <<  vec[2] << "\"" << '\n' << "Since " << prev_date << ", interest has accrued " << first_months << " times." << '\n' << "$" << fixed << setprecision(2) << int_earned << " interest has been earned." << '\n' << "Balance: " << fixed << setprecision(2) << bal << '\n';
    string s2 = oss.str();
    s += s2;
    oss.clear();
  }
  //withdraw without
  else if(vec[1] == "Withdraw" && first_months == 0)
  {
    bool ans = withdraw(bal,amt_db);
    if(ans == true)
    {
      oss << "On " << vec[0] << ": " << "Instructed to perform " << "\"" << vec[1] << " " <<  vec[2] << "\"" << '\n' << "Balance: " << fixed << setprecision(2) << bal << '\n';
    }
    else
    {
      bal = overdraft(bal,amt_db);
      oss << "On " << vec[0] << ": " << "Instructed to perform " << "\"" << vec[1] << " " <<  vec[2] << "\"" << '\n' << "Overdraft!" << '\n' << "Balance: " << fixed << setprecision(2) << bal << '\n';
    }
    string s2 = oss.str();
    s += s2;
    oss.clear();
  }
  //withdraw with
  else
  {
    if(bal < 0)
    {
      int_earned = 0.0;
    }
    bool ans = withdraw(bal,amt_db);
    if(ans == true)
    {
      bal += int_earned;
      oss << "On " << vec[0] << ": " << "Instructed to perform " << "\"" << vec[1] << " " <<  vec[2] << "\"" << '\n' << "Since " << prev_date << ", interest has accrued " << first_months << " times." << '\n' << "$" << fixed << setprecision(2) << int_earned << " interest has been earned." << '\n' << "Balance: " << fixed << setprecision(2) << bal << '\n';
    }
    else
    {
      bal = overdraft(bal,amt_db) + int_earned;
      oss << "On " << vec[0] << ": " << "Instructed to perform " << "\"" << vec[1] << " " <<  vec[2] << "\"" << '\n' << "Since " << prev_date << ", interest has accrued " << first_months << " times." << '\n' << "$" << fixed << setprecision(2) << int_earned << " interest has been earned." << '\n' << "Overdraft!" << '\n' << "Balance: " << fixed << setprecision(2) << bal << '\n';
    }
    string s2 = oss.str();
    s += s2;
    oss.clear();
  }
  //passing of the dates for the os stream
  prev_date = curr_date;
  return s;

}

string process_commands(string &input, int apr)
{
  //function breaks down the raw string literal into a vector
  string prev_date = "";
  string commands;
  string s = "";
  double bal = 0.0;
  istringstream iss(input);
  vector<string> v;
  while(getline(iss,commands,'\n'))
  {
    v.push_back(commands);
  }
  //function loops through the vector and preforms process_command for each elements

  for(int i = 0; i < v.size(); i++)
  {
    //appends the results for each command
    s += process_command(v[i],prev_date,bal,apr);
  }
  //returns all commands 
  return s;
}

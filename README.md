# Bank-Ledger
In this project, I created a bank account calculator that can process withdraws and deposits, calculate interest, and apply overdraft fees. 

Example:

string input = 
"2016-09-02 Deposit $500\n"
"2016-09-02 Withdraw $23.54\n"
"2016-09-04 Withdraw $58\n"
"2016-11-02 Deposit $200\n"
"2017-03-02 Withdraw $1000\n"
"2019-11-02 Deposit $500\n";

string result = process_commands(input, 7);

string expected = 
"On 2016-09-02: Instructed to perform \"Deposit $500\"\n"
"Balance: 500.00\n"
"On 2016-09-02: Instructed to perform \"Withdraw $23.54\"\n"
"Balance: 476.46\n"
"On 2016-09-04: Instructed to perform \"Withdraw $58\"\n"
"Balance: 418.46\n"
"On 2016-11-02: Instructed to perform \"Deposit $200\"\n"
"Since 2016-09-04, interest has accrued 2 times.\n"
"$4.89 interest has been earned.\n"
"Balance: 623.35\n"
"On 2017-03-02: Instructed to perform \"Withdraw $1000\"\n"
"Since 2016-11-02, interest has accrued 4 times.\n"
"$14.65 interest has been earned.\n"
"Overdraft!\n"
"Balance: -397.00\n"
"On 2019-11-02: Instructed to perform \"Deposit $500\"\n"
"Since 2017-03-02, interest has accrued 32 times.\n"
"$0.00 interest has been earned.\n"
"Balance: 103.00\n";

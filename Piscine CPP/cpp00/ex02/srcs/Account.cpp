#include "Account.hpp"
#include <ctime>
#include <iostream>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
    : _accountIndex(this->_nbAccounts++)
    , _amount(initial_deposit)
    , _nbDeposits(0)
    , _nbWithdrawals(0) {

    _displayTimestamp();

    this->_totalAmount += this->_amount;

    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "created" << std::endl;
}

Account::~Account(void) {

    _displayTimestamp();

    this->_nbAccounts--;
    this->_totalAmount -= this->_amount;
    this->_totalNbDeposits -= this->_nbDeposits;
    this->_totalNbWithdrawals -= this->_nbWithdrawals;

    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "closed" << std::endl;
}

int Account::getNbAccounts(void) {
    return _nbAccounts;
}

int Account::getTotalAmount(void) {
    return _totalAmount;
}

int Account::getNbDeposits(void) {
    return _totalNbDeposits;
}

int Account::getNbWithdrawals(void) {
    return _totalNbWithdrawals;
}

int Account::checkAmount(void) const {
    return _amount;
}

void Account::_displayTimestamp(void) {

    time_t now = time(NULL);
    struct tm tstruct = *localtime(&now);
    char buffer[40];

    strftime(buffer, sizeof(buffer), "[%Y%m%d_%H%M%S] ", &tstruct);
    std::cout << buffer;
}

void Account::displayAccountsInfos(void) {

    _displayTimestamp();

    std::cout << "accounts:" << _nbAccounts << ";"
              << "total:" << _totalAmount << ";"
              << "deposits:" << _totalNbDeposits << ";"
              << "withdrawals:" << _totalNbWithdrawals << std::endl;
}

void Account::displayStatus(void) const {

    _displayTimestamp();

    std::cout << "index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "deposits:" << this->_nbDeposits << ";"
              << "withdrawals:" << this->_nbWithdrawals << std::endl;
}

void Account::makeDeposit(int deposit) {

    _displayTimestamp();

    std::cout << "index:" << this->_accountIndex << ";"
              << "p_amount:" << this->_amount << ";"
              << "deposit:" << deposit << ";";

    this->_amount += deposit;
    _totalAmount += deposit;
    this->_nbDeposits++;
    _totalNbDeposits++;

    std::cout << "amount:" << this->_amount << ";"
              << "nb_deposits:" << this->_nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {

    _displayTimestamp();

    std::cout << "index:" << this->_accountIndex << ";"
              << "p_amount:" << this->_amount << ";"
              << "withdrawal:";

    if (this->_amount < withdrawal) {
        std::cout << "refused" << std::endl;
        return false;
    } else {
        this->_amount -= withdrawal;
        _totalAmount -= withdrawal;
        this->_nbWithdrawals++;
        _totalNbWithdrawals++;

        std::cout << withdrawal << ";" << "amount:" << this->_amount << ";";
        std::cout << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
    }
    return true;
}
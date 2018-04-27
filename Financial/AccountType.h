#pragma once

/* Enumeration of account types (stored as unsigned 8 bit number - no more than 256 account types) */
enum AccountType : uint8_t {
	CURRENT, SAVINGS, CREDIT
};
//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2005 Pavel Medvedev
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef SQLITEPP_TRANSACTION_HPP_INCLUDED
#define SQLITEPP_TRANSACTION_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////

namespace sqlitepp {

//////////////////////////////////////////////////////////////////////////////

class session;

// Transaction. Noncopyable.
class transaction
{
public:
	// Transaction type
	enum type { deferred, immediate, exclusive };

	// Begin transaction in context of session.
	explicit transaction(session& s, type t = deferred);

	transaction(transaction&& src);
	transaction& operator=(transaction&& src);

	// End transaction with rollback if it is not commited.
	~transaction();

	// Rollback transaction
	void rollback();

	// Commit transaction.
	void commit();

private:
	transaction(transaction const&); // = delete
	transaction& operator=(transaction const&); // = delete

	session* s_;
	bool do_rollback_;
};

//////////////////////////////////////////////////////////////////////////////

} // namespace sqlitepp

//////////////////////////////////////////////////////////////////////////////

#endif // SQLITEPP_TRANSACTION_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////

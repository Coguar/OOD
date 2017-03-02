#pragma once
#include <vector>
#include <boost/signals2.hpp>

struct ScopedConnectionsStorage
{
	ScopedConnectionsStorage& operator+=(const boost::signals2::connection & conn)
	{
		m_items.emplace_back(conn);
		return *this;
	}
	ScopedConnectionsStorage& operator+=(boost::signals2::connection && conn)
	{
		m_items.emplace_back(std::move(conn));
		return *this;
	}
	ScopedConnectionsStorage& operator+=(boost::signals2::scoped_connection && conn)
	{
		m_items.emplace_back(std::move(conn));
		return *this;
	}
	ScopedConnectionsStorage& operator += (std::initializer_list<boost::signals2::connection> const & connections)
	{
		for (const auto & con : connections)
		{
			*this += con;
		}
		return *this;
	}

private:
	std::vector<boost::signals2::scoped_connection> m_items;
};
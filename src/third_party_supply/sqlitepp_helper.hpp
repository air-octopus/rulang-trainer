// ***************************************************************
//  sqlitepp_helper.h   version:  1.0   #   date: 2016.08.02
//  --------------------------------------------------------------
//  author:     Kozharin Maks
//  company:    WayRay
// ***************************************************************
/// \file
///      Функции, упрощающие работу с библиотеками sqlite и sqlitepp
// 
// ***************************************************************

#pragma once

#include <list>
#include <cstring>

#include "third_party/sqlitepp/sqlitepp/sqlitepp.hpp"
#include "third_party/sqlitepp/sqlite/sqlite3.h"

#include "typedefs.hpp"

namespace sqlitepp_helper {

using byte_array = std::vector<unsigned char>;

inline sqlitepp::blob nullblob() { return sqlitepp::blob{nullptr, 0}; }

struct transaction_auto_commit
{
    explicit transaction_auto_commit (sqlitepp::session & s_, uint64_t auto_commit_step=0) : tr(s_), s(s_), step_cur(0), step_max(auto_commit_step) {}
    ~transaction_auto_commit() { tr.commit(); }

    void step()
    {
        if (step_max > 0 && ++step_cur > step_max)
            step_cur = 0, intermediate_commit();
    }

    void intermediate_commit()
    {
        tr.commit();
        tr.~transaction();
        new (&tr) sqlitepp::transaction(s);
    }

private:
    sqlitepp::transaction tr;
    sqlitepp::session & s;
    uint64_t step_cur, step_max;
};

// В библиотеке sqlitepp методы statement::use_value(...) не понимают целые беззнаковые числа...
// Эти функции оборачивают методы statement::use_value(...), расширяя их интерфейс.
// По умолчанию будет применяться шаблонная версия, которая просто перенаправляет вызов
template<typename T>
inline void st_use_value(sqlitepp::statement & st, int pos, const T             & v) { st.use_value(pos, v); }
inline void st_use_value(sqlitepp::statement & st, int pos, const uint32_t      & v) { st.use_value(pos, static_cast<int>(v)); }
inline void st_use_value(sqlitepp::statement & st, int pos, const uint64_t      & v) { st.use_value(pos, static_cast<long long>(v)); }
inline void st_use_value(sqlitepp::statement & st, int pos, const std::string   & v) { st.use_value(pos, static_cast<sqlitepp::string_t>(v)); }


// Отсутствующие идентификаторы в базе хранятся как '-1'. Для них мы должны возвращать wrong<...>() соответствующего типа.
// Используем для этого специальный метод конвертации.
// typed_null здесь просто для указания типа возвращаемого значения
template <typename T>
inline T convert_from_int64 (int64_t v)
{
    return (v == -1) ? wrong<T>() : static_cast<T>(v);
}

inline int64_t insert (sqlitepp::session & s, sqlitepp::statement & st)
{
    st.reset();
    st.exec();
    return sqlite3_last_insert_rowid(s.impl());
}

template <typename T1>
inline int64_t insert (sqlitepp::session & s, sqlitepp::statement & st, const T1 & v1)
{
    st.reset();
    st_use_value(st, 1, v1);
    st.exec();
    return sqlite3_last_insert_rowid(s.impl());
}

template <typename T1, typename T2>
inline int64_t insert (sqlitepp::session & s, sqlitepp::statement & st, const T1 & v1, const T2 & v2)
{
    st.reset();
    st_use_value(st, 1, v1);
    st_use_value(st, 2, v2);
    st.exec();
    return sqlite3_last_insert_rowid(s.impl());
}

template <typename T1, typename T2, typename T3>
inline int64_t insert (sqlitepp::session & s, sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3)
{
    st.reset();
    st_use_value(st, 1, v1);
    st_use_value(st, 2, v2);
    st_use_value(st, 3, v3);
    st.exec();
    return sqlite3_last_insert_rowid(s.impl());
}

template <typename T1, typename T2, typename T3, typename T4>
inline int64_t insert (sqlitepp::session & s, sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3, const T4 & v4)
{
    st.reset();
    st_use_value(st, 1, v1);
    st_use_value(st, 2, v2);
    st_use_value(st, 3, v3);
    st_use_value(st, 4, v4);
    st.exec();
    return sqlite3_last_insert_rowid(s.impl());
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline int64_t insert (sqlitepp::session & s, sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3, const T4 & v4, const T5 & v5)
{
    st.reset();
    st_use_value(st, 1, v1);
    st_use_value(st, 2, v2);
    st_use_value(st, 3, v3);
    st_use_value(st, 4, v4);
    st_use_value(st, 5, v5);
    st.exec();
    return sqlite3_last_insert_rowid(s.impl());
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline int64_t insert(sqlitepp::session & s, sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3, const T4 & v4, const T5 & v5, const T6& v6)
{
    st.reset();
    st_use_value(st, 1, v1);
    st_use_value(st, 2, v2);
    st_use_value(st, 3, v3);
    st_use_value(st, 4, v4);
    st_use_value(st, 5, v5);
    st_use_value(st, 6, v6);
    st.exec();
    return sqlite3_last_insert_rowid(s.impl());
}

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline int64_t insert(sqlitepp::session & s, sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3, const T4 & v4, const T5 & v5, const T6& v6, const T7& v7)
{
    st.reset();
    st_use_value(st, 1, v1);
    st_use_value(st, 2, v2);
    st_use_value(st, 3, v3);
    st_use_value(st, 4, v4);
    st_use_value(st, 5, v5);
    st_use_value(st, 6, v6);
    st_use_value(st, 7, v7);
    st.exec();
    return sqlite3_last_insert_rowid(s.impl());
}

template <typename Tw>
inline void update (sqlitepp::statement & st, const Tw & w)
{
    st.reset();
    st_use_value(st, 1, w); // параметр для WHERE
    st.exec();
}

template <typename Tv, typename Tw>
inline void update (sqlitepp::statement & st, const Tv & v, const Tw & w)
{
    st.reset();
    st_use_value(st, 1, v);
    st_use_value(st, 2, w); // параметр для WHERE
    st.exec();
}

template <typename T1, typename T2, typename Tw>
inline void update(sqlitepp::statement & st, const T1 & v1, const T2 & v2,  const Tw & w)
{
    st.reset();
    st_use_value(st, 1, v1); // что меняем
    st_use_value(st, 2, v2); // что меняем
    st_use_value(st, 3, w); // параметр для WHERE
    st.exec();
}


template <typename T1, typename T2, typename T3, typename Tw>
inline void update(sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3,  const Tw & w)
{
    st.reset();
    st_use_value(st, 1, v1); // что меняем
    st_use_value(st, 2, v2); // что меняем
    st_use_value(st, 3, v3); // что меняем
    st_use_value(st, 4, w); // параметр для WHERE
    st.exec();
}

template <typename T1, typename T2, typename T3, typename T4, typename Tw>
inline void update(sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3, const T4 & v4,  const Tw & w)
{
    st.reset();
    st_use_value(st, 1, v1); // что меняем
    st_use_value(st, 2, v2); // что меняем
    st_use_value(st, 3, v3); // что меняем
    st_use_value(st, 4, v4); // что меняем
    st_use_value(st, 5, w); // параметр для WHERE
    st.exec();
}


template <typename T1, typename T2, typename T3, typename T4, typename T5, typename Tw>
inline void update(sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3, const T4 & v4, const T5 & v5 , const Tw & w)
{
    st.reset();
    st_use_value(st, 1, v1); // что меняем
    st_use_value(st, 2, v2); // что меняем
    st_use_value(st, 3, v3); // что меняем
    st_use_value(st, 4, v4); // что меняем
    st_use_value(st, 5, v5); // что меняем   
    st_use_value(st, 6, w); // параметр для WHERE
    st.exec();
}

template <typename Tw>
inline void update (sqlitepp::statement & st, const byte_array & v, const Tw & w)
{
    sqlitepp::blob blb = {v.data(), v.size()};
    st.reset();
    st.use_value(1, blb); // что меняем
    st_use_value(st, 2, w); // параметр для WHERE
    st.exec();
}

inline void update_by_0 (sqlitepp::statement & st)
{
    st.reset();
    st.exec();
}

template <typename Tv>
inline void update_by_0 (sqlitepp::statement & st, const Tv & v)
{
    st.reset();
    st_use_value(st, 1, v); // что меняем
    st.exec();
}

template <typename T1, typename T2>
inline void update_by_0(sqlitepp::statement & st, const T1 & v1, const T2 & v2)
{
    st.reset();
    st_use_value(st, 1, v1); // что меняем
    st_use_value(st, 2, v2); // что меняем
    st.exec();
}


template <typename T1, typename T2, typename T3>
inline void update_by_0(sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3)
{
    st.reset();
    st_use_value(st, 1, v1); // что меняем
    st_use_value(st, 2, v2); // что меняем
    st_use_value(st, 3, v3); // что меняем
    st.exec();
}

template <typename T1, typename T2, typename T3, typename T4>
inline void update_by_0(sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3, const T4 & v4)
{
    st.reset();
    st_use_value(st, 1, v1); // что меняем
    st_use_value(st, 2, v2); // что меняем
    st_use_value(st, 3, v3); // что меняем
    st_use_value(st, 4, v4); // что меняем
    st.exec();
}


template <typename T1, typename T2, typename T3, typename T4, typename T5>
inline void update_by_0(sqlitepp::statement & st, const T1 & v1, const T2 & v2, const T3 & v3, const T4 & v4, const T5 & v5)
{
    st.reset();
    st_use_value(st, 1, v1); // что меняем
    st_use_value(st, 2, v2); // что меняем
    st_use_value(st, 3, v3); // что меняем
    st_use_value(st, 4, v4); // что меняем
    st_use_value(st, 5, v5); // что меняем   
    st.exec();
}

inline void update_by_0 (sqlitepp::statement & st, const byte_array & v)
{
    sqlitepp::blob blb = {v.data(), v.size()};
    st.reset();
    st.use_value(1, blb); // что меняем
    st.exec();
}

template <typename Tw>
inline void remove (sqlitepp::statement & st, const Tw & w)
{
    st.reset();
    st_use_value(st, 1, w); // параметр для WHERE
    st.exec();
}

template <typename T1, typename Tw>
inline bool select (sqlitepp::statement & st, T1 & v1, const Tw & w)
{
    st.reset();
    st_use_value(st, 1, w); // параметр для WHERE
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    return true;
}

template <typename T1, typename Tw>
inline T1 select (sqlitepp::statement & st, const Tw & w)
{
    st.reset();
    st_use_value(st, 1, w); // параметр для WHERE
    if (!st.exec()) return wrong<T1>();
    return st.get<T1>(0);
}

template <typename T1>
inline T1 select(sqlitepp::statement & st)
{
    st.reset();
    if (!st.exec()) return wrong<T1>();
    return st.get<T1>(0);
}

template <typename T1, typename T2, typename Tw>
inline bool select (sqlitepp::statement & st, T1 & v1, T2 & v2, const Tw & w)
{
    st.reset();
    st_use_value(st, 1, w); // параметр для WHERE
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    return true;
}

template <typename T1, typename T2, typename T3, typename Tw>
inline bool select (sqlitepp::statement & st, T1 & v1, T2 & v2, T3 & v3, const Tw & w)
{
    st.reset();
    st_use_value(st, 1, w); // параметр для WHERE
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    v3 = st.get<T3>(2);
    return true;
}

template <typename T1, typename T2, typename T3, typename T4, typename Tw>
inline bool select (sqlitepp::statement & st, T1 & v1, T2 & v2, T3 & v3, T4 & v4, const Tw & w)
{
    st.reset();
    st_use_value(st, 1, w); // параметр для WHERE
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    v3 = st.get<T3>(2);
    v4 = st.get<T4>(3);
    return true;
}

template <typename T1>
inline bool select_by_0 (sqlitepp::statement & st, T1 & v1)
{
    st.reset();
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    return true;
}

template <typename T1>
inline T1 select_by_0 (sqlitepp::statement & st)
{
    st.reset();
    if (!st.exec()) return wrong<T1>();
    return st.get<T1>(0);
}

template <typename T1, typename T2>
inline bool select_by_0 (sqlitepp::statement & st, T1 & v1, T2 & v2)
{
    st.reset();
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    return true;
}

template <typename T1, typename T2, typename T3>
inline bool select_by_0 (sqlitepp::statement & st, T1 & v1, T2 & v2, T3 & v3)
{
    st.reset();
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    v3 = st.get<T3>(2);
    return true;
}

template <typename T1, typename T2, typename T3, typename T4>
inline bool select_by_0 (sqlitepp::statement & st, T1 & v1, T2 & v2, T3 & v3, T3 & v4)
{
    st.reset();
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    v3 = st.get<T3>(2);
    v4 = st.get<T4>(3);
    return true;
}

template <typename T1, typename Tw1, typename Tw2>
inline bool select_by_2 (sqlitepp::statement & st, T1 & v1, const Tw1 & w1, const Tw2 & w2)
{
    st.reset();
    st_use_value(st, 1, w1); // параметр для WHERE
    st_use_value(st, 2, w2); // параметр для WHERE
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    return true;
}

template <typename T1, typename Tw1, typename Tw2>
inline T1 select_by_2 (sqlitepp::statement & st, const Tw1 & w1, const Tw2 & w2)
{
    st.reset();
    st_use_value(st, 1, w1); // параметр для WHERE
    st_use_value(st, 2, w2); // параметр для WHERE
    if (!st.exec()) return wrong<T1>();
    return st.get<T1>(0);
}

template <typename T1, typename Tw1, typename Tw2, typename Tw3>
inline bool select_by_3 (sqlitepp::statement & st, T1 & v1, const Tw1 & w1, const Tw2 & w2, const Tw3 & w3)
{
    st.reset();
    st_use_value(st, 1, w1); // параметр для WHERE
    st_use_value(st, 2, w2); // параметр для WHERE
    st_use_value(st, 3, w3); // параметр для WHERE
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    return true;
}

template <typename T1, typename Tw1, typename Tw2, typename Tw3>
inline T1 select_by_3 (sqlitepp::statement & st, const Tw1 & w1, const Tw2 & w2, const Tw3 & w3)
{
    st.reset();
    st_use_value(st, 1, w1); // параметр для WHERE
    st_use_value(st, 2, w2); // параметр для WHERE
    st_use_value(st, 3, w3); // параметр для WHERE
    if (!st.exec()) return wrong<T1>();
    return st.get<T1>(0);
}

template <typename T1>
inline bool select_next (sqlitepp::statement & st, T1 & v1)
{
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    return true;
}

template <typename T1>
inline T1 select_next (sqlitepp::statement & st)
{
    if (!st.exec()) return wrong<T1>();
    return st.get<T1>(0);
}

template <typename T1, typename T2>
inline bool select_next (sqlitepp::statement & st, T1 & v1, T2 & v2)
{
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    return true;
}

template <typename T1, typename T2, typename T3>
inline bool select_next (sqlitepp::statement & st, T1 & v1, T2 & v2, T3 & v3)
{
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    v3 = st.get<T3>(2);
    return true;
}

template <typename T1, typename T2, typename T3, typename T4>
inline bool select_next (sqlitepp::statement & st, T1 & v1, T2 & v2, T3 & v3, T3 & v4)
{
    if (!st.exec()) return false;
    v1 = st.get<T1>(0);
    v2 = st.get<T2>(1);
    v3 = st.get<T3>(2);
    v4 = st.get<T4>(3);
    return true;
}

//////////////////////////////////////////////////////////////////////////
/// Инициализация statement'а
inline void init_statement(sqlitepp::statement & st, const std::string & sql)
{
    st << sql; st.prepare();
}
inline sqlitepp::statement make_statement(sqlitepp::session & s, const std::string & sql)
{
    sqlitepp::statement st(s); init_statement(st, sql);
    return std::move(st);
}

//////////////////////////////////////////////////////////////////////////
/// Проверка наличия таблицы в базе данных
inline bool is_sqlite_table_exist(sqlitepp::session & s, const std::string & tbl_name)
{
    sqlitepp::statement st = make_statement(s, "SELECT count(*) FROM sqlite_master WHERE type='table' AND name=:1");
    return select<int>(st, tbl_name) > 0;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///     Общий интерфейс контейнера предкомпилированных statement'ов.
///     для выполнения групповых операций сразу над несколькими statement'ами
//////////////////////////////////////////////////////////////////////////
class SqliteppStatementContainer
{
public:
    virtual ~SqliteppStatementContainer() {}

    /// Подготавливаем все statement'ы
    virtual void prepareAll () = 0;

    /// Финализируем все statement'ы
    virtual void finalizeAll() = 0;

    /// Очистить контейнер
    virtual void clear() = 0;

    /// Иногда требуется изменить структуру базы (добавить или удалить таблицы, добавить в таблицу колонки...)
    /// Для корректной работы sqlite рекомендуется закрывать все существующие statement'ы,
    /// а после изменения базы -- делать им prepare.
    /// Для автоматизации этого процесса предназначен данный класс
    /// (дополнительно см. SqliteppStatementContainer::createRePreparerGuard())
    /// 
    /// Использование:
    ///     {
    ///         // начальные условия: имеется sqliteppStatementContainer -- указатель на некоторый экземпляр SqliteppStatementContainer
    ///         // создаем guard-объект (при этом автоматически финализируются все statement'ы, сохраненные в объекте sqliteppStatementContainer)
    ///         auto guard = sqliteppStatementContainer->createRePreparerGuard();
    ///         
    ///         // меняем структуру базы данных
    ///         ...
    ///         
    ///         // при выходе из блока автоматически будет выполнена операция prepareAll()
    ///     }
    /// 
    class RePreparerGuard
    {
    public:
        using ptr = std::unique_ptr<RePreparerGuard>;

    private:
        friend class SqliteppStatementContainer;
        friend typename ptr::deleter_type;
        static ptr create(SqliteppStatementContainer * owner)  { return ptr(new RePreparerGuard(owner)); }
        RePreparerGuard  (SqliteppStatementContainer * owner) : mOwner(owner) { mOwner->finalizeAll(); }
        ~RePreparerGuard () { mOwner->prepareAll(); }

        SqliteppStatementContainer * mOwner;
    };

    /// Создать guard-объект для автоматического выполнения операций finalizeAll-prepareAll
    RePreparerGuard::ptr createRePreparerGuard() { return RePreparerGuard::create(this); }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///     Контейнер предкомпилированных statement'ов.
///     Сохраняет адрес statement'а в момент его создания (для этого используется специальный враппер -- statement_wrapper)
///     и реализует групповые операциии сразу над всеми statement'ами
//////////////////////////////////////////////////////////////////////////
class SqliteppStatementSimpleContainer : public SqliteppStatementContainer
{
public:
    virtual ~SqliteppStatementSimpleContainer() { clear(); }

    //************************************************************
    //      ИНТЕРФЕЙС БАЗОВОГО КЛАССА
    virtual void prepareAll  () override {
        for (auto * p : mStatements)
        {
            try {
                p->prepare();
            }
            catch (...)
            {
                throw std::runtime_error("Sqlite statement prepare error.");
            }
        }
    }
    virtual void finalizeAll () override { for (auto * p : mStatements) p->finalize(); }
    virtual void clear       () override { finalizeAll(); mStatements.clear(); }

protected:

    /// Обертка над sqlitepp::statement для автоматизации поддержки классов SqliteppStatementContainer
    struct statement_wrapper
    {
        statement_wrapper(SqliteppStatementSimpleContainer * owner, sqlitepp::session & s, const char * query)
            : st(s)
        {
            st << query;
            owner->mStatements.push_back(&st);
        }
        sqlitepp::statement st;
    };

private:
    std::vector<sqlitepp::statement*> mStatements;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///     "Контейнер контейнеров" предкомпилированных statement'ов.
//////////////////////////////////////////////////////////////////////////
class SqliteppStatementSuperContainer : public SqliteppStatementContainer
{
public:
    virtual ~SqliteppStatementSuperContainer() { clear(); }

    /// Добавляем еще один контейнер
    void addContainer(SqliteppStatementContainer * st_cont)
    {
        mContainers.push_back(st_cont);
    }

    //************************************************************
    //      ИНТЕРФЕЙС БАЗОВОГО КЛАССА
    virtual void prepareAll  () override { for (auto * p : mContainers) p->prepareAll (); }
    virtual void finalizeAll () override { for (auto * p : mContainers) p->finalizeAll(); }
    virtual void clear       () override { for (auto * p : mContainers) p->clear(); mContainers.clear(); }

private:
    std::vector<SqliteppStatementContainer*> mContainers;
};

template<typename T>
inline sqlitepp::blob byte_array_to_blob(const T& t)
{
    sqlitepp::blob res;
    res.data = t.data();
    res.size = t.size();
    return res;
}

inline byte_array blob_to_byte_array(const sqlitepp::blob& blob)
{
    byte_array res(blob.size);
    std::memcpy(res.data(), blob.data, blob.size);
    return res;
}

} // sqlitepp

//--- END OF FILE ------------------------------------------------
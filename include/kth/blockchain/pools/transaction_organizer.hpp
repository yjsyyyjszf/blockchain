// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_BLOCKCHAIN_TRANSACTION_ORGANIZER_HPP
#define KTH_BLOCKCHAIN_TRANSACTION_ORGANIZER_HPP

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <future>
#include <memory>
#include <kth/domain.hpp>
#include <kth/blockchain/define.hpp>
#include <kth/blockchain/interface/fast_chain.hpp>
#include <kth/blockchain/interface/safe_chain.hpp>
#include <kth/blockchain/pools/transaction_pool.hpp>
#include <kth/blockchain/settings.hpp>
#include <kth/blockchain/validate/validate_transaction.hpp>

#if defined(KTH_WITH_MEMPOOL)
#include <kth/mining/mempool.hpp>

#endif

namespace kth {
namespace blockchain {

/// This class is thread safe.
/// Organises transactions via the transaction pool to the blockchain.
class BCB_API transaction_organizer
{
public:
    typedef handle0 result_handler;
    typedef std::shared_ptr<transaction_organizer> ptr;
    typedef safe_chain::transaction_handler transaction_handler;
    typedef safe_chain::inventory_fetch_handler inventory_fetch_handler;
    typedef safe_chain::merkle_block_fetch_handler merkle_block_fetch_handler;
    typedef resubscriber<code, transaction_const_ptr> transaction_subscriber;

    /// Construct an instance.

#if defined(KTH_WITH_MEMPOOL)
    transaction_organizer(prioritized_mutex& mutex, dispatcher& dispatch, threadpool& thread_pool, fast_chain& chain, const settings& settings, mining::mempool& mp);
#else
    transaction_organizer(prioritized_mutex& mutex, dispatcher& dispatch, threadpool& thread_pool, fast_chain& chain, const settings& settings);
#endif

    bool start();
    bool stop();

    void organize(transaction_const_ptr tx, result_handler handler);
    void transaction_validate(transaction_const_ptr tx, result_handler handler) const;

    void subscribe(transaction_handler&& handler);
    void unsubscribe();

    void fetch_template(merkle_block_fetch_handler) const;
    void fetch_mempool(size_t maximum, inventory_fetch_handler) const;

protected:
    bool stopped() const;
    uint64_t price(transaction_const_ptr tx) const;

private:
    // Verify sub-sequence.
    void handle_check(code const& ec, transaction_const_ptr tx, result_handler handler);
    void handle_accept(code const& ec, transaction_const_ptr tx, result_handler handler);
    void handle_connect(code const& ec, transaction_const_ptr tx, result_handler handler);
    void handle_pushed(code const& ec, transaction_const_ptr tx, result_handler handler);
    void signal_completion(code const& ec);

    void validate_handle_check(code const& ec, transaction_const_ptr tx, result_handler handler) const;
    void validate_handle_accept(code const& ec, transaction_const_ptr tx, result_handler handler) const;
    void validate_handle_connect(code const& ec, transaction_const_ptr tx, result_handler handler) const;

    // Subscription.
    void notify(transaction_const_ptr tx);

    // This must be protected by the implementation.
    fast_chain& fast_chain_;

    // These are thread safe.
    prioritized_mutex& mutex_;
    std::atomic<bool> stopped_;
    std::promise<code> resume_;
    const settings& settings_;
    dispatcher& dispatch_;
    transaction_pool transaction_pool_;
    validate_transaction validator_;
    transaction_subscriber::ptr subscriber_;

#if defined(KTH_WITH_MEMPOOL)
    mining::mempool& mempool_;
#endif
};

} // namespace blockchain
} // namespace kth

#endif

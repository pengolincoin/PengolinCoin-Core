// Copyright (c) 2020 PIVX developers
// Copyright (c) 2020-2021 The PENGOLINCOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PENGOLINCOIN_LEGACY_ZPOS_H
#define PENGOLINCOIN_LEGACY_ZPOS_H

#include "stakeinput.h"
#include "txdb.h"

class CLegacyZPgoStake : public CStakeInput
{
private:
    uint32_t nChecksum{0};
    libzerocoin::CoinDenomination denom{libzerocoin::ZQ_ERROR};
    uint256 hashSerial{UINT256_ZERO};

public:
    CLegacyZPgoStake() : CStakeInput(nullptr) {}

    explicit CLegacyZPgoStake(const libzerocoin::CoinSpend& spend);
    bool InitFromTxIn(const CTxIn& txin) override;
    bool IsZPGO() const override { return true; }
    uint32_t GetChecksum() const { return nChecksum; }
    const CBlockIndex* GetIndexFrom() const override;
    CAmount GetValue() const override;
    CDataStream GetUniqueness() const override;
    bool GetTxOutFrom(CTxOut& out) const override { return false; /* not available */ }
    virtual bool ContextCheck(int nHeight, uint32_t nTime) override;
};

#endif //PENGOLINCOIN_LEGACY_ZPOS_H

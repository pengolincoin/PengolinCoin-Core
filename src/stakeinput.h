// Copyright (c) 2017-2020 PIVX developers
// Copyright (c) 2020-2021 The PENGOLINCOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PENGOLINCOIN_STAKEINPUT_H
#define PENGOLINCOIN_STAKEINPUT_H

#include "chain.h"
#include "streams.h"
#include "uint256.h"

class CKeyStore;
class CWallet;
class CWalletTx;

class CStakeInput
{
protected:
    const CBlockIndex* pindexFrom = nullptr;

public:
    CStakeInput(const CBlockIndex* _pindexFrom) : pindexFrom(_pindexFrom) {}
    virtual ~CStakeInput(){};
    virtual bool InitFromTxIn(const CTxIn& txin) = 0;
    virtual const CBlockIndex* GetIndexFrom() const = 0;
    virtual bool GetTxOutFrom(CTxOut& out) const = 0;
    virtual CAmount GetValue() const = 0;
    virtual bool IsZPGO() const = 0;
    virtual CDataStream GetUniqueness() const = 0;
    virtual bool ContextCheck(int nHeight, uint32_t nTime) = 0;
};


class CPgoStake : public CStakeInput
{
private:
    const CTxOut outputFrom;
    const COutPoint outpointFrom;

public:
    CPgoStake(const CTxOut& _from, const COutPoint& _outPointFrom, const CBlockIndex* _pindexFrom) :
            CStakeInput(_pindexFrom), outputFrom(_from), outpointFrom(_outPointFrom) {}

    static CPgoStake* NewPgoStake(const CTxIn& txin);

    bool InitFromTxIn(const CTxIn& txin) override { return pindexFrom; }
    const CBlockIndex* GetIndexFrom() const override;
    bool GetTxOutFrom(CTxOut& out) const override;
    CAmount GetValue() const override;
    CDataStream GetUniqueness() const override;
    CTxIn GetTxIn() const;
    bool CreateTxOuts(const CWallet* pwallet, std::vector<CTxOut>& vout, CAmount nTotal) const;
    bool IsZPGO() const override { return false; }
    bool ContextCheck(int nHeight, uint32_t nTime) override;
};


#endif //PENGOLINCOIN_STAKEINPUT_H

// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PENGOLINCOIN developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"
#include "libzerocoin/Params.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>
#include <limits>


struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("00000865fddb23c371506db1692c393b7f4c5813f9139ea20b808b325aa96316"))
    (100, uint256("0000014b512647f2f87826dc1f74bdae9a79d69af072035f7133e58796857a9c"))
    (1100, uint256("a32107ba6b3fd2a48d89a9825889c014a2479d8f17211fc7125874eb781c5286"))
    // (616764, uint256("29dd0bd1c59484f290896687b4ffb6a49afa5c498caf61967c69a541f8191557")) //first block to use modifierV2
    // (623933, uint256("c7aafa648a0f1450157dc93bd4d7448913a85b7448f803b4ab970d91fc2a7da7"))
    // (791150, uint256("8e76f462e4e82d1bd21cb72e1ce1567d4ddda2390f26074ffd1f5d9c270e5e50"))
    // (795000, uint256("4423cceeb9fd574137a18733416275a70fdf95283cc79ad976ca399aa424a443"))
    // (863787, uint256("5b2482eca24caf2a46bb22e0545db7b7037282733faa3a42ec20542509999a64"))
    // (863795, uint256("2ad866818c4866e0d555181daccc628056216c0db431f88a825e84ed4f469067"))
    // (863805, uint256("a755bd9a22b63c70d3db474f4b2b61a1f86c835b290a081bb3ec1ba2103eb4cb"))
    // (867733, uint256("03b26296bf693de5782c76843d2fb649cb66d4b05550c6a79c047ff7e1c3ae15"))
    // (879650, uint256("227e1d2b738b6cd83c46d1d64617934ec899d77cee34336a56e61b71acd10bb2"))
    // (895400, uint256("7796a0274a608fac12d400198174e50beda992c1d522e52e5b95b884bc1beac6"))//block that serial# range is enforced
    // (895991, uint256("d53013ed7ea5c325b9696c95e07667d6858f8ff7ee13fecfa90827bf3c9ae316"))//network split here
    // (908000, uint256("202708f8c289b676fceb832a079ff6b308a28608339acbf7584de533619d014d"))
    // (1142400, uint256("98aff9d605bf123247f98b1e3a02567eb5799d208d78ec30fb89737b1c1f79c5"))
    // (1679090, uint256("f747ce055ba1b12e1f2e842bd480bc647210799359cb2e553ab292065e3419d6")) //!< First block with a "wrapped" serial spend
    // (1686229, uint256("bb42bf1e886a7c23474634c90893dd3d68a6ccbfea4ac92a98da5cad0c6a6cb7")) //!< Last block in the "wrapped" serial attack range
    // (1778954, uint256("0d3241268264a2908d6babf00d9cd1ffb83d93d7bb4e428820127fe227c2029c")) //!< Network split here
    // (1788528, uint256("ea9243ff8fc079fdd7a04f11fac415de4d98e1bb0dc38db6f79f8f8bbfdbe496"))
    ; //!< Network split here
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1593582000, // * UNIX timestamp of last checkpoint block
    4271692,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x000001f6742d9291290bba1058d68321b85e5a88f16b4334b68997a678972dc8"))
    // (1016800, uint256("6ae7d52092fd918c8ac8d9b1334400387d3057997e6e927a88e57186dc395231"))
    // (1106100, uint256("c54b3e7e8b710e4075da1806adf2d508ae722627d5bcc43f594cf64d5eef8b30")) //!< zc public spend activation height
    // (1112700, uint256("2ad8d507dbe3d3841b9f8a29c3878d570228e9361c3e057362d7915777bbc849"))
    ;
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1593582001,
    2501682,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1593582002,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

bool CChainParams::HasStakeMinAgeOrDepth(const int contextHeight, const uint32_t contextTime, const int utxoFromBlockHeight, const uint32_t utxoFromBlockTime) const
{
    // before stake modifier V2, the age required was 60 * 60 (1 hour). Not required for regtest
    if (!IsStakeModifierV2(contextHeight))
        return NetworkID() == CBaseChainParams::REGTEST || (utxoFromBlockTime + nStakeMinAge <= contextTime);

    // after stake modifier V2, we require the utxo to be nStakeMinDepth deep in the chain
    return (contextHeight - utxoFromBlockHeight >= nStakeMinDepth);
}

int CChainParams::FutureBlockTimeDrift(const int nHeight) const
{
    if (IsTimeProtocolV2(nHeight))
        // PoS (TimeV2): 14 seconds
        return TimeSlotLength() - 1;

    // PoS (TimeV1): 3 minutes
    // PoW: 2 hours
    return (nHeight > LAST_POW_BLOCK()) ? nFutureTimeDriftPoS : nFutureTimeDriftPoW;
}

bool CChainParams::IsValidBlockTimeStamp(const int64_t nTime, const int nHeight) const
{
    // Before time protocol V2, blocks can have arbitrary timestamps
    if (!IsTimeProtocolV2(nHeight))
        return true;

    // Time protocol v2 requires time in slots
    return (nTime % TimeSlotLength()) == 0;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x86;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xee;
        pchMessageStart[3] = 0xe5;
        vAlertPubKey = ParseHex("046611c68d0ab86abb09aa7297bd71f3c51096e4e51f49659d301d9d5f6698f19e7ead64079c95553fd77c915e8722b647439a3024baffc45e6e99a947443979d4");
        nDefaultPort = 33001;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // PENGOLINCOIN starting difficulty is 1 / 2^12
        bnProofOfStakeLimit = ~uint256(0) >> 24;
        bnProofOfStakeLimit_V2 = ~uint256(0) >> 20; // 60/4 = 15 ==> use 2**4 higher limit
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100;  // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetSpacing = 1 * 60;                       // 1 minute
        nTargetTimespan = 40 * 60;                     // 40 minutes
        nTimeSlotLength = 15;                          // 15 seconds
        nTargetTimespan_V2 = 2 * nTimeSlotLength * 60; // 30 minutes
        nMaturity = 20;
        nStakeMinAge = 60 * 60; // 1 hour
        nStakeMinDepth = 600;
        nFutureTimeDriftPoW = 7200;
        nFutureTimeDriftPoS = 180;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 100000000 * COIN;
        nMinColdStakingAmount = 1 * COIN;
        nMNCollateral = 100000 * COIN;
        strDevpubkey = "0244c600ccbd92f0b940a4b6272901c671b8bb4f3f7497257edb410c813f9c6b81";

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nPengolinCoinBadBlockTime = 1471401614;  // Skip nBit validation of Block 259201 per PR #915
        nPengolinCoinBadBlocknBits = 0x1c056dac; // Skip nBit validation of Block 259201 per PR #915
        nModifierUpdateBlock = 615800;
        nZerocoinStartHeight = 1500000;
        nZerocoinStartTime = 1667216798;        // October 17, 2017 4:30:00 AM
        nBlockEnforceSerialRange = 895400;      //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 891737;         //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 891730;      //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 902850;      //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 268200 * COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 1153160;             //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nBlockDoubleAccumulated = 1050010;
        nEnforceNewSporkKey = 1566860400; //!> Sporks signed after Monday, August 26, 2019 11:00:00 PM GMT must use the new spork key
        nRejectOldSporkKey = 1569538800;  //!> Fully reject old spork key after Thursday, September 26, 2019 11:00:00 PM GMT
        nBlockStakeModifierlV2 = 1967000;
        nBIP65ActivationHeight = 1808634;
        // Activation height for TimeProtocolV2, Blocks V7 and newMessageSignatures
        nBlockTimeProtocolV2 = 2153200;

        // Public coin spend enforcement
        nPublicZCSpends = 1880000;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = nBlockTimeProtocolV2;

        // Blocks v7
        nBlockLastAccumulatorCheckpoint = 1686240;
        nBlockV7StartHeight = nBlockTimeProtocolV2;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;
        nSupplyBeforeFakeSerial = 0 * COIN; // zerocoin supply at block nFakeSerialBlockheightEnd

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "PengolinCoin Genesis Block 2020-07-04";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("043daa0db52fb84a9a537ab2d8cdc449ba564fee95ba48ea85941504d92e472e7da793fd3683c5a60805d0197c355f308f03aca84a5c412d7ee309f694e161522b") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
        genesis.nVersion = 1;
        genesis.nTime = 1593582000;
        genesis.nBits = 0x1e0ffff0;

        genesis.nNonce = 1056171;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000865fddb23c371506db1692c393b7f4c5813f9139ea20b808b325aa96316"));
        assert(genesis.hashMerkleRoot == uint256("0xfcfa14c0ca9a1a800cf9aa280214160c58862e99d9448e0930ccdf81cce7084d"));

        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed01.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed02.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed03.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed04.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed05.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed06.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 57);  // starting with 'P' or 'Q'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // starting with '8'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63); // starting with 'S'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 205);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x03)(0x2E)(0x26)(0x34).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x03)(0x22)(0x32)(0x2C).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x81)(0x00)(0x00)(0x78).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        nBudgetCycleBlocks = 43200; //!< Amount of blocks in a months period of time (using 1 minutes per) = (60*24*30)
        strSporkPubKey = "044acc158410ea5d4b70e1d41e8a6188926e3c1f4929ba2364bc646b6f96ba042efa3e522b3a384f7d470ffb1d16642a902c9987c77a3dae10eb1dbb0a71a9816c";
        strSporkPubKeyOld = "04741c129026abe1bd39585aec6a462748452b5d68a904a2de8d52c4fe9faeb7d4d9755978013bb828e1625274fe5c25c95f54c954f55f2f4ba7528f6e586f46f0";
        strObfuscationPoolDummyAddress = "D87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                          "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                          "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                          "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                          "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                          "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7;         // Assume about 20kb each
        nMaxZerocoinPublicSpendsPerTransaction = 637; // Assume about 220 bytes each input
        nMinZerocoinMintFee = 1 * CENT;               //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20;              //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100;       //full security level for accumulators
        nZerocoinHeaderVersion = 4;        //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zpgo to be stakable

        nBudget_Fee_Confirmations = 6;             // Number of confirmations for the finalization fee
        nProposalEstablishmentTime = 60 * 60 * 24; // Proposals must be at least a day old to make it into a budget
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("04abf72ec1a4ceb858205fde2e166949fb9a66275e423a0664e3f4658ca5c1404abed454ce01ce6f6b1d91183290d569a6bf5a79755cd51a6b31116944c2647d08");
        nDefaultPort = 33003;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nLastPOWBlock = 200;
        nPengolinCoinBadBlockTime = 1489001494;  // Skip nBit validation of Block 259201 per PR #915
        nPengolinCoinBadBlocknBits = 0x1e0a20bd; // Skip nBit validation of Block 201 per PR #915
        nMaturity = 15;
        nStakeMinDepth = 100;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 100000000 * COIN;
        nZerocoinStartHeight = 201576;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1;            //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737;         //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730;      //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850;      //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0;              //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 444020;               //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1566860400;        //!> Sporks signed after Monday, August 26, 2019 11:00:00 PM GMT must use the new spork key
        nRejectOldSporkKey = 1569538800;         //!> Reject old spork key after Thursday, September 26, 2019 11:00:00 PM GMT
        nBlockStakeModifierlV2 = 1214000;
        nBIP65ActivationHeight = 851019;
        // Activation height for TimeProtocolV2, Blocks V7 and newMessageSignatures
        nBlockTimeProtocolV2 = 1347000;

        // Public coin spend enforcement
        nPublicZCSpends = 1106100;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = nBlockTimeProtocolV2;

        // Blocks v7
        nBlockLastAccumulatorCheckpoint = nPublicZCSpends - 10;
        nBlockV7StartHeight = nBlockTimeProtocolV2;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;
        nSupplyBeforeFakeSerial = 0;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1593582001;

        genesis.nNonce = 1474993;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000cde1f27e0baa02b4291f9357975e132b97f6e97a73e3c0fdb4571de19e1"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed01.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed02.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed03.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed04.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed05.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls
        vSeeds.push_back(CDNSSeedData("pengolincoin.xyz", "seed06.pengolincoin.xyz")); // Primary DNS Seeder from Fuzzbawls


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 117);  // Testnet pengolincoin addresses start with 'p'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 10);   // Testnet pengolincoin script addresses start with '5'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 125); // starting with 's'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 204);      // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet pengolincoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet pengolincoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet pengolincoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        nBudgetCycleBlocks = 144; //!< Ten cycles per day on testnet
        strSporkPubKey = "044acc158410ea5d4b70e1d41e8a6188926e3c1f4929ba2364bc646b6f96ba042efa3e522b3a384f7d470ffb1d16642a902c9987c77a3dae10eb1dbb0a71a9816c";
        strSporkPubKeyOld = "04741c129026abe1bd39585aec6a462748452b5d68a904a2de8d52c4fe9faeb7d4d9755978013bb828e1625274fe5c25c95f54c954f55f2f4ba7528f6e586f46f0";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3;         // Number of confirmations for the finalization fee. We have to make this very short
                                               // here because we only have a 8 block finalization window on testnet

        nProposalEstablishmentTime = 60 * 5; // Proposals must be at least 5 mns old to make it into a test budget
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 33005;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 250;
        nMaturity = 100;
        nStakeMinAge = 0;
        nStakeMinDepth = 0;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 300;
        nBlockZerocoinV2 = 300;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1;              //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 999999999; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 999999999;         //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 999999999;      //Last valid accumulator checkpoint
        nBlockStakeModifierlV2 = 255;
        nBlockTimeProtocolV2 = 999999999;

        // Public coin spend enforcement
        nPublicZCSpends = 350;

        // Blocks v7
        nBlockV7StartHeight = nPublicZCSpends + 1;
        nBlockLastAccumulatorCheckpoint = nPublicZCSpends - 10;

        // New P2P messages signatures
        nBlockEnforceNewMessageSignatures = 1;

        // Fake Serial Attack
        nFakeSerialBlockheightEnd = -1;

        //! Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1593582002;
        genesis.nNonce = 3;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x63a30a6b4ff0e4de73bc326e4fb1357dcb4c395b5239751684115fca4d1222e7"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        strSporkPubKey = "044acc158410ea5d4b70e1d41e8a6188926e3c1f4929ba2364bc646b6f96ba042efa3e522b3a384f7d470ffb1d16642a902c9987c77a3dae10eb1dbb0a71a9816c";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 33007;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;

static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

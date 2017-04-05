/*
 * Authors: Sanchayan Maity
 */

/**
 * @file
 * Definitions of a LFU tag store.
 */

#include "mem/cache/tags/lfu.hh"

#include "debug/CacheRepl.hh"
#include "mem/cache/base.hh"

LFU::LFU(const Params *p) : BaseSetAssoc(p)
{

}

CacheBlk*
LFU::accessBlock(Addr addr, bool is_secure, Cycles &lat, int master_id)
{
    CacheBlk *blk = BaseSetAssoc::accessBlock(addr,
                        is_secure, lat, master_id);

    return blk;
}

CacheBlk*
LFU::findVictim(Addr addr)
{
    CacheBlk *blk = BaseSetAssoc::findVictim(addr);
    unsigned set = extractSet(addr);
    unsigned minimum;

    if (blk && blk->isValid()) {
            BlkType *blk = nullptr;
            for (int i = 0; i < allocAssoc; ++i) {
                    BlkType *b = sets[set].blks[i];
                    if (i == 0) {
                            minimum = b->refCount;
                            blk = b;
                    }
                    else if (b->refCount < minimum) {
                            minimum = b->refCount;
                            blk = b;
                    }
            }
            assert(!blk || blk->way < allocAssoc);

            DPRINTF(CacheRepl,
                    "set %x: selecting blk %x for replacement\n",
                    set, regenerateBlkAddr(blk->tag, set));
    }

    return blk;
}

void
LFU::insertBlock(PacketPtr pkt, BlkType *blk)
{
    BaseSetAssoc::insertBlock(pkt, blk);

    int set = extractSet(pkt->getAddr());
    sets[set].moveToHead(blk);
}

void
LFU::invalidate(CacheBlk *blk)
{
    BaseSetAssoc::invalidate(blk);

    int set = blk->set;
    sets[set].moveToTail(blk);
}

LFU*
LFUParams::create()
{
    return new LFU(this);
}

/*
 * Authors: Sanchayan Maity
 */


/**
 * @file
 * Declaration of a LFU tag store.
 * The LFU tags guarantee that the system will
 * purge the item with the lowest reference frequency.
 * */

#ifndef __MEM_CACHE_TAGS_LFU_HH__
#define __MEM_CACHE_TAGS_LFU_HH__

#include "mem/cache/tags/base_set_assoc.hh"
#include "params/LFU.hh"

class LFU : public BaseSetAssoc
{
  public:
    /** Convenience typedef. */
    typedef LFUParams Params;

    /**
     * Construct and initialize this tag store.
     */
    LFU(const Params *p);

    /**
     * Destructor
     */
    ~LFU() {}

    CacheBlk* accessBlock(Addr addr, bool is_secure,
                        Cycles &lat, int context_src);
    CacheBlk* findVictim(Addr addr);
    void insertBlock(PacketPtr pkt, BlkType *blk);
    void invalidate(CacheBlk *blk);
};

#endif // __MEM_CACHE_TAGS_LFU_HH__

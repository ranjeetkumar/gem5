/*
 * Authors: Prashanth Ramaprasad
 */

/**
 * @file
 * Declaration of a LIFO tag store.
 * The LIFO tags guarantee that the true least-recently-used way in
 * a set will always be evicted.
 */

#ifndef __MEM_CACHE_TAGS_LIFO_HH__
#define __MEM_CACHE_TAGS_LIFO_HH__

#include "mem/cache/tags/base_set_assoc.hh"
#include "params/LIFO.hh"

class LIFO : public BaseSetAssoc
{
  public:
    /** Convenience typedef. */
    typedef LIFOParams Params;

    /**
     * Construct and initialize this tag store.
     */
    LIFO(const Params *p);

    /**
     * Destructor
     */
    ~LIFO() {}

    CacheBlk* accessBlock(Addr addr, bool is_secure, Cycles &lat,
                         int context_src);
    CacheBlk* findVictim(Addr addr);
    void insertBlock(PacketPtr pkt, BlkType *blk);
    void invalidate(CacheBlk *blk);
};

#endif // __MEM_CACHE_TAGS_LIFO_HH__

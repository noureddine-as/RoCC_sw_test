/*======================================================================*/
/* TIMA LABORATORY                                                      */
/*======================================================================*/
#include "encoding.h"
#include "util.h"

void init_csrs()
{
    write_csr(mie, 0);
    write_csr(sie, 0);
    write_csr(mip, 0);
    write_csr(sip, 0);
    write_csr(mideleg, 0);
    write_csr(medeleg, 0);
}

void enable_timer_interrupts()
{
    MTIMECMP[0] = (uint64_t)-1ULL;
    set_csr(mie, MIP_MTIP);
    set_csr(mstatus, MSTATUS_MIE);    
}

int main(int argc, char** argv)
{
    init_csrs();
    
    int local = 0;

    unsigned hartid = read_csr(mhartid);
    unsigned m_status = read_csr(mstatus);
    unsigned s_status = read_csr(sstatus);

    enable_timer_interrupts();

    MTIMECMP[0] = MTIME + 4000;

    printf("mhartid = 0x%llx   -   mstatus = 0x%llx   -   sstatus = 0x%llx   -   mideleg = 0x%llx   -   medeleg = 0x%llx \n",
            hartid, m_status, s_status, read_csr(mideleg), read_csr(medeleg));

    printf("Starting waiting loop ..  mtime = %lld  ..  mtimecmp = %lld \n", MTIME, MTIMECMP[0]);

    while (local < 8000) {
        local++;
        if(local % 50 == 0)
            printf("Waiting ..  mtime = %lld  ..  mtimecmp = %lld \n", MTIME, MTIMECMP[0]);
    }

    return 0;
}

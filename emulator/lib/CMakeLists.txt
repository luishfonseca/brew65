add_library(mos6502)
target_sources(mos6502 PRIVATE 6502/mos6502.cpp)
target_include_directories(mos6502 PUBLIC 6502)

add_library(da65)
target_sources(da65 PRIVATE
    cc65/src/common/abend.c      cc65/src/common/cmdline.c    cc65/src/common/filestat.c  cc65/src/common/hashtab.c      cc65/src/common/segnames.c  cc65/src/common/tgttrans.c
    cc65/src/common/addrsize.c   cc65/src/common/coll.c       cc65/src/common/filetime.c  cc65/src/common/intptrstack.c  cc65/src/common/shift.c     cc65/src/common/version.c
    cc65/src/common/alignment.c  cc65/src/common/cpu.c        cc65/src/common/filetype.c  cc65/src/common/intstack.c     cc65/src/common/strbuf.c    cc65/src/common/xmalloc.c
    cc65/src/common/assertion.c  cc65/src/common/debugflag.c  cc65/src/common/fname.c     cc65/src/common/matchpat.c     cc65/src/common/strpool.c   cc65/src/common/xsprintf.c
    cc65/src/common/bitops.c     cc65/src/common/exprdefs.c   cc65/src/common/fp.c        cc65/src/common/mmodel.c       cc65/src/common/strstack.c
    cc65/src/common/chartype.c   cc65/src/common/fileid.c     cc65/src/common/gentype.c   cc65/src/common/print.c        cc65/src/common/strutil.c
    cc65/src/common/check.c      cc65/src/common/filepos.c    cc65/src/common/hashfunc.c  cc65/src/common/searchpath.c   cc65/src/common/target.c

    cc65/src/da65/asminc.c    cc65/src/da65/data.c     cc65/src/da65/infofile.c  cc65/src/da65/opc6502.c     cc65/src/da65/opc65c02.c   cc65/src/da65/opctable.c
    cc65/src/da65/attrtab.c   cc65/src/da65/error.c    cc65/src/da65/labels.c    cc65/src/da65/opc6502dtv.c  cc65/src/da65/opc65sc02.c  cc65/src/da65/output.c
    cc65/src/da65/code.c      cc65/src/da65/global.c   cc65/src/da65/opc6502x.c  cc65/src/da65/opchuc6280.c  cc65/src/da65/scanner.c    cc65/src/da65/comments.c  
    cc65/src/da65/handler.c   cc65/src/da65/opc4510.c  cc65/src/da65/opc65816.c  cc65/src/da65/opcm740.c     cc65/src/da65/segment.c
)
target_include_directories(da65 PUBLIC cc65/src/da65 cc65/src/common)

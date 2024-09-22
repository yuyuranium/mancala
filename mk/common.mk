# Ref: https://github.com/sysprog21/shecc/blob/master/mk/common.mk
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    PRINTF = printf
else
    PRINTF = env printf
endif

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
    REDIR =
else
    Q := @
    VECHO = @$(PRINTF)
    REDIR = >/dev/null
endif

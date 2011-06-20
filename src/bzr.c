#include <string.h>
#include "common.h"
#include "bzr.h"

static int
bzr_probe(vccontext_t* context)
{
    return isdir(".bzr");
}

static result_t*
bzr_get_info(vccontext_t* context)
{
    result_t* result = init_result();
    char buf[1024];

    if (read_first_line(".bzr/branch/last-revision", buf, 1024)) {
        debug("read first line from .bzr/branch/last-revision: '%s'", buf);
        result->revision = strdup(buf);   /* XXX mem leak */
        *(strchr(result->revision, ' ')) = '\0';
    }
    else {
        debug("failed to read from .bzr/branch/last-revision: assuming not an bzr repo");
        return NULL;
    }

    return result;
}

vccontext_t* get_bzr_context(options_t* options)
{
    return init_context("bzr", options, bzr_probe, bzr_get_info);
}

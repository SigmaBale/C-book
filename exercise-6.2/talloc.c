#include <stdlib.h>
#include "treenode.h"

struct treenode *talloc(void) {
    return (struct treenode *) malloc(sizeof(struct treenode));
}

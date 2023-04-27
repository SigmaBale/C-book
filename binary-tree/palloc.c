#include <stdlib.h>
#include "keycount.h"

struct treenode *palloc() {
    return (struct treenode *) malloc(sizeof(struct treenode));
}

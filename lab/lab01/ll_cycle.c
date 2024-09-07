#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
	if (!head)
		return 0;
	node *tortoise=head,*hare=head;
	do
	{
		hare=hare->next;
                if (!hare)
                        return 0;
		hare=hare->next;
		if (!hare)
			return 0;
		tortoise=tortoise->next;
	}
	while (tortoise!=hare);
	return 1;
}

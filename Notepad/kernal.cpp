#include "stdafx.h"
#include "kernal.h"

SITEXT::SITEXT()
{
	headp = new SICHARNODE('\n');
	tailp = new SICHARNODE('\n');
	headp->nextp = tailp;
	tailp->prevp = headp;
	cursorp = tailp;
	pagewidth = DEFAULT_PAGEWIDTH;
	vlinep.clear();
	vparap.clear();

	text_changed_f = false;
	set_curfontp_f = false;
	inselect = false;
	fwdnum = 0;
}



void SITEXT::print_list()
{
	for (SICHARNODE_P p = headp->nextp; p != tailp; p = p->nextp)
	{
		if (isenter(p->ch))
		{
			printf("-------------------------\n");
			continue;
		}
		printf("%c\n", p->ch);
		//		p->draw_infop->POS->print();
		p->draw_infop->POS.print();
		printf("\n");
		p->draw_infop->L.print();
		printf("\n\n");
	}
}

void del(SICHARNODE* p)
{
	p->prevp->nextp = p->nextp;
	p->nextp->prevp = p->prevp;
	delete p;
}
void del(SICHARNODE* ps, SICHARNODE* pe)
{
	if (ps == pe)
	{
		del(ps);
		return;
	}
	ps->prevp->nextp = pe->nextp;
	pe->nextp->prevp = ps->prevp;
	for (SICHARNODE_P p = ps->nextp; p != pe; p = p->nextp) delete p->prevp;
	delete pe;
}
void del(const SIRANGE& range)
{
	del(range.sp, range.ep);
}
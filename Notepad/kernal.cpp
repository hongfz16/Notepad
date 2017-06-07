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

inline void SITEXT::anticolor(SICHARNODE_P ps, SICHARNODE_P pe)
{
	for (SICHARNODE_P p = ps; p != pe; p = p->nextp)
	{
		p->char_infop->bgcolor = (~(p->char_infop->bgcolor))&((1 << 25) - 1);
		p->char_infop->color = (~(p->char_infop->color))&((1 << 25) - 1);
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
	if (ps == pe) return;
	if (ps->nextp == pe)
	{
		del(ps);
		return;
	}
	SICHARNODE_P p;
	ps->prevp->nextp = pe;
	pe->prevp = ps->prevp;
	for (p = ps->nextp; p->nextp != pe; p = p->nextp) delete p->prevp;
	delete p->prevp;
	delete p;
}
void del(const SIRANGE& range)
{
	del(range.sp, range.ep);
}
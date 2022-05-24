void
shiftviewclients(const Arg *arg)
{
	Arg shifted;
	Client *c;
	unsigned int tagmask = 0;

	Monitor *origselmon = selmon;
	for (selmon = mons; selmon; selmon = selmon->next)
	for (c = selmon->clients; c; c = c->next) {
		if (!(c->tags & SPTAGMASK))
			tagmask = tagmask | c->tags;
	}
	selmon = origselmon;

	shifted.ui = selmon->tagset[selmon->seltags] & ~SPTAGMASK;

	do {
		if (arg->i > 0) // left circular shift
			shifted.ui = (shifted.ui << arg->i)
			   | (shifted.ui >> (NUMTAGS - arg->i));
		else // right circular shift
			shifted.ui = (shifted.ui >> -arg->i)
			   | (shifted.ui << (NUMTAGS + arg->i));
		shifted.ui &= ~SPTAGMASK;
	} while (tagmask && !(shifted.ui & tagmask));

	view(&shifted);
}


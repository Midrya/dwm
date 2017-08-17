void
landscape (Monitor *mon)
{
  unsigned int n, nx, ny, nw, nh;
  Client *c;

  nx = mon->wx;
  ny = 0;
  nw = mon->ww;
  nh = mon->wh;

  for (n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);

  if (0 == n) return;

  if (1 == n)
    {
      c = nexttiled(mon->clients);
      resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
    }
  else
    {
      nh /= 2;
      c = nexttiled(mon->clients);
      resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);

      ny += nh;
      nw /= n - 1;

      while ((c = nexttiled(c->next)))
        {
          resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
          nx += nw;
        }
    }
}

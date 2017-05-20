void
central (Monitor *mon) 
{
  unsigned int i, n, nx, ny, nw, nh;
  Client *c;

  nx = mon->wx;
  ny = 0;
  nw = mon->ww;
  nh = mon->wh;

  for (n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);

  if (n == 0) return;

  if (n < 3)
    {
      nw /= n;
      for (c = nexttiled(mon->clients); c; c = nexttiled(c->next))
        {
          resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
          nx += nw;
        }
    }
  else
    {
      unsigned int lnx, rnx, cnx, lrnw, cnw, lnh, rnh, lny, rny;

      cnw  = nw / 2;
      lrnw = nw / 4;
      lnx  = nx;
      cnx  = lnx + lrnw;
      rnx  = cnx + cnw;
      lnh  = nh / (((n - 1) / 2) + ((n - 1) % 2));
      rnh  = nh / ((n - 1) / 2);
      lny  = ny;
      rny  = ny;

      c = nexttiled(mon->clients);
      resize(c, cnx, ny, cnw - 2 * c->bw, nh - 2 * c->bw, False); 

      for (i = 1, c = nexttiled(c->next); c; c = nexttiled(c->next), i++)
        {
          if ((i % 2) == 1)
            {
              resize(c, lnx, lny, lrnw - 2 * c->bw, lnh - 2 * c->bw, False);
              lny += lnh;
            }
          else
            {
              resize(c, rnx, rny, lrnw - 2 * c->bw, rnh - 2 * c->bw, False);
              rny += rnh;
            }
        }
    }

}

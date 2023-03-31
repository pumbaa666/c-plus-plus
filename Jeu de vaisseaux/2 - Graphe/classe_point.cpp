Point::Point()
{
	Init(0,0);
}

void Point::Init(int x, int y)
{
	vX = x;
   vY = y;
}

int Point::GetX()
{
	return vX;
}

int Point::GetY()
{
	return vY;
}

void Point::SetDonnees(int vPlace, int vValeur)
{
	tDonnees[vPlace] = vValeur;
}

int Point::GetDonnees(int vPlace)
{
	return tDonnees[vPlace];
}

void Point::Dessiner(TDC & dc, TColor vCouleur)
{
	TPen Stylo(vCouleur,1,0);
   TBrush Pinceau(vCouleur);
   dc.SelectObject(Stylo);
   dc.SelectObject(Pinceau);
	dc.Ellipse(vX-3, vY-3, vX+3, vY+3);
}

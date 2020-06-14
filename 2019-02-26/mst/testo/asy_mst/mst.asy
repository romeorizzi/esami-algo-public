unitsize(1cm);
import math;
settings.tex = "pdflatex";

real node_size = .45;
real text_size = 2;

void disegna_nodo(pair pos, string txt = "", pen color = black, pen background = white) {
	path c = circle(pos, node_size);
	fill(c, background);
	draw(c, black+1);
	label(scale(text_size)*txt, pos, color);
}

void disegna_array(pair pos, int n) {
	path l = pos -- pos+(n, 0) -- pos+(n, 1) -- pos+(0, 1) -- pos;
	draw(l);
	for (int i=0; i<n; ++i)
		draw(pos+(i+1, 0) -- pos+(i+1, 1));
}

pair[] P = {(0, 0), (2, 2), (4, 0), (2, -2), (6, 0), (8, 2), (8, -2)};
string[] S = {"0", "1", "2", "3", "4", "5", "6"};


void disegna_arco(int x, int y, string txt = "", pen p = black, real deg = 0, bool arrow = false) {
    path l;
    pair start = P[x];
    pair end = P[y];
    if (start != end) {
        pair d = unit(end-start) * node_size;
        l = (start+d) -- (end-d);
    } else {
        pair center = start+dir(deg)*node_size*sqrt(2);
        if (arrow) l = arc(center, node_size, deg-135, deg+90) -- start+dir(deg+45)*node_size;
        else l = arc(center, node_size, deg-135, deg+135);
    }
    if (arrow) draw(l, p, EndArrow(21*node_size));
    else draw(l, p);
    label(scale(text_size*0.45)*txt, l, p);
}

disegna_arco(0, 1, "7", green);
disegna_arco(0, 3, "30");
disegna_arco(0, 2, "14", green);
disegna_arco(1, 2, "21");
disegna_arco(2, 3, "10", green);
disegna_arco(2, 4, "1", green);
disegna_arco(4, 5, "6", green);
disegna_arco(4, 6, "9");
disegna_arco(5, 6, "4", green);



for (int i=0; i<P.length; ++i)
	disegna_nodo(P[i], S[i]);



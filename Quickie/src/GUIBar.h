#include "VertexShape.h"

#ifndef _GUI_BAR_H_
#define _GUI_BAR_H_

class GUIBar : public VertexShape {

public:

	GUIBar(VertexShape*, D3DXVECTOR3&);
	~GUIBar();

	float			max;
	float			percent;

	VertexShape*	parent;

	void init(Graphics*);
	void update(float);
	void draw(D3DXMATRIX&);

};

#endif _GUI_BAR_H_
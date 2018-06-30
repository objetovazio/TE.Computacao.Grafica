#include "MeshItem.h"

MeshItem::MeshItem()
{
}


MeshItem::~MeshItem()
{
}

void MeshItem::Draw(bool isSelection, bool drawBoundingBox)
{
	float ambiente[] = { Ambiente.x, Ambiente.y, Ambiente.z, 1.0 };
	float difusa[] = { Difusa.x, Difusa.y, Difusa.z, 1.0 };
	float especular[] = { ComponenteEspecular.x, ComponenteEspecular.y, ComponenteEspecular.z, 1.0 };
	float coeficienteEspecular[] = { CoeficienteEspecular };
	float thisColor[3];

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	if (!isSelection) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
		glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
		glMaterialfv(GL_FRONT, GL_SHININESS, coeficienteEspecular);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, GetIdTextura());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, GetTextureCoordenate());

		thisColor[0] = GetColor().r;
		thisColor[1] = GetColor().g;
		thisColor[2] = GetColor().b;
	}
	else {
		thisColor[0] = GetSelectColor().r;
		thisColor[1] = GetSelectColor().g;
		thisColor[2] = GetSelectColor().b;
	}

	glNormalPointer(GL_FLOAT, 0, this->GetNormais());

	glVertexPointer(3, GL_FLOAT, 0, this->GetVertices());

	glPushMatrix();

	if (isSelection) {
		glColor3f(thisColor[0], thisColor[1], thisColor[2]);
	}

	glTranslated(this->GetPosition().x, this->GetPosition().y, this->GetPosition().z);

	glDrawElements(GL_TRIANGLES, GetQuantidadeIndices(), GL_UNSIGNED_INT, this->GetIndices());

	glPopMatrix();

	if (drawBoundingBox) DrawBoundingBox();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	if (!isSelection) {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
}

void MeshItem::DrawBoundingBox() {
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(2.0f, 2.0f, 0.0f);

	glVertex3f(MinCoord.x + Position.x, MinCoord.y + Position.y, MinCoord.z + Position.z);
	glVertex3f(MinCoord.x + Position.x, MaxCoord.y + Position.y, MinCoord.z + Position.z);

	glVertex3f(MinCoord.x + Position.x, MinCoord.y + Position.y, MaxCoord.z + Position.z);
	glVertex3f(MinCoord.x + Position.x, MaxCoord.y + Position.y, MaxCoord.z + Position.z);

	glVertex3f(MinCoord.x + Position.x, MinCoord.y + Position.y, MinCoord.z + Position.z);
	glVertex3f(MinCoord.x + Position.x, MinCoord.y + Position.y, MaxCoord.z + Position.z);

	glVertex3f(MinCoord.x + Position.x, MaxCoord.y + Position.y, MinCoord.z + Position.z);
	glVertex3f(MinCoord.x + Position.x, MaxCoord.y + Position.y, MaxCoord.z + Position.z);

	glVertex3f(MaxCoord.x + Position.x, MinCoord.y + Position.y, MinCoord.z + Position.z);
	glVertex3f(MaxCoord.x + Position.x, MaxCoord.y + Position.y, MinCoord.z + Position.z);

	glVertex3f(MaxCoord.x + Position.x, MinCoord.y + Position.y, MaxCoord.z + Position.z);
	glVertex3f(MaxCoord.x + Position.x, MaxCoord.y + Position.y, MaxCoord.z + Position.z);

	glVertex3f(MaxCoord.x + Position.x, MinCoord.y + Position.y, MinCoord.z + Position.z);
	glVertex3f(MaxCoord.x + Position.x, MinCoord.y + Position.y, MaxCoord.z + Position.z);

	glVertex3f(MaxCoord.x + Position.x, MaxCoord.y + Position.y, MinCoord.z + Position.z);
	glVertex3f(MaxCoord.x + Position.x, MaxCoord.y + Position.y, MaxCoord.z + Position.z);

	glVertex3f(MinCoord.x + Position.x, MinCoord.y + Position.y, MinCoord.z + Position.z);
	glVertex3f(MaxCoord.x + Position.x, MinCoord.y + Position.y, MinCoord.z + Position.z);

	glVertex3f(MinCoord.x + Position.x, MaxCoord.y + Position.y, MinCoord.z + Position.z);
	glVertex3f(MaxCoord.x + Position.x, MaxCoord.y + Position.y, MinCoord.z + Position.z);

	glVertex3f(MinCoord.x + Position.x, MinCoord.y + Position.y, MaxCoord.z + Position.z);
	glVertex3f(MaxCoord.x + Position.x, MinCoord.y + Position.y, MaxCoord.z + Position.z);

	glVertex3f(MinCoord.x + Position.x, MaxCoord.y + Position.y, MaxCoord.z + Position.z);
	glVertex3f(MaxCoord.x + Position.x, MaxCoord.y + Position.y, MaxCoord.z + Position.z);

	glEnd();
	glPopMatrix();
}

void MeshItem::printObject()
{
	for (int i = 0; i < QuantidadeIndices; i = i + 3) {

		int x, y, z;
		x = this->GetIndices()[i];
		y = this->GetIndices()[i] + 1;
		z = (this->GetIndices()[i] + 2);

		printf("vertice: %.5f %.5f %.5f normais: %.5f %.5f %.5f\n", this->GetVertices()[x],
			this->GetVertices()[y],
			this->GetVertices()[z],
			this->GetNormais()[x],
			this->GetNormais()[y],
			this->GetNormais()[z]);
	}
}

bool MeshItem::CompareColor(glm::vec3 cores)
{
	return cores == this->GetSelectColor();
}

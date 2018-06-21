#include "MeshItem.h"

MeshItem::MeshItem()
{
}


MeshItem::~MeshItem()
{
}

void MeshItem::draw(bool isSelection)
{
	glm::vec3 thisColor = isSelection ? this->GetSelectColor() : this->GetColor();

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(GL_FLOAT, 0, this->GetNormais());

	glVertexPointer(3, GL_FLOAT, 0, this->GetVertices());

	glPushMatrix();
	glColor3f(thisColor.r, thisColor.g, thisColor.b);
	glTranslated(this->GetPosition().x, this->GetPosition().y, this->GetPosition().z);
	//glRotated(a, 0, 1, 0);
	glDrawElements(GL_TRIANGLES, this->GetIncidencia(), GL_UNSIGNED_INT, this->GetIndices());
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void MeshItem::printObject()
{
	for (int i = 0; i < this->GetIncidencia(); i = i + 3) {

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

	//printf("X: %.2f Y: %.2f Z: %.2f", this->GetPosition().x, this->GetPosition().y, this->GetPosition().z);
	/*printf("vertice: %.5f %.5f %.5f normais: %.5f %.5f %.5f\n", vertices[i], vertices[i + 1], vertices[i + 2], normais[i], normais[i + 1], normais[i + 2]);
	printf("%d inc\n", incidencia);*/
}

bool MeshItem::compareColor(glm::vec3 cores)
{
	return cores == this->GetSelectColor();
}

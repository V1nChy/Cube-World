#include "Primitive.h"

void cPrimitive::Init()
{}
void cPrimitive::Enter(GLuint vIndex, GLuint vnIndex, GLuint vtIndex, GLuint vnT)
{
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glEnableVertexAttribArray(vIndex);
	glVertexAttribPointer(vIndex, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(vtIndex);
	glVertexAttribPointer(vtIndex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point3)*mVerticesCount));

	glEnableVertexAttribArray(vnIndex);
	glVertexAttribPointer(vnIndex, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET((sizeof(point3)+sizeof(point2))*mVerticesCount));

	glEnableVertexAttribArray(vnT);
	glVertexAttribPointer(vnT, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET((sizeof(point3) + sizeof(point2)+sizeof(vec3))*mVerticesCount));
}
void cPrimitive::Render()
{
	glDrawArrays(GL_TRIANGLES, 0, mVerticesCount);
}

cFacePrimi::cFacePrimi()
{
	Init();
}
void cFacePrimi::Init()
{
	mVerticesCount = 6;
	point3 vertices[6] = {
		point3(-1,1,0),point3(-1,-1,0),point3(1,-1,0),
		point3(-1,1,0),point3(1,-1,0),point3(1,1,0)
	};

	point2 tex[6] = {
		point2(0,1),point2(0,0),point2(1,0),
		point2(0,1),point2(1,0),point2(1,1)
	};

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2))*mVerticesCount, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point3)*mVerticesCount, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point3)*mVerticesCount, sizeof(point2)*mVerticesCount, tex);

}

cPlanePrimi::cPlanePrimi()
{
	Init();
}
void cPlanePrimi::Init()
{
	mVerticesCount = 36;
	point3 vertices[36] = {
		//前
		point3(-0.5,0.5,0.5),point3(-0.5,-0.5,0.5),point3(0.5,-0.5,0.5),
		point3(-0.5,0.5,0.5),point3(0.5,-0.5,0.5),point3(0.5,0.5,0.5),
		//后
		point3(-0.5,0.5,-0.5),point3(0.5,0.5,-0.5),point3(0.5,-0.5,-0.5),
		point3(-0.5,0.5,-0.5),point3(0.5,-0.5,-0.5),point3(-0.5,-0.5,-0.5),
		//左
		point3(-0.5,0.5,0.5),point3(-0.5,0.5,-0.5),point3(-0.5,-0.5,-0.5),
		point3(-0.5,0.5,0.5),point3(-0.5,-0.5,-0.5),point3(-0.5,-0.5,0.5),
		//右
		point3(0.5,0.5,0.5),point3(0.5,-0.5,0.5),point3(0.5,-0.5,-0.5),
		point3(0.5,0.5,0.5),point3(0.5,-0.5,-0.5),point3(0.5,0.5,-0.5),
		//上
		point3(-0.5,0.5,0.5),point3(0.5,0.5,0.5),point3(0.5,0.5,-0.5),
		point3(-0.5,0.5,0.5),point3(0.5,0.5,-0.5),point3(-0.5,0.5,-0.5),
		//下
		point3(-0.5,-0.5,0.5),point3(-0.5,-0.5,-0.5),point3(0.5,-0.5,-0.5),
		point3(-0.5,-0.5,0.5),point3(0.5,-0.5,-0.5),point3(0.5,-0.5,0.5)
	};

	point2 tex[36] = {
		point2(0,1),point2(0,0),point2(1,0),
		point2(0,1),point2(1,0),point2(1,1)
	};

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2))*mVerticesCount, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point3)*mVerticesCount, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point3)*mVerticesCount, sizeof(point2)*mVerticesCount, tex);

}

cBlockPrimi::cBlockPrimi()
{
	Init();
}
void cBlockPrimi::Init()
{
	mVerticesCount = 36;
	point3 v[36] = {
		//前
		point3(-0.5,0.5,0.5),point3(-0.5,-0.5,0.5),point3(0.5,-0.5,0.5),
		point3(-0.5,0.5,0.5),point3(0.5,-0.5,0.5),point3(0.5,0.5,0.5),
		//后
		point3(-0.5,0.5,-0.5),point3(0.5,0.5,-0.5),point3(0.5,-0.5,-0.5),
		point3(-0.5,0.5,-0.5),point3(0.5,-0.5,-0.5),point3(-0.5,-0.5,-0.5),
		//左
		point3(-0.5,0.5,0.5),point3(-0.5,0.5,-0.5),point3(-0.5,-0.5,-0.5),
		point3(-0.5,0.5,0.5),point3(-0.5,-0.5,-0.5),point3(-0.5,-0.5,0.5),
		//右
		point3(0.5,0.5,0.5),point3(0.5,-0.5,0.5),point3(0.5,-0.5,-0.5),
		point3(0.5,0.5,0.5),point3(0.5,-0.5,-0.5),point3(0.5,0.5,-0.5),
		//上
		point3(-0.5,0.5,0.5),point3(0.5,0.5,0.5),point3(0.5,0.5,-0.5),
		point3(-0.5,0.5,0.5),point3(0.5,0.5,-0.5),point3(-0.5,0.5,-0.5),
		//下
		point3(-0.5,-0.5,0.5),point3(-0.5,-0.5,-0.5),point3(0.5,-0.5,-0.5),
		point3(-0.5,-0.5,0.5),point3(0.5,-0.5,-0.5),point3(0.5,-0.5,0.5)
	};

	point2 vt[36] = {
		point2(0,1),point2(0,0),point2(1,0),
		point2(0,1),point2(1,0),point2(1,1),

		point2(1,1),point2(0,1),point2(0,0),
		point2(1,1),point2(0,0),point2(1,0),

		point2(1,1),point2(0,1),point2(0,0),
		point2(1,1),point2(0,0),point2(1,0),

		point2(0,1),point2(0,0),point2(1,0),
		point2(0,1),point2(1,0),point2(1,1),

		point2(1,1),point2(0,1),point2(0,0),
		point2(1,1),point2(0,0),point2(1,0),

		point2(0,1),point2(0,0),point2(1,0),
		point2(0,1),point2(1,0),point2(1,1),
	};

	vec3 vn[36] = {
	vec3(0,0,1),vec3(0,0,1),vec3(0,0,1),
	vec3(0,0,1),vec3(0,0,1),vec3(0,0,1),

	vec3(0,0,-1),vec3(0,0,-1),vec3(0,0,-1),
	vec3(0,0,-1),vec3(0,0,-1),vec3(0,0,-1),

	vec3(-1,0,0),vec3(-1,0,0),vec3(-1,0,0),
	vec3(-1,0,0),vec3(-1,0,0),vec3(-1,0,0),

	vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
	vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

	vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
	vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

	vec3(0,-1,0),vec3(0,-1,0),vec3(0,-1,0),
	vec3(0,-1,0),vec3(0,-1,0),vec3(0,-1,0),
	};
	vec3 vnTangent[36] = {
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0)
	};
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2)+sizeof(vec3)+sizeof(vec3))*mVerticesCount, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point3)*mVerticesCount, v);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point3)*mVerticesCount, sizeof(point2)*mVerticesCount, vt);
	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2))*mVerticesCount, sizeof(vec3)*mVerticesCount, vn);
	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2)+sizeof(vec3))*mVerticesCount, sizeof(vec3)*mVerticesCount, vnTangent);

}

cBlock2Primi::cBlock2Primi()
{
	Init();
}
void cBlock2Primi::Init()
{
	mVerticesCount = 36;
	point3 v[36] = {
		//前
		point3(-0.5,0.5,0.5),point3(-0.5,-0.5,0.5),point3(0.5,-0.5,0.5),
		point3(-0.5,0.5,0.5),point3(0.5,-0.5,0.5),point3(0.5,0.5,0.5),
		//后
		point3(-0.5,0.5,-0.5),point3(0.5,0.5,-0.5),point3(0.5,-0.5,-0.5),
		point3(-0.5,0.5,-0.5),point3(0.5,-0.5,-0.5),point3(-0.5,-0.5,-0.5),
		//左
		point3(-0.5,0.5,0.5),point3(-0.5,0.5,-0.5),point3(-0.5,-0.5,-0.5),
		point3(-0.5,0.5,0.5),point3(-0.5,-0.5,-0.5),point3(-0.5,-0.5,0.5),
		//右
		point3(0.5,0.5,0.5),point3(0.5,-0.5,0.5),point3(0.5,-0.5,-0.5),
		point3(0.5,0.5,0.5),point3(0.5,-0.5,-0.5),point3(0.5,0.5,-0.5),
		//上
		point3(-0.5,0.5,0.5),point3(0.5,0.5,0.5),point3(0.5,0.5,-0.5),
		point3(-0.5,0.5,0.5),point3(0.5,0.5,-0.5),point3(-0.5,0.5,-0.5),
		//下
		point3(-0.5,-0.5,0.5),point3(-0.5,-0.5,-0.5),point3(0.5,-0.5,-0.5),
		point3(-0.5,-0.5,0.5),point3(0.5,-0.5,-0.5),point3(0.5,-0.5,0.5)
	};

	point2 vt[36] = {
		point2(0.5,1),point2(0.5,0),point2(1,0),
		point2(0.5,1),point2(1,0),point2(1,1),

		point2(1,1),point2(0.5,1),point2(0.5,0),
		point2(1,1),point2(0.5,0),point2(1,0),

		point2(1,1),point2(0.5,1),point2(0.5,0),
		point2(1,1),point2(0.5,0),point2(1,0),

		point2(0.5,1),point2(0.5,0),point2(1,0),
		point2(0.5,1),point2(1,0),point2(1,1),

		point2(0,1),point2(0,0),point2(0.5,0),
		point2(0,1),point2(0.5,0),point2(0.5,1),

		point2(0,1),point2(0,0),point2(0.5,0),
		point2(0,1),point2(0.5,0),point2(0.5,1)
	};
	vec3 vn[36] = {
		vec3(0,0,1),vec3(0,0,1),vec3(0,0,1),
		vec3(0,0,1),vec3(0,0,1),vec3(0,0,1),

		vec3(0,0,-1),vec3(0,0,-1),vec3(0,0,-1),
		vec3(0,0,-1),vec3(0,0,-1),vec3(0,0,-1),

		vec3(-1,0,0),vec3(-1,0,0),vec3(-1,0,0),
		vec3(-1,0,0),vec3(-1,0,0),vec3(-1,0,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

		vec3(0,-1,0),vec3(0,-1,0),vec3(0,-1,0),
		vec3(0,-1,0),vec3(0,-1,0),vec3(0,-1,0),
	};
	vec3 vnTangent[36] = {
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0)
	};

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2)+sizeof(vec3)+sizeof(vec3))*mVerticesCount, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point3)*mVerticesCount, v);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point3)*mVerticesCount, sizeof(point2)*mVerticesCount, vt);
	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(point3)+sizeof(point2))*mVerticesCount, sizeof(vec3)*mVerticesCount, vn);
	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2)+sizeof(vec3))*mVerticesCount, sizeof(vec3)*mVerticesCount, vnTangent);
}

cCubePrimi::cCubePrimi()
{
	Init();
}
void cCubePrimi::Init()
{
	mVerticesCount = 36;
	point3 v[36] = {
		//前
		point3(-0.5,0.5,0.5),point3(-0.5,-0.5,0.5),point3(0.5,-0.5,0.5),
		point3(-0.5,0.5,0.5),point3(0.5,-0.5,0.5),point3(0.5,0.5,0.5),
		//后
		point3(-0.5,0.5,-0.5),point3(0.5,0.5,-0.5),point3(0.5,-0.5,-0.5),
		point3(-0.5,0.5,-0.5),point3(0.5,-0.5,-0.5),point3(-0.5,-0.5,-0.5),
		//左
		point3(-0.5,0.5,0.5),point3(-0.5,0.5,-0.5),point3(-0.5,-0.5,-0.5),
		point3(-0.5,0.5,0.5),point3(-0.5,-0.5,-0.5),point3(-0.5,-0.5,0.5),
		//右
		point3(0.5,0.5,0.5),point3(0.5,-0.5,0.5),point3(0.5,-0.5,-0.5),
		point3(0.5,0.5,0.5),point3(0.5,-0.5,-0.5),point3(0.5,0.5,-0.5),
		//上
		point3(-0.5,0.5,0.5),point3(0.5,0.5,0.5),point3(0.5,0.5,-0.5),
		point3(-0.5,0.5,0.5),point3(0.5,0.5,-0.5),point3(-0.5,0.5,-0.5),
		//下
		point3(-0.5,-0.5,0.5),point3(-0.5,-0.5,-0.5),point3(0.5,-0.5,-0.5),
		point3(-0.5,-0.5,0.5),point3(0.5,-0.5,-0.5),point3(0.5,-0.5,0.5)
	};

	point2 vt[36] = {
		point2(0,1),point2(0,0),point2(1,0),
		point2(0,1),point2(1,0),point2(1,1),

		point2(1,1),point2(0,1),point2(0,0),
		point2(1,1),point2(0,0),point2(1,0),

		point2(1,1),point2(0,1),point2(0,0),
		point2(1,1),point2(0,0),point2(1,0),

		point2(0,1),point2(0,0),point2(1,0),
		point2(0,1),point2(1,0),point2(1,1),

		point2(1,1),point2(0,1),point2(0,0),
		point2(1,1),point2(0,0),point2(1,0),

		point2(0,1),point2(0,0),point2(1,0),
		point2(0,1),point2(1,0),point2(1,1),
	};

	vec3 vn[36] = {
		vec3(0,0,1),vec3(0,0,1),vec3(0,0,1),
		vec3(0,0,1),vec3(0,0,1),vec3(0,0,1),

		vec3(0,0,-1),vec3(0,0,-1),vec3(0,0,-1),
		vec3(0,0,-1),vec3(0,0,-1),vec3(0,0,-1),

		vec3(-1,0,0),vec3(-1,0,0),vec3(-1,0,0),
		vec3(-1,0,0),vec3(-1,0,0),vec3(-1,0,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

		vec3(0,-1,0),vec3(0,-1,0),vec3(0,-1,0),
		vec3(0,-1,0),vec3(0,-1,0),vec3(0,-1,0),
	};
	vec3 vnTangent[36] = {
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),
		vec3(0,1,0),vec3(0,1,0),vec3(0,1,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),

		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0),
		vec3(1,0,0),vec3(1,0,0),vec3(1,0,0)
	};
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2) + sizeof(vec3) + sizeof(vec3))*mVerticesCount, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(point3)*mVerticesCount, v);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(point3)*mVerticesCount, sizeof(point2)*mVerticesCount, vt);
	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2))*mVerticesCount, sizeof(vec3)*mVerticesCount, vn);
	glBufferSubData(GL_ARRAY_BUFFER, (sizeof(point3) + sizeof(point2) + sizeof(vec3))*mVerticesCount, sizeof(vec3)*mVerticesCount, vnTangent);

}

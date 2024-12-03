#include "Billboard.h"

void Billboard::reloadData(){
	reloadData(&(meshes[0]->vertices));
}

void Billboard::reloadData(vector<Vertex> *vertices){
    float verts[] = {
	// positions        // texture coords
		1.0f, 1.0f, 0.0f, textCoords[0], textCoords[1], //bottom left
		0.0f, 1.0f, 0.0f, textCoords[2], textCoords[3],  //bottom right
		0.0f, 0.0f, 0.0f, textCoords[4], textCoords[5],   //top right
		1.0f, 0.0f, 0.0f, textCoords[6], textCoords[7],  //top left
	};
//	vertices->clear();
	for (int i = 0; i < 20; i=i+5) {
		Vertex &v = vertices->at(i/5);
		v.Position = glm::vec3(*(verts + i), *(verts + i + 1), *(verts + i + 2));
		v.TexCoords = glm::vec2(*(verts + i + 3), *(verts + i + 4));
//		vertices->emplace_back(v);
	}
}

void Billboard::reloadData(vector<Vertex> *vertices, glm::vec3 origin){
	glm::vec3 billcam = glm::vec3(cameraDetails->getPosition().x - origin.x,
		cameraDetails->getPosition().y - origin.y,
		cameraDetails->getPosition().z - origin.z);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 right = glm::normalize(glm::cross(up, billcam));
	right.x *= this->ancho / 2.0;
	right.z *= this->ancho / 2.0;

	float verts[] = {
		// positions        // texture coords
		origin.x + right.x, origin.y       , origin.z + right.z, textCoords[0], textCoords[1], //bottom left
		origin.x - right.x, origin.y       , origin.z - right.z, textCoords[2], textCoords[3], //bottom right

		origin.x - right.x, origin.y + alto, origin.z - right.z, textCoords[4], textCoords[5], //top right
		origin.x + right.x, origin.y + alto, origin.z + right.z, textCoords[6], textCoords[7], //top left
	};
//	vertices->clear();
	for (int i = 0; i < 20; i = i + 5) {
		Vertex &v = vertices->at(i/5);
		v.Position = glm::vec3(*(verts + i), *(verts + i + 1), *(verts + i + 2));
		v.TexCoords = glm::vec2(*(verts + i + 3), *(verts + i + 4));
//		vertices->emplace_back(v);
	}
//	buildKDtree();
}

Billboard::Billboard(int glTextura, WCHAR textura[], float x, float y, float z, Camera* camera) {
	wstring tex((const wchar_t*)textura);
	string text(tex.begin(), tex.end());
	Texture t = { glTextura , "texture_diffuse", text.c_str() };
	initBillboard(t, ancho, alto, x, y, z, camera, GL_DYNAMIC_DRAW);
}

Billboard::Billboard(WCHAR textura[], float ancho, float alto, float x, float y, float z, Camera* camera) {
	unsigned int texturaB;
	bool alpha = true;
	wstring tex((const wchar_t*)textura);
	string text(tex.begin(), tex.end());
	texturaB = TextureFromFile(text.c_str(), this->directory, false, true, &alpha);
	Texture t = { texturaB , "texture_diffuse", text.c_str() };
	initBillboard(t, ancho, alto, x, y, z, camera, GL_DYNAMIC_DRAW);
}

void Billboard::initBillboard(Texture texture, float ancho, float alto, float x, float y, float z, Camera* camera,  int VBOGLDrawType, int EBOGLDrawType){
	cameraDetails = camera;
	vector<unsigned int> indices;
	vector<Vertex>	vertices;
	vector<Texture>	textures;

	this->alto = alto;
	this->ancho= ancho;
//		this->ancho = ancho * 2;
//		this->alto = alto * 2;
	glm::vec3 origin = glm::vec3(x, y, z);
	setTranslate(&origin);
	textures_loaded.emplace_back(texture);
	textures.emplace_back(texture);
	for (int i = 0; i < 4; i++)
		vertices.emplace_back();
	reloadData(&vertices);
	indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	gpuDemo = NULL;
	meshes.emplace_back(new Mesh(vertices, indices, textures, VBOGLDrawType, EBOGLDrawType));
	buildKDtree();
}

Billboard::~Billboard(){
	//nos aseguramos de disponer de los recursos previamente reservados
}

// Usa el shader default para poder imprimir el billboard
void Billboard::Draw() {
	reloadData(&(meshes[0]->vertices), *getTranslate());
	if (gpuDemo == NULL) {
		// build and compile our shader zprogram
		// ------------------------------------
		gpuDemo = new Shader("shaders/billboard.vs", "shaders/billboard.fs");
//		gpuDemo = new Shader("shaders/models/1.model_material_loading.vs", "shaders/models/1.model_material_loading.fs");
		setDefaultShader(true);
	}
	if (getDefaultShader()) {
		gpuDemo->use();
		Model::prepShader(*gpuDemo);
		prepShader(*gpuDemo);
		gpuDemo->setInt("texture_diffuse1", 0);
		Draw(*gpuDemo);
		gpuDemo->desuse();
	} else Draw(*gpuDemo);
}

void Billboard::Draw(Shader &shader) {
//	glDisable(GL_DEPTH_TEST);
	Model::Draw(shader);
//	glEnable(GL_DEPTH_TEST);
}

void Billboard::prepShader(Shader& shader) {
	glm::mat4 projection = cameraDetails->getProjection();
	glm::mat4 view = cameraDetails->getView();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f)); // translate it down so it's at the center of the scene
//	model = glm::scale(model, glm::vec3(3.0f,3.0f,3.0f));

	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);
}

void Billboard::setTextureCoords(float *tCoords){
	for (int i = 0; i < 8; i++)
		textCoords[i] = tCoords[i];
}

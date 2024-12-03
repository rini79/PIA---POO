#include "Texto.h"

Texto::Texto(wstring &texto, float escala, float rotacion, float x, float y, float z, Model* camera){
	this->scale = escala;
	this->rotacion = rotacion;
	this->x = x;
	this->y = y;
	this->z = z;
	cameraDetails = camera;
	this->texto = texto;
    initTexto();
}

Texto::Texto(WCHAR *texto, float escala, float rotacion, float x, float y, float z, Model* camera){
	this->scale = escala;
	this->rotacion = rotacion;
	this->x = x;
	this->y = y;
	this->z = z;
	cameraDetails = camera;
	this->texto.assign((wchar_t*)texto);
    initTexto();
}

void Texto::initTexto(wstring &texto){
	this->texto = texto;
	initTexto();
}

void Texto::initTexto(WCHAR *texto){
	this->texto.assign((wchar_t*)texto);
	initTexto();
}

void Texto::initTexto(){
	for (int i = 0; i < this->textBillboard.size(); i++){
		delete textBillboard[i];
	}
	this->textBillboard.clear();
    long tLength = texto.size();
	if (this->textBillboard.capacity() < tLength)
	    this->textBillboard.reserve(tLength);
	font_atlas &fontTexture = font_atlas::getInstance();
    std::string stext(texto.begin(), texto.end());
	// Store the x,y location
	glm::vec2 loc = glm::vec2(x,y);
	glm::vec2 rotated_pt;

	float xpos = x;
	float ypos = y;
	for (int i = 0; i < tLength; i++) {
		// get the atlas information
		char ch = stext[i];

		Character &ch_data = fontTexture.ch_atlas[ch];

//		float xpos = x + (ch_data.Bearing.x * scale);
//		float ypos = y - (ch_data.Size.y - ch_data.Bearing.y) * scale;

		float w = ch_data.Size.x * scale;
		float h = ch_data.Size.y * scale;

		float margin = 0.00002; // This value prevents the minor overlap with the next char when rendering
//		rotated_pt = rotate_pt(loc, glm::vec2(xpos, ypos + h), rotacion);
        textBillboard.emplace_back(new Billboard(fontTexture.textureID, (WCHAR*)L"TEXTO", xpos, ypos, 0, cameraDetails->cameraDetails));
        float texCoords[] = { ch_data.bot_right.x - margin, ch_data.bot_right.y,
		                      ch_data.top_left.x+ margin,  ch_data.bot_right.y,
		                      ch_data.top_left.x + margin, ch_data.top_left.y,
		                      ch_data.bot_right.x - margin, ch_data.top_left.y };
        textBillboard.back()->setTextureCoords(texCoords);
		textBillboard.back()->setCleanTextures(false);
        textBillboard.back()->reloadData();
		xpos += scale;
	}
}

Texto::~Texto(){
    if (gpuDemo != NULL)
        delete gpuDemo;
	textBillboard.clear();
}

// Usa el shader default para poder imprimir el billboard
void Texto::Draw(){
	if (gpuDemo == NULL) {
		// build and compile our shader zprogram
		// ------------------------------------
		gpuDemo = new Shader("shaders/text_shader.vs", "shaders/text_shader.fs");
//		gpuDemo = new Shader("shaders/models/1.model_material_loading.vs", "shaders/models/1.model_material_loading.fs");
		setDefaultShader(true);
	}
	if (defaultShader) {
		gpuDemo->use();
		gpuDemo->setInt("texture_diffuse1", 0);
		Draw(*gpuDemo);
		gpuDemo->desuse();
	} else Draw(*gpuDemo);
}

void Texto::Draw(Shader &shader){
    for (int i = 0; i < textBillboard.size(); i ++){
		prepShader(shader,*textBillboard[i]->getTranslate());
        textBillboard[i]->Draw(shader);
    }
}

void Texto::prepShader(Shader& shader, glm::vec3 &pos){
//	glm::mat4 projection = cameraDetails->cameraDetails->getProjection();
    glm::mat4 projection = glm::ortho(0.0f, (SCR_WIDTH+0.0f), (SCR_HEIGHT+0.0f), 0.0f, -1.0f, 1.0f);
	glm::mat4 view = cameraDetails->cameraDetails->getView();

	glm::mat4 model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::translate(model, pos); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(scale,scale,0.0f));

	shader.setVec3("color", glm::vec3(100,100,100));
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);
}

glm::vec2 Texto::rotate_pt(glm::vec2& rotate_about, glm::vec2 pt, float& rotation_angle){
	// Return the rotation point
	glm::vec2 translated_pt = pt - rotate_about;

	// Apply rotation
	float radians = (rotation_angle  * 3.14159365f) / 180.0f; // convert degrees to radians
	float cos_theta = cos(radians);
	float sin_theta = sin(radians);

	// Rotated point of the corners
	glm::vec2 rotated_pt = glm::vec2((translated_pt.x * cos_theta) - (translated_pt.y * sin_theta),
		(translated_pt.x * sin_theta) + (translated_pt.y * cos_theta));

	return (rotated_pt + rotate_about);
}

void Texto::setDefaultShader(bool defaultShader){
    this->defaultShader = defaultShader;
}
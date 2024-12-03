#include "Scenario.h"
#include "Producto.h"
#include "Comprador.h"
#ifdef __linux__ 
#define ZeroMemory(x,y) memset(x,0,y)
#define wcscpy_s(x,y,z) wcscpy(x,z)
#define wcscat_s(x,y,z) wcscat(x,z)
#endif



Scenario::Scenario(Camera *cam) {
    glm::vec3 translate;
	glm::vec3 scale;
    Model* model = new Model("models/Cube.obj", cam);
	translate = glm::vec3(0.0f, 0.0f, 3.0f);
	scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
	model->setScale(&scale);
	model->setTranslate(&translate);
	InitGraph(model);
}
Scenario::Scenario(Model *camIni) {
    InitGraph(camIni);
}
void Scenario::InitGraph(Model *main) {
    float matAmbient[] = { 1,1,1,1 };
	float matDiff[] = { 1,1,1,1 };
	angulo = 0;
	camara = main;
	//creamos el objeto skydome
	sky = new SkyDome(32, 32, 20, (WCHAR*)L"skydome/atardecer4.jpg", main->cameraDetails);
	//creamos el terreno
	terreno = new Terreno((WCHAR*)L"skydome/terreno5.jpg", (WCHAR*)L"skydome/grass4.jpg", 400, 400, main->cameraDetails);
	water = new Water((WCHAR*)L"textures/terreno.bmp", (WCHAR*)L"textures/water.bmp", 25, 25, camara->cameraDetails);
	glm::vec3 translate;
	glm::vec3 scale;
	glm::vec3 rotation;
	std::rand();
	bool posicionActual2 = 0;
	int posicionActual = 0;
	translate = glm::vec3(-32.0f, 11.5f, 14.0f);
	water->setTranslate(&translate);
	water->setRotZ(180);
	// load models
	// -----------
	ourModel.emplace_back(main);
	Model* model;

	model = new Model("models/tiendaaaa.obj", main->cameraDetails, true, true);				//1
	translate = glm::vec3(0.0f, 13.0f, 80.0f);
	scale = glm::vec3(6.0f, 6.0f, 6.0f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotX(0); // 45� rotation
	model->setRotY(90);

	model->lightColor = glm::vec3(5, 5, 5);
	model->lightPos = glm::vec3(5, 5, 5);
	delete model->AABB;
	ourModel.emplace_back(model);
	
	model = new Model("models/shelf.obj", main->cameraDetails, false, false);				//2
	translate = glm::vec3(23.0f, 13.0f, 82.0f);
	scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(270);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);

	model = new Model("models/shelf.obj", main->cameraDetails, false, false);				//2 repetido
	translate = glm::vec3(-23.0f, 13.0f, 82.0f);
	scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(90);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);

	model = new Model("models/shelf.obj", main->cameraDetails, false, false);				//2 repetido
	translate = glm::vec3(23.0f, 13.0f, 70.0f);
	scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(270);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);

	model = new Model("models/shelf.obj", main->cameraDetails, false, false);				//2 repetido
	translate = glm::vec3(-23.0f, 13.0f, 70.0f);
	scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(90);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);

	model = new Model("models/shelf.obj", main->cameraDetails, false, false);				//2 repetido
	translate = glm::vec3(0.0f, 13.0f, 70.0f);
	scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(180);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);

	model = new Model("models/shelf.obj", main->cameraDetails, false, false);				//2 repetido
	translate = glm::vec3(0.0f, 13.0f, 82.0f);
	scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(180);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);



	model = new Model("models/cashier.obj", main->cameraDetails, false, false);				//3
	translate = glm::vec3(10.0f, 12.8f, 50.0f);
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(270);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);

	model = new Model("models/cashier.obj", main->cameraDetails, false, false);				//3 repetido
	translate = glm::vec3(0.0f, 12.8f, 50.0f);
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(270);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);



	model = new Model("models/cashier.obj", main->cameraDetails, false, false);				//3 repetido
	translate = glm::vec3(-10.0f, 12.8f, 50.0f);
	scale = glm::vec3(0.03f, 0.03f, 0.03f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(270);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);



	//model = new Model("models/fogata.obj", main->cameraDetails);
	//translate = glm::vec3(0.0f, 10.0f, 25.0f);
	//model->setTranslate(&translate);
	//rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation X
	//model->setRotX(45); // 45� rotation
	//ourModel.emplace_back(model);
	//model= new Model("models/pez.obj", main->cameraDetails);
	//translate = glm::vec3(0.0f, 7.0f, 50.0f);
	//model->setTranslate(&translate);
	//ourModel.emplace_back(model);
	//model = new Model("models/dancing_vampire.dae", main->cameraDetails);
	//translate = glm::vec3(0.0f, terreno->Superficie(0.0f, 60.0f) , 60.0f);
	//scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	//model->setTranslate(&translate);
	//model->setScale(&scale);
	//model->setRotY(90);
	//ourModel.emplace_back(model);
/*	try{
		Animation *ani = new Animation("models/dancing_vampire.dae", model->GetBoneInfoMap(), model->GetBoneCount());
	    model->setAnimator(new Animator(ani));
	}catch(...){
		cout << "Could not load animation!\n";
	}*/
	//model = new Model("models/Silly_Dancing.dae", main->cameraDetails);
	//translate = glm::vec3(10.0f, terreno->Superficie(0.0f, 60.0f) , 60.0f);
	//scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	//model->setTranslate(&translate);
	//model->setScale(&scale);
	//model->setRotY(180);
	//ourModel.emplace_back(model);
/*	try{
		Animation *ani = new Animation("models/Silly_Dancing.dae", model->GetBoneInfoMap(), model->GetBoneCount());
	    model->setAnimator(new Animator(ani));
	}catch(...){
		cout << "Could not load animation!\n";
	}*/
//	model = new Model("models/IronMan.obj", main);
//	translate = glm::vec3(0.0f, 20.0f, 30.0f);
//	scale = glm::vec3(0.025f, 0.025f, 0.025f);	// it's a bit too big for our scene, so scale it down
//	model->setScale(&scale);
//	model->setTranslate(&translate);
//	ourModel.emplace_back(model);
	model = new Model("models/plaatano.obj", main->cameraDetails, false, false);				//4
	srand(time(NULL));	
	int randomNumber = rand() % 3;		//genera num random
	switch ((posicionActual + randomNumber) % 4 + 1) {
	case 1:
		translate = glm::vec3(0.0f, 15.0f, 70.0f);
		break;
	case 2:
		translate = glm::vec3(0.0f, 15.0f, 82.0f);
		break;
	case 3:
		translate = glm::vec3(-23.0f, 15.0f, 82.0f);
		break;
	case 4:
		translate = glm::vec3(23.0f, 15.0f, 70.0f);
		break;
	}
	//translate = glm::vec3(0.0f, 15.0f, 70.0f);
	scale = glm::vec3(0.8f, 0.8f, 0.8f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(90);
	ourModel.emplace_back(model);
	model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	model->lightPos = glm::vec3(2, 2, 2);

	model = new Model("models/huevo.obj", main->cameraDetails, false, false);					//5
	srand(time(NULL));
	int randomNumber2 = rand() % 3;		//genera num random
	switch ((posicionActual2 + randomNumber2) % 4 + 1) {
	case 1:
		translate = glm::vec3(0.0f, 17.5f, 70.0f);
		break;
	case 2:
		translate = glm::vec3(0.0f, 17.5f, 82.0f);
		break;
	case 3:
		translate = glm::vec3(-23.0f, 17.5f, 82.0f);
		break;
	case 4:
		translate = glm::vec3(23.0f, 17.5f, 70.0f);
		break;
	}
	//translate = glm::vec3(-23.0f, 17.5f, 70.0f);
	scale = glm::vec3(0.08f, 0.08f, 0.08f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setScale(&scale);
	ourModel.emplace_back(model);
	//model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	//model->lightPos = glm::vec3(2, 2, 2);

	//model = new Model("models/.obj", main->cameraDetails, false, false);
	//translate = glm::vec3(0.0f, 15.0f, 82.0f);
	//scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
	//model->setTranslate(&translate);
	//model->setScale(&scale);
	//model->setRotY(180);
	//ourModel.emplace_back(model);
	//model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	//model->lightPos = glm::vec3(2, 2, 2);

	model = new Model("models/Car.obj", main->cameraDetails);									//6
	translate = glm::vec3(2.0f, 13.0f, -15.0f);
	scale = glm::vec3(0.4f, 0.4f, 0.4f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(60);
	ourModel.emplace_back(model);

	model = new Model("models/Orange.obj", main->cameraDetails);								//7
	translate = glm::vec3(-22.0f, 14.5f, 69.0f);
	//scale = glm::vec3(0.4f, 0.4f, 0.4f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(60);
	ourModel.emplace_back(model);

	model = new Model("models/cereales.obj", main->cameraDetails);								//8
	translate = glm::vec3(-3.0f, 16.0f, 52.0f);
	//scale = glm::vec3(0.4f, 0.4f, 0.4f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(60);
	ourModel.emplace_back(model);

	model = new Model("models/leche.obj", main->cameraDetails);								//9
	translate = glm::vec3(0.0f, 14.0f, 70.0f);
	//scale = glm::vec3(0.4f, 0.4f, 0.4f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(0);
	ourModel.emplace_back(model);

	model = new Model("models/pan.obj", main->cameraDetails);								//10
	translate = glm::vec3(23.0f, 14.0f, 70.0f);
	//scale = glm::vec3(0.4f, 0.4f, 0.4f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(90);
	ourModel.emplace_back(model);

	//model = new Model("models/Car.obj", main->cameraDetails);
	//translate = glm::vec3(-12.0f, 13.0f, 4.0f);
	//scale = glm::vec3(0.4f, 0.4f, 0.4f);
	//model->setTranslate(&translate);
	//model->setScale(&scale);
	//model->setRotY(160);
	//ourModel.push_back(model);


	model = new Model("models/bancaa.obj", main->cameraDetails);								//11
	translate = glm::vec3(13.0f, 13.0f, 30.0f);
	scale = glm::vec3(2.0f, 2.0f, 2.0f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(180);
	ourModel.emplace_back(model);

	model = new Model("models/bancaa.obj", main->cameraDetails); 								//11 repetido
	translate = glm::vec3(-13.0f, 13.0f, 30.0f);
	scale = glm::vec3(2.0f, 2.0f, 2.0f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(180);
	ourModel.emplace_back(model);


	model = new Model("models/carrito.obj", main->cameraDetails);								//12
	translate = glm::vec3(10.0f, 13.0f, 05.0f);
	scale = glm::vec3(2.0f, 2.0f, 2.0f);
	model->setTranslate(&translate);
	model->setRotY(30);
	ourModel.emplace_back(model);
	model->setScale(&scale);

	model = new Model("models/carrito.obj", main->cameraDetails);								//13 repetido
	translate = glm::vec3(15.0f, 13.0f, 015.0f);
	scale = glm::vec3(2.0f, 2.0f, 2.0f);
	model->setTranslate(&translate);
	model->setRotY(80);
	model->setScale(&scale);
	ourModel.emplace_back(model);

	model = new Model("models/carrito.obj", main->cameraDetails);								//13 repetido
	translate = glm::vec3(-10.0f, 13.0f, 5.0f);
	scale = glm::vec3(2.0f, 2.0f, 2.0f);
	model->setTranslate(&translate);
	model->setRotY(100);
	model->setScale(&scale);
	ourModel.emplace_back(model);



	//model = new Model("models/manzanaaaaa.obj", main->cameraDetails, false, false);
	//translate = glm::vec3(10.0f, 14.0f, 0.0f);
	//scale = glm::vec3(1.0f, 1.0f, 1.0f);	// it's a bit too big for our scene, so scale it down
	//model->setTranslate(&translate);
	//model->setScale(&scale);
	//ourModel.emplace_back(model);
	//model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	//model->lightPos = glm::vec3(2, 2, 2);


	model = new Model("models/guagua.obj", main->cameraDetails, false, false);					//14
	translate = glm::vec3(10.0f, 12.7f, 24.0f);
	scale = glm::vec3(1.3f, 1.3f, 1.3f);	// it's a bit too big for our scene, so scale it down
	model->setTranslate(&translate);
	model->setRotY(30);
	model->setScale(&scale);
	ourModel.emplace_back(model);
	//model->lightColor = glm::vec3(2, 2, 2);                    // luz fija
	//model->lightPos = glm::vec3(2, 2, 2);

	//model = new Model("models/INDUSTRIAL SHELVES.obj", main->cameraDetails);
	//translate = glm::vec3(0.0f, 10.0f, 25.0f);
	//model->setTranslate(&translate);
	//
	//ourModel.emplace_back(model);


	//ANIMACIONES

	model = new Model("models/vendedor.fbx", translate, main->cameraDetails);				//15
	translate = glm::vec3(-3.0f, 12.0f, 55.0f);
	scale = glm::vec3(0.008f, 0.008f, 0.008f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(90);
	ourModel.emplace_back(model);
	try {
		Animation* ani = new Animation("models/vendedor.fbx", model->GetBoneInfoMap(), model->GetBoneCount());
		model->setAnimator(new Animator(ani));

	}
	catch (...) {
		cout << "Could not load animation!\n";
	}


	model = new Model("models/vendedor2.fbx", translate, main->cameraDetails);				//16
	translate = glm::vec3(5.0f, 12.0f, 55.0f);
	scale = glm::vec3(0.008f, 0.008f, 0.008f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(-90);
	ourModel.emplace_back(model);
	try {
		Animation* ani = new Animation("models/vendedor2.fbx", model->GetBoneInfoMap(), model->GetBoneCount());
		model->setAnimator(new Animator(ani));

	}
	catch (...) {
		cout << "Could not load animation!\n";
	}


	model = new Model("models/Excited.fbx", translate, main->cameraDetails);				//17
	translate = glm::vec3(-15.0f, 12.0f, 15.0f);
	scale = glm::vec3(0.008f, 0.008f, 0.008f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(-90);
	ourModel.emplace_back(model);
	try {
		Animation* ani = new Animation("models/Excited.fbx", model->GetBoneInfoMap(), model->GetBoneCount());
		model->setAnimator(new Animator(ani));

	}
	catch (...) {
		cout << "Could not load animation!\n";
	}

	model = new Model("models/Shuffling.fbx", translate, main->cameraDetails);				//18
	translate = glm::vec3(-15.0f, 12.0f, 20.0f);
	scale = glm::vec3(0.008f, 0.008f, 0.008f);
	model->setTranslate(&translate);
	model->setScale(&scale);
	model->setRotY(0);
	ourModel.emplace_back(model);
	try {
		Animation* ani = new Animation("models/Shuffling.fbx", model->GetBoneInfoMap(), model->GetBoneCount());
		model->setAnimator(new Animator(ani));

	}
	catch (...) {
		cout << "Could not load animation!\n";
	}



	inicializaBillboards();
	/*std::wstring prueba(L"Recoge los 10 objetos c:");
	ourText.emplace_back(new Texto(prueba, 20, 0, 0, SCR_HEIGHT, 0, camara));*/
	billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"billboards/carritopov.png", 6, 6, 100, 100, 0, camara->cameraDetails));
	scale = glm::vec3(600.0f, 600.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	billBoard2D.back()->setScale(&scale);

	wchar_t componente[100] = { 0 };
	wcscpy_s(wCoordenadas, 350, L"X: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->x);
	wcscat_s(wCoordenadas, 350, componente);
	wcscat_s(wCoordenadas, 350, L" Y: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->y);
	wcscat_s(wCoordenadas, 350, componente);
	wcscat_s(wCoordenadas, 350, L" Z: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->z);
	wcscat_s(wCoordenadas, 350, componente);
	coordenadas = new Texto((WCHAR*)wCoordenadas, 15, 0, 0, 0, 0, camara);
}

void Scenario::inicializaBillboards() {
	float ye = terreno->Superficie(0, 0);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol.png", 6, 6, 15, ye - 1, 0, camara->cameraDetails));

	ye = terreno->Superficie(5, -5);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol2.png", 6, 6, 2, ye - 1, -5, camara->cameraDetails));

	ye = terreno->Superficie(-9, -15);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol3.png", 8, 8, -9, ye - 1, -15, camara->cameraDetails));
}


float posX = 5.0f;  // pos X
float posY;        
float posZ = -5.0f; // pos Z
float speedX = 0.1f; // velocidad X
float speedZ = 0.1f; // velocidad Z

	//el metodo render toma el dispositivo sobre el cual va a dibujar
	//y hace su tarea ya conocida
Scene* Scenario::Render() {


	//borramos el biffer de color y el z para el control de profundidad a la 
	//hora del render a nivel pixel.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);

	// Actualizamos la camara
	camara->cameraDetails->CamaraUpdate(camara->getRotY(), camara->getTranslate());

	posX += speedX;
	posZ += speedZ; 
	posY = terreno->Superficie(posX, posZ) - 1;


	if (posX > 10 || posX < -10) speedX = -speedX;
	if (posZ > 10 || posZ < -10) speedZ = -speedZ;


	if (this->animacion > 25) { 
		wchar_t textura[50] = { L"billboards/tornado" };
		if (this->frameArbol != 1) {
			wcscat_s(textura, 50, to_wstring(this->frameArbol).c_str());
		}
		wcscat_s(textura, 50, L".png");


		if (billBoard[1]) {
			delete billBoard[1];
		}
		billBoard[1] = new Billboard((WCHAR*)textura, 6, 6, posX, posY, posZ, camara->cameraDetails);


		if (this->frameArbol == 3) {
			this->frameArbol = 1;
		}
		else {
			this->frameArbol++;
		}
		this->animacion = 0;
	}
	else {
		this->animacion++;
	}
	// Decimos que dibuje la media esfera
	sky->Draw();
	// Ahora el terreno
	terreno->Draw();
	water->Draw();
	// Dibujamos cada billboard que este cargado en el arreglo de billboards.
	for (int i = 0; i < billBoard.size(); i++)
		billBoard[i]->Draw();
	for (int i = 0; i < billBoard2D.size(); i++)
		billBoard2D[i]->Draw();
	// Dibujamos cada modelo que este cargado en nuestro arreglo de modelos
	for (int i = 0; i < ourModel.size(); i++) {
		ourModel[i]->Draw();
	}
	for (int i = 0; i < ourText.size(); i++) {
		ourText[i]->Draw();
	}
	// No es optimo ya que crea el texto cada renderizado....
	wchar_t componente[100] = { 0 };
	wcscpy_s(wCoordenadas, 350, L"X: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->x);
	wcscat_s(wCoordenadas, 350, componente);
	wcscat_s(wCoordenadas, 350, L" Y: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->y);
	wcscat_s(wCoordenadas, 350, componente);
	wcscat_s(wCoordenadas, 350, L" Z: ");
	swprintf(componente, 100, L"%f", getMainModel()->getTranslate()->z);
	wcscat_s(wCoordenadas, 350, componente);
	coordenadas->initTexto((WCHAR*)wCoordenadas);
	coordenadas->Draw();
	// Le decimos a winapi que haga el update en la ventana
	return this;
}
	
std::vector<Model*> *Scenario::getLoadedModels() {
	return &ourModel;
}
std::vector<Billboard*> *Scenario::getLoadedBillboards() {
	return &billBoard;
}
Model* Scenario::getMainModel() {
	return this->camara;
}
float Scenario::getAngulo() {
	return this->angulo;
}
void Scenario::setAngulo(float angulo) {
	this->angulo = angulo;
}
SkyDome* Scenario::getSky() {
	return sky;
}
Terreno* Scenario::getTerreno() {
	return terreno;
}

	Scenario::~Scenario() {
	if (this->sky != NULL) {
		delete this->sky;
		this->sky = NULL;
	}
	if (this->terreno != NULL) {
		delete this->terreno;
		this->terreno = NULL;
	}
	if (billBoard.size() > 0)
		for (int i = 0; i < billBoard.size(); i++)
			delete billBoard[i];
	if (billBoard2D.size() > 0)
		for (int i = 0; i < billBoard2D.size(); i++)
			delete billBoard2D[i];
	this->billBoard.clear();
	if (ourText.size() > 0)
		for (int i = 0; i < ourText.size(); i++)
			delete ourText[i];
	this->ourText.clear();
	if (ourModel.size() > 0)
		for (int i = 0; i < ourModel.size(); i++)
			if (ourModel[i] != camara)
			delete ourModel[i];
	this->ourModel.clear();
}

#include <iostream>
#include <vector>
#include <cmath>
#include <any>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "graphics/utils/GLUtils.h"

#include "shader/Shader.h"
#include "shader/Program.h"

#include "graphics/gl_objects/Vao_e.h"
#include "graphics/gl_objects/Vao.h"

#include "graphics/gl_objects/buffers/Vbo.h"
#include "graphics/gl_objects/buffers/Ebo.h"
#include "graphics/gl_objects/buffers/fbo/Fbo.h"
#include "graphics/gl_objects/buffers/fbo/LayerFbo.h"

#include "graphics/gl_objects/texture/Texture.h"
#include "graphics/gl_objects/texture/DepthTexture.h"

#include "graphics/elements/window/Window.h"

#include "graphics/param/RenderParam.h"

#include "matrix/utils/MatrixUtils.h"

#include "matrix/projection/ProjectionMatrix.h"

#include "matrix/projection/OrthogonalMatrix.h"
#include "matrix/projection/perspective/PerspectiveMatrix.h"
#include "matrix/projection/perspective/PerspectiveWindowMatrix.h"

#include "matrix/transform/TransformMatrix.h"

#include "world/scene/Scene.h"
#include "world/camera/Camera.h"

#include "world/objects/Object.h"
#include "world/objects/Cube.h"

#include "events/Dispatcher.h"

#include "graphics/elements/window/callback/GLFWCallback.h"
#include "graphics/elements/window/callback/keyCallback/KeyDispatcher.h"
#include "graphics/elements/window/callback/mouseCallback/MouseDispatcher.h"
#include "graphics/elements/window/callback/windowCallback/WindowDispatcher.h"

#include "graphics/IRenderable.h"

#include "world/scene/elements/Elements.h"

#include "utils/file/files/File.h"
#include "utils/file/files/Any.h"
#include "utils/file/files/folders/Folder.h"
#include "utils/file/utils/FileUtils.h"
#include "utils/file/utils/FileListener.h"

#include "utils/time/TimeUtils.h"

#include "events/update/UpdateDispatcher.h"
#include "events/update/listeners/DynamicUpdatable.h"

#include "engine/Engine.h"
#include "engine/update/Updater.h"
#include "engine/controller/controllers/TestController.h"
#include "engine/sample/samples/TestSample.h"

#include "utils/collision/gjk/hitbox/obb/OBBHitbox.h"
#include "utils/collision/gjk/GJKUtils.h"


using namespace std;

class Print {
public:
    Print() = default;

    virtual ~Print() = default;

    void foo() {
	cout << "Output from Pring class" << endl;
    }
};

class Swap : public IRenderable {
public:
    void render(RenderParam &param) override {
	param.fbo_input->cloneData(*param.fbo_output);
    }
};

class A : public IRenderable {
public:
    A(shared_ptr<Program> program) {
	this->program = program;
    }

    void render(RenderParam &param) override {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glUseProgram(program->getProgram());
	param.setProgram(program);
    }
private:
    shared_ptr<Program> program;
};

bool w = false, a = false, s = false, d = false, q = false, e = false, up = false, down = false, right = false, left = false;

float x_p = 0, y_p = 0, z_p = 0;
float x_r = 0, y_r = 180, z_r = 0;

class L2 : public callback::KeyListener {
public:
    void onKeyEvent(callback::KeyEvent &event) override {
	switch(event.getKey()) {
	    case 87:
		w = event.getAction();
		break;
	    case 65:
		a = event.getAction();
		break;
	    case 83:
		s = event.getAction();
		break;
	    case 68:
		d = event.getAction();
		break;
	    case 81:
		q = event.getAction();
		break;
	    case 69:
		e = event.getAction();
		break;
	    case 262:
		::right = event.getAction();
		break;
	    case 263:
		::left = event.getAction();
		break;
	    case 265:
		::up = event.getAction();
		break;
	    case 264:
		::down = event.getAction();
		break;
	}

	cout << "w: " << w << " a: " << a << " s: " << s << " d: " << d << " q: " << q << " e: " << e << " up: " << ::up << " down: " << ::down << " right: " << ::right << " left: " << ::left << endl;
    }
};

class L : public callback::KeyListener, public callback::MouseListener, public callback::WindowListener, public DynamicUpdatable, public fls::FileListener {
public:
    void onKeyEvent(callback::KeyEvent &event) override {
	cout << "KeyEvent: " << event.getKey() << " " << event.getAction() << endl;
    }

    void onMouseButtonEvent(callback::MouseButtonEvent &event) override {
	cout << "MouseEvent: " << event.getButton() << " " << event.getAction() << endl;
    }

    void onFramebufferSizeEvent(callback::FramebufferSizeEvent &event) {
	cout << "WindowEvent: " << event.getWidth() << " " << event.getHeight() << endl;
	glViewport(0, 0, event.getWidth(), event.getHeight());
    }

    void onUpdate(float delta_time) {
	cout << "Update: " << delta_time << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    void onFile(std::shared_ptr<fls::IFile> file, std::stack<std::pair<std::shared_ptr<fls::IFolder>, int>> stack) {
	cout << "FILE <<<<<< " << file->getName() << endl;
    }
};

class Test {
public:
    Test(string s) {
	this->s = s;
    }   

    void print() {
	cout << s << endl;
    }
private:
    string s;
};

void readFolder(shared_ptr<fls::IFolder> folder, const string space) {
    vector<shared_ptr<fls::IFile>> files = folder->getFiles();

    for (int i = 0; i < files.size(); i++) {
	shared_ptr<fls::IFile> file = files[i];

	cout << space << " - " << "filename: " << file->getName() << endl;

	if (file->getType() == fls::Type::Folder) {
	    cout << space << "      " << "/\\ is folder" << endl;

	    readFolder(dynamic_pointer_cast<fls::IFolder>(file), space + "    ");
	}
    }
}

class MyFolder : public fls::Folder {
public:
    MyFolder(const string &name) : fls::Folder(name) {}

    vector<shared_ptr<fls::IFile>> getFiles() const override {
	cout << "myFolder" << endl;

	return this->files;
    }
};

int main() {
/*
    //инициализация
    Engine engine("root");

    shared_ptr<fls::Any<Print>> print_object = make_shared<fls::Any<Print>>(make_shared<Print>(), "print");

    shared_ptr<fls::IFolder> folder = engine.getRoot(), folder2 = make_shared<MyFolder>("folder2"), folder3 = make_shared<fls::Folder>("folder3"), folder4 = make_shared<fls::Folder>("folder4");

    shared_ptr<TestController> controller = make_shared<TestController>("TestController");

    shared_ptr<fls::File> file1 = make_shared<fls::File>("file1", fls::Type::File);
    shared_ptr<fls::File> file2 = make_shared<fls::File>("file2", fls::Type::File);
    shared_ptr<fls::File> file3 = make_shared<fls::File>("file3", fls::Type::File);
    shared_ptr<fls::File> file4 = make_shared<fls::File>("file4", fls::Type::File);
    shared_ptr<fls::File> file5 = make_shared<fls::File>("file5", fls::Type::File);
    shared_ptr<fls::File> file6 = make_shared<fls::File>("file6", fls::Type::File);
    shared_ptr<fls::File> file7 = make_shared<fls::File>("file7", fls::Type::File);
    shared_ptr<fls::File> file8 = make_shared<fls::File>("file8", fls::Type::File);

    //установка файловой системы
    folder->add(file1);
    folder->add(file2);
    folder->add(folder2);

    folder2->add(file3);
    folder2->add(folder3);

    folder3->add(file6);
    folder3->add(controller);

    folder2->add(file4);
    folder2->add(folder4);

    folder->add(file5);

    folder4->add(file7);
    folder4->add(print_object);
    folder4->add(file8);
    
    //установка контроллеров
    engine.reg(*controller);

    //запуск контроллеров
    engine.run();

    shared_ptr<fls::IFolder> folder3_s = dynamic_pointer_cast<fls::IFolder>(file6->getParent());
    shared_ptr<fls::IFolder> folder2_s = dynamic_pointer_cast<fls::IFolder>(folder3_s->getParent());
    shared_ptr<fls::IFolder> folder_s = dynamic_pointer_cast<fls::IFolder>(folder2_s->getParent());

    //file1->setParent(folder2);
    folder2->add(file1);

    readFolder(folder_s, "");

    //controller->setRoot(folder);
    //controller->run();

    shared_ptr<fls::IFile> my_file = fls::get("folder2/folder3/../../folder2/file3/../file1", std::dynamic_pointer_cast<fls::IFile>(folder));

    //
    fls::getAs<fls::Any<Print>>("folder2/folder4/print", fls::cast<fls::IFolder, fls::IFile>(folder))->get()->foo();
    //

    cout << "MY_FILE: " << (my_file ? my_file->getName() : "nullptr") << endl;
*/

    try {
	gl::glfwInit();
    }
    catch (const runtime_error &e) {
	cout << e.what() << endl;
    }

    shared_ptr<L> l = make_shared<L>();
    
    shared_ptr<gr::Window> window = make_shared<gr::Window>(500, 500, "OpenGL Project");

    window->createCallback();

    window->getCallback()->getKeyEvent()->addListener(l);
    window->getCallback()->getMouseEvent()->addListener(l);
    window->getCallback()->getWindowEvent()->addListener(l);

    Updater updater(20);

    updater.addListener(l);

    thread updater_thread([&updater]() {
        updater.start();
    });

    try {
	gl::glInit();
    }
    catch (const runtime_error &e) {
	cout << e.what() << endl;
    }

    //Enable
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    auto vert_shader = make_shared<Shader>("../shaders/test.vert", GL_VERTEX_SHADER);
    auto frag_shader = make_shared<Shader>("../shaders/test.frag", GL_FRAGMENT_SHADER);

    vector<shared_ptr<Shader>> shaders = {vert_shader, frag_shader};

    shared_ptr<Program> program = make_shared<Program>(shaders);

    cout << "PROGRAM: " << program->getProgram() << endl;
	
    //render param
    RenderParam param(program);

    shared_ptr<tex::Texture> texture = make_shared<tex::Texture>("../textures/03.png");
    
    LayerFBO fbo(1920, 1080);

    cout << "layer FBO: " << fbo.getWidth() << " " << fbo.getHeight() << " created" << endl; 

    shared_ptr<Scene> scene = make_shared<Scene>(1920, 1080);

    ////////test
    TestSample sample(window, scene);

    shared_ptr<fls::IFolder> root = sample.getRoot();

    Engine engine(root);

    shared_ptr<TestController> controller = make_shared<TestController>("TestController");

    engine.getRoot()->getAs<fls::IFolder>("engine")->add(controller);

    engine.reg(*controller);

    engine.run();

    readFolder(engine.getRoot(), "");
    //////////

    cout << "texture loaded: w: " << texture->getWidth() << " h: " << texture->getHeight() << " t: " << endl;

    //glUseProgram(program->getProgram());

    vector<float> vert = {
	-0.5f, -0.5f, 1,
	-0.5f, 0.5f, 1,
	0.5f, 0.5f, 1,
	0.5f, -0.5f, 1
    };

    vector<float> col = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1,
	1, 1, 0
    };

    vector<float> texCords = {
	1, 0,
	1, 1,
	0, 1,
	0, 0
    };
    
    auto vert_vbo = make_shared<VBO>(vert, 3);
    auto col_vbo = make_shared<VBO>(col, 3);
    auto tex_vbo = make_shared<VBO>(texCords, 2);

    vector<shared_ptr<VBO>> vbos = {vert_vbo, col_vbo, tex_vbo};

    vector<int> ids = {
	0, 1, 2,
	0, 2, 3 
    };

    shared_ptr<EBO> ebo = make_shared<EBO>(ids);

    shared_ptr<VAO_E> vao = make_shared<VAO_E>(vbos, ebo, ebo->getLength());

    shared_ptr<Object> object = make_shared<Object>(vao, texture);

    shared_ptr<Object> object2 = make_shared<Object>(vao, scene->getFBOOutput()->getColorTexture());
    object2->getModel()->setPosition(glm::vec3(0.5f, 1, 1));
    object2->getModel()->setRotation(glm::vec3(-25, 45, 0));

    shared_ptr<Cube> cube = make_shared<Cube>(-0.5f, -0.5f, -0.5f, 1, 1, 1);
    shared_ptr<Cube> cube2 = make_shared<Cube>(-0.5f, -0.5f, -0.5f, 1, 1, 1);
    cube->getModel()->setPosition(glm::vec3(2, 0, 2));//change cube position
    cube->getModel()->setRotation(glm::vec3(0, 0, 45));//change cube rotation
    cube->getModel()->setScale(glm::vec3(1, 2, 1));//change cube scale
    //cube.setTexture(texture);

    gjk::OBBHitbox hitbox1({
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, 0.5f),
	glm::vec3(-0.5f, -0.5f, 0.5f),
	glm::vec3(-0.5f, 0.5f, -0.5f),
	glm::vec3(0.5f, 0.5f, -0.5f),
	glm::vec3(0.5f, 0.5f, 0.5f),
	glm::vec3(-0.5f, 0.5f, 0.5f)
    }, cube->getModel());

    gjk::OBBHitbox hitbox2({
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, 0.5f),
	glm::vec3(-0.5f, -0.5f, 0.5f),
	glm::vec3(-0.5f, 0.5f, -0.5f),
	glm::vec3(0.5f, 0.5f, -0.5f),
	glm::vec3(0.5f, 0.5f, 0.5f),
	glm::vec3(-0.5f, 0.5f, 0.5f)
    }, cube2->getModel());

    glm::vec3 pos(0, 2, 1), rot(x_r, y_r, z_r), scal(1, 1, 1);

    //Camera camera(pos, rot, scal, 90, 1, 0.1f, 100);
    
    shared_ptr<mtrx::PerspectiveWindowMatrix> projection_matrix = make_shared<mtrx::PerspectiveWindowMatrix>(90, 1, 0.1f, 100);
    
    window->getCallback()->getWindowEvent()->addListener(projection_matrix);

    Camera camera(pos, rot, scal, projection_matrix);

    shared_ptr<L2> l2 = make_shared<L2>();

    window->getCallback()->getKeyEvent()->addListener(l2);

    int view_matrix_uniform = glGetUniformLocation(program->getProgram(), "view_matrix"), projection_matrix_uniform = glGetUniformLocation(program->getProgram(), "projection_matrix");

    float theta = 0;

    glClearColor(1, 1, 1, 1);

    scene->addLink(make_shared<render::BindFBO>(scene->getFBOInput(), true));
    scene->addLink(make_shared<A>(program));
    scene->addLink(object);
    scene->addLink(object2);
    scene->addLink(cube);
    scene->addLink(cube2);
    scene->addLink(make_shared<render::Swap>());
    scene->addLink(make_shared<render::BindFBO>(scene->getFBOInput(), false));
    scene->addLink(make_shared<render::Display>(scene->getFBOInput()->getColorTexture()));

    window->getCallback()->getWindowEvent()->addListener(scene);

    while(!glfwWindowShouldClose(window->getWindow())) {
        glUseProgram(program->getProgram());
	theta ++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (::up) x_r += 1;
	if (::down) x_r -= 1;
	if (::left) y_r += 1;
	if (::right) y_r -= 1;
	if (q) z_r += 1;
	if (e) z_r -= 1;
	
	//ВЕКТОРА КАМЕРЫ

/*
	glm::quat q = camera.getView()->getRotationQuat();

	glm::vec3 c_forward = q * glm::vec3(0, 0, -1);
	glm::vec3 c_up = q * glm::vec3(0, 1, 0);
	glm::vec3 c_right = q * glm::vec3(1, 0, 0);
	
	c_forward /= 100;
	c_up /= 100;
	c_right /= 100;

	if (w) {
	    x_p -= c_forward.x;
	    y_p -= c_forward.y;
	    z_p -= c_forward.z;
	}
	if (s) {
	    x_p += c_forward.x;
	    y_p += c_forward.y;
	    z_p += c_forward.z;
	}
	if (d) {
	    x_p -= c_right.x;
	    y_p -= c_right.y;
	    z_p -= c_right.z;
	}
	if (a) {
	    x_p += c_right.x;
	    y_p += c_right.y;
	    z_p += c_right.z;
	}
*/
/*
	glm::quat rot_x = glm::angleAxis(glm::radians(x_r), glm::normalize(c_right));
	glm::quat rot_y = glm::angleAxis(glm::radians(y_r), glm::normalize(c_up));
	glm::quat rot_z = glm::angleAxis(glm::radians(z_r), glm::normalize(c_forward));

	//camera.getView()->setRotation(rot_y * rot_x * rot_z);

	camera.getView()->rotate(rot_x);
	camera.getView()->rotate(rot_y);
	camera.getView()->rotate(rot_z);

	x_r = 0;
	y_r = 0;
	z_r = 0;
*/
	float speed = 0.01f;
	if (w) {
	    z_p += speed;
	}
	if (s) {
	    z_p -= speed;
	}
	if (d) {
	    x_p -= speed;
	}
	if (a) {
	    x_p += speed;
	}

	cube2->getModel()->setPosition(glm::vec3(x_p, y_p, z_p));
	//camera.getView()->setPosition(glm::vec3(x_p, y_p, z_p));
	camera.getView()->setRotation(glm::vec3(x_r, y_r, z_r));
	
	cout << "GJK COLLISION STATUS: " << gjk::collision(hitbox1, hitbox2) << endl;

	//camera.getView()->setRotation(glm::vec3(0, cos(theta*3.14f/180) * 45 + 180, 0));

	//cube squash

	//cube->getModel()->rotate(glm::angleAxis(glm::radians(1.0f), glm::normalize(glm::vec3(1, 1, 1))));
	//cube->getModel()->setRotation(glm::angleAxis(glm::radians(theta), glm::normalize(glm::vec3(1, 1, 1))));
	//cube->getModel()->setRotation(glm::vec3(0, theta, theta/2));
	//cube->getModel()->setScale(glm::vec3(1, cos(theta*3.14f/180)+2, 1));

	//Наблюдение. Куб вращаеться. Кватернион переводиться в углы Эйлера, и снова применяються к кубу. Куб продолжает вращаться правильно
	glm::vec3 c_rot = cube->getModel()->getRotation();
	cube->getModel()->setRotation(c_rot);
	
	glm::mat4 view_matrix = camera.getView()->getMatrix();
	glUniformMatrix4fv(view_matrix_uniform, 1, GL_FALSE, glm::value_ptr(view_matrix));

	glm::mat4 projection_matrix = camera.getProjection()->getMatrix();

	glUniformMatrix4fv(projection_matrix_uniform, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	scene->render();

	glfwPollEvents();
	glfwSwapBuffers(window->getWindow());
    }

    updater.stop();

    updater_thread.join();

    gl::terminate();

    cout << "Hello world" << endl;
    return 0;
}

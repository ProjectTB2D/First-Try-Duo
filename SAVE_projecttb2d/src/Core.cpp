#include <math.h>
#include "global.h"
#include "Core.h"
#include "World.h"

#include <string>
#include <iostream>

#define FPSLIMIT 60

#define DISPLAY_COLLISION 0

Core::Core()
:   _view(NULL),
    _app(NULL),
    _world(NULL),
    _imgMan(NULL),
    _item_counter(0)

{
}


// ----------------------------------- ENGINE ---------------------------------------------------


void Core::initApp(int x, int y){

//sf::VideoMode DesktopMode = sf::VideoMode::getDesktopMode();

//_app = new sf::RenderWindow(DesktopMode, "jorbienEngine", sf::Style::Fullscreen);

_app = new sf::RenderWindow(sf::VideoMode(x,y,32), "jorbienEngine");

_app->setFramerateLimit(FPSLIMIT);

_win_H = y;
_win_W = x;



// ------------- INIT MANAGERS -------------------

_imgMan = new ImageManager();


}

void Core::initWorld(const char* worldname){

cout << worldname << " loaded ... " << endl;

_world = new World();

_world->createWorld(worldname);

_world->createPlayer();

 _menu = new Menu(1, sf::Vector2f(50,50), 100, 20, 0.5f);

}

void Core::initView(){

    _view = new sf::View(sf::Vector2f(0,0), sf::Vector2f(_win_W, _win_H));

}

void Core::run() {

    initApp(640,480);
    initWorld("map/bbb.map");
    initView();


while(_app->isOpen()){

    _frameTime = _clockFrame.restart().asSeconds();

    sf::Event Event;
    while (_app->pollEvent(Event)){

            if (Event.type == sf::Event::Closed)
                _app->close();
            //if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A)){

            //}

            if(Event.type == sf::Event::KeyReleased && Event.key.code == sf::Keyboard::Escape){
				_app->close();
			}

    }

/*    if(lagrefresh.GetElapsedTime() > 0.5){
        sprintf(txt, "%f", 1.f / _app->GetFrameTime());
        texte.SetText(txt);
        lagrefresh.Reset();
    }
*/

    _app->setView(*(g_core->getView()));

    _app->clear();

    // UPDATEWORLD()

    if(_menu->getEtat() != CRAFTER_OFF)
        _menu->update();

    _world->update();

    // RENDERWORLD()

    _world->render();

    // DISOLVE()

    _world->disolve();


    // *** VIEW : DEFAULT ***

    _app->setView(_app->getDefaultView());

    // Display Menu

    if(_menu->getEtat() != CRAFTER_OFF)
        _menu->render();

    // DISPLAY FPS

    sf::Text fpsMessage;
    int FPS;
    ostringstream oss;

    FPS = 1 / _frameTime;
    oss << "FPS : " << FPS;

    fpsMessage.setPosition(50.0f, 100.0f);
    fpsMessage.setColor(sf::Color(255,0,0,255));
    fpsMessage.setString(oss.str());
    fpsMessage.setCharacterSize(14);

    _app->draw(fpsMessage);


    // DISPLAY COMPLETE BUFFER

    _app->display();


}

}


////////////////////////////////////////////// GENERIC COLLISION /////////////////////////////////////////////////


bool Core::dot_in_box(sf::Vector2f a, float b[4]){

/*

    sf::Shape recta(sf::Shape::Circle(a.x,a.y,3,sf::Color::Green));
    recta.EnableFill(true);
    getApp()->Draw(recta);

    sf::Shape rectb(sf::Shape::Rectangle(b[0],b[1],b[2],b[3],sf::Color::Blue,3,sf::Color::Yellow));
    rectb.EnableFill(false);
    getApp()->Draw(rectb);

    return (a.x >= b[0] && a.x <= b[2] && a.y >= b[1] && a.y <= b[3]);
*/

return true;
}

/*
 * bounding_box()
 * bounding box collision method
 * r[4] = x1, y1, x2(=x1+w), y2(=y1+h)
 */
bool Core::bounding_box(float a[4], float b[4], bool debug){

    if(debug){

    sf::RectangleShape r1;
    r1.setSize(sf::Vector2f(a[2] - a[0], a[3] - a[1]));
    r1.setOutlineColor(sf::Color::Blue);
    r1.setPosition(a[0], a[1]);

    sf::RectangleShape r2;
    r2.setSize(sf::Vector2f(b[2] - b[0], b[3] - b[1]));
    r2.setOutlineColor(sf::Color::Green);
    r2.setPosition(b[0], b[1]);

    getApp()->draw(r1);

    getApp()->draw(r2);

/*
    cout << "-----------------------------------------------------" << endl;
    cout << "a[0] = " << a[0] << " < b[2] = " << b[2] << endl;
    cout << "a[2] = " << a[2] << " > b[0] = " << b[0] << endl;
    cout << "a[1] = " << a[0] << " < b[2] = " << b[2] << endl;
    cout << "b[3] = " << a[2] << " > b[0] = " << b[0] << endl;
*/

    }


    if(a[0]<b[2] && a[2]>b[0] && a[1]<b[3] && a[3]>b[1]){

    //cout << "YEAH !" << endl;
    return true;

    }else
    {
     return false;
    }

}

bool Core::dot_in_circle(sf::Vector2f a, sf::Vector2f b, float r){

    float dist = sqrt(pow((a.x - b.x),2) + pow((a.y - b.y),2));
    return(dist <= r);

}

sf::Vector2f Core::rotate_vector(sf::Vector2f v, float ang){

    float x = v.x, y = v.y;
    sf::Vector2f w;

    w.x = x*cos(ang) - y*sin(ang);
    w.y = y*cos(ang) + x*sin(ang);

    return w;

}

/////////////////////////////////////////// GETTER ////////////////////////////////////////////////////////////////

void Core::getInfo(){

 cout << " info ... " << endl;

}

World* Core::getWorld() {

    return _world;

}

sf::RenderWindow* Core::getApp(){

    return _app;
}

sf::View*   Core::getView() {

 return _view;

}

ImageManager* Core::getImageManager(){


return _imgMan;

}

sf::Vector2f Core::getRotatedVector(sf::Vector2f base, float ang) const{

    float x = base.x, y = base.y;
    sf::Vector2f w;

    w.x = x*cos(ang) - y*sin(ang);
    w.y = y*cos(ang) + x*sin(ang);

    return w;

}

sf::Vector2i Core::getWinSize() const{

 return sf::Vector2i(_win_W, _win_H);

}

float Core::getFrameTime() const{

    return _frameTime;

}

Core::~Core(){

delete _app;
cout << "_app ----------------[DELETED] " << endl;
delete _world;
cout << "_world --------------[DELETED] " << endl;
//delete _editor;
cout << "_world --------------[DELETED] " << endl;
delete _view;
cout << "_view ---------------[DELETED] " << endl;
delete _menu;
cout << "_menu ---------------[DELETED] " << endl;

cout << "CORE DELETED !" << endl;

cout << _item_counter << " items were generated ..." << endl;

delete _imgMan;
cout << "_imgMan ------------ [DELETED] " << endl;

}


// ////////////////////////////////////////// DEBUG //////////////////////////////////////////

void Core::countItemGenerated(){

 _item_counter++;

}

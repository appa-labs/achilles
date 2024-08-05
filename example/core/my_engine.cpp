#include "example/core/my_engine.h"

void MyEngine::initialization() {
    Engine::initialization();

    loadObjTypes("example/resources/objectTypes.txt");
    loadObjects("example/resources/objectMap.txt");
}

void MyEngine::loadObjTypes(const std::string& path) {
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        spdlog::error("Bad file path for objects patterns file: {}", path);
        stop();
    }
    LineSegment buf({0, 0}, {0, 0});
    std::string inputbuffer;
    std::string strbuf;
    std::vector<LineSegment> vectorbuf;
    float x1, y1, x2, y2;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        input >> strbuf;
        while (input >> x1 >> y1 >> x2 >> y2) {
            buf = LineSegment({x1, y1}, {x2, y2});
            vectorbuf.push_back(buf);
        }
        objtypes_.insert({strbuf, vectorbuf});
        vectorbuf.clear();
    }
}

void MyEngine::loadObjects(const std::string& path) {
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        spdlog::error("Bad file path for objects map file: {}", path);
        stop();
    }
    Vector2f buf(0, 0);
    std::string inputbuffer;
    std::string name;
    std::vector<LineSegment> vectorcache;
    std::string cachename;
    float x1, y1;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        input >> name >> x1 >> y1;
        buf = Vector2f(x1, y1);
        if (cachename != name) {
            cachename = name;
            vectorcache = objtypes_[name];
        }
        input >> inputbuffer;
        if (inputbuffer == "m") {
            float mass;
            input >> mass;
            moveable_objects_.push_back(std::make_unique<MoveableObject>(buf, vectorcache, mass));
        }
        if (inputbuffer == "s") {
            objects_.push_back(std::make_unique<Object>(buf, vectorcache));
        }
    }
    objtypes_.clear();
}

void MyEngine::stop() {
    spdlog::info("Engine close window");
    Engine::stop();
}

void MyEngine::renderFrame() {
    const auto green = sf::Color(0, 100, 0, 0);
    window.clear(green);
    for (const auto& obj : objects_) {
        renderObject(obj);
    }
    for (const auto& obj : moveable_objects_) {
        // renderObject(obj);
        // TODO(): fix this
        camera = obj->basepoint; // works only with one moveable objectss
        drawBaton(obj);
    }
    window.display();
}

void MyEngine::renderObject(const std::unique_ptr<Object>& object) {
    for (const auto& line : object->polygons) {
        sf::Vertex vline[] = {
          sf::Vertex(sf::Vector2f(
              (object->basepoint + line.p1 - camera).getSfmlCords(width, height).x,
              (object->basepoint + line.p1 - camera).getSfmlCords(width, height).y)),
          sf::Vertex(sf::Vector2f(
              (object->basepoint + line.p2 - camera).getSfmlCords(width, height).x,
              (object->basepoint + line.p2 - camera).getSfmlCords(width, height).y))};
        window.draw(vline, 2, sf::Lines);
    }
}

void MyEngine::characterJump() {
    auto* player = dynamic_cast<MoveableObject*>(moveable_objects_[0].get());
    if (player->in_touch) {
        player->velocity = player->velocity + Vector2f(0, 3);
    }
}

void MyEngine::characterLeft() {
    auto* player = dynamic_cast<MoveableObject*>(moveable_objects_[0].get());
    player->magic_force = Vector2f(-20, 0);
}

void MyEngine::characterRight() {
    auto* player = dynamic_cast<MoveableObject*>(moveable_objects_[0].get());
    player->magic_force = Vector2f(20, 0);
}

void MyEngine::restart() {
    auto* player = dynamic_cast<MoveableObject*>(moveable_objects_[0].get());
    player->basepoint = Vector2f(0, 0);
    player->magic_force = Vector2f(0, 0);
    player->velocity = Vector2f(0, 0);
    player->resultant_force = Vector2f(0, 0);
}

void MyEngine::drawBaton(const std::unique_ptr<Object>& obj) {
    LineSegment l = obj->polygons[0];
    l = l.move(obj->basepoint - Vector2f(kPhysCollisionPres, -kPhysCollisionPres) - camera);
    //auto white = sf::Color(255, 255, 255);
    auto white = player_color; // DEBUG

    sf::CircleShape circle1(kPhysCollisionPres / 2 * height);
    circle1.setFillColor(white);
    circle1.move(l.p1.getSfmlCords(width, height).x, l.p1.getSfmlCords(width, height).y);

    sf::CircleShape circle2(kPhysCollisionPres / 2 * height);
    circle2.setFillColor(white);
    circle2.move(l.p2.getSfmlCords(width, height).x, l.p2.getSfmlCords(width, height).y);

    sf::RectangleShape rect(sf::Vector2f(
        kPhysCollisionPres * height,
        0.3 / 2 * height));  // the rectangle is specified by the size
    rect.setFillColor(white);
    rect.move(
        l.p1.getSfmlCords(width, height).x, (l.p1 - Vector2f(0, kPhysCollisionPres))
                                        .getSfmlCords(width, height)
                                        .y);  // shifted relative to the top left point

    window.draw(circle1);
    window.draw(circle2);
    window.draw(rect);
}

void MyEngine::renderFPS(sf::Text& frame_rate_text) {
    if (frametime == 0) {
        ++frametime;
    }
    int fps = 2000.f / frametime;
    frame_rate_text.setString(std::to_string(fps));
    frame_rate_text.setCharacterSize(20);

    window.draw(frame_rate_text);
    window.display();
}

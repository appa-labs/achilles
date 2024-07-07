#include "src/core/engine/engine.h"

void Engine::initialization() {
    width = sf::VideoMode::getDesktopMode().width;
    height = sf::VideoMode::getDesktopMode().height;
    aspect = static_cast<float>(width) / height;

    sf::ContextSettings settings(0, 0, 8, 1, 1, 0, false);
    window.create(sf::VideoMode(width, height), "Achilles", sf::Style::Fullscreen, settings);
    window.setMouseCursorVisible(false);

    loadObjTypes("resources/objectTypes.txt");
    loadObjects("resources/objectMap.txt");
}

void Engine::loadObjTypes(const std::string& path) {
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        spdlog::error("Bad file path for objects patterns file: {}", path);
        stop();
    }
    line buf({0, 0}, {0, 0});
    std::string inputbuffer;
    std::string strbuf;
    std::vector<line> vectorbuf;
    float x1, y1, x2, y2;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        input >> strbuf;
        while (input >> x1 >> y1 >> x2 >> y2) {
            buf = line({x1, y1}, {x2, y2});
            vectorbuf.push_back(buf);
        }
        objtypes_.insert({strbuf, vectorbuf});
        vectorbuf.clear();
    }
}

void Engine::loadObjects(
    const std::string& path) {  // ���� ���, ���������� �����������: ������ � �����
    // ������� � ����������� ���������� ������
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        spdlog::error("Bad file path for objects map file: {}", path);
        stop();
    }
    vec buf(0, 0);
    std::string inputbuffer;
    std::string name;
    std::vector<line> vectorcache;
    std::string cachename;
    float x1, y1;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        input >> name >> x1 >> y1;
        buf = vec(x1, y1);
        if (cachename != name) {
            cachename = name;
            vectorcache = objtypes_[name];
        }
        input >> inputbuffer;
        if (inputbuffer == "m") {
            float mass;
            input >> mass;
            moveableObjects_.push_back(std::make_unique<MoveableObject>(buf, vectorcache, mass));
        }
        if (inputbuffer == "s") {
            objects_.push_back(std::make_unique<Object>(buf, vectorcache));
        }
    }
    objtypes_.clear();  // ����������� ������, ���� ����� ��
}

void Engine::stop() {
    spdlog::info("Engine close window");
    window.close();
}

void Engine::renderFrame() {
    const auto black = sf::Color(0, 0, 0, 0);
    window.clear(black);
    for (const auto& obj : objects_) {
        renderObject(obj);
    }
    for (const auto& obj : moveableObjects_) {
        // renderObject(obj);
        drawCollider(obj);
    }
    window.display();
}

void Engine::renderObject(const std::unique_ptr<Object>& object) {
    for (const auto& line : object->polygons) {
        sf::Vertex vline[] = {
          sf::Vertex(sf::Vector2f(
              (object->basepoint + line.p1).cord(width, height).x,
              (object->basepoint + line.p1).cord(width, height).y)),
          sf::Vertex(sf::Vector2f(
              (object->basepoint + line.p2).cord(width, height).x,
              (object->basepoint + line.p2).cord(width, height).y))};
        window.draw(vline, 2, sf::Lines);
    }
}

void Engine::physicsPerFrame() {
    for (auto& _obj : moveableObjects_) {
        auto obj = static_cast<MoveableObject*>(_obj.get());
        vec& F = obj->resultantForce;
        float m = obj->mass;
        vec& vel = obj->velocity;

        F = vec(0, -1 * m * PH_CONST_G) + obj->magicForces;
        obj->isInTouch = false;
        for (const auto& coln : objects_) {
            obj->sumNormalForces(coln.get());
        }
        for (const auto& coln : moveableObjects_) {
            obj->sumNormalForces(coln.get());
        }

        obj->magicForces = vec(0, 0);

        vec a = F / m;
        vel = vel + a * frametime / 1000.f;
        obj->move(vel * frametime / 1000.f);
    }
}

void Engine::characterJump() {
    auto player = static_cast<MoveableObject*>(moveableObjects_[0].get());
    if (player->isInTouch) {
        player->velocity = player->velocity + vec(0, 3);
    }
}

void Engine::characterLeft() {
    auto player = static_cast<MoveableObject*>(moveableObjects_[0].get());
    player->magicForces = vec(-20, 0);
}

void Engine::characterRight() {
    auto player = static_cast<MoveableObject*>(moveableObjects_[0].get());
    player->magicForces = vec(20, 0);
}

void Engine::restart() {
    auto player = static_cast<MoveableObject*>(moveableObjects_[0].get());
    player->basepoint = vec(0, 0);
    player->magicForces = vec(0, 0);
    player->velocity = vec(0, 0);
    player->resultantForce = vec(0, 0);
}

void Engine::drawCollider(const std::unique_ptr<Object>& obj) {
    line l = obj->polygons[0];
    l = l.move(obj->basepoint - vec(PH_CONST_COLLISION_PRES, -PH_CONST_COLLISION_PRES));
    auto white = sf::Color(255, 255, 255);

    sf::CircleShape circle1(PH_CONST_COLLISION_PRES / 2 * height);
    circle1.setFillColor(white);
    circle1.move(l.p1.cord(width, height).x, l.p1.cord(width, height).y);

    sf::CircleShape circle2(PH_CONST_COLLISION_PRES / 2 * height);
    circle2.setFillColor(white);
    circle2.move(l.p2.cord(width, height).x, l.p2.cord(width, height).y);

    sf::RectangleShape rect(sf::Vector2f(
        PH_CONST_COLLISION_PRES * height,
        0.3 / 2 * height));  // the rectangle is specified by the size
    rect.setFillColor(white);
    rect.move(
        l.p1.cord(width, height).x, (l.p1 - vec(0, PH_CONST_COLLISION_PRES))
                                        .cord(width, height)
                                        .y);  // shifted relative to the top left point

    window.draw(circle1);
    window.draw(circle2);
    window.draw(rect);
}

void Engine::renderFPS(sf::Text& frame_rate_text) {
    if (frametime == 0) {
        ++frametime;
    }
    int fps = 2000.f / frametime;
    frame_rate_text.setString(std::to_string(fps));
    frame_rate_text.setCharacterSize(20);

    window.draw(frame_rate_text);
    window.display();
}

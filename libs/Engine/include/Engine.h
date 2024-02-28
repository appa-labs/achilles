#pragma once
#include <Engine/include/tools.h>
#include <string>
#include <vector>

class Engine {
   public:
    static inline int height;
    static inline int width;
    static inline double aspect;

    Engine() = delete;

    static void Initialization();
    static void LoadObjects(std::string path);
    static void Stop();

   private:
    static inline std::vector<line> objects_;
};
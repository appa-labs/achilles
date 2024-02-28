#pragma once
#include <Engine/include/tools.h>
#include <string>
#include <vector>

class Engine {
   public:
    static inline int height;
    static inline int width;
    static inline double aspect;

    static void Initialization();
    static void LoadTextures(std::string path);
    static void Stop();

   private:
    static inline std::vector<line> objects_;
    // потом обязательно оптимизирую хранение и поиск текстурок, но пока так
};
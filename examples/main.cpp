#include "Volty.h"

int main() {
    Application app("Volty Example", { 2560, 1440 }, true, "../Data/res.list");
    return app.run();
}
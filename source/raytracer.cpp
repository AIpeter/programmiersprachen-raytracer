#include <thread>
#include <renderer.hpp>
#include <sdfloader.hpp>
#include <fensterchen.hpp>

int main(int argc, char* argv[])
{
  unsigned const width = 480;
  unsigned const height = 320;
  std::string const filename = "./image.ppm";
  std::string const sdfname = "sdfdatei.sdf";
  Scene* scene = loadSDF(sdfname);

  std::thread thr([&scene]() { scene->render.render(scene->shapes, scene->lights); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , scene->render.colorbuffer().data());

    win.update();
  }

  thr.join();

  return 0;
}

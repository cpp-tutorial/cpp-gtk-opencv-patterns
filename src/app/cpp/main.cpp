#include "main-window.hpp"

#include "service-locator.hpp"


int main (int argc, char *argv[]) {

    ServiceLocator::startUp();
    
    auto app = Gtk::Application::create(
            argc, 
            argv, 
            "ch.agl-developpement.cpp-tutorial.raspberry-cpp-gtk-opencv");

    MainWindow mainWindow(300, 300);
    return app->run(mainWindow);    
}

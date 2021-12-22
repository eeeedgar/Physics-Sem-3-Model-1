#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double x, y;
double v_x, v_y;
double m, l, k;
int FPS;
double g;
int how_many_seconds;

string config_name;


struct force
{
    double X;
    double Y;
};

double length(double x_, double y_)
{
    return sqrt(x_ * x_ + y_ * y_);
}

double angle_rad(double x_, double y_)
{
    return atan2(x_, y_);
}

double angle_grad(double x_, double y_)
{
    return angle_rad(x_, y_) * 180 / M_PI;
}

force elastic_force(double x_, double y_)
{
    double delta_l = length(x_, y_) - l;
    double module_f = k * delta_l;
    double angle_f_rad = angle_rad(-x_, -y_);
    double f_x = module_f * sin(angle_f_rad);
    double f_y = module_f * cos(angle_f_rad);
    force f = {f_x, f_y};
    return f;
}

force gravity_force()
{
    force f = {0, g * m};
    return f;
}

void update_velocity(force f)
{
    v_x += f.X / m / FPS;
    v_y += f.Y / m / FPS;
}

void update_position()
{
    x += v_x / FPS;
    y += v_y / FPS;
}

void update()
{
    force elastic_f = elastic_force(x, y);
    force gravity_f = gravity_force();
    update_velocity(elastic_f);
    update_velocity(gravity_f);
    update_position();
}

void setup()
{
    // x = 2;
    // y = 2;
    v_x = 0;
    v_y = 0;
    // m = 1;
    // l = 1;
    // k = 1;
    FPS = 100;
    g = 9.8;
    // how_many_seconds = 100;
}

void config(const string& filename)
{
    ifstream config;
    config.open(filename);
    config
    >> x
    >> y
    >> m
    >> k
    >> l
    >> how_many_seconds;
    config.close();
}

int main() {
    setup();
    config_name = "config.txt";
    config(config_name);

    ofstream coords;
    coords.open("trajectory.txt");
    coords.clear();

    ofstream x_t;
    x_t.open("x_t.txt");
    x_t.clear();

    int dt = 0;
    while (dt++ < how_many_seconds * FPS)
    {
        update();
        coords << x << " " << y << "\n";
        x_t << (double) dt / FPS << " " << x << "\n";
    }
    x_t.close();
    coords.close();
}

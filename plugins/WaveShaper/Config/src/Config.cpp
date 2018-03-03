#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

#include "Color.hpp"
#include "INIReader.h"
#include "StringManipulation.hpp"

START_NAMESPACE_DISTRHO

namespace WaveShaperConfig
{

enum ColorType
{
    kColorTypeRGB = 3,
    kColorTypeRGBA = 4,
    kColorTypeHSL = 3,
    kColorTypeHSLA = 4
};

bool isLoaded = false;

Color grid_foreground = Color(103, 98, 102, 255);
Color grid_background = Color(25, 24, 26, 255);
Color sub_grid = Color(27, 27, 27, 255);
Color graph_background = Color(40, 40, 47, 255);
Color in_out_labels = Color(255, 255, 255, 125);

Color alignment_lines = Color(255, 255, 255, 180);
Color input_volume_indicator = Color(255, 255, 255, 180);

Color graph_edges_background_normal = Color(169, 29, 239, 100);
Color graph_edges_background_focused = Color(255, 255, 0, 100);

Color graph_edges_foreground_normal = Color(245, 112, 188, 255);
Color graph_edges_foreground_focused = Color(255, 255, 0, 255);

Color vertex_fill_normal = Color(255, 255, 255, 255);
Color vertex_fill_focused = Color(0, 0, 0, 255);
Color vertex_halo = Color(0, 0, 0, 255);

Color vertex_stroke_normal = Color(0, 0, 0, 255);
Color vertex_stroke_focused = Color(0, 0, 0, 255);

Color tension_handle_normal = Color(228, 104, 181, 255);
Color tension_handle_focused = Color(228, 228, 181, 255);

Color plugin_background = Color(37, 38, 46, 255);
Color graph_margin = Color(33, 32, 39, 255);
Color top_border = Color(0, 0, 0, 255);
Color side_borders = Color(100, 100, 100, 255);

/**
 * Convert a string containing color values to a Color struct.
 * Supported formats: rgb(rgb), rgba(r,g,b,a), hsl(h,s,l), hsla(h,s,l,a)
 */
static void colorFromString(std::string colorStr, Color *targetColor)
{
    if (colorStr == "")
    {
        fprintf(stderr, "Key not loaded: %s\n", colorStr.c_str());
        return;
    }

    const char *str = colorStr.c_str();
    char const *rest;

    std::string colorTypeString = spoonie::takeUntil(str, '(');
    ColorType colorType;

    unsigned char x, y, z;
    unsigned char a = 255;
    int scanStatus;

    if (colorTypeString == "rgb")
    {
        scanStatus = sscanf(str, " rgb ( %hhu , %hhu , %hhu ) ", &x, &y, &z);
        colorType = kColorTypeRGB;
    }
    else if (colorTypeString == "hsl")
    {
        scanStatus = sscanf(str, " hsl ( %hhu , %hhu , %hhu ) ", &x, &y, &z);
        colorType = kColorTypeHSL;
    }
    else if (colorTypeString == "rgba")
    {
        scanStatus = sscanf(str, " rgba ( %hhu , %hhu , %hhu , %hhu ) ", &x, &y, &z, &a);
        colorType = kColorTypeRGBA;
    }
    else if (colorTypeString == "hsla")
    {
        scanStatus = sscanf(str, " hsla ( %hhu , %hhu , %hhu , %hhu ) ", &x, &y, &z, &a);
        colorType = kColorTypeHSLA;
    }
    else
    {
        fprintf(stderr, "spoonie-waveshaper: Warning! Invalid color type in config file: %s.\n", colorStr.c_str());

        return;
    }

    if (scanStatus == colorType)
    {
        if (colorType == kColorTypeRGB || colorType == kColorTypeRGBA)
            *targetColor = Color(x, y, z, a);
        else
            *targetColor = Color::fromHSL(x, y, z, a / 255.f);
    }
    else
    {
        fprintf(stderr, "spoonie-waveshaper: Warning! Color has an invalid number of arguments: %s.\n", colorStr.c_str());
    }

    return;
}

void load()
{
    const char *homeDirectory;

    if ((homeDirectory = getenv("HOME")) == NULL)
    {
        homeDirectory = getpwuid(getuid())->pw_dir;
    }

    const std::string pathToConfig = std::string(homeDirectory) + "/.config/spoonie-waveshaper.conf";

    std::cout << pathToConfig << "\n";
    INIReader reader(pathToConfig);

    if (reader.ParseError() < 0)
    {
        std::cout << "Can't load 'spoonie-waveshaper.conf', using defaults\n";
        return;
    }

    colorFromString(reader.Get("colors", "grid_foreground", ""), &grid_foreground);
    colorFromString(reader.Get("colors", "grid_background", ""), &grid_background);
    colorFromString(reader.Get("colors", "sub_grid", ""), &sub_grid);
    colorFromString(reader.Get("colors", "graph_background", ""), &graph_background);
    colorFromString(reader.Get("colors", "in_out_labels", ""), &in_out_labels);
    colorFromString(reader.Get("colors", "alignment_lines", ""), &alignment_lines);
    colorFromString(reader.Get("colors", "input_volume_indicator", ""), &input_volume_indicator);
    colorFromString(reader.Get("colors", "graph_edges_background_normal", ""), &graph_edges_background_normal);
    colorFromString(reader.Get("colors", "graph_edges_background_focused", ""), &graph_edges_background_focused);
    colorFromString(reader.Get("colors", "graph_edges_foreground_normal", ""), &graph_edges_foreground_normal);
    colorFromString(reader.Get("colors", "graph_edges_foreground_focused", ""), &graph_edges_foreground_focused);
    colorFromString(reader.Get("colors", "vertex_fill_normal", ""), &vertex_fill_normal);
    colorFromString(reader.Get("colors", "vertex_fill_focused", ""), &vertex_fill_focused);
    colorFromString(reader.Get("colors", "vertex_halo", ""), &vertex_halo);
    colorFromString(reader.Get("colors", "vertex_stroke_normal", ""), &vertex_stroke_normal);
    colorFromString(reader.Get("colors", "vertex_stroke_focused", ""), &vertex_stroke_focused);
    colorFromString(reader.Get("colors", "tension_handle_normal", ""), &tension_handle_normal);
    colorFromString(reader.Get("colors", "tension_handle_focused", ""), &tension_handle_focused);
    colorFromString(reader.Get("colors", "plugin_background", ""), &plugin_background);
    colorFromString(reader.Get("colors", "graph_margin", ""), &graph_margin);
    colorFromString(reader.Get("colors", "top_border", ""), &top_border);
    colorFromString(reader.Get("colors", "side_borders", ""), &side_borders);

    isLoaded = true;
    std::cout << "Config loaded from 'spoonie-waveshaper.conf'\n";
}
}

END_NAMESPACE_DISTRHO
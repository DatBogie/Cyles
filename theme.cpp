#include "theme.h"

Theme::Theme() {}

Theme::Theme(QString name, bool dark, std::vector<QColor> colors) {
    Name = name;
    IsDark = dark;
    ButtonColor = colors[0];
    TextInputColor = colors[1];
    BackgroundColor = colors[2];
    AccentColor = colors[3];
}

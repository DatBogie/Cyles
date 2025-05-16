// #include "themebuilder.h"
// #include "cylesutils.h"
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QLineEdit>
// #include <QPushButton>
// #include <QComboBox>
// #include <QCheckBox>
// #include <QJsonObject>
// #include <QString>
// #include <QColorDialog>
// #include <QTextEdit>
// #include <QMap>

// ThemeBuilder::ThemeBuilder(QJsonObject* theme)
// {
//     setAttribute(Qt::WA_DeleteOnClose);
//     setFixedSize(400,300);

//     setWindowFlag(Qt::WindowType::WindowStaysOnTopHint, true);
//     setWindowFlag(Qt::WindowType::WindowMinimizeButtonHint, false);

//     show();

//     QVBoxLayout* mainLay = new QVBoxLayout();
//     setLayout(mainLay);

//     nameField->setPlaceholderText("Name...");
//     mainLay->addWidget(nameField);

//     darkField->setToolTip("If true, uses white icons.");
//     mainLay->addWidget(darkField);

//     QHBoxLayout* btnLay = new QHBoxLayout();
//     mainLay->addLayout(btnLay);
//     btnLay->addWidget(pickButtonColor);
//     btnLay->addWidget(pickTextInputColor);
//     btnLay->addWidget(pickBackgroundColor);
//     btnLay->addWidget(pickAccentColor);

//     if (theme) {
//         nameField->setText(theme->value("Name").toString());
//         nameField->setDisabled(true);
//         darkField->setChecked(theme->value("Dark").toBool());
//     }
//     connect(pickButtonColor, &QPushButton::clicked, this,[this](void){ updateColor(0); });
//     connect(pickTextInputColor, &QPushButton::clicked, this,[this](void){ updateColor(1); });
//     connect(pickBackgroundColor, &QPushButton::clicked, this,[this](void){ updateColor(2); });
//     connect(pickAccentColor, &QPushButton::clicked, this,[this](void){ updateColor(3); });

//     QHBoxLayout* botBar = new QHBoxLayout();
//     mainLay->addLayout(botBar);

//     QPushButton* create = new QPushButton("Create");
//     botBar->addWidget(create);
//     connect(create,&QPushButton::clicked,this,&ThemeBuilder::Complete);
// }

// void ThemeBuilder::updateColor(int key) {
//     QColor clr = QColorDialog::getColor(nullptr,this,"Theme Builder");
//     if (clr == nullptr) return;
//     *colors[key] = clr;
// }

// void ThemeBuilder::Complete() {
//     Theme theme = Theme(
//         nameField->text(),
//         darkField->isChecked(),
//         std::vector<QColor>{buttonColor,textInputColor,backgroundColor,accentColor}
//     );
//     emit completed(theme);
//     emit CylesUtils::Signals->ThemesUpdated();
//     close();
// }

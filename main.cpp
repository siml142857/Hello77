#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    std::vector< ButtonKb> keys ={
        // function keys 13
        ButtonKb("ESC",uint8_t(KeyUsageID::ESC), 40, 30, 51, 51,1 ),
        ButtonKb("F1", uint8_t(KeyUsageID::F1), 160, 30, 51, 51, 1),
        ButtonKb("F2", uint8_t(KeyUsageID::F2), 220, 30, 51, 51, 1),
        ButtonKb("F3", uint8_t(KeyUsageID::F3), 280, 30, 51, 51, 1),
        ButtonKb("F4", uint8_t(KeyUsageID::F4), 340, 30, 51, 51, 1 ),
        ButtonKb("F5", uint8_t(KeyUsageID::F5), 430, 30, 51, 51, 1),
        ButtonKb("F6", uint8_t(KeyUsageID::F6), 490, 30, 51, 51, 1 ),
        ButtonKb("F7", uint8_t(KeyUsageID::F7), 550, 30, 51, 51, 1 ),
        ButtonKb("F8", uint8_t(KeyUsageID::F8), 610, 30, 51, 51, 1 ),
        ButtonKb("F9", uint8_t(KeyUsageID::F9), 700, 30, 51, 51, 1),
        ButtonKb("F10",uint8_t(KeyUsageID::F10), 760, 30, 51, 51, 1 ),
        ButtonKb("F11",uint8_t(KeyUsageID::F11), 820, 30, 51, 51, 1 ),
        ButtonKb("F12",uint8_t(KeyUsageID::F12), 880, 30, 51, 51, 1 ),

        // character_A-Z keys 26
        ButtonKb("A", uint8_t(KeyUsageID::A), 150, 210, 51, 51 ),
        ButtonKb("B", uint8_t(KeyUsageID::B), 410, 270, 51, 51 ),
        ButtonKb("C", uint8_t(KeyUsageID::C), 290, 270, 51, 51 ),
        ButtonKb("D", uint8_t(KeyUsageID::D), 270, 210, 51, 51 ),
        ButtonKb("E", uint8_t(KeyUsageID::E), 250, 150, 51, 51 ),
        ButtonKb("F", uint8_t(KeyUsageID::F), 330, 210, 51, 51 ),
        ButtonKb("G", uint8_t(KeyUsageID::G), 390, 210, 51, 51 ),
        ButtonKb("H", uint8_t(KeyUsageID::H), 450, 210, 51, 51),
        ButtonKb("I", uint8_t(KeyUsageID::I), 550, 150, 51, 51 ),
        ButtonKb("J", uint8_t(KeyUsageID::J), 510, 210, 51, 51 ),
        ButtonKb("K", uint8_t(KeyUsageID::K), 570, 210, 51, 51 ),
        ButtonKb("L", uint8_t(KeyUsageID::L), 630, 210, 51, 51 ),
        ButtonKb("M", uint8_t(KeyUsageID::M), 530, 270, 51, 51 ),
        ButtonKb("N", uint8_t(KeyUsageID::N), 470, 270, 51, 51 ),
        ButtonKb("O", uint8_t(KeyUsageID::O), 610, 150, 51, 51 ),
        ButtonKb("P", uint8_t(KeyUsageID::P), 670, 150, 51, 51 ),
        ButtonKb("Q", uint8_t(KeyUsageID::Q), 130, 150, 51, 51 ),
        ButtonKb("R", uint8_t(KeyUsageID::R), 310, 150, 51, 51 ),
        ButtonKb("S", uint8_t(KeyUsageID::S), 210, 210, 51, 51 ),
        ButtonKb("T", uint8_t(KeyUsageID::T), 370, 150, 51, 51 ),
        ButtonKb("U", uint8_t(KeyUsageID::U), 490, 150, 51, 51 ),
        ButtonKb("V", uint8_t(KeyUsageID::V), 350, 270, 51, 51 ),
        ButtonKb("W", uint8_t(KeyUsageID::W), 190, 150, 51, 51 ),
        ButtonKb("X", uint8_t(KeyUsageID::X), 230, 270, 51, 51 ),
        ButtonKb("Y", uint8_t(KeyUsageID::Y), 430, 150, 51, 51 ),
        ButtonKb("Z", uint8_t(KeyUsageID::Z), 170, 270, 51, 51 ),

        // character_0-9 keys 10
        ButtonKb("1", uint8_t(KeyUsageID::NUM_1), 100, 90, 51, 51 ),
        ButtonKb("2", uint8_t(KeyUsageID::NUM_2), 160, 90, 51, 51 ),
        ButtonKb("3", uint8_t(KeyUsageID::NUM_3), 220, 90, 51, 51 ),
        ButtonKb("4", uint8_t(KeyUsageID::NUM_4), 280, 90, 51, 51 ),
        ButtonKb("5", uint8_t(KeyUsageID::NUM_5), 340, 90, 51, 51 ),
        ButtonKb("6", uint8_t(KeyUsageID::NUM_6), 400, 90, 51, 51 ),
        ButtonKb("7", uint8_t(KeyUsageID::NUM_7), 460, 90, 51, 51 ),
        ButtonKb("8", uint8_t(KeyUsageID::NUM_8), 520, 90, 51, 51 ),
        ButtonKb("9", uint8_t(KeyUsageID::NUM_9), 580, 90, 51, 51 ),
        ButtonKb("0", uint8_t(KeyUsageID::NUM_0), 640, 90, 51, 51 ),
        // character11 keys 11
        ButtonKb("-_", uint8_t(KeyUsageID::MINUS), 700, 90, 51, 51 ),
        ButtonKb("+=", uint8_t(KeyUsageID::EQUAL), 760, 90, 51, 51 ),
        ButtonKb("{[", uint8_t(KeyUsageID::LEFT_U_BRACE), 730, 150, 51, 51 ),
        ButtonKb("]}", uint8_t(KeyUsageID::RIGHT_U_BRACE), 790, 150, 51, 51 ),
        ButtonKb("| \\", uint8_t(KeyUsageID::BACKSLASH), 850, 150, 81, 51 ),
        ButtonKb(":;", uint8_t(KeyUsageID::SEMI_COLON), 690, 210, 51, 51 ),
        ButtonKb("\" '", uint8_t(KeyUsageID::QUOTE), 750, 210, 51, 51 ),
        ButtonKb("~`", uint8_t(KeyUsageID::GRAVE_ACCENT), 40, 90, 51, 51 ),
        ButtonKb("< ,", uint8_t(KeyUsageID::COMMA), 590, 270, 51, 51 ),
        ButtonKb("> .", uint8_t(KeyUsageID::PERIOD), 650, 270, 51, 51 ),
        ButtonKb("? /", uint8_t(KeyUsageID::SLASH), 710, 270, 51, 51 ),
        // control1  13+1 = 14
        ButtonKb("Enter", uint8_t(KeyUsageID::ENTER), 810, 210, 121, 51, 2 ),
        ButtonKb("BackSpace", uint8_t(KeyUsageID::BACKSPACE), 820, 90, 111, 51, 2 ),
        ButtonKb("Tab", uint8_t(KeyUsageID::TAB), 40, 150, 81, 51, 2 ),
        ButtonKb("SpaceBar", uint8_t(KeyUsageID::SPACE), 280, 330, 341, 51, 2 ),
        ButtonKb("Caps", uint8_t(KeyUsageID::CAP_LOCK), 40, 210, 101, 51, 2 ),

        ButtonKb("lCtrl", uint8_t(KeyUsageID::LEFT_CTRL), 40, 330, 71, 51, 2 ),
        ButtonKb("lShift",uint8_t(KeyUsageID::LEFT_SHIFT), 40, 270, 121, 51, 2 ),
        ButtonKb("lAlt", uint8_t(KeyUsageID::LEFT_ALT), 200, 330, 71, 51, 2 ),
        ButtonKb("lWin", uint8_t(KeyUsageID::LEFT_GUI), 120, 330, 71, 51, 2 ),
        ButtonKb("rCtrl",uint8_t(KeyUsageID::RIGHT_CTRL), 750, 330, 51, 51, 2 ),
        ButtonKb("rShift",uint8_t(KeyUsageID::RIGHT_SHIFT), 770, 270, 101, 51, 2 ),
        ButtonKb("rAlt", uint8_t(KeyUsageID::RIGHT_ALT), 630, 330, 51, 51, 2 ),
        ButtonKb("rWin", uint8_t(KeyUsageID::RIGHT_GUI), 1020, 90, 51, 51, 3 ),  //

        ButtonKb("Fn", KeyUsageID::FN, 690, 330, 51, 51, 2 ),

        // control2 keys  9 + 4 = 13
        ButtonKb("PrtSc", uint8_t(KeyUsageID::PRINT), 1020, 150, 51, 51, 3 ),   //
        ButtonKb("ScrLock", uint8_t(KeyUsageID::SCROLL_LOCK), 1020, 210, 51, 51, 3),  //
        ButtonKb("Pause", uint8_t(KeyUsageID::PAUSE), 1020, 270, 51, 51, 3 ),  //
        ButtonKb("Insert", uint8_t(KeyUsageID::INSERT), 940, 90, 51, 51, 2 ),
        ButtonKb("Home", uint8_t(KeyUsageID::HOME), 940, 30, 51, 51, 1),
        ButtonKb("PgUp", uint8_t(KeyUsageID::PAGE_UP), 940, 210, 51, 51, 2 ),
        ButtonKb("Del", uint8_t(KeyUsageID::DELETE), 940, 150, 51, 51, 2 ),
        ButtonKb("End", uint8_t(KeyUsageID::END), 1020, 330, 51, 51, 3 ),    //
        ButtonKb("PgDn", uint8_t(KeyUsageID::PAGE_DOWN), 940, 270, 51, 51, 2 ),
        ButtonKb("Right", uint8_t(KeyUsageID::RIGHT_ARROW), 940, 330, 51, 51 ),
        ButtonKb("Left", uint8_t(KeyUsageID::LEFT_ARROW), 820, 330, 51, 51 ),
        ButtonKb("Down", uint8_t(KeyUsageID::DOWN_ARROW), 880, 330, 51, 51 ),
        ButtonKb("Up", uint8_t(KeyUsageID::UP_ARROW), 880, 270, 51, 51),

    };
    std::vector< ButtonKb> func_buttons ={
        ButtonKb("RESET", RESET, 1020, 30, 51, 51, 4),
        ButtonKb("LOAD", EXPORT_TO_KB, 1085, 30, 94, 51, 4),
    };
    std::vector< ButtonKb> all_keys;
    all_keys.insert(all_keys.end(), func_buttons.begin(), func_buttons.end());
    all_keys.insert(all_keys.end(), keys.begin(), keys.end());

    QApplication a(argc, argv);
    MainWindow w;
    w.setAllKeys(all_keys);
    w.displayWindow();
    w.show();
    return a.exec();
}

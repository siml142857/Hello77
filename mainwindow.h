#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <exception>
#include <queue>
#include <unordered_set>
#include <map>
#include <set>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <unordered_map>
#include <limits>
#include <stack>
#include <math.h>
#include <memory>
#include <QComboBox>
#include <QTextBrowser>
#include <QTimer>
#include "usb_con.hpp"

struct ButtonKb;

enum KeyUsageID : uint8_t
{
    /*------------------------- HID report data -------------------------*/

    RESERVED = 0,ERROR_ROLL_OVER,POST_FAIL,ERROR_UNDEFINED,
    A,B,C,D,E,F,G,H,I,J,K,L,M,
    N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
    NUM_1/*1!*/,NUM_2/*2@*/,NUM_3/*3#*/,NUM_4/*4$*/,NUM_5/*5%*/,
    NUM_6/*6^*/,NUM_7/*7&*/,NUM_8/*8**/,NUM_9/*9(*/,NUM_0/*0)*/,
    ENTER,ESC,BACKSPACE,TAB,SPACE,
    MINUS/*-_*/,EQUAL/*=+*/,LEFT_U_BRACE/*[{*/,RIGHT_U_BRACE/*]}*/,
    BACKSLASH/*\|*/,NONE_US/**/,SEMI_COLON/*;:*/,QUOTE/*'"*/,
    GRAVE_ACCENT/*`~*/,COMMA/*,<*/,PERIOD/*.>*/,SLASH/*/?*/,
    CAP_LOCK,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
    PRINT,SCROLL_LOCK,PAUSE,INSERT,HOME,PAGE_UP,DELETE,END,PAGE_DOWN,
    RIGHT_ARROW,LEFT_ARROW,DOWN_ARROW,UP_ARROW,PAD_NUM_LOCK,
    PAD_SLASH,PAD_ASTERISK,PAD_MINUS,PAD_PLUS,PAD_ENTER,
    PAD_NUM_1,PAD_NUM_2,PAD_NUM_3,PAD_NUM_4,PAD_NUM_5,
    PAD_NUM_6,PAD_NUM_7,PAD_NUM_8,PAD_NUM_9,PAD_NUM_0,
    PAD_PERIOD , NONUS_BACKSLASH,APPLICATION,POWER,PAD_EQUAL,
    F13,F14,F15,F16,F17,F18,F19,F20,F21,F22,F23,F24, EXECUTE,
    HELP,MENU,SELECT,STOP,AGAIN,UNDO,CUT,COPY,PASTE,FIND,MUTE,VOLUME_UP,VOLUME_DOWN,
    LEFT_CTRL = 224,LEFT_SHIFT = 225,LEFT_ALT = 226,LEFT_GUI = 227,                    // BYTE1 -- 特殊按键,不需要关注usage_id 224-231
    RIGHT_CTRL = 228,RIGHT_SHIFT = 229,RIGHT_ALT = 230,RIGHT_GUI = 231,
    FN = 250
    /*------------------------- HID report data -------------------------*/
};

enum ButtonId: uint8_t {
    RESET = 251,
    EXPORT_TO_KB = 252,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setAllKeys( const std::vector<ButtonKb>& keys );

    void setKeysTable(const std::map<uint8_t, std::string> key_id2name );

    void displayWindow();

private:
    std::map<uint8_t, ButtonKb> keys_;
    std::map<uint8_t, std::string> key_id2name_;
    std::map<uint8_t, QPushButton*> buttons_ptr_;
    std::map<uint8_t, uint8_t> key_id_to_loc_;
    std::vector<uint8_t> key_loc_to_id_remap_;
    std::vector<uint8_t> key_remap_list_;
    std::pair<uint8_t, uint8_t> remap_one_key_ = {0, 0};   // first 0: 1:
    int key_click_count_ =0;
    QTimer* timer_;

    QComboBox* combox_function_item_;
    QTextBrowser* text_window_;
    UsbCon usb_con_;

    std::map<uint8_t, std::string> key_style_ ={
        {0, "background-color: rgb(176,224,230);color: rgb(8,46,84);"} ,
        {1, "background-color:#5F9EA0;color: rgb(8,46,84);"},
        {2, "background-color:#A39480;color: rgb(8,46,84);"},
        {3, "background-color:#2F4F4F;color: rgb(0,0,0);"},
        {4, "background-color:#CD5C5C;color: rgb(255,255,255);"},
        {10, "background-color: rgb(176,224,230);color:#8B2323;"} ,
        {11, "background-color:#5F9EA0;color: #8B2323;"},
        {12, "background-color:#A39480;color: #8B2323;"},
        {20, "background-color:#CDC673;color: #8B2323;"},
    };

    std::pair<int, int> keys_offset_ ={-20,0};

    void onKeyClick(uint8_t key_id);

    void onTimerEvent();

    void keyMapReset();

    void reset();

    void buildKeyId2Loc();

    uint8_t getLocById(uint8_t id);

    uint8_t getIdByLoc(uint8_t loc);

    void onLoadKeyClick();

    std::set<uint8_t> additional_keys_ = {  uint8_t(RIGHT_GUI),  uint8_t(PRINT), uint8_t(SCROLL_LOCK),  uint8_t(PAUSE),  uint8_t(END) };

    std::vector<uint8_t> key_loc_to_id_= {ESC,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,PAUSE,
         GRAVE_ACCENT,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9,NUM_0,MINUS,EQUAL,BACKSPACE,INSERT,
         TAB,Q,W,E,R,T,Y,U,I,O,P,LEFT_U_BRACE,RIGHT_U_BRACE,BACKSLASH,DELETE,
         CAP_LOCK,A,S,D,F,G,H,J,K,L,SEMI_COLON,QUOTE,ENTER,PAGE_UP,
         LEFT_SHIFT,Z,X,C,V,B,N,M,COMMA,PERIOD,SLASH,RIGHT_SHIFT,UP_ARROW,PAGE_DOWN,
         LEFT_CTRL,LEFT_GUI,LEFT_ALT,SPACE,RIGHT_ALT,FN,RIGHT_CTRL,LEFT_ARROW,DOWN_ARROW,RIGHT_ARROW };    // 82 keys



};


struct ButtonKb {
    std::string name;
    uint8_t id;
    int coord_x;
    int coord_y;
    int size_width;
    int size_hight;
    int color;

    ButtonKb(const std::string& _name, uint8_t _id, int x, int y,int w = 60, int h = 60, int _color = 0 ):
        name(_name), id(_id), coord_x(x), coord_y(y), size_hight(h), size_width(w), color(_color) {}
};


#endif // MAINWINDOW_H

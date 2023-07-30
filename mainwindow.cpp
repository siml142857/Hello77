#include "mainwindow.h"
#include <QPushButton>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    buildKeyId2Loc();
    timer_ = new QTimer(this);
    timer_->start(1000);
    connect(timer_,&QTimer::timeout,this, &::MainWindow::onTimerEvent );
    usb_con_.setTargetDevice(0x1001, 0x03ef);

}

MainWindow::~MainWindow()
{
}

void MainWindow::setAllKeys( const std::vector<ButtonKb>& keys ){
    for( auto &k: keys ){
        keys_.insert( std::make_pair( k.id, k) );
    }
}

void MainWindow::setKeysTable(const std::map<uint8_t, std::string> key_id2name ){
    key_id2name_ = key_id2name;
}

void MainWindow::onKeyClick( uint8_t key_id ) {
    auto ik =  keys_.find( key_id );
    ButtonKb &k_pty = ik->second;
    if( key_id == RESET ) {
        reset();
    } else if( key_id == EXPORT_TO_KB ){
        onLoadKeyClick();
    } else {
        bool addi_not_click = additional_keys_.find(key_id) ==additional_keys_.end();
        if( remap_one_key_.first == 0 ){
            if( addi_not_click  ){
                remap_one_key_ = {1, key_id};
                buttons_ptr_[key_id]->setText(  QString::fromStdString(k_pty.name));//显示文本
                buttons_ptr_[key_id]->setStyleSheet( key_style_[20].c_str() );
            }
        } else if( remap_one_key_.first == 1 ){
            //
            remap_one_key_.first = 0;
            uint8_t modify_k = remap_one_key_.second;
            if( modify_k == key_id ){
                buttons_ptr_[modify_k]->setStyleSheet( key_style_[k_pty.color].c_str() );   // color recover
            } else{
                auto ik2 =  keys_.find( modify_k );
                ButtonKb &k_pty2 = ik2->second;
                buttons_ptr_[modify_k]->setStyleSheet( key_style_[k_pty2.color+10].c_str() );   // color set
                buttons_ptr_[modify_k]->setText(  QString::fromStdString(k_pty2.name)+ "\n"+ QString::fromStdString(k_pty.name));//显示文本
                //
                uint8_t lo = getLocById( modify_k );
                key_loc_to_id_remap_[lo] = key_id;
                //
                key_remap_list_.push_back(modify_k);
                std::string msg = "Idx["+ std::to_string(lo) + "]=>"+keys_.at(key_id).name.c_str();
                text_window_->append( msg.c_str() );
                //qDebug("DD03 remap(%d %d) pre(%d) modify-size=%ld ",lo,  key_id, modify_k,key_remap_list_.size() );
            }

        }
    }
}

void MainWindow::onLoadKeyClick(){
    bool w=false;
    bool r= usb_con_.hidOpen();
    if( r ){
        std::vector<uint8_t> data = { 0x77, 0xF1, 0xFF, 0xA5,0xA5,0xA5,0xA5,0xA5  };
        data.insert(data.end(), key_loc_to_id_remap_.begin(), key_loc_to_id_remap_.end()  );
        data.push_back( combox_function_item_->currentIndex() );
        w = usb_con_.hidWrite(data);
    }
    if(w){
        text_window_->append( "KeyMap write success !!! " );
    } else{
        text_window_->append( "KeyMap write failed !!! " );
    }
    usb_con_.close();
}

void MainWindow::displayWindow(){

    setFixedSize(1280,420);//设置固定窗口大小
    setWindowTitle("HELLO77");//设置窗口标题

    for( auto &p: keys_ ){
        QPushButton* k = new QPushButton;
        buttons_ptr_.insert( std::make_pair(p.second.id, k) );
        k->setParent(this);//指定QWidget作为btn的父类，其中this是作为QWidget的指针
        k->setText(  QString::fromStdString(p.second.name));//显示文本
        k->setFixedSize(p.second.size_width, p.second.size_hight);
        k->move(p.second.coord_x+ keys_offset_.first,p.second.coord_y+ keys_offset_.second);//按钮键的移动r
        k->setStyleSheet( key_style_[p.second.color].c_str() );
        connect(k, &QPushButton::clicked, this, [=](){ MainWindow::onKeyClick(p.second.id);});
    }

    text_window_ = new QTextBrowser(this);
    text_window_->setFixedSize(200, 290);
    text_window_->move( 1065, 90 );
    text_window_->setText("Hello world !!!");
    text_window_->document()->setMaximumBlockCount(100);

    combox_function_item_ = new QComboBox(this);
    combox_function_item_->setFixedSize(94,51);
    combox_function_item_->move(1170, 30);
    combox_function_item_->insertItem(0,"LAYER 1");
    combox_function_item_->insertItem(1,"LAYER 2");
    combox_function_item_->insertItem(2,"LAYER 3");
    combox_function_item_->insertItem(3,"LAYER 4");
    combox_function_item_->insertItem(4,"LAYER 5");
    combox_function_item_->setStyleSheet(key_style_[4].c_str());
    int a1 = combox_function_item_->currentIndex();
    QString a2 = combox_function_item_->currentText();
    qDebug("DD05 layer =%d %s ",a1,a2.toStdString().c_str()  );
    reset();
}

void MainWindow::keyMapReset(){
    key_loc_to_id_remap_ = key_loc_to_id_;
}

void MainWindow::reset(){
    key_click_count_ = 0;
    keyMapReset();
    // recover key display
    for( auto &p: keys_ ){
        buttons_ptr_[p.first]->setText(  QString::fromStdString(p.second.name));//显示文本
        buttons_ptr_[p.first]->setStyleSheet( key_style_[p.second.color].c_str() );
    }
    remap_one_key_ = {0,0};

    text_window_->setText("Hello world !!!");
}

void MainWindow::buildKeyId2Loc(){
    int i=0;
    for( auto &k: key_loc_to_id_ ){
        key_id_to_loc_.insert( std::make_pair( k, i++) );
    }
}

uint8_t MainWindow::getLocById(uint8_t id){
    return key_id_to_loc_[id];
}

uint8_t MainWindow::getIdByLoc(uint8_t loc){
    return key_loc_to_id_[loc];
}

void MainWindow::onTimerEvent(){


//    int a1 = combox_function_item_->currentIndex();
//    QString a2 = combox_function_item_->currentText();
//    qDebug("DD07 layer =%d %s ",a1,a2.toStdString().c_str()  );
//    printf("DATA: \n");
//    for( int i=0, s= key_loc_to_id_remap_.size(); i <s ;++i ){
//        printf("{%d %d} ",i, key_loc_to_id_remap_[i]  );
//    }
//    printf("\n");
}

#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <map>
#include <chrono>         // std::chrono::seconds
#include <stack>
#include <math.h>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi/hidapi.h"
#include <chrono>         // std::chrono::seconds
#include <QThread>

class UsbCon {
public:
    UsbCon(){

    }

    ~UsbCon(){
        close();
    }

    void setTargetDevice(uint16_t man, uint16_t pro){
        target_device_pro_ = pro;
        target_device_man_ = man;
    }

    bool hidOpen(){
        handle_ = hid_open(target_device_man_, target_device_pro_, NULL);
        if (!handle_) {
            printf("unable to open device\n");
            hid_exit();
            return false;
        }
        return true;
    }

    bool hidWrite(std::vector<uint8_t>& data ){
        int i=0;
        printf("hidWrite data[%d ] :", data.size());
        for( auto &p: data ){
            buf_send_[i] = p;
            i++;
            printf("%d ",p);
        }
        printf("\n");

        int res= hid_write(handle_, buf_send_, 128);
        if (res < 0) {
            printf("Unable to write(): %ls\n", hid_error(handle_));
            return false;
        }
        return true;
    }

    bool hidRead( std::vector<uint8_t>& data  ){
        data.clear();

        int res = 0;
        int c=0;
        while(res == 0){
            res = hid_read(handle_, buf_rev_, sizeof(buf_rev_));
            if( res ==0 ){
                printf("waiting...\n");
                QThread::msleep(100);
            }
            if( c>= 1 || res< 0 ) break;
            c++;
        }
        if (res < 0) {
            printf("Unable to read(): %ls\n", hid_error(handle_));
        } else if( res>0 ){
            for(int i=0; i<sizeof(buf_rev_);++i ){
                data.push_back( buf_rev_[i] );
            }
            return true;
        }
        return false;
    }

    bool close(){
        hid_close(handle_);
        /* Free static HIDAPI objects. */
        hid_exit();
    }



private:
    unsigned char buf_send_[128];
    unsigned char buf_rev_[128];
    hid_device *handle_;
    struct hid_device_info *devs_;
    uint16_t target_device_man_ = 0;
    uint16_t target_device_pro_ = 0;


    const char *hid_bus_name(hid_bus_type bus_type) {
        static const char *const HidBusTypeName[] = {
            "Unknown",
            "USB",
            "Bluetooth",
            "I2C",
            "SPI",
        };

        if ((int)bus_type < 0)
            bus_type = HID_API_BUS_UNKNOWN;
        if ((int)bus_type >= (int)(sizeof(HidBusTypeName) / sizeof(HidBusTypeName[0])))
            bus_type = HID_API_BUS_UNKNOWN;

        return HidBusTypeName[bus_type];
    }

    void print_device(struct hid_device_info *cur_dev) {
        printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        printf("\n");
        printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        printf("  Product:      %ls\n", cur_dev->product_string);
        printf("  Release:      %hx\n", cur_dev->release_number);
        printf("  Interface:    %d\n",  cur_dev->interface_number);
        printf("  Usage (page): 0x%hx (0x%hx)\n", cur_dev->usage, cur_dev->usage_page);
        printf("  Bus type: %d (%s)\n", cur_dev->bus_type, hid_bus_name(cur_dev->bus_type));
        printf("\n");
    }

    void print_hid_report_descriptor_from_device(hid_device *device) {
        unsigned char descriptor[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
        int res = 0;

        printf("  Report Descriptor: ");
        res = hid_get_report_descriptor(device, descriptor, sizeof(descriptor));
        if (res < 0) {
            printf("error getting: %ls", hid_error(device));
        }
        else {
            printf("(%d bytes)", res);
        }
        for (int i = 0; i < res; i++) {
            if (i % 10 == 0) {
                printf("\n");
            }
            printf("0x%02x, ", descriptor[i]);
        }
        printf("\n");
    }

    void print_hid_report_descriptor_from_path(const char *path) {
        hid_device *device = hid_open_path(path);
        if (device) {
            print_hid_report_descriptor_from_device(device);
            hid_close(device);
        }
        else {
            printf("  Report Descriptor: Unable to open device by path\n");
        }
    }

    void print_devices(struct hid_device_info *cur_dev) {
        for (; cur_dev; cur_dev = cur_dev->next) {
            print_device(cur_dev);
        }
    }

    void print_devices_with_descriptor(struct hid_device_info *cur_dev) {
        for (; cur_dev; cur_dev = cur_dev->next) {
            print_device(cur_dev);
            print_hid_report_descriptor_from_path(cur_dev->path);
        }
    }
};

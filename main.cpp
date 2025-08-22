#include <iostream>
#include "libwdi.h"


int main(){
    constexpr char * DESC = "MD USB-TO-CAN";
    constexpr short  VID = 0x0069;
    constexpr short  PID = 0x1000;

    struct wdi_device_info device = {0};
    struct wdi_device_info* ldev;

    device.desc = DESC;
    device.vid  = VID;
    device.pid  = PID;

    
    constexpr char * DEFAULT_DIR = "driver";
    constexpr char * INF_NAME = "mab_driver.inf";
    constexpr char * CERT_NAME = "MAB_USB_CERT";

    wdi_options_create_list create_list_options = {0};
    create_list_options.list_all = true;
    wdi_options_install_driver install_driver_options = {0};
    wdi_options_prepare_driver prepare_driver_options = {0};

	wdi_set_log_level(WDI_LOG_LEVEL_DEBUG);

    int r = 0;

    // printf("Installing certificate '%s' as a Trusted Publisher...\n", CERT_NAME);
	// static struct wdi_options_install_cert oic = { 0 };
    // r = wdi_install_trusted_certificate(CERT_NAME, &oic);
    // if (r != WDI_SUCCESS) 
    // {
    //     std::cout << "ERROR INSTALLING CERT DRIVER!\n Code: " << r << '\n';
    //     exit(1);
    // }

    r = wdi_prepare_driver(&device, DEFAULT_DIR, INF_NAME, &prepare_driver_options);
    if (r != WDI_SUCCESS) 
    {
        std::cout << "ERROR EXTRACTING DRIVER!\n Code: " << r << '\n';
        exit(1);
    }

    bool matching_device_found = FALSE;
    r = wdi_create_list(&ldev, &create_list_options);
	if (r == WDI_SUCCESS) {
		r = WDI_SUCCESS;
		for (; (ldev != NULL) && (r == WDI_SUCCESS); ldev = ldev->next) {
			if ( (ldev->vid == device.vid) && (ldev->pid == device.pid) ) {
				
				device.hardware_id = ldev->hardware_id;
				device.device_id = ldev->device_id;
				matching_device_found = TRUE;
				printf("  %s: ", device.hardware_id);
				fflush(stdout);
				r = wdi_install_driver(&device, DEFAULT_DIR, INF_NAME, &install_driver_options);
				printf("%s\n", wdi_strerror(r));
			}
		}
	}
    else
    {   std::cout << GetLastError() << '\n';
        std::cout << "ERROR CREATING LIST!\n Code: " << r << '\n';
        exit(1);
    }
                

    return 0;
}
#include "../RESOURCES/ECE497/BoneHeader.h"
#include "../../exercises/i2c/i2c-dev.h"
#include <poll.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

// MiniProject01
// =======

// In this project, I use the gpio interrupt from an external pushbutton to trigger temperature 
// readings off of the TC74 temperature sensor. The temperature in degrees Celcius is output to 
// the terminal.

// At the same time, an analog input is read once a second. The voltage is used to control the 
// PWM duty cycle on an output that goes to LED1. A heartbeat pattern is output on LED0. The 
// program handles the ^C interrupt by printing a shutdown message to the terminal.

// LED0 on GPIO1_16
#define LED0 48
// LED1 on GPIO1_17
#define LED1 49

// Button on GPIO3_19
#define BUTTON 115

// Pot on AIN5

// Temperature sensor on I2C2 (bus 3)
#define I2C_BUS_FILE "/dev/i2c-3"
#define I2C_DEV_ADDRESS 0x4A
#define I2C_REG_ADDRESS 0

int led0_fd, led1_fd, button_fd;
int led0_value = 0;
int led1_value = 0;

//signal handler that breaks program loop and cleans up
void signal_handler(int signo){
	if (signo == SIGINT) {
		printf("\n^C pressed, unexporting gpios and exiting..\n");
		
		gpio_fd_close(led0_fd);
		gpio_fd_close(led1_fd);
		gpio_fd_close(button_fd);
		unexport_gpio(led0_fd);
		unexport_gpio(led1_fd);
		unexport_gpio(button_fd);

		fflush(stdout);

		exit(0);
	}
}

void init(void) {
	//Set LEDs to outputs
	export_gpio(LED0);
	set_gpio_direction(LED0, "out");
	set_gpio_value(LED0, led0_value);
	led0_fd = gpio_fd_open(LED0);
	export_gpio(LED1);
	set_gpio_direction(LED1, "out");
	set_gpio_value(LED1, led1_value);
	led1_fd = gpio_fd_open(LED1);

	//Set button to input
	export_gpio(BUTTON);
	set_gpio_direction(BUTTON, "in");
	set_gpio_edge(BUTTON, "falling");
	button_fd = gpio_fd_open(BUTTON);
}

int getTemp(void) {
	int res, file;

	file = open(I2C_BUS_FILE, O_RDWR);
	if (file<0) {
		if (errno == ENOENT) {
			fprintf(stderr, "Error: Could not open file "
				I2C_BUS_FILE ": %s\n", strerror(ENOENT));
		} else {
			fprintf(stderr, "Error: Could not open file "
				I2C_BUS_FILE ": %s\n", strerror(errno));
			if (errno == EACCES)
				fprintf(stderr, "Run as root?\n");
		}
		return -1;
	}

	if (ioctl(file, I2C_SLAVE, I2C_DEV_ADDRESS) < 0) {
		fprintf(stderr,
			"Error: Could not set address to 0x%02x: %s\n",
			I2C_DEV_ADDRESS, strerror(errno));
		return -1;
	}

	res = i2c_smbus_read_byte_data(file, I2C_REG_ADDRESS);
	close(file);

	if (res < 0) {
		fprintf(stderr, "Error: Read failed, res=%d\n", res);
		return -1;
	}
	return res;
}

int main(int argc, char** argv){
	//variable declarations
	struct pollfd fdset[1];
	int nfds = 1;
	int timeout = 3000;
	int rc;
	char buf[MAX_BUF];

	init();

	//set signal handler
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		printf("\ncan't catch SIGINT\n");

	while (1) {
		memset((void*)fdset, 0, sizeof(fdset));
	
		fdset[0].fd = button_fd;
		fdset[0].events = POLLPRI;

		rc = poll(fdset, nfds, timeout);

		if (rc < 0){
			printf("\npoll() failed!\n");
			break;
		}
	
		if (rc == 0){
			printf(".");
		}

		if((fdset[0].revents & POLLPRI) == POLLPRI) {
 			if (read(fdset[0].fd, (void *)buf, MAX_BUF) > 0) {
				printf("interrupt value=%s\n", buf);
			}
			led0_value = led0_value^1;
			led1_value = led0_value^1;
			set_gpio_value(LED0, led0_value);
			set_gpio_value(LED1, led1_value);
			printf("led0_value  = %d\n", led0_value);
			printf("led1_value  = %d\n", led1_value);
		}			
		
	}

	return -1;
}

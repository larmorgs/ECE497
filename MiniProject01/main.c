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
// the terminal. LED0 also toggles when the button is pressed.

// At the same time, an analog input is read ten times a second. The voltage is used to control 
// the PWM duty cycle on an output that goes to LED1. The program handles the ^C interrupt by
// printing a shutdown message to the terminal.

// LED0 on GPIO1_16
#define LED0 48
// LED1 on ehrpwm1A
#define LED1_MUX "gpmc_a2"
#define LED1_MUX_VAL 6
#define LED1_PWM "ehrpwm.1\:0"

// Button on GPIO3_19
#define BUTTON 115

// Pot on AIN5 (ain6)
#define POT "ain6"

// Temperature sensor on I2C2 (bus 3)
#define I2C_BUS_FILE "/dev/i2c-3"
#define I2C_DEV_ADDRESS 0x4B
#define I2C_REG_ADDRESS 0

#define TIMEOUT 100

int led0_fd, led1_fd, button_fd;
int led0_value = 1;
int led1_value = 1;

//signal handler that breaks program loop and cleans up
void signal_handler(int signo){
	if (signo == SIGINT) {
		printf("\n^C pressed, unexporting gpios and exiting..\n");
		
		gpio_fd_close(led0_fd);
		gpio_fd_close(led1_fd);
		gpio_fd_close(button_fd);
		unexport_gpio(LED0);
		unexport_gpio(BUTTON);

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

	set_mux_value(LED1_MUX, LED1_MUX_VAL);
	set_pwm(LED1_PWM, 10, read_ain(POT)/41);

	//Set button to input
	export_gpio(BUTTON);
	set_gpio_direction(BUTTON, "in");
	set_gpio_edge(BUTTON, "rising");
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
		exit(-1);
	}

	if (ioctl(file, I2C_SLAVE, I2C_DEV_ADDRESS) < 0) {
		fprintf(stderr,
			"Error: Could not set address to 0x%02x: %s\n",
			I2C_DEV_ADDRESS, strerror(errno));
		exit(-2);
	}

	res = i2c_smbus_read_byte_data(file, I2C_REG_ADDRESS);
	close(file);

	if (res < 0) {
		fprintf(stderr, "Error: Read failed, res=%d\n", res);
		exit(-3);
	}
	return res;
}

int main(int argc, char** argv){
	//variable declarations
	struct pollfd fdset[1];
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

		rc = poll(fdset, POLLIN, TIMEOUT);

		if (rc < 0){
			printf("\npoll() failed!\n");
			break;
		}
	
		if (rc == 0){
			set_pwm(LED1_PWM, 10, read_ain(POT)/41);
			fflush(stdout);
		}

		if((fdset[0].revents & POLLPRI) == POLLPRI) {
			read(fdset[0].fd, (void *)buf, MAX_BUF);
			printf("\nCurrent Temperature = %d degrees C", getTemp());
			led0_value = led0_value^1;
			set_gpio_value(LED0, led0_value);
		}			
		
	}

	return -1;
}

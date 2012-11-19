#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#define STX 0x02
#define ETX 0x03
#define DC1 0x11

int fd;

//Initialize serial port
int init_port()
{
    int portstatus = 0;

    struct termios options;
    // Get the current options for the port...
    tcgetattr(fd, &options);
    // Set the baud rates to 9600...'textB' un
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    // Enable the receiver and setSTX local mode...
    options.c_cflag |= (CLOCAL | CREAD);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    //options.c_cflag |= SerialDataBitsInterp(8);           /* CS8 - Selects 8 data bits */
    options.c_cflag &= ~CRTSCTS;                            // disable hardware flow control
    options.c_iflag &= ~(IXON | IXOFF | IXANY);           // disable XON XOFF (for transmit and receive)
    //options.c_cflag |= CRTSCTS;                     /* enable hardware flow control */


    options.c_cc[VMIN] = 0;     //min carachters to be read
    options.c_cc[VTIME] = 0;    //Time to wait for data (tenths of seconds)


    // Set the new options for the port...
    //tcsetattr(fd, TCSANOW, &options);


    //Set the new options for the port...
    tcflush(fd, TCIFLUSH);
    if (tcsetattr(fd, TCSANOW, &options)==-1)
    {
        perror("On tcsetattr:");
        portstatus = -1;
    }
    else
        portstatus = 1;

    return portstatus;
}


/*
* send command to reciver
*/
void send_cmd(char *n) {
    int len = strlen(n);

    // create command
    char cmd[len + 2];
    cmd[0]=STX;
    cmd[len + 1]=ETX;

    // copy string to char array
    int i;
    for (i = 0; i < strlen(n); i++) {
        cmd[i + 1] = n[i];
    }

/*
    // debug
    printf("CMD:");
    for (i = 0; i < sizeof(cmd); i++) {
        printf("%c|", cmd[i]);
    }
    printf("\n");
*/

    write(fd, cmd, sizeof(cmd));
}

/*
* send init command to reciver
*/
void init_cmd() {
    char b[5];
    b[0]=DC1;
    b[1]=0;
    b[2]=0;
    b[3]=1;
    b[4]=ETX;

    int n = write(fd, b, sizeof(b));
}

/*
* open serial port
*/
int open_port(void)
{
    int fd; /* File descriptor for the port */
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        /*
        * Could not open the port.
        */
        perror("open_port: Unable to open /dev/ttyUSB0 --- \n");
    } else {
        fcntl(fd, F_SETFL, 0);
    }

    return (fd);
}

/*
* decode command
*/
void cmd(char **argv) {
    char *cmd1 = argv[1];
    char *cmd2 = argv[2];

    if(strcmp(cmd1, "power") == 0) {
        if(strcmp(cmd2, "on") == 0) {
            send_cmd("07E7E");
        } else if(strcmp(cmd2, "off") == 0) {
            send_cmd("07E7F");
        }
    } else if(strcmp(cmd1, "input") == 0) {http://www.panticz.de/sites/default/files/lyc/lyc
        if(strcmp(cmd2, "cd") == 0) {
            send_cmd("07A15");
        } else if(strcmp(cmd2, "dvd") == 0) {
            send_cmd("07AC1");
        }  else if(strcmp(cmd2, "bd") == 0) {
            send_cmd("07AC8");
        } else if(strcmp(cmd2, "pc") == 0) {
            send_cmd("0F7F013FC0"); // set input to NET/USB
            send_cmd("0F7F0136C9");
        } else if(strcmp(cmd2, "net") == 0) {
            send_cmd("0F7F013FC0"); // set input to NET/USB
            send_cmd("0F7F013FC8");
        } else if(strcmp(cmd2, "usb") == 0) {
            send_cmd("0F7F013FC0"); // set input to NET/USB
            send_cmd("0F7F0138C7");
        }
    } else if(strcmp(cmd1, "volume") == 0) {
        // todo calculate volume
        //int i = (int) strtol(cmd2, (char **)NULL, 10);
        //printf("%d", i);
        // "System Zone1Volume Set -50"07A15 dvd
        if(strcmp(cmd2, "-45") == 0) {
            send_cmd("2306D");
        } else if(strcmp(cmd2, "-50") == 0) {
            send_cmd("23063");
        } else if(strcmp(cmd2, "-55") == 0) {
            send_cmd("23059");
        } else if(strcmp(cmd2, "up") == 0) {
            send_cmd("07A1A");
        } else if(strcmp(cmd2, "down") == 0) {
            send_cmd("07A1B");
        }
    } else if(strcmp(cmd1, "mute") == 0) {
        if(strcmp(cmd2, "on") == 0) {
            send_cmd("07EA2");
        } else if(strcmp(cmd2, "off") == 0) {
            send_cmd("07EA3");
        }
    } else if(strcmp(cmd1, "sleep") == 0) {
        if(strcmp(cmd2, "off") == 0) {
            send_cmd("07EB3");
        } else if(strcmp(cmd2, "120") == 0) {
            send_cmd("07EB4");
        } else if(strcmp(cmd2, "90") == 0) {
            send_cmd("07EB5");
        } else if(strcmp(cmd2, "60") == 0) {
            send_cmd("07EB6");
        } else if(strcmp(cmd2, "30") == 0) {
            send_cmd("07EB7");
        }
    } else if(strcmp(cmd1, "dsp") == 0) {
        if(strcmp(cmd2, "7ch") == 0) {
            send_cmd("07EFF");
        } else if(strcmp(cmd2, "2ch") == 0) {
            send_cmd("07EC0");
        } else if(strcmp(cmd2, "normal") == 0) {
            send_cmd("07EFD");
        } else if(strcmp(cmd2, "straight") == 0) {
            send_cmd("07EE0");
        } else if(strcmp(cmd2, "general") == 0) {
            send_cmd("07EFC");
        }
    } else if(strcmp(cmd1, "memory") == 0) {
        if(strcmp(cmd2, "1") == 0) {
            send_cmd("07E35");
        } else if(strcmp(cmd2, "2") == 0) {
            send_cmd("07E36");
        } else if(strcmp(cmd2, "3") == 0) {
            send_cmd("07E37");
        } else if(strcmp(cmd2, "4") == 0) {
            send_cmd("07E38");
        } else if(strcmp(cmd2, "5") == 0) {
            send_cmd("07E39");
        } else if(strcmp(cmd2, "6") == 0) {
            send_cmd("07E3A");
        }
    } else if(strcmp(cmd1, "enhancer") == 0) {
        if(strcmp(cmd2, "on") == 0) {
            send_cmd("07ED8");
        } if(strcmp(cmd2, "off") == 0) {
            send_cmd("07ED9");
        }
    } else if(strcmp(cmd1, "stop") == 0) {
        send_cmd("0F7F013DC2");
    } else if(strcmp(cmd1, "play") == 0) {
        send_cmd("0F7F013EC1");
    } else if(strcmp(cmd1, "next") == 0) {
        send_cmd("0F7F013CC3");
    } else if(strcmp(cmd1, "prev") == 0) {
        send_cmd("0F7F013BC4");
    } else if(strcmp(cmd1, "display") == 0) {
        send_cmd("0F7F0135CA");
    } else {
        printf("Command not found");
    }
}

/*
* main
*/
int main(int argc, char **argv) {
    fd = open_port();

    if(fd == -1) {
        printf("Error opening serial port\n");
    } else {
        if(init_port() == -1) {  
            sleep(.5);
            printf("Error initializing serial port\n");

            close(fd);
            return 0;
        }

        sleep(.5);
        init_cmd();

/*
        // todo: recive response from reciver
        if (n < 0) {
            fputs("write() of X bytes failed!\n", stderr);
        } else {
            printf("Successfully wrote 8 bytes\n");

            sleep(.5);
            char buffer[200];
            int n = read(fd, buffer, sizeof(buffer));
            sleep(.5);
            if (n < 0) {
                fputs("read failed!\n", stderr);
            } else {
                printf("Successfully read from serial port -- %s\n", buffer);
            }
        }
*/

        sleep(.5);
        cmd(argv);

        sleep(.5);
        close(fd);
    }

    return 0;
}


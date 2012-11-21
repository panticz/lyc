#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include "rxvx700.h" /* Yamaha RX-Vx700 protocol codes */

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
void send_cmd(const char *n) {
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
int run_cmd(char *cmd1, char *cmd2) {
    int l = 0;

    // check parameter
    if(cmd1 != NULL) {
        l += strlen(cmd1);
    }

    if(cmd2 != NULL) {
        l += strlen(cmd2);
    }

    // put parameter together
    char c[l + 2];
    strcpy(c, cmd1);
    if(cmd2 != NULL) {
        strcat(c, " ");
        strcat(c, cmd2);
    }

    int i;
    int size = (int)(sizeof(cmd) / sizeof(*cmd));
    for(i = 0; i < size; i++) {
        // search command
        if(strcmp(c, cmd[i][0]) == 0) {
            // todo calculate volume
            // int i = (int)strtol(cmd[i][1], (char **)NULL, 10);

            char code[strlen(cmd[i][1]) + 1];
            strcpy(code, cmd[i][1]);

            char *pch;
            pch = strtok(code, " ");
            while (pch != NULL) {
                send_cmd(pch);

                pch = strtok(NULL, " ");
            }

            return 0;
        }
    }

    return 1;
}

/*
* main
*/
int main(int argc, char **argv) {
    if(argc == 1) {
        return 1;
    }
        
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
        if(run_cmd(argv[1], argv[2]) == 1) {
            printf("Command not found\n");
        }

        sleep(.5);
        close(fd);
    }

    return 0;
}


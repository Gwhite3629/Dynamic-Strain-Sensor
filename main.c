//  Start of program
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

#include "file.h"
#include "serial.h"
#include "measurements.h"
#include "setup.h"

int main(void)
{
    uint ret = 0;
    HANDLE fd;
    char *dev = NULL;
    float *data = NULL;

    MEM(data, 2500, float);

    MEM(dev, 64, char);

    printf("Enter device name: ");
    scanf("%s", dev);

    CHECK((fd = open_port(dev)));
    printf("Opened\n");
    CHECK((ret = GPIB_conf(fd, 0)));
    printf("GPIB configured\n");
    CHECK((ret = init(fd)));
    printf("Setup complete\n");
    CHECK((ret = get_curve(fd, &data)));
    printf("Completed\n");

exit:
    if (dev)
        free(dev);
    if (fd)
        fclose(fd);
    if (data)
        free(data);

    return ret;
}
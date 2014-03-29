#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <scsi/sg.h>
#include <stdio.h>
#include <string.h>


void superdriveEnabler(const char *device)
{
    int fd;
    sg_io_hdr_t IO_hdr;
    unsigned char magic[] = {0xea,0x00,0x00,0x00,0x00,0x00,0x01};
    unsigned char sbuf[32];
    unsigned char dxfp[32];

    fd = open(device, O_RDWR|O_NONBLOCK);
    if (fd < 0) {
        fprintf(stderr, "Error opening MBA SuperDrive \"%s\".\n", device);
        return;
    }
    else {
        memset(&IO_hdr, 0, sizeof(sg_io_hdr_t));
        IO_hdr.interface_id = 'S';
        IO_hdr.cmd_len = sizeof(magic);
        IO_hdr.mx_sb_len = sizeof(sbuf);
        IO_hdr.dxfer_direction = SG_DXFER_TO_DEV;
        IO_hdr.dxfer_len = sizeof(dxfp);
        IO_hdr.dxferp = dxfp;
        IO_hdr.cmdp = magic;
        IO_hdr.sbp = sbuf;
        IO_hdr.timeout = 1000;
        if (ioctl(fd, SG_IO, &IO_hdr) < 0) {
            fprintf(stderr, "Error initialising MBA SuperDrive.\n");
            return;
        }
        close(fd);
    }
}


int main(int argc, const char* argv[])
{
    superdriveEnabler(argv[1]);
    return 0;
}

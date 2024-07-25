#ifndef _REMOTE_LOG_H_
#define _REMOTE_LOG_H_

#import <Foundation/Foundation.h>
#import <netinet/in.h>
#import <sys/socket.h>
#import <unistd.h>
#import <arpa/inet.h>

#define RLOG_IP_ADDRESS "255.255.255.255" 
#define RLOG_PORT 5000  

#define RLo

__attribute__((unused)) static void RLogv(NSString* format, va_list args)
{
    #if DEBUG
        NSString* str = [[NSString alloc] initWithFormat:format arguments:args];

        int sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sd <= 0)
        {
            NSLog(@"[RemoteLog] Error: Could not open socket");
            return;
        }

        int broadcastEnable = 1;
        int ret = setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
        if (ret)
        {
            NSLog(@"[RemoteLog] Error: Could not set socket to broadcast mode");
            close(sd);
            return;
        }

        struct sockaddr_in broadcastAddr;
        memset(&broadcastAddr, 0, sizeof broadcastAddr);
        broadcastAddr.sin_family = AF_INET;
        ret = inet_pton(AF_INET, RLOG_IP_ADDRESS, &broadcastAddr.sin_addr);
        if (ret <= 0)
        {
            NSLog(@"[RemoteLog] Error: Invalid broadcast IP address");
            close(sd);
            return;
        }
        broadcastAddr.sin_port = htons(RLOG_PORT);

        const char* request = [str UTF8String];
        ret = sendto(sd, request, strlen(request), 0, (struct sockaddr*)&broadcastAddr, sizeof broadcastAddr);
        if (ret < 0)
        {
            NSLog(@"[RemoteLog] Error: Could not send broadcast");
        }
        close(sd);
    #endif
}

__attribute__((unused)) static void RLog(NSString* format, ...)
{
    #if DEBUG
        va_list args;
        va_start(args, format);
        RLogv(format, args);
        va_end(args);
    #endif
}

#endif  // _REMOTE_LOG_H_

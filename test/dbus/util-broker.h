#pragma once

/*
 * Test Infrastructure around dbus-broker
 */

#include <c-macro.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <systemd/sd-bus.h>
#include <systemd/sd-event.h>

typedef struct Broker Broker;

struct Broker {
        pthread_t thread;
        struct sockaddr_un address;
        socklen_t n_address;
        int listener_fd;
};

#define BROKER_NULL {                                                           \
                .address.sun_family = AF_UNIX,                                  \
                .n_address = sizeof(struct sockaddr_un),                        \
                .listener_fd = -1,                                              \
        }

/* misc */

void util_event_new(sd_event **eventp);
void util_fork_broker(sd_bus **busp, sd_event *event, int listener_fd);

/* broker */

void util_broker_new(Broker **brokerp);
Broker *util_broker_free(Broker *broker);
void util_broker_spawn(Broker *broker);
void util_broker_terminate(Broker *broker);

void util_broker_connect(Broker *broker, sd_bus **busp);

C_DEFINE_CLEANUP(Broker *, util_broker_free);

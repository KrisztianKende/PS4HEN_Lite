#pragma once

#ifndef SYSUTIL_H
#define SYSUTIL_H

// HUGE shoutout to OSM-Made for removing the need to use the football/soccer icon in the notifications
// https://github.com/OSM-Made/PS4-Notify
#define printf_notification(...)                                                                         \
  do {                                                                                                   \
    SceNotificationRequest noti_buffer = {};                                                             \
    static const char icon_uri[] = "cxml://psnotification/tex_icon_system";                              \
    noti_buffer.use_icon_image_uri = 1;                                                                  \
    noti_buffer.target_id = -1;                                                                          \
    memcpy(noti_buffer.uri, icon_uri, sizeof(icon_uri));                                                 \
    const int len = snprintf_s(noti_buffer.message, sizeof(noti_buffer.message), ##__VA_ARGS__);         \
    const int len2 = len - 1;                                                                            \
    if (len > 0 && noti_buffer.message[len2] == '\n') {                                                  \
      noti_buffer.message[len2] = 0;                                                                     \
    }                                                                                                    \
    sceKernelSendNotificationRequest(0, (SceNotificationRequest *)&noti_buffer, sizeof(noti_buffer), 0); \
  } while (0)

#endif

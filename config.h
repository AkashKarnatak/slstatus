/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * separator           string to echo                  NULL
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer control ("Master")
 *                                                     NULL on OpenBSD
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */

const char *
battery(const char * bat) {
  int perc = battery_perc(bat);
  const char * status = battery_state(bat);
  if (status == NULL)
    return NULL;
  if (*status == '+' || *status =='o') {
    return bprintf(" ^c#88c0d0^  ^c#abb2bf^%d%% ^c#666666^|", perc);
  } else if (perc > 90) {
    return bprintf(" ^c#a3be8c^  ^c#abb2bf^%d%% ^c#666666^|", perc);
  } else if (perc > 70) {
    return bprintf(" ^c#a3be8c^  ^c#abb2bf^%d%% ^c#666666^|", perc);
  } else if (perc > 40) {
    return bprintf(" ^c#f4ac6c^  ^c#abb2bf^%d%% ^c#666666^|", perc);
  } else if (perc > 20) {
    return bprintf(" ^c#bf616a^  ^c#abb2bf^%d%% ^c#666666^|", perc);
  } else if (perc >= 0) {
    return bprintf(" ^c#bf616a^  ^c#abb2bf^%d%% ^c#666666^|", perc);
  }
  return NULL;
}

// alt string is used when function returns NULL
static const struct arg args[] = {
// function               format                                                         alt string                                                                argument
  {wifi_essid,            "^c#666666^| ^c#a3be8c^󰤨 ^c#abb2bf^%s ^c#666666^|",            "^c#666666^| ^c#bf616a^󰤭 ^c#abb2bf^Disconnected ^c#666666^|",             "wlan0"},
  {vol_perc,              " ^c#d7ba7d^  ^c#abb2bf^%s%% ^c#666666^|",                    " ^c#d7ba7d^  ^c#abb2bf^Mute ^c#666666^|",                               "Master"},
  {battery,               "%s",                                                          "",                                                                       "BAT1"},
  {cpu_perc,              " ^c#5e81ac^  ^c#abb2bf^%s%% ^c#666666^|",                    "",                                                                       NULL},
  // {ram_perc,              " ^c#b48ead^  ^c#abb2bf^%s%% ^c#666666^|",                    "",                                                                       NULL},
  {ram_used,              " ^c#b48ead^  ^c#abb2bf^%sB / ",                              "",                                                                       NULL},
  {ram_total,             "^c#abb2bf^%sB ^c#666666^|",                                   "",                                                                       NULL},
  {datetime,              " ^c#88c0d0^  ^c#abb2bf^%s ",                                 "",                                                                       "%b %d - %I:%M%p"},
};

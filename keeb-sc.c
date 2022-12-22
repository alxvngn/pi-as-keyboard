#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_LEN 512

struct options {
	const char    *opt;
	unsigned char val;
};

static struct options kmod[] = {
    {.opt = "KEY_LEFTCTRL", .val = 0x01},
	{.opt = "KEY_LEFTSHIFT",	.val = 0x02},
	{.opt = "KEY_LEFTALT",	.val = 0x04},
	{.opt = "KEY_LEFTMETA",	.val = 0x08},
	{.opt = "KEY_RIGHTCTRL",	.val = 0x10},
	{.opt = "KEY_RIGHTSHIFT",	.val = 0x20},
	{.opt = "KEY_RIGHTALT",	.val = 0x40},
	{.opt = "KEY_RIGHTMETA",	.val = 0x80},
    {.opt = NULL}
};

static struct options kval[] = {
	{.opt = "KEY_A",	.val = 0x04},
	{.opt = "KEY_B",	.val = 0x05},
	{.opt = "KEY_C",	.val = 0x06},
	{.opt = "KEY_D",	.val = 0x07},
	{.opt = "KEY_E",	.val = 0x08},
	{.opt = "KEY_F",	.val = 0x09},
	{.opt = "KEY_G",	.val = 0x0a},
	{.opt = "KEY_H",	.val = 0x0b},
	{.opt = "KEY_I",	.val = 0x0c},
	{.opt = "KEY_J",	.val = 0x0d},
	{.opt = "KEY_K",	.val = 0x0e},
	{.opt = "KEY_L",	.val = 0x0f},
	{.opt = "KEY_M",	.val = 0x10},
	{.opt = "KEY_N",	.val = 0x11},
	{.opt = "KEY_O",	.val = 0x12},
	{.opt = "KEY_P",	.val = 0x13},
	{.opt = "KEY_Q",	.val = 0x14},
	{.opt = "KEY_R",	.val = 0x15},
	{.opt = "KEY_S",	.val = 0x16},
	{.opt = "KEY_T",	.val = 0x17},
	{.opt = "KEY_U",	.val = 0x18},
	{.opt = "KEY_V",	.val = 0x19},
	{.opt = "KEY_W",	.val = 0x1a},
	{.opt = "KEY_X",	.val = 0x1b},
	{.opt = "KEY_Y",	.val = 0x1c},
	{.opt = "KEY_Z",	.val = 0x1d},
	{.opt = "KEY_1",	.val = 0x1e},
	{.opt = "KEY_2",	.val = 0x1f},
	{.opt = "KEY_3",	.val = 0x20},
	{.opt = "KEY_4",	.val = 0x21},
	{.opt = "KEY_5",	.val = 0x22},
	{.opt = "KEY_6",	.val = 0x23},
	{.opt = "KEY_7",	.val = 0x24},
	{.opt = "KEY_8",	.val = 0x25},
	{.opt = "KEY_9",	.val = 0x26},
	{.opt = "KEY_0",	.val = 0x27},
	{.opt = "KEY_ENTER",	.val = 0x28},
	{.opt = "KEY_ESC",	.val = 0x29},
	{.opt = "KEY_BACKSPACE",	.val = 0x2a},
	{.opt = "KEY_TAB",	.val = 0x2b},
	{.opt = "KEY_SPACE",	.val = 0x2c},
	{.opt = "KEY_MINUS",	.val = 0x2d},
	{.opt = "KEY_EQUAL",	.val = 0x2e},
	{.opt = "KEY_LEFTBRACE",	.val = 0x2f},
	{.opt = "KEY_RIGHTBRACE",	.val = 0x30},
	{.opt = "KEY_BACKSLASH",	.val = 0x31},
	{.opt = "KEY_HASHTILDE",	.val = 0x32},
	{.opt = "KEY_SEMICOLON",	.val = 0x33},
	{.opt = "KEY_APOSTROPHE",	.val = 0x34},
	{.opt = "KEY_GRAVE",	.val = 0x35},
	{.opt = "KEY_COMMA",	.val = 0x36},
	{.opt = "KEY_DOT",	.val = 0x37},
	{.opt = "KEY_SLASH",	.val = 0x38},
	{.opt = "KEY_CAPSLOCK",	.val = 0x39},
	{.opt = "KEY_F1",	.val = 0x3a},
	{.opt = "KEY_F2",	.val = 0x3b},
	{.opt = "KEY_F3",	.val = 0x3c},
	{.opt = "KEY_F4",	.val = 0x3d},
	{.opt = "KEY_F5",	.val = 0x3e},
	{.opt = "KEY_F6",	.val = 0x3f},
	{.opt = "KEY_F7",	.val = 0x40},
	{.opt = "KEY_F8",	.val = 0x41},
	{.opt = "KEY_F9",	.val = 0x42},
	{.opt = "KEY_F10",	.val = 0x43},
	{.opt = "KEY_F11",	.val = 0x44},
	{.opt = "KEY_F12",	.val = 0x45},
	{.opt = "KEY_SYSRQ",	.val = 0x46},
	{.opt = "KEY_SCROLLLOCK",	.val = 0x47},
	{.opt = "KEY_PAUSE",	.val = 0x48},
	{.opt = "KEY_INSERT",	.val = 0x49},
	{.opt = "KEY_HOME",	.val = 0x4a},
	{.opt = "KEY_PAGEUP",	.val = 0x4b},
	{.opt = "KEY_DELETE",	.val = 0x4c},
	{.opt = "KEY_END",	.val = 0x4d},
	{.opt = "KEY_PAGEDOWN",	.val = 0x4e},
	{.opt = "KEY_RIGHT",	.val = 0x4f},
	{.opt = "KEY_LEFT",	.val = 0x50},
	{.opt = "KEY_DOWN",	.val = 0x51},
	{.opt = "KEY_UP",	.val = 0x52},
	{.opt = "KEY_NUMLOCK",	.val = 0x53},
	{.opt = "KEY_KPSLASH",	.val = 0x54},
	{.opt = "KEY_KPASTERISK",	.val = 0x55},
	{.opt = "KEY_KPMINUS",	.val = 0x56},
	{.opt = "KEY_KPPLUS",	.val = 0x57},
	{.opt = "KEY_KPENTER",	.val = 0x58},
	{.opt = "KEY_KP1",	.val = 0x59},
	{.opt = "KEY_KP2",	.val = 0x5a},
	{.opt = "KEY_KP3",	.val = 0x5b},
	{.opt = "KEY_KP4",	.val = 0x5c},
	{.opt = "KEY_KP5",	.val = 0x5d},
	{.opt = "KEY_KP6",	.val = 0x5e},
	{.opt = "KEY_KP7",	.val = 0x5f},
	{.opt = "KEY_KP8",	.val = 0x60},
	{.opt = "KEY_KP9",	.val = 0x61},
	{.opt = "KEY_KP0",	.val = 0x62},
	{.opt = "KEY_KPDOT",	.val = 0x63},
	{.opt = "KEY_102ND",	.val = 0x64},
	{.opt = "KEY_COMPOSE",	.val = 0x65},
	{.opt = "KEY_POWER",	.val = 0x66},
	{.opt = "KEY_KPEQUAL",	.val = 0x67},
	{.opt = "KEY_F13",	.val = 0x68},
	{.opt = "KEY_F14",	.val = 0x69},
	{.opt = "KEY_F15",	.val = 0x6a},
	{.opt = "KEY_F16",	.val = 0x6b},
	{.opt = "KEY_F17",	.val = 0x6c},
	{.opt = "KEY_F18",	.val = 0x6d},
	{.opt = "KEY_F19",	.val = 0x6e},
	{.opt = "KEY_F20",	.val = 0x6f},
	{.opt = "KEY_F21",	.val = 0x70},
	{.opt = "KEY_F22",	.val = 0x71},
	{.opt = "KEY_F23",	.val = 0x72},
	{.opt = "KEY_F24",	.val = 0x73},
	{.opt = "KEY_OPEN",	.val = 0x74},
	{.opt = "KEY_HELP",	.val = 0x75},
	{.opt = "KEY_PROPS",	.val = 0x76},
	{.opt = "KEY_FRONT",	.val = 0x77},
	{.opt = "KEY_STOP",	.val = 0x78},
	{.opt = "KEY_AGAIN",	.val = 0x79},
	{.opt = "KEY_UNDO",	.val = 0x7a},
	{.opt = "KEY_CUT",	.val = 0x7b},
	{.opt = "KEY_COPY",	.val = 0x7c},
	{.opt = "KEY_PASTE",	.val = 0x7d},
	{.opt = "KEY_FIND",	.val = 0x7e},
	{.opt = "KEY_MUTE",	.val = 0x7f},
	{.opt = "KEY_VOLUMEUP",	.val = 0x80},
	{.opt = "KEY_VOLUMEDOWN",	.val = 0x81},
	{.opt = "KEY_KPCOMMA",	.val = 0x85},
	{.opt = "KEY_RO",	.val = 0x87},
	{.opt = "KEY_KATAKANAHIRAGANA",	.val = 0x88},
	{.opt = "KEY_YEN",	.val = 0x89},
	{.opt = "KEY_HENKAN",	.val = 0x8a},
	{.opt = "KEY_MUHENKAN",	.val = 0x8b},
	{.opt = "KEY_KPJPCOMMA",	.val = 0x8c},
	{.opt = "KEY_HANGEUL",	.val = 0x90},
	{.opt = "KEY_HANJA",	.val = 0x91},
	{.opt = "KEY_KATAKANA",	.val = 0x92},
	{.opt = "KEY_HIRAGANA",	.val = 0x93},
	{.opt = "KEY_ZENKAKUHANKAKU",	.val = 0x94},
	{.opt = "KEY_KPLEFTPAREN",	.val = 0xb6},
	{.opt = "KEY_KPRIGHTPAREN",	.val = 0xb7},
	{.opt = "KEY_MEDIA_PLAYPAUSE",	.val = 0xe8},
	{.opt = "KEY_MEDIA_STOPCD",	.val = 0xe9},
	{.opt = "KEY_MEDIA_PREVIOUSSONG",	.val = 0xea},
	{.opt = "KEY_MEDIA_NEXTSONG",	.val = 0xeb},
	{.opt = "KEY_MEDIA_EJECTCD",	.val = 0xec},
	{.opt = "KEY_MEDIA_VOLUMEUP",	.val = 0xed},
	{.opt = "KEY_MEDIA_VOLUMEDOWN",	.val = 0xee},
	{.opt = "KEY_MEDIA_MUTE",	.val = 0xef},
	{.opt = "KEY_MEDIA_WWW",	.val = 0xf0},
	{.opt = "KEY_MEDIA_BACK",	.val = 0xf1},
	{.opt = "KEY_MEDIA_FORWARD",	.val = 0xf2},
	{.opt = "KEY_MEDIA_STOP",	.val = 0xf3},
	{.opt = "KEY_MEDIA_FIND",	.val = 0xf4},
	{.opt = "KEY_MEDIA_SCROLLUP",	.val = 0xf5},
	{.opt = "KEY_MEDIA_SCROLLDOWN",	.val = 0xf6},
	{.opt = "KEY_MEDIA_EDIT",	.val = 0xf7},
	{.opt = "KEY_MEDIA_SLEEP",	.val = 0xf8},
	{.opt = "KEY_MEDIA_COFFEE",	.val = 0xf9},
	{.opt = "KEY_MEDIA_REFRESH",	.val = 0xfa},
	{.opt = "KEY_MEDIA_CALC",	.val = 0xfb}
};

int keyboard_fill_report(char report[8], char buf[BUF_LEN], int *hold)
{
	char *tok = strtok(buf, " ");
	int key = 0;
	int i = 0;

	for (; tok != NULL; tok = strtok(NULL, " ")) {

		if (strncmp(tok, "--", 2) == 0)
			tok += 2;

		if (strcmp(tok, "quit") == 0)
			return -1;

		if (strcmp(tok, "hold") == 0) {
			*hold = 1;
			continue;
		}

		if (key < 6) {
			for (i = 0; kval[i].opt != NULL; i++)
				if (strcmp(tok, kval[i].opt) == 0) {
					report[2 + key++] = kval[i].val;
					break;
				}
			if (kval[i].opt != NULL)
				continue;
		}

		for (i = 0; kmod[i].opt != NULL; i++)
			if (strcmp(tok, kmod[i].opt) == 0) {
				report[0] = report[0] | kmod[i].val;
				break;
			}
		if (kmod[i].opt != NULL)
			continue;

		if (key < 6)
			fprintf(stderr, "unknown option: %s\n", tok);
	}
	return 8;
}

static struct options mmod[] = {
	{.opt = "--b1", .val = 0x01},
	{.opt = "--b2", .val = 0x02},
	{.opt = "--b3", .val = 0x04},
	{.opt = NULL}
};

int mouse_fill_report(char report[8], char buf[BUF_LEN], int *hold)
{
	char *tok = strtok(buf, " ");
	int mvt = 0;
	int i = 0;
	for (; tok != NULL; tok = strtok(NULL, " ")) {

		if (strcmp(tok, "--quit") == 0)
			return -1;

		if (strcmp(tok, "--hold") == 0) {
			*hold = 1;
			continue;
		}

		for (i = 0; mmod[i].opt != NULL; i++)
			if (strcmp(tok, mmod[i].opt) == 0) {
				report[0] = report[0] | mmod[i].val;
				break;
			}
		if (mmod[i].opt != NULL)
			continue;

		if (!(tok[0] == '-' && tok[1] == '-') && mvt < 2) {
			errno = 0;
			report[1 + mvt++] = (char)strtol(tok, NULL, 0);
			if (errno != 0) {
				fprintf(stderr, "Bad value:'%s'\n", tok);
				report[1 + mvt--] = 0;
			}
			continue;
		}

		fprintf(stderr, "unknown option: %s\n", tok);
	}
	return 3;
}

static struct options jmod[] = {
	{.opt = "--b1",		.val = 0x10},
	{.opt = "--b2",		.val = 0x20},
	{.opt = "--b3",		.val = 0x40},
	{.opt = "--b4",		.val = 0x80},
	{.opt = "--hat1",	.val = 0x00},
	{.opt = "--hat2",	.val = 0x01},
	{.opt = "--hat3",	.val = 0x02},
	{.opt = "--hat4",	.val = 0x03},
	{.opt = "--hatneutral",	.val = 0x04},
	{.opt = NULL}
};

int joystick_fill_report(char report[8], char buf[BUF_LEN], int *hold)
{
	char *tok = strtok(buf, " ");
	int mvt = 0;
	int i = 0;

	*hold = 1;

	/* set default hat position: neutral */
	report[3] = 0x04;

	for (; tok != NULL; tok = strtok(NULL, " ")) {

		if (strcmp(tok, "--quit") == 0)
			return -1;

		for (i = 0; jmod[i].opt != NULL; i++)
			if (strcmp(tok, jmod[i].opt) == 0) {
				report[3] = (report[3] & 0xF0) | jmod[i].val;
				break;
			}
		if (jmod[i].opt != NULL)
			continue;

		if (!(tok[0] == '-' && tok[1] == '-') && mvt < 3) {
			errno = 0;
			report[mvt++] = (char)strtol(tok, NULL, 0);
			if (errno != 0) {
				fprintf(stderr, "Bad value:'%s'\n", tok);
				report[mvt--] = 0;
			}
			continue;
		}

		fprintf(stderr, "unknown option: %s\n", tok);
	}
	return 4;
}

void print_options(char c)
{
	int i = 0;

	if (c == 'k') {
		printf("	keyboard options:\n"
		       "		hold\n");
		for (i = 0; kmod[i].opt != NULL; i++)
			printf("\t\t%s\n", kmod[i].opt);
		printf("\n	keyboard values:\n"
		       "		[a-z] or [0-9] or\n");
		for (i = 0; kval[i].opt != NULL; i++)
			printf("\t\t%-8s%s", kval[i].opt, i % 2 ? "\n" : "");
		printf("\n");
	} else if (c == 'm') {
		printf("	mouse options:\n"
		       "		--hold\n");
		for (i = 0; mmod[i].opt != NULL; i++)
			printf("\t\t%s\n", mmod[i].opt);
		printf("\n	mouse values:\n"
		       "		Two signed numbers\n\n");
	} else {
		printf("	joystick options:\n");
		for (i = 0; jmod[i].opt != NULL; i++)
			printf("\t\t%s\n", jmod[i].opt);
		printf("\n	joystick values:\n"
		       "		three signed numbers\n"
		       "--quit to close\n");
	}
}

int main(int argc, const char *argv[])
{
	const char *filename = NULL;
	int fd = 0;
	char buf[BUF_LEN];
	int cmd_len;
	char report[8];
	int to_send = 8;
	int hold = 0;
	fd_set rfds;
	int retval, i;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s devname mouse|keyboard|joystick\n",
			argv[0]);

		print_options('k');
		print_options('m');
		print_options('j');

		return 1;
	}

	if (argv[2][0] != 'k' && argv[2][0] != 'm' && argv[2][0] != 'j')
	  return 2;

	filename = argv[1];

	if ((fd = open(filename, O_RDWR, 0666)) == -1) {
		perror(filename);
		return 3;
	}

	while (42) {

		FD_ZERO(&rfds);
		FD_SET(STDIN_FILENO, &rfds);
		FD_SET(fd, &rfds);

		retval = select(fd + 1, &rfds, NULL, NULL, NULL);
		if (retval == -1 && errno == EINTR)
			continue;
		if (retval < 0) {
			perror("select()");
			return 4;
		}

		if (FD_ISSET(fd, &rfds)) {
			cmd_len = read(fd, buf, BUF_LEN - 1);
			printf("recv report:");
			for (i = 0; i < cmd_len; i++)
				printf(" %02x", buf[i]);
			printf("\n");
		}

		if (FD_ISSET(STDIN_FILENO, &rfds)) {
			memset(report, 0x0, sizeof(report));
			cmd_len = read(STDIN_FILENO, buf, BUF_LEN - 1);

			if (cmd_len == 0)
				break;

			buf[cmd_len - 1] = '\0';
			hold = 0;

			memset(report, 0x0, sizeof(report));
			if (argv[2][0] == 'k')
				to_send = keyboard_fill_report(report, buf, &hold);
			else if (argv[2][0] == 'm')
				to_send = mouse_fill_report(report, buf, &hold);
			else
				to_send = joystick_fill_report(report, buf, &hold);

			if (to_send == -1)
				break;

			if (write(fd, report, to_send) != to_send) {
				perror(filename);
				return 5;
			}
			if (!hold) {
				memset(report, 0x0, sizeof(report));
				if (write(fd, report, to_send) != to_send) {
					perror(filename);
					return 6;
				}
			}
		}
	}

	close(fd);
	return 0;
}
